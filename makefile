################################################################################
# These lines are system-specific
################################################################################

include_dirs := /usr/local/lib/systemc-2.3.1/include

librarypaths := /usr/local/lib/systemc-2.3.1/lib-linux64
libraries := systemc

################################################################################

LINK_LIBS     = $(addprefix -l,$(libraries))
LINK_LIBPATHS = $(addprefix -L,$(librarypaths))

CC       := g++
CPPFLAGS := -Wall -g3 -O0 -std=c++11 $(addprefix -I,$(include_dirs)) $(LINK_LIBPATHS) $(LINK_LIBS)

SOURCES      := $(wildcard src/*.cpp)
OBJECTS      := $(subst .cpp,.o,$(SOURCES))
DEPENDENCIES := $(subst .cpp,.d,$(SOURCES))

TESTSOURCES      := test/main.cpp test/source.cpp test/sink.cpp
TESTOBJECTS      := $(subst .cpp,.o,$(TESTSOURCES))
TESTDEPENDENCIES := $(subst .cpp,.d,$(TESTSOURCES))

.PHONY: all
all: libsc_map.a

libsc_map.a: $(DEPENDENCIES) $(OBJECTS)
	ar rvs libsc_map.a $(OBJECTS)

.PHONY: test
test: sc_map_test

sc_map_test: libsc_map.a $(TESTDEPENDENCIES) $(TESTOBJECTS)
	$(CC) -o $@ $(TESTOBJECTS) $(CPPFLAGS) $(TARGET_ARCH) -L. -lsc_map

%.d: %.cpp
	$(CC) $(CPPFLAGS) $(TARGET_ARCH) $< -MM -MF $(subst .cpp,.d,$<)

%.o : %.cpp
	$(CC) $(CPPFLAGS) -MD -c $< -o $(patsubst %.cpp, %.o, $<)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDENCIES) $(TESTDEPENDENCIES) $(TESTOBJECTS)
	rm -f libsc_map.a sc_map_test wave.vcd

ifneq "$(MAKECMDGOALS)" "clean"
	include $(DEPENDENCIES)
	@echo "included dependencies"
endif
