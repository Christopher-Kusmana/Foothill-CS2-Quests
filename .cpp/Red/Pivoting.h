// Student ID: 20527001
#ifndef PIVOTING_H
#define PIVOTING_H
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class Pivoting
{
private:
    static size_t _partition(vector<T> &elems, size_t lo, size_t hi)
    {
        if (hi <= lo)
        {
            return hi;
        }

        T pivot = elems[lo + ((hi - lo) / 2)];
        size_t i = lo, j = hi;

        while (true)
        {

            while (i < hi && elems[i] < pivot)
            {
                ++i;
            }
            while (j > lo && elems[j] > pivot)
            {
                --j;
            }
            if (i >= j)
            {
                return j;
            }

            T tmp = elems[i];
            elems[i] = elems[j];
            elems[j] = tmp;
            ++i;
            --j;
        }
    }
    static T _find_kth_least_elem(vector<T> &elems, size_t lo, size_t hi, size_t k)
    {
        if (lo == hi)
        {
            return elems[lo];
        }
        while (lo < hi)
        {

            size_t part_index = _partition(elems, lo, hi);
            if (k <= part_index)
            {
                hi = part_index;
            }
            else
            {
                lo = ++part_index;
            }
        }

        return elems[lo];
    }
    static void _do_qsort(vector<T> &elems, size_t lo, size_t hi)
    {
        if (hi <= lo)
        {
            return;
        }

        size_t pivot_idx = _partition(elems, lo, hi);
        _do_qsort(elems, lo, pivot_idx);
        _do_qsort(elems, pivot_idx + 1, hi);
    }

public:

    static T find_median(vector<T> &elems)
    {
        return _find_kth_least_elem(elems, 0, elems.size() - 1, elems.size() / 2);
    }
    static T find_kth_least_elem(vector<T> &elems, size_t k)
    {

        if (k >= elems.size())
        {
            return T();
        }
        return _find_kth_least_elem(elems, 0, elems.size() - 1, k);
    }
    static void do_qsort(vector<T> &elems)
    {
        _do_qsort(elems, 0, elems.size() - 1);
    }
    friend class Tests;
};

#endif