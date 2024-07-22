// Student ID: 20527001
#ifndef HASH_TABLE_QP_H
#define HASH_TABLE_QP_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <list>
#include "Hash_Table_LP.h"
using namespace std;

template <typename T>
class Hash_Table_QP : public Hash_Table_LP<T>
{
public:
    Hash_Table_QP(size_t n = Hash_Table_LP<T>::DEFAULT_INIT_CAPACITY) : Hash_Table_LP<T>(n)
    {
        this->_max_load_factor = Hash_Table_QP::_get_biggest_allowed_max_load_factor();
    }

protected:
    virtual float _get_biggest_allowed_max_load_factor() const { return 0.49; }
    virtual size_t _find_pos(const T &item) const
    {
        if (this->_num_non_vacant_cells == this->_elems.size())
        {
            return string::npos; // find not found
        }
        size_t i = this->_get_hash_modulus(item);
        size_t offset = 1;
        while (this->_elems[i]._state != Hash_Table_QP::Entry::VACANT && this->_elems[i]._data != item)
        {
            i += offset;
            offset += 2;
            if (i >= this->_elems.size())
            {
                i -= this->_elems.size();
            }
        }
        return i;
    }
    virtual void _grow_capacity()
    {
        size_t new_capacity = _next_prime(2 * this->_elems.size());
        this->_elems.resize(new_capacity);
    }

    // Private Helper
    static bool isPrime(size_t n)
    {

        if (n <= 1)
            return false;
        if (n <= 3)
            return true;

        if (n % 2 == 0 || n % 3 == 0)
            return false;

        for (size_t i = 5; i * i <= n; i = i + 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;

        return true;
    }

    static size_t _next_prime(size_t n)
    {
        if (n <= 1)
            return 2;

        size_t prime = n;
        bool found = false;

        while (!found)
        {
            prime++;

            if (isPrime(prime))
                found = true;
        }

        return prime;
        // size_t candidate = n + 1;
        // while (true)
        // {
        //     bool is_prime = true;
        //     for (size_t i = 2; i <= std::sqrt(candidate); i++)
        //     {
        //         if (candidate % i == 0)
        //         {
        //             is_prime = false;
        //             break;
        //         }
        //     }
        //     if (is_prime)
        //     {
        //         return candidate;
        //     }
        //     candidate++;
        // }
    }
    friend class Tests;
};

#endif