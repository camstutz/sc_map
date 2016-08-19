/*!
 * @file sc_map_linear_range.hpp
 * @author Christian Amstutz
 * @date August 19, 2016
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_linear_key.hpp"
#include "sc_map_regular_range.hpp"

//******************************************************************************

/*!
 * @brief Implementation of the range for the linear (1-dimensional) structure
 *        of sc_map.
 *
 * The range itself is not stored within this class, but in the base class
 * sc_map_range. sc_map_linear_range inherits from sc_map_range and specializes
 * it with the sc_map_linear_key. This class implements the functions specific
 * to sc_map_linear_range, whenever possible functions are inherited from the
 * base class.
 */
class sc_map_linear_range : public sc_map_regular_range<sc_map_linear_key>
{
public:
    /*!
     * @brief The type of the keys is inherited from sc_map_regular_key.
     */
    using sc_map_range::key_type;

    /*!
     * @brief Constructor: INVALID
     *
     * Here for some compatibility?
     */
    sc_map_linear_range();

    /*!
     * @brief Constructor: Creates new linear range between two keys.
     *
     * The last_key does not need to be larger than the first_key. This allows
     * to define down counting ranges.
     *
     * @param start_key first key of the range
     * @param end_key last key of the range
     */
    sc_map_linear_range(const key_type& start_key, const key_type& end_key);

    /*!
     * @brief Constructor: Creates new linear range between two keys.
     *
     * The last_key does not need to be larger than the first_key. This allows
     * to define down counting ranges. Generally, no difference exists to
     * sc_map_linear_range(start_key, end_key), but it is here to keep
     * consitency with the other range types.
     *
     * @param base_range Defines the range which the keys are part of. Not
     *        relevant for sc_map_linear_range.
     * @param start_key First key of the range
     * @param end_key Last key of the range
     */
    sc_map_linear_range(const sc_map_range<key_type>* base_range, const key_type& start_key, const key_type& end_key);

    /*!
     * @brief Destructor: empty
     */
    virtual ~sc_map_linear_range() {};

    /*!
     * @brief Creates an exact copy of the object on the heap memory.
     *
     * @return Pointer to the newly created sc_map_linear_range object.
     */
    virtual sc_map_linear_range* clone() const;

    /*!
     * @brief Calculates the next key in the range.
     *
     * Depending on the counting direction the index is increased or decreased
     * unless the end_key is reached. The key passed to the function is casted
     * into a sc_map_linear_key.
     *
     * @param key A pointer to a key for which the next key is calculated is
     *        calculated. The key is updated by the function. The type of the
     *        key should be sc_map_linear_key.
     * @return true if a next key could be calculated and false if the last key
     *         has been reached.
     */
    virtual bool next_key(key_type& key) const;

private:
    /*!
     * @brief Defines the direction of counting of the keys: UP or DOWN.
     *
     * This member is automatically initialized during construction.
     */
    direction X_dir;

    /*!
     * @brief Common initialization tasks for all contstructors.
     *
     * The counting direction is set by this function.
     *
     * @param start_key The key from which the range starts.
     * @param end_key The key at which the range stops.
     */
    void init(const key_type& start_key, const key_type& end_key);
};
