/*!
 * @file sc_map_linear.hpp
 * @author Christian Amstutz
 * @date June 9, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_base.hpp"
#include "sc_map_linear_key.hpp"
#include <systemc.h>

#include <string>
#include <sstream>
#include "sc_map_linear_range.hpp"

//******************************************************************************

/*!
 * @brief Implementation of a linear (1-dimensional) structure for sc_map.
 *
 * It implements mainly the constructors which are needed to create the
 * structures. Other functions are inherited from the base class.
 *
 * @tparam object_T SystemC object type which is organized by the sc_map_linear
 * class.
 */
template <typename object_T>
class sc_map_linear : public sc_map_base<sc_map_linear_range, object_T>
{
public:

    /*!
     * @brief Definition of base data type from which sc_map_linear is
     * inherited.
     *
     * The first template parameter is fixed to a linear range.
     */
    typedef sc_map_base<sc_map_linear_range, object_T> base;

    /*!
     * @brief Range type as in the base class.
     */
    typedef typename base::range_type range_type;

    /*!
     * @brief Key type as in the base class.
     */
    typedef typename base::key_type key_type;

    /*!
     * @brief Key vector type as in the base class.
     */
    typedef typename base::key_vector_type key_vector_type;

    /*!
     * @brief Index type for the element lookup as in the base class.
     */
    typedef typename base::key_type::index_type index_type;

    /*!
     * @brief Size type as in the base class.
     */
    typedef typename base::size_type size_type;

    /*!
     * @brief Creates a linear (1D) sc_map with a certain number of elements.
     *
     * Generates the range of indexes and calls init() function from base class.
     *
     * @param element_cnt_X Number of elements within the sc_map_linear.
     * @param name Base of the name for the SystemC elements within the
     *        sc_map_linear container.
     * @param start_id_X The number from which the range of elements starts.
     *        This argument is optional. The default value is defined in
     *        sc_map_regular_key.
     */
    sc_map_linear(const size_type element_cnt_X, const sc_module_name name, const index_type start_id_X = sc_map_linear_key::default_start_id);

    /*!
     * @brief Creates a linear (1D) sc_map with a certain number of elements and
     *        configures them.
     *
     * Generates the range of indexes and calls init() function from base class.
     * The configuration is passed to the init() function. This configuration
     * may consist of a single configuration or a std::map or std::vector of
     * congiuration objects for more details see also sc_map_base::init().
     *
     * @tparam type of the configuration object
     * @param element_cnt_X Number of elements within the sc_map_linear.
     * @param name Base of the name for the SystemC elements within the
     *        sc_map_linear container.
     * @param configuration One configuration object or a set of configuration
              objects.
     * @param start_id_X The number from which the range of elements starts.
     *        This argument is optional. The default value is defined in
     *        sc_map_regular_key.
     */
    template <typename config_type>
    sc_map_linear(const size_type element_cnt_X, const sc_module_name name, const config_type& configuration, const index_type start_id_X = sc_map_linear_key::default_start_id);

    /*!
     * @brief Creates a linear (1D) sc_map with elements within a certain
     *        range.
     *
     * Generates the range between the start and the end value. Then, calls the
     * init() function from base class.
     *
     * @param start_key First key in the range.
     * @param end_key Last key in the range.
     * @param name Base of the name for the SystemC elements within the
     *        sc_map_linear container.
     */
    sc_map_linear(const key_type start_key, const key_type end_key, const sc_module_name name);

    /*!
     * @brief Creates a linear (1D) sc_map with elements within a certain range
     *        and configures them.
     *
     * Generates the range between the start and the end value. Then, calls the
     * init() function from base class.
     * The configuration is passed to the init() function. This configuration
     * may consist of a single configuration or a std::map or std::vector of
     * congiuration objects for more details see also sc_map_base::init().
     *
     * @tparam type of the configuration object
     * @param start_key First key in the range.
     * @param end_key Last key in the range.
     * @param name Base of the name for the SystemC elements within the
     *        sc_map_linear container.
     * @param configuration One configuration object or a set of configuration
              objects.
     */
    template <typename config_type>
    sc_map_linear(const key_type start_key, const key_type end_key, const sc_module_name name, const config_type configuration);

    /*!
     * @brief Creates a linear (1D) sc_map according to a specified range.
     *
     * Calls init() function from the base class.
     *
     * @param new_range Range that defines the elements existing within the
     *        container.
     * @param name Base of the name for the SystemC elements within the
     *        sc_map_linear container.
     */
    sc_map_linear(const range_type new_range, const sc_module_name name);

    /*!
     * @brief Creates a linear (1D) sc_map according to a specified range and
     *        configures them.
     *
     * Calls init() function from the base class.
     * The configuration is passed to the init() function. This configuration
     * may consist of a single configuration or a std::map or std::vector of
     * congiuration objects for more details see also sc_map_base::init().
     *
     * @tparam type of the configuration object
     * @param new_range Range that defines the elements existing within the
     *        container.
     * @param name Base of the name for the SystemC elements within the
     *        sc_map_linear container.
     * @param configuration One configuration object or a set of configuration
              objects.
     */
    template <typename config_type>
    sc_map_linear(const range_type new_range, const sc_module_name name, const config_type& configuration);

    /*!
     * @brief Empty destructor.
     */
    virtual ~sc_map_linear() {};

    /*!
     * @brief Returns a string with the name of the class. Standard for SystemC
     * objects.
     * @return Character string with 'sc_map_linear'.
     */
    const char* kind() const;
};

//******************************************************************************

//******************************************************************************
template <typename object_T>
sc_map_linear<object_T>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const index_type start_id_X) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_linear_key(start_id_X),
            sc_map_linear_key(start_id_X+element_cnt_X-1));

    this->init(range, typename base::creator());

   // simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_linear<object_T>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const config_type& configuration,
        const index_type start_id_X) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_linear_key(start_id_X),
                sc_map_linear_key(start_id_X+element_cnt_X-1));

    this->init(range, typename base::creator(), configuration);

   // simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_linear<object_T>::sc_map_linear(const key_type start_key,
        const key_type end_key, const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(start_key, end_key);
    this->init(range, typename base::creator());

  //  simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_linear<object_T>::sc_map_linear(const key_type start_key,
        const key_type end_key, const sc_module_name name,
        const config_type configuration) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(start_key, end_key);
    this->init(range, typename base::creator(), configuration);

   // simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_linear<object_T>::sc_map_linear(const range_type new_range,
        const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator());

  //  simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_linear<object_T>::sc_map_linear(const range_type new_range,
        const sc_module_name name, const config_type& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator(), configuration);

  //  simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
const char* sc_map_linear<object_T>::kind() const
{
    return ("sc_map_linear");
}
