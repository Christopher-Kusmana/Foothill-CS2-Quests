// Student ID: 20527001
#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <list>

#include "Matrix.h"
using namespace std;

template <typename T>
class Sparse_Matrix
{
private:
    static double constexpr FLOOR = 1e-10;

    struct Node
    {
        size_t _col;
        T _val;

        Node(size_t c, const T &v) : _col(c), _val(v) {}
        size_t get_col() const { return _col; }
        const T get_val() const { return _val; }
        void set_val(const T &val) { _val = val; }
        virtual const T &operator=(const T &val) { return _val = val; }
        friend ostream &operator<<(ostream &os, const Node &node)
        {
            return os << "{ C: " << node._col << ", V: " << node._val << " }";
        }
        friend class Mx;
    };

    vector<list<Node>> _rows;
    size_t _num_rows, _num_cols;
    T _default_val;

public:
    Sparse_Matrix(size_t nr = 0, size_t nc = 0, const T &default_val = T()) : _num_rows(nr), _num_cols(nc), _default_val(default_val) { _rows.resize(nr); }
    size_t get_num_rows() const { return _num_rows; }
    size_t get_num_cols() const { return _num_cols; }
    T get_def() const {return _default_val;}

    bool is_valid(size_t r, size_t c) const { return !(r < 0 || r >= _num_rows || c < 0 || c >= _num_cols); };
    void clear()
    {
        for (auto &row : _rows)
        {
            row.clear();
        }
    }
    const T get(size_t r, size_t c) const
    {

        if (!is_valid(r, c))
        {
            return _default_val;
        }
        auto &row = _rows[r];
        for (auto it = _rows[r].begin(); it != row.end(); ++it)
        {
            if (it->get_col() == c)
            {
                return it->get_val();
            }
        }
        return _default_val;
    };
        const T set(size_t row, size_t col, const T &val)
        {
            if (!is_valid(row, col))
            {
                return _default_val;
            }
            auto &nodes = _rows[row];
            auto it = nodes.begin();
            while (it != nodes.end())
            {
                if (it->_col == col)
                {
                    if (val == _default_val)
                    {
                        it = nodes.erase(it);
                    }
                    else
                    {

                        it->set_val(val);
                    }
                    return val;
                }
                else if (it->_col > col)
                {

                    if (val != _default_val)
                    {
                        nodes.insert(it, Node(col, val));
                    }
                    return val;
                }

                ++it;
            }
            if (val != _default_val)
            {
                nodes.push_back(Node(col, val));
            }
            return val;
        }
    Matrix<T> get_slice(size_t r1, size_t c1, size_t r2, size_t c2) const
    {
        if (r1 > r2)
            swap(r1, r2);
        if (c1 > c2)
            swap(c1, c2);
        size_t numRows = r2 - r1 + 1;
        size_t numCols = c2 - c1 + 1;
        Matrix<T> mat(numRows, numCols);
        for (size_t i = r1; i <= r2; ++i)
        {
            for (const auto &node : _rows[i])
            {
                if (node._col >= c1 && node._col <= c2)
                {
                    mat.at(i - r1, node._col - c1) = node._val;
                }
            }
        }
        return mat;
    }
    bool is_default(const T &val)
    {
        return std::abs(val - _default_val) < FLOOR;
    }
    friend class Tests;
    friend class Mx;
};

#endif