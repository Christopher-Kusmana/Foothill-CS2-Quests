// Student ID: 20527001
#ifndef HASH_TABLE_LP_H
#define HASH_TABLE_LP_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <list>
using namespace std;

template <typename T>
size_t Hash(const T &elem);

template <typename T>
class Hash_Table_LP
{
protected:
    struct Entry
    {
        T _data; // payload
        enum STATE
        {
            ACTIVE,
            VACANT,
            DELETED
        } _state;
        Entry(const T &d = T(), STATE st = Entry::VACANT) : _data(d), _state(st) {}
    };
    class Table_full_exception : public exception
    {
    public:
        const string to_string() const throw() { return string("Table full exception"); }
    };
    class Not_found_exception : public exception
    {
    public:
        const string to_string() const throw() { return string("Not found exception"); }
    };
    static const size_t DEFAULT_INIT_CAPACITY = 3; // first odd prime (Don't change)
    vector<Entry> _elems;
    size_t _size;                 // doesnt count deleted elems
    size_t _num_non_vacant_cells; // does
    float _max_load_factor;
    virtual size_t _get_hash_modulus(const T &item) const
    {
        return Hash<T>(item) % _elems.size();
    } // uses Hash(item), ext.
    virtual void _rehash()
    {

        vector<Entry> old_elems = _elems;
        _grow_capacity();

        for (auto &elem : _elems)
        {
            elem._state = Entry::VACANT;
        }
        _size = 0;
        _num_non_vacant_cells = 0;
        for (size_t i = 0; i < old_elems.size(); i++)
        {
            if (old_elems[i]._state == Entry::ACTIVE)
            {
                insert(old_elems[i]._data);
            }
        }
    }

    // most common overrdes
    virtual bool set_max_load_factor(float x)
    {
        if (x <= 0 || x > _get_biggest_allowed_max_load_factor())
        {
            return false;
        }
        _max_load_factor = x;
        return true;
    }
    virtual float _get_biggest_allowed_max_load_factor() const
    {
        return 0.75;
    }
    virtual size_t _find_pos(const T &item) const
    {
        if (this->_num_non_vacant_cells == this->_elems.size())
        {
            return string::npos; // find not found
        }
        size_t i = _get_hash_modulus(item);
        while (_elems[i]._state != Entry::VACANT && _elems[i]._data != item)
        {
            i++;
            if (i >= _elems.size())
            {
                i = 0;
            }
        }
        return i;
    }
    virtual void _grow_capacity()
    {
        _elems.resize(_elems.size() * 2);

        // for (size_t i = _elems.size() / 2; i < _elems.size(); i++)
        // {
        //     _elems[i] = Entry();
        // }
    }

public:
    Hash_Table_LP(size_t n = DEFAULT_INIT_CAPACITY)
    {
        if (n <= 0)
        {
            n = DEFAULT_INIT_CAPACITY;
        }
        _elems.resize(n);
        _size = 0;
        _num_non_vacant_cells = 0;
        set_max_load_factor(_get_biggest_allowed_max_load_factor());
    }
    size_t get_size() const { return _size; }
    bool is_empty() const { return _size == 0; }
    bool contains(const T &item) const
    {

        size_t pos = _find_pos(item);
        if (pos != _elems.size() && _elems[pos]._state == Entry::ACTIVE)
        {
            return true;
        }
        return false;
    }
    T &find(const T &item)
    {
        size_t pos = _find_pos(item);
        if (pos == string::npos)
        {
            throw Not_found_exception();
        }
        if (pos == string::npos || _elems[pos]._state == Entry::VACANT || _elems[pos]._data != item)
        {
            throw Not_found_exception();
        }
        return _elems[pos]._data;
    }
    bool clear();
    bool insert(const T &item)
    {
        // if (_num_non_vacant_cells == get_size())
        // {
        //     return false;
        // }
        size_t pos = _find_pos(item);
        if (pos == string::npos)
        {
            throw Table_full_exception();
        }
        if (_elems[pos]._state == Entry::ACTIVE)
        {

            return false;
        }
        if (_elems[pos]._state == Entry::DELETED)
        {
            _elems[pos]._state = Entry::ACTIVE;
            _size++;
            _num_non_vacant_cells++;
            return true;
        }

        _elems[pos]._data = item;
        _elems[pos]._state = Entry::ACTIVE;
        _size++;
        if (_elems[pos]._state != Entry::VACANT)
        {
            _num_non_vacant_cells++;
        }

        if (_num_non_vacant_cells > _max_load_factor * _elems.size())
        {
            _rehash();
        }

        return true;
    }
    bool remove(const T &item)
    {
        if (_num_non_vacant_cells == _elems.size())
        {
            return false;
        }
        size_t pos = _find_pos(item);
        if(pos == string::npos) {
            throw Not_found_exception();
        }
        if (_elems[pos]._state == Entry::ACTIVE)
        {
            _elems[pos]._state = Entry::DELETED;
            --_size;

            return true;
        }
        else
        {
            return false;
        }
    }

    friend class Tests;
};
#endif