// Student ID: 20527001
#ifndef SET_H
#define SET_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
using namespace std;

template <typename T>
class Set
{
private:
    vector<T> *_master_ptr;
    vector<size_t> _elems;
    size_t _sum;

public:
    Set() : _master_ptr(nullptr), _sum(0) {}
    Set(vector<T> *mast_ptr) : _master_ptr(mast_ptr), _sum(0) {}
    const size_t size() const { return _elems.size(); }
    const vector<T> *get_master_ptr() const { return _master_ptr; }
    const size_t get_sum() const { return _sum; }

    bool add_elem(size_t n)
    {
        if (_master_ptr == nullptr)
        {
            return false;
        }
        if (_elems.size() >= _master_ptr->size() || n >= _master_ptr->size())
        {
            return false;
        }
        _elems.push_back(n);
        _sum = _sum + (*_master_ptr)[n];
        return true;
    }

    bool add_all_elems()
    {
        if (_master_ptr == nullptr)
        {
            return false;
        }
        if (_elems.size() >= _master_ptr->size())
        {
            return false;
        }
        for (size_t i = 0; i < _master_ptr->size(); i++)
        {
            _elems.push_back(i);
            _sum = _sum + (*_master_ptr)[i];
        }
        return true;
    }

    Set<T> find_biggest_subset_le(size_t target)
    {
        this->add_all_elems();
        Set<T> empty_set;
        if (_master_ptr == nullptr)
        {
            return empty_set;
        }
        if (_master_ptr->empty())
        {
            return empty_set;
        }
        if (target == 0)
        {
            return empty_set;
        }

        if (target > _sum)
        {
            return *this;
        }
        Set<T> best_set;
        size_t largest_sum = 0;
        size_t n = _master_ptr->size();
        size_t numSubsets = pow(2, n);

        for (size_t i = 0; i < numSubsets; i++)
        {
            Set<T> subset(_master_ptr);
            for (size_t j = 0; j < n; j++)
            {
                if ((i >> j) & 1)
                {
                    subset.add_elem(j);
                }
            }
            if (subset.get_sum() == target)
            {
                return subset;
            }
            if (subset.get_sum() <= target && subset.get_sum() > largest_sum)
            {
                largest_sum = subset.get_sum();
                best_set = subset;
            }
        }

        return best_set;
    }

    friend ostream &operator<<(ostream &os, const Set<T> &set)
    {
        const vector<T> *mast_ptr = set.get_master_ptr();
        os << "{\n";
        for (size_t index : set._elems)
            os << " " << mast_ptr->at(index) << "\n";
        return os << "}";
    }
    friend class Tests;
};

#endif