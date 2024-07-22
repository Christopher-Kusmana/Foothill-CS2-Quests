// Student ID: 20527001
#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <iomanip>
using namespace std;

template <typename T>
class Matrix
{
protected:
    vector<vector<T>> _rows;

public:
    Matrix(size_t nr = 0, size_t nc = 0) { _rows.resize(nr, vector<T>(nc)); }
    size_t get_num_rows() const { return _rows.size(); }
    size_t get_num_cols() const { return (_rows.size() > 0 ? _rows[0].size() : 0); }
    void clear() { _rows.clear(); }

    void resize(size_t nr, size_t nc)
    {
        _rows.resize(nr);
        for (auto &row : _rows)
        {
            row.resize(nc);
        }
    }
    T &at(size_t r, size_t c)
    {
        if (r >= get_num_rows() || c >= get_num_cols())
        {
            throw OOB_exception();
        }
        return _rows[r][c];
    }
    string to_string() const
    {
        stringstream ss;
        ss << "# Matrix\n";
        for (size_t r = 0; r < get_num_rows(); ++r)
        {
            for (size_t c = 0; c < get_num_cols(); ++c)
            {

                ss << setw(6) << _rows[r][c];
                if (c != get_num_cols()-1)
                {
                    ss << " ";
                }
            }
            ss << "\n";
        }
        return ss.str();
    }
    class OOB_exception : public exception
    {
    public:
        string what() { return "Out of bounds access"; }
    };

    friend ostream &operator<<(ostream &os, const Matrix<T> &mat)
    {
        return os << mat.to_string();
    }
    friend bool operator==(const Matrix<T> &m1, const Matrix<T> &m2)
    {
        if (m1.get_num_rows() != m2.get_num_rows())
        {
            return false;
        }
        if (m1.get_num_cols() != m2.get_num_cols())
        {
            return false;
        }

        for (size_t i = 0; i < m1.get_num_rows(); i++)
        {
            for (size_t j = 0; j < m1.get_num_cols(); j++)
            {
                if (m1._rows[i][j] != m2._rows[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    friend bool operator!=(const Matrix<T> &m1, const Matrix<T> &m2)
    {
        return !(m1 == m2);
    }
    friend class Tests;
    friend class Mx;
};
#endif