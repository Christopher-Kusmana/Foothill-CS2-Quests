// Student ID: 20527001
#ifndef MARTIX_ALGORITHMS_H
#define MARTIX_ALGORITHMS_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <list>
#include "Matrix.h"
#include "Sparse_Matrix.h"
using namespace std;

class Mx
{

public:
    // Matrix Util
    template <typename T>
    static bool can_multiply(const Matrix<T> &a, const Matrix<T> &b)
    {
        return a.get_num_cols() == b.get_num_rows();
    }
    template <typename T>
    static bool multiply(Matrix<T> const &a, Matrix<T> const &b, Matrix<T> &res)
    {
        if (!can_multiply(a, b))
        {
            return false;
        }
        res.resize(a.get_num_rows(), b.get_num_cols());
        for (size_t i = 0; i < a.get_num_rows(); i++)
        {
            for (size_t j = 0; j < b.get_num_cols(); j++)
            {
                T sum = 0;
                for (size_t k = 0; k < a.get_num_cols(); k++)
                {
                    sum += a._rows[i][k] * b._rows[k][j];
                }
                res._rows[i][j] = sum;
            }
        }

        return true;
    }
    // Sparse Matrix Util
    template <typename T>
    static bool can_multiply(const Sparse_Matrix<T> &a, const Sparse_Matrix<T> &b)
    {
        return a.get_num_cols() == b.get_num_rows();
    }
    template <typename T>
    static bool add_to_cell(Sparse_Matrix<T> &spmat, size_t r, size_t c, const T &val)
    {
        if (!spmat.is_valid(r, c))
        {
            return false;
        }
        if (r >= spmat.get_num_rows() || c >= spmat.get_num_cols())
        {
            return false;
        }
        list<typename Sparse_Matrix<T>::Node> &row = spmat._rows[r];
        typename list<typename Sparse_Matrix<T>::Node>::iterator it = row.begin();
        while (it != row.end() && it->_col != c)
        {
            ++it;
        }
        if (it != row.end() && it->_col == c)
        {

            if (spmat.is_default(it->_val + val))
            {
                row.erase(it);
            }
            else
            {
                spmat.set(r, c, val + it->_val);
            }
        }
        return true;
    }
    template <typename T>
    // static bool multiply(Sparse_Matrix<T> &a, Sparse_Matrix<T> &b, Sparse_Matrix<T> &res)
    // {
    //     vector<size_t> cols;
    //     if (!can_multiply(a, b))
    //     {
    //         return false;
    //     }
    //     Sparse_Matrix<T> temp(a.get_num_rows(), b.get_num_cols(), res._default_val);
    //     res = temp;
    //     size_t b_cols = b.get_num_cols();
    //     for (size_t i = 0; i < a._rows.size(); i++) // i is #of rows of A
    //     {

    //         for (const auto &node : a._rows[i])
    //         {

    //             size_t a_col = node._col;
    //             for (size_t k = 0; k < b_cols; k++)
    //             {
    //                 if (!b.is_default(b.get(a_col, k)))
    //                 {
    //                     if (res.is_default(res.get(i, k)))
    //                     {
    //                         res.set(i, k, a.get(i, a_col) * b.get(a_col, k));
    //                     }
    //                     else
    //                     {
    //                         Mx::add_to_cell(res, i, k, a.get(i, a_col) * b.get(a_col, k));
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     return true;
    // }
    static bool multiply(Sparse_Matrix<T> &a, Sparse_Matrix<T> &b, Sparse_Matrix<T> &res)
    {
        vector<size_t> cols;
        if (!can_multiply(a, b))
        {
            return false;
        }
        res._rows.resize(a.get_num_rows());
        res._num_rows = a.get_num_rows();
        size_t b_cols = b.get_num_cols();
        res._num_cols = b_cols;
        for (size_t i = 0; i < a._rows.size(); i++) // i is #of rows of A
        {

            for (const auto &node : a._rows[i])
            {

                size_t a_col = node._col;
                for (const auto &nodeb : b._rows[a_col])
                {
                    if (res.is_default(res.get(i, nodeb._col)))
                    {
                        res.set(i, nodeb._col, a.get(i, a_col) * b.get(a_col, nodeb._col));
                    }
                    else
                    {
                        Mx::add_to_cell(res, i, nodeb._col, a.get(i, a_col) * b.get(a_col, nodeb._col));
                    }
                }
            }
        }

        return true;
    }
    friend class Tests;
};

#endif