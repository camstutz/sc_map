/*!
 * @file sc_map_linear_key.hpp
 * @author Christian Amstutz
 * @date June 9, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_regular_key.hpp"

#include <string>
#include <sstream>

//******************************************************************************

/*!
 * @brief Implementation of the key for the linear (1-dimensional) structure of
 *        sc_map.
 *
 * The only dimension of sc_map_linear_key is called X, which is stored in a
 * member variable that can directly accessed. As all keys a string
 * representation can be generated and the key can be compared with keys of the
 * same type.
 */
class sc_map_linear_key : public sc_map_regular_key
{
public:
    /*!
     * @brief The type of the key is inherited from sc_map_regular_key.
     */
    using sc_map_regular_key::index_type;

    /*!
     * @brief The value of the index/coordinate.
     */
    index_type X;

    /*!
     * @brief Constructor: Initializes the indx
     *
     * @param X value for the index. Default value is 0.
     */
    sc_map_linear_key(index_type X = 0);

    /*!
     * @brief Destructor: empty
     */
    virtual ~sc_map_linear_key() {};

    /*!
     * @brief Generates string representation of index
     *
     * @return String of index X
     */
    virtual std::string get_string() const;

    /*!
     * @brief Tests for equality between two key objects.
     *
     * The second key is casted to sc_map_linear_key as the function needs to be
     * generic to be accessed from sc_map_key. To execute this function
     * sucessfully both keys need to be of the same key type. Finally, the X
     * value of both objects is compared.
     *
     * @param other_key another key that should have the type sc_map_linear_key.
     * @return true if equal, otherwise false
     */
    virtual bool operator==(const sc_map_key& other_key) const;

    /*!
     * @brief Tests if this object is smaller than another key obejct.
     *
     * The second key is casted to sc_map_linear_key as the function needs to be
     * generic to be accessed from sc_map_key. To execute this function
     * sucessfully both keys need to be of the same key type. Finally, the X
     * value of both objects is compared.
     *
     * @param other_key another key that should have the type sc_map_linear_key.
     * @return true if lefthand object is smaller, otherwise false
     */
    virtual bool operator<(const sc_map_key& other_key) const;
};
