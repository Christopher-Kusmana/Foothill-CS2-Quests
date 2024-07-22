// Student ID: 20527001
#ifndef SPECIAL_HEAP_H
#define SPECIAL_HEAP_H
#include "Heap.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <algorithm>
#include <ostream>
#include <cmath>
#include <list>
using namespace std;

template <typename T>
class Special_Heap : public Heap<T>
{
public:
    Special_Heap() : Heap<T>(){};
    Special_Heap(const vector<T> &vec) : Heap<T>(vec){};
    const vector<T> &get_least_k(size_t k)
    {
        if (k > this->_size)
        {
            return this->_elems;
        }
        for (size_t i = 0; i < k; i++)
        {

            T min_elem = this->peek_min();
            this->delete_min();

            this->_elems[this->_size+1] = min_elem;
        }

        this->_size = 0;
        return this->_elems;
    }
    friend class Tests;
};

#endif