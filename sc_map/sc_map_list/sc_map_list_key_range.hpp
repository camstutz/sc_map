/*!
 * @file sc_map_list_key_range.hpp
 * @author Christian Amstutz
 * @date June 3, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_list_key.hpp"

#include "../sc_map_key_range.hpp"

#include <vector>

//******************************************************************************
template <typename value_T>
class sc_map_list_key_range : public sc_map_key_range<sc_map_list_key<value_T> >
{
public:
    typedef value_T value_type;
    typedef sc_map_list_key<value_T> key_type;

    sc_map_list_key_range();
    sc_map_list_key_range(const std::vector<key_type>& keys);
    sc_map_list_key_range(sc_map_key_range<key_type>* source_range, key_type start_key, key_type end_key);
    virtual ~sc_map_list_key_range() {};

    virtual sc_map_list_key_range<value_type>* clone();

    void add_key(const key_type& new_key);
    //void add_key(const std::vector<key_type>& new_keys);

    virtual key_type first() const;
    virtual key_type last() const;
    virtual bool next_key(key_type& key) const;
    virtual bool key_in_range(const key_type& key) const;

    std::vector<key_type> get_key_vector() const;

private:
    std::vector<key_type> keys;
};

//******************************************************************************

//******************************************************************************
template <typename value_T>
sc_map_list_key_range<value_T>::sc_map_list_key_range()
{}

//******************************************************************************
template <typename value_T>
sc_map_list_key_range<value_T>::sc_map_list_key_range(
        const std::vector<key_type>& keys) :
        keys(keys)
{}

//******************************************************************************
template <typename value_T>
sc_map_list_key_range<value_T>::sc_map_list_key_range(
        sc_map_key_range<key_type>* source_range, key_type start_key,
        key_type end_key)
{

    if (source_range->key_in_range(start_key))
    {
        key_type key = start_key;

        do
        {
            add_key(key);
        } while (source_range->next_key(key));
    }
    else
    {
        return;
    }

    return;
}

//******************************************************************************
template <typename value_T>
sc_map_list_key_range<value_T>* sc_map_list_key_range<value_T>::clone()
{
    return new sc_map_list_key_range<value_type>(*this);
}

//******************************************************************************
template <typename value_T>
void sc_map_list_key_range<value_T>::add_key(const key_type& new_key)
{
    keys.push_back(new_key);

    return;
}

////******************************************************************************
//template <typename key_T>
//void sc_map_list_key_range<key_T>::add_key(const std::vector<key_type>& new_keys)
//{
//    keys.insert(keys.end(), new_keys.begin(), new_keys.end());
//
//    return;
//}

//******************************************************************************
template <typename key_T>
typename sc_map_list_key_range<key_T>::key_type
        sc_map_list_key_range<key_T>::first() const

// sc_map_list_key_range<key_T>::key_type sc_map_list_key_range<key_T>::first() const [with key_T = sc_map_linear_key; sc_map_list_key_range<key_T>::key_type = sc_map_linear_key]’
// sc_map_key_range<key_T>::key_type sc_map_key_range<key_T>::first() const [with key_T = sc_map_list_key<sc_map_linear_key>; sc_map_key_range<key_T>::key_type = sc_map_list_key<sc_map_linear_key>]’

{
    return keys[0];
}

//******************************************************************************
template <typename key_T>
typename sc_map_list_key_range<key_T>::key_type
        sc_map_list_key_range<key_T>::last() const
{
    return keys[keys.size()-1];
}

//******************************************************************************
template <typename key_T>
bool sc_map_list_key_range<key_T>::next_key(key_type& key) const
{
    for (typename std::vector<key_type>::const_iterator key_it = keys.begin();
         key_it != keys.end();
         ++key_it)
    {
        if (*key_it == key)
        {
            ++key_it;
            if (key_it != keys.end())
            {
                key = *key_it;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

//******************************************************************************
template <typename key_T>
bool sc_map_list_key_range<key_T>::key_in_range(const key_type& key) const
{
    for (typename std::vector<key_type>::const_iterator key_it = keys.begin();
         key_it != keys.end();
         ++key_it)
    {
        if (*key_it == key)
        {
            return true;
        }
    }

    return false;
}

//******************************************************************************
template <typename key_T>
std::vector<typename sc_map_list_key_range<key_T>::key_type>
        sc_map_list_key_range<key_T>::get_key_vector() const
{
    return keys;
}
