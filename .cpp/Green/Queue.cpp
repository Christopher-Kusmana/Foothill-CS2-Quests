// Student ID: 20527001
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "Queue.h"
using namespace std;

// template <typename T>
// bool Queue<T>::enqueue(const T &elem)
// {

//     if (_data.size() == _tail)
//     {
//         return false;
//     }
//     else
//     {
        
//         _tail++;
//         _data.insert(_data.begin() + _tail, elem);
//         return true;
//     }
// }

// template <typename T>
// bool Queue<T>::dequeue()
// {
//     if (_head == _tail)
//     {
//         return false;
//     }
//     else
//     {
//         _tail--;
//         _data.erase(_data.begin());
//         return true;
//     }
// }

// template <typename T>
// const T &Queue<T>::peek() const
// {
//     return _data.front();
// }

// template <typename T>
// bool Queue<T>::is_empty() const
// {
//     return _tail == _head;
// }

// template <typename T>
// void Queue<T>::resize(size_t size)
// {
//     _data.resize(size);
// }

// template <typename T>
// string Queue<T>::to_string(size_t lim) const
// {
//     ostringstream oss;
//     oss << "# Queue - size = " << _data.size() << endl;
//     oss << "data : ";
//     size_t count = min(MAX_DISP_ELEMS, _data.size());
//     for (size_t i = _head; i < _head + count; i++)
//     {
//         oss << _data[i] << " ";
//     }
//     if (count < _data.size())
//     {
//         oss << "...";
//     }
//     return oss.str();
// }

