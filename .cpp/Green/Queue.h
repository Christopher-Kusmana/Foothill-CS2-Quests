// Student ID: 20527001
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <ostream>
#include <sstream>
using namespace std;

template <typename T>
class Queue
{
private:
    vector<T> _data;
    size_t _head, _tail;
    static T _sentinel;
    size_t capacity;

public:
    static const size_t MAX_DISP_ELEMS = 100;
    Queue(size_t size)
    {
        _data.resize(size + 1);
        capacity = size;
        _head = 0;
        _tail = 0;
    };
    static void set_sentinel(const T &elem) { _sentinel = elem; }
    static T get_sentinel() { return _sentinel; }
    bool is_empty() const { return _tail == _head; }
    size_t size() const
    {
        if (_tail >= _head)
        {
            return _tail - _head;
        }
        else
        {
            return _data.size() - _head + _tail;
        }
    }
    void resize(size_t size)
    {
        _data.resize(size+1);
    };
    const T &peek() const
    {
        if (_head == _tail)
        {
            return _sentinel;
        }
        else
        {
            return _data.front();
        }
    }
    bool dequeue() // eff
    {
        if (is_empty())
        {
            return false;
        }
        else
        {
            _head = (_head + 1) % _data.size();
            return true;
        }
    }
    bool enqueue(const T &elem)
    {

        if ((_tail + 1) % _data.size() == _head)
        {
            return false;
        }
        else
        {
            _data[_tail] = elem;
            _tail = (_tail + 1) % _data.size();
            return true;
        }
    };
    string to_string(size_t limit = MAX_DISP_ELEMS) const
    {

        ostringstream oss;
        oss << "# Queue - size = ";
        oss << size();
        oss << endl;
        oss << "data :";
        if (size() == 0)
        {
            oss << endl;
            return oss.str();
        }
        oss << " ";
        size_t count = min(limit, size());
        for (size_t i = _head; i < _head + count; i++)
        {
            oss << _data[i] << " ";
        }
        if (count < size())
        {
            oss << "...";
        }
        oss << endl;
        return oss.str();
    }
    friend class Tests; // Don't remove this line
};
template <typename T>
T Queue<T>::_sentinel = T();
template <typename T>
void popalot(Queue<T> &q)
{
    while (!q.is_empty())
    {
        q.dequeue();
    }
}

#endif