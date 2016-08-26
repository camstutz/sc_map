/*!
 * @file sc_map_iterator.hpp
 * @author Christian Amstutz
 * @date July 15, 2015
 *
 * @brief
 *
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_range.hpp"

#include <systemc.h>

#include <iterator>
#include <utility>


template <typename range_T, typename object_T>
class sc_map_base;

//******************************************************************************

/*!
 * @brief Iterator for the sc_map containers.
 *
 * The direction in which the iterator goes over the elements of a container is
 * defined by the range.
 *
 * @tparam sc_map_T container type to iterate over.
 */
template <typename sc_map_T>
class sc_map_iterator : public std::iterator<std::forward_iterator_tag, typename sc_map_T::object_type>
{
public:
    /*!
    * @brief Type of the sc_map container.
    *
    * Alias for the template parameter sc_map_T.
    */
    typedef sc_map_T map_type;

    /*!
    * @brief Type of the SystemC objects within the container.
    */
    typedef typename map_type::object_type object_type;

    /*!
    * @brief Type of the key used to access elements within the container.
    */
    typedef typename map_type::key_type key_type;

    /*!
    * @brief Type of the flag signalling that the end of the container has been
    *        reached.
    */
    typedef bool end_type;

    /*!
    * @brief Pre-defined constant that shows that the end of the container has
    *        been reached. The value is set to true.
    */
    static const end_type end;

    /*!
    * @brief Constructor: Creates an iterator that covers the whole range of a
    *        provided sc_map container.
    *
    * Clones the range of the provided container and sets the pointer to the
    * first element.
    *
    * @param sc_map Pointer to the sc_map container on which the iterator works.
    */
    sc_map_iterator(sc_map_T* sc_map);

    /*!
    * @brief Constructor: Creates iterator that runs over the whole range of a
    *        provided container. Sets end_flag to specific value.
    *
    * Clones the range of the provided container and sets the pointer to the
    * first element.
    *
    * @param sc_map Pointer to the sc_map container on which the iterator works.
    * @param end_id Value of the end_flag
    */
    sc_map_iterator(sc_map_T* sc_map, const end_type end_id);

    /*!
    * @brief Constructor: Creates iterator that runs over the whole range of a
    *        provided container. Sets the initial element to which the iterator
    *        points.
    *
    * Clones the range of the provided container.
    *
    * @param sc_map Pointer to the sc_map container on which the iterator works.
    * @param map_pos Position within the container to which the iterator should
    *        point initially.
    */
    sc_map_iterator(sc_map_T* sc_map, const key_type& map_pos);

    /*!
    * @brief Constructor: Creates iterator that runs over a specfified range of
    *        a provided container.
    *
    * Copies the range into the local range and sets the iterator to the start
    * of the range. And starts from the first element of this range.
    *
    * @param sc_map Pointer to the sc_map container on which the iterator works.
    * @param range Range which defines the part of the container over which it
    *        iterates.
    */
    sc_map_iterator(sc_map_T* sc_map, const sc_map_range<key_type>& range);

    /*!
    * @brief Constructor: Creates iterator that runs over a specfified range of
    *        a provided container. Specifies also a position to start from.
    *
    * Copies the range into the local range and sets the iterator to the start
    * of the range. And sets the element to start the iteration from.
    *
    * @param sc_map Pointer to the sc_map container on which the iterator works.
    * @param range Range which defines the part of the container over which it
    *        iterates.
    * @param map_pos Position within the container to which the iterator should
    *        point initially.
    */
    sc_map_iterator(sc_map_T* sc_map, const sc_map_range<key_type>& range, const key_type& map_pos);

    /*!
    * @brief Constructor: Creates iterator that runs between two defined keys of
    *        container.
    *
    * A new range is created for the iterator which covers the values between
    * the defined start and end keys.
    *
    * @param sc_map Pointer to the sc_map container on which the iterator works.
    * @param start_key Start key of the iterator.
    * @param end_key Last key of the iterator.
    */
    sc_map_iterator(sc_map_T* sc_map, const key_type& start_key, const key_type& end_key);

    /*!
    * @brief Copy Constructor:
    *
    * Copies the member of the iterator. For the range it generates a new range
    * based on the range of the original iterator.
    *
    * @param original Iterator which values are copied to the new iterator.
    */
    sc_map_iterator(const sc_map_iterator& original);

    /*!
    * @brief Destructor:
    *
    * Frees the memory of the range that belong to the iterator.
    */
    virtual ~sc_map_iterator();

    /*!
    * @brief Assignment operator
    *
    * Creates an exact copy, i.e. the same range is used as by the original
    * iterator.
    *
    * @param rhs Original iterator.
    * @return reference to this iterator.
    */
    sc_map_iterator& operator= (const sc_map_iterator& rhs);

    /*!
    * @brief Check if two iterators point to the same element
    *
    * Checks if both iterators work on the same sc_map container and if they are
    * at the same position.
    *
    * @param other Second iterator to compare with.
    * @return true if both iterators point to the same element
    */
    bool operator==(const sc_map_iterator& other) const;

    /*!
    * @brief Check if two iterators point to a different element
    *
    * Calls the operator== function and negates it.
    *
    * @param other Second iterator to compare with.
    * @return true if both iterators point to a different element
    */
    bool operator!=(const sc_map_iterator& other) const;

    /*!
    * @brief Moves iterator to the next element of the container.
    *
    * Uses the next_key function of the range to determine the next key to which
    * the iterator points.
    *
    * @return A reference to the iterator.
    */
    virtual sc_map_iterator& operator++();

    /*!
    * @brief Gets the reference to the object the iterator actually points to.
    *
    * @return A reference to the object to which the iterator points.
    */
    virtual object_type& operator*();

    /*!
    * @brief Allows to access members of an object to which the iterator points.
    *
    * @return A pointer to the object to which the iterator points.
    */
    virtual object_type* operator->();

    /*!
    * @brief Writes a value to all SystemC objects which belong to the
    *        iterator range.
    *
    * Iterates over all objects from the one the pointer actually points to, to
    * the end of the covered range. If the write() function is not part of the
    * SystemC object, a compilation error occurs.
    *
    * @tparam data_type Data type of the value that is written. It does not to
              be explicitly specified and can be derived from the function call.
    * @param value Value that is written to the signals.
    */
    template<typename data_type>
    void write(const data_type& value);

    /*!
    * @brief Short form to write a value to all SystemC objects organized which
    *        belong to the iterator range.
    *
    * Calls the write() function of this class.
    *
    * @tparam data_type Data type of the value that is written. It does not to
              be explicitly specified and can be derived from the function call.
    * @param value Value that is written to the signals.
    */
    template<typename data_type>
    void operator= (const data_type& value);

    /*!
    * @brief Binds a SystemC signal to all SystemC objects which belong to the
    *        iterator range.
    *
    * Iterates over all objects from the one the pointer actually points to, to
    * the end of the covered range. If the bind() function is not part of the
    * SystemC object, a compilation error occurs.
    *
    * @tparam signal_T Data type that is transmitted on the sc_signal which is
    *         bound. It does not to be explicitly specified and can be derived
    *         from the function call.
    * @param signal Signal that is bound.
    */
    template <typename signal_T>
    void bind(sc_signal<signal_T>& signal);

    /*!
    * @brief Operator notation: Binds a SystemC signal to all SystemC objects
    *        which belong to the iterator range.
    *
    * Calls the according bind(sc_signal<signal_T>&) function.
    *
    * @tparam signal_T Data type of the signal that should be bound. It does not
    *         to be explicitly specified and can be derived from the function
    *         call.
    * @param signal Signal that is bound.
    */
    template <typename signal_T>
    void operator() (sc_signal<signal_T>& signal);

    /*!
    * @brief Binds the sc_signal objects of another sc_map to the SystemC
    *        objects of the container.
    *
    * It starts with the element to which the iterator points and binds it to
    * the first signal in the provided sc_map. Then it increases both the
    * iterator itself and the iterator of the sc_map. Binds the new pair. This
    * is continued until the end of the iterator is reached.
    * If the bind() function is not part of the SystemC object, a compilation
    * error occurs.
    *
    * @tparam signal_range_T Range type of the bound sc_map. It does not to be
    *         explicitly specified and can be derived from the function call.
    * @tparam signal_T Data type that is transmitted on the sc_signal which is
    *         bound. It does not to be explicitly specified and can be derived
    *         from the function call.
    * @param signal_map The sc_map of signals whose signals are bound.
    */
    template <typename signal_range_T, typename signal_T>
    void bind(sc_map_base<signal_range_T, signal_T>& signal_map);

    /*!
    * @brief Operator notation: Binds the sc_signal objects of another sc_map
    *        to the SystemC objects of the container.
    *
    * Calls the according bind(sc_map_base<signal_range_T, signal_T>&) function.
    *
    * @tparam signal_range_T Range type of the bound sc_map. It does not to be
    *         explicitly specified and can be derived from the function call.
    * @tparam signal_T Data type that is transmitted on the sc_signal which is
    *         bound. It does not to be explicitly specified and can be derived
    *         from the function call.
    * @param signal_map The sc_map of signals whose signals are bound.
    */
    template <typename signal_range_T, typename signal_T>
    void operator() (sc_map_base<signal_range_T, signal_T>& signal_map);

    /*!
    * @brief Binds the sc_signal objects of another iterator to the SystemC
    *        objects of the container.
    *
    * This function allows to select a part from another sc_map, defined by the
    * itertor passed as a parameter, to be bound to the elements of the sc_map
    * over which this iterator iterates. By configuring the range of this
    * iterator, it is also possible to bind a part of an sc_map with a part of
    * another sc_map : "Slicing"
    * The function iterates over the elements defined by this iterator and
    * iterates in parallel over the elements of the passed iterator.
    * If the bind() function is not part of the SystemC object, a compilation
    * error occurs.
    *
    * @tparam signal_map_T Type of the sc_map wich is passed by the parameter to
    *         the iterator. It does not need to be explicitly specified and can
    *         be derived from the function call.
    * @param signal_it The sc_map_iterator on a sc_map with signals whose
    *        signals are bound.
    */
    template <typename signal_map_T>
    void bind(sc_map_iterator<signal_map_T> signal_it);

    /*!
    * @brief Operator notation: Binds the sc_signal objects of another iterator
    *        to the SystemC objects of the container.
    *
    * Calls the according bind(sc_map_base<signal_range_T, signal_T>& signal_map)
    * function.
    *
    * @tparam signal_map_T Type of the sc_map wich is passed by the parameter to
    *         the iterator. It does not need to be explicitly specified and can
    *         be derived from the function call.
    * @param signal_it The sc_map_iterator on a sc_map with signals whose
    *        signals are bound.
    */
    template <typename signal_map_T>
    void operator() (sc_map_iterator<signal_map_T> signal_it);

    /*!
    * @brief Returns the key to which the iterator currently points.
    *
    * @return The function returns a std::pair with the first element signals if
    *         the end of the range is reached. The second element is the actual
    *         key.
    */
    std::pair<end_type, key_type> get_key() const;

private:
    /*!
    * @brief Pointer to sc_map object to which the iterator belong.
    */
    map_type* map;

    /*!
    * @brief Pointer to the range over which the iterator iterates.
    */
    sc_map_range<key_type>* range;

    /*!
    * @brief The position of the object to which the iterator currently points.
    */
    key_type position;

    /*!
    * @brief Flag that inidicates if the end of the range is reached.
    */
    end_type end_flag;
};

//******************************************************************************

//******************************************************************************
template <typename sc_map_T>
const typename sc_map_iterator<sc_map_T>::end_type
        sc_map_iterator<sc_map_T>::end = true;

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(sc_map_T* sc_map) :
        map(sc_map),
        end_flag(!end)
{
    range = map->get_range()->clone();
    position = range->first();

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const end_type end_id) :
        map(sc_map),
        end_flag(end_id)
{
    range = map->get_range()->clone();
    position = range->first();

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const key_type& map_pos) :
        map(sc_map),
        position(map_pos),
        end_flag(!end)
{
    // todo: check if map_pos exists within container

    range = map->get_range()->clone();

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const sc_map_range<key_type>& range) :
        map(sc_map),
        end_flag(!end)
{
    // todo: check if range is compatible with container

    this->range = range.clone();

    position = this->range->first();

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const sc_map_range<key_type>& range, const key_type& map_pos) :
        map(sc_map),
        end_flag(!end)
{
    // todo: check if range is compatible with container
    // todo: check if map_pos exists within container

    this->range = range.clone();

    position = map_pos;

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const key_type& start_key, const key_type& end_key) :
        map(sc_map),
        position(start_key),
        end_flag(!end)
{
    // todo: check if keys exist within container

    range = new typename map_type::range_type(map->get_range(), start_key, end_key);

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(const sc_map_iterator& original)
{
    map = original.map;
    typename map_type::range_type* original_range_ptr = static_cast<typename map_type::range_type*>(original.range);
    range = new typename map_type::range_type(*original_range_ptr);
    position = original.position;
    end_flag = original.end_flag;

    return;
}

//************************************************************ ******************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::~sc_map_iterator()
{
    delete range;

    return;
};

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>& sc_map_iterator<sc_map_T>::operator= (const sc_map_iterator& rhs)
{
    map = rhs.map;
    *range = *(rhs.range);
    position = rhs.position;
    end_flag = rhs.end_flag;

    return *this;
}

//******************************************************************************
template <typename sc_map_T>
bool sc_map_iterator<sc_map_T>::operator==(const sc_map_iterator& rhs)
        const
{
    bool equal = false;

    if (this->end_flag == rhs.end_flag)
    {
        if (this->end_flag == end)
        {
            equal = true;
        }
        else
        {
            equal &= this->map == rhs.map;
            equal &= this->position == rhs.position;
        }
    }

    return equal;
}

//******************************************************************************
template <typename sc_map_T>
bool sc_map_iterator<sc_map_T>::operator!=(const sc_map_iterator& other) const
{
    return !(*this==other);
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>& sc_map_iterator<sc_map_T>::operator++ ()
{
    bool success = range->next_key(position);
    if (!success)
    {
        end_flag = true;
    }

    return *this;
}

//******************************************************************************
template <typename sc_map_T>
typename sc_map_iterator<sc_map_T>::object_type&
        sc_map_iterator<sc_map_T>::operator*()
{
    // todo: ensure that out of range is not accessed (end iterator)
    return *(map->objects[position]);
}

//******************************************************************************
template <typename sc_map_T>
typename sc_map_iterator<sc_map_T>::object_type*
        sc_map_iterator<sc_map_T>::operator->()
{
    return map->objects[position];
}

//******************************************************************************
template <typename sc_map_T>
template <typename data_type>
void sc_map_iterator<sc_map_T>::write(const data_type& value)
{
    for (; *this != map->end(); ++(*this))
    {
        (**this).write(value);
    }

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename data_type>
void sc_map_iterator<sc_map_T>::operator= (const data_type& value)
{
    write(value);

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_T>
void sc_map_iterator<sc_map_T>::bind(sc_signal<signal_T>& signal)
{
    for (; *this != map->end(); ++(*this))
    {
        (**this).bind(signal);
    }

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_T>
void sc_map_iterator<sc_map_T>::operator() (sc_signal<signal_T>& signal)
{
    bind(signal);

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_range_T, typename signal_T>
void sc_map_iterator<sc_map_T>::bind(
        sc_map_base<signal_range_T, signal_T>& signal_map)
{
    for (typename sc_map_base<signal_range_T, signal_T>::iterator signal_it = signal_map.begin();
         *this != map->end();
         ++(*this))
    {
        (**this).bind(*signal_it);

        ++signal_it;
    }

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_range_T, typename signal_T>
void sc_map_iterator<sc_map_T>::operator() (
        sc_map_base<signal_range_T, signal_T>& signal_map)
{
    bind(signal_map);

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_map_T>
void sc_map_iterator<sc_map_T>::bind(sc_map_iterator<signal_map_T> signal_it)
{
    for (; *this != map->end(); ++(*this))
    {
        (**this).bind(*signal_it);

        ++signal_it;
    }

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_map_T>
void sc_map_iterator<sc_map_T>::operator() (
        sc_map_iterator<signal_map_T> signal_it)
{
    bind(signal_it);

    return;
}

//******************************************************************************
template <typename sc_map_T>
std::pair<typename sc_map_iterator<sc_map_T>::end_type,
        typename sc_map_iterator<sc_map_T>::key_type>
        sc_map_iterator<sc_map_T>::get_key() const
{
    return std::pair<end_type, key_type>(end_flag, position);
}

////******************************************************************************
//template <typename sc_map_T>
//bool sc_map_iterator<sc_map_T>::update_dim(key_type& key,
//        const key_type key_start, const key_type key_stop,
//        const cnt_direction_t direction)
//{
//    if (direction == up)
//    {
//        ++key;
//        if (key <= key_stop)
//        {
//            return true;
//        }
//        else
//        {
//            key = key_start;
//            return false;
//        }
//    }
//    else
//    {
//        --key;
//        if (key >= key_stop)
//        {
//            return true;
//        }
//        else
//        {
//            key = key_start;
//            return false;
//        }
//    }
//};
