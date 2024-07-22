// Student ID: 20527001
#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <climits>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <list>
using namespace std;

// Notes
//  - T must implement <() via get_sentinel<T>() {return min possible T}
//  The max size of a heap = capacity - 1 because the element 0 is the sentinel
//  Capacity is simply elems.size() (= max_size + 1)

template <typename T>
T get_sentinel()
{
    return T();
}
template <typename T>
bool operator>(const T &a, const T &b)
{
    return b < a;
}

template <typename T>
class Heap
{
protected:
    vector<T> _elems;
    size_t _size;
    static const int INIT_HEAP_CAPACITY = 128;
    // private helper
    bool _percolate_down(size_t pos)
    {
        if (_size < pos)
        {
            return false;
        }
        size_t left_child = pos * 2;
        size_t right_child = left_child + 1;
        size_t min_child = pos;
        if (left_child <= _size && _elems[left_child] < _elems[min_child])
        {
            min_child = left_child;
        }
        if (right_child <= _size && _elems[right_child] < _elems[min_child])
        {
            min_child = right_child;
        }
        if (min_child != pos)
        {
            std::swap(_elems[pos], _elems[min_child]);
            _percolate_down(min_child);
        }

        return true;
    }
    bool _heapify()
    {
        bool swaps = false;
        for (size_t i = _size / 2; i > 0; i--)
        {
            swaps |= _percolate_down(i);
        }
        return swaps;
    }

public:
    Heap()
    {

        _elems.resize(Heap<T>::INIT_HEAP_CAPACITY);
        _elems[0] = get_sentinel<T>();
        _size = 0;
    }
    Heap(const vector<T> &vec)
    {
        _size = vec.size();
        _elems.resize(_size + 1);
        _elems[0] = get_sentinel<T>();
        for (size_t i = 0; i < _size; i++)
        {
            _elems[i + 1] = vec[i];
        }
        _heapify();
    }
    virtual bool is_empty() const { return _size == 0; }
    virtual bool insert(const T &elem)
    {
        if (_size + 1 == _elems.size())
        {
            _elems.resize(_elems.size() * 2);
        }
        size_t pos = ++_size;
        _elems[pos] = elem;
        while (pos > 1 && _elems[pos] < _elems[pos / 2])
        {
            swap(_elems[pos], _elems[pos / 2]);
            pos /= 2;
        }
        return true;
    }
    virtual bool delete_min()
    {
        if (is_empty())
        {
            return false;
        }
        _elems[1] = _elems[_size];
        _percolate_down(1);
        _size--;
        return true;
    }
    virtual const T &peek_min() const
    {
        if (_size == 0)
        {
            return _elems[0];
        }
        return _elems[1];
    }
    virtual string to_string()
    {
        ostringstream oss;
        if (_size == 0)
        {
            return oss.str();
        }
        oss << "# Heap with min = " << peek_min() << endl;
        oss << "# Size = " << _size << endl;

        size_t last_parent = _size / 2;
        for (size_t i = 1; i <= last_parent; i++)
        {
            size_t left_child = 2 * i;
            size_t right_child = 2 * i + 1;
            if (left_child <= _size)
            {
                oss << _elems[i] << " : ";
                if (left_child <= _size)
                {
                    oss << _elems[left_child] << " ";
                }

                if (right_child <= _size)
                {
                    oss << _elems[right_child];
                }
                else
                {
                    oss << "-";
                }

                oss << endl;
            }
        }


        oss << "# End of Heap" << endl;

        return oss.str();
    }
    friend class Tests;
};
#endif