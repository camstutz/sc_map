/*!
 * @file sc_map_key.hpp
 * @author Christian Amstutz
 * @date May 28, 2015
 *
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>
#include <functional>
#include <ostream>

//******************************************************************************

/*!
 * @brief Abstract base class for all sc_map key classes.
 *
 * Defines the minimum interface that an sc_map key has to provide and
 * implements the functions where possible.
 */
class sc_map_key
{
public:
    /*!
     * @brief Comparision class
     *
     * Needed to add key objects to an std::map. It defines the order of two
     * key objects within the std::map.
     */
    class Comperator : public std::binary_function<sc_map_key&, sc_map_key&, bool>
    {
    public:
        /*!
         * @brief Defines the order between two keys.
         *
         * The smaller than (<) operation is used to order the keys.
         *
         * @param lhs Key on the left hand side.
         * @param rhs Key on the right hand side.
         / @return True if the order of the two keys is correct.
         */
        bool operator()(const sc_map_key& lhs, const sc_map_key& rhs) const;
    };

    /*!
     * @brief Destructor: empty
     */
    virtual ~sc_map_key() {};

    /*!
     * @brief Definition of function that returns the key as a string.
     *
     * @return String representation of key.
     */
    virtual std::string get_string() const =0;

    /*!
     * @brief Definition of function for test of equality.
     *
     * @param other_key Second key to compare with.
     * @return True if both keys are equal.
     */
    virtual bool operator==(const sc_map_key& other_key) const =0;

    /*!
     * @brief Tests for inequality.
     *
     * This function is implemented on the base of operator==().
     *
     * @param other_key Second key to compare with.
     * @return True if both keys are not equal.
     */
    virtual bool operator!=(const sc_map_key& other_key) const;

    /*!
     * @brief Definition of function for test if other key is smaller than this
     *        one.
     *
     * @param other_key Second key to compare with.
     * @return True if this key is smaller than second one.
     */
    virtual bool operator<(const sc_map_key& other_key) const =0;

    /*!
     * @brief Tests if other key is larger than this one.
     *
     * This function is implemented on the base of operator<().
     *
     * @param other_key Second key to compare with.
     * @return True if this key is larger than second one.
     */
    virtual bool operator>(const sc_map_key& other_key) const;

    /*!
     * @brief Tests if other key is smaller or equal compared to this one.
     *
     * This function is implemented on the base of operator>().
     *
     * @param other_key Second key to compare with.
     * @return True if this key is smaller or equal than second one.
     */
    virtual bool operator<=(const sc_map_key& other_key) const;

    /*!
     * @brief Tests if other key is larger or equal compared to this one.
     *
     * This function is implemented on the base of operator<().
     *
     * @param other_key Second key to compare with.
     * @return True if this key is smaller or equal than second one.
     */
    virtual bool operator>=(const sc_map_key& other_key) const;
};

/*!
 * @brief Puts the string representation of a key to an output stream.
 *
 * This function relies on the implementation of get_string() in an actual key
 * class.
 *
 * @param out Output stream to which the string is written.
 * @param key The key that is placed to the stream
 * @return Output stream to allow concatentation.
 */
std::ostream& operator<< (std::ostream& out, const sc_map_key& key);
