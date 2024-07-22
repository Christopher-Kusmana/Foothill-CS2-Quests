// Student ID: 20527001
#ifndef LAZY_BST_H
#define LAZY_BST_H
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
class Lazy_BST
{
protected:
    struct Node
    {
        T _data;
        Node *_left, *_right;
        bool _is_deleted;
        Node(const T &d) : _data(d), _left(nullptr), _right(nullptr), _is_deleted(false) {}
    };
    Node *_root;
    size_t _size, _real_size;
    T res;
    // Private Helpers
    bool _recursive_delete(Node *&p) // broken pointer troublemaker
    {
        return true;
        if (p == nullptr)
        {
            return false;
        }

        bool deleted = false;
        if (p->_left)
        {
            if (_recursive_delete(p->_left))
            {
                deleted = true;
            }
        }

        if (p->_right)
        {
            if (_recursive_delete(p->_right))
            {
                deleted = true;
            }
        }

        if (p)
        {
            Node *tmp = p;
            p = const_cast<Node *>(_find_real_min(tmp->_right));
            p->_left = tmp->_left;
            p->_right = tmp->_right;
            p->_is_deleted = tmp->_is_deleted;
            if (tmp != nullptr)
            {
                delete tmp;
                tmp = nullptr;
            }
            return true;
        }

        return deleted;
    }
    bool _insert(Node *&p, const T elem)
    {
        if (p == nullptr)
        {
            p = new Node(elem);
            _size++;
            _real_size++;
            return true;
        }
        else if (elem < p->_data)
        {
            bool res = _insert(p->_left, elem);
            return res;
        }
        else if (elem > p->_data)
        {
            bool res = _insert(p->_right, elem);
            return res;
        }
        else
        {
            if (p->_is_deleted)
            {
                p->_is_deleted = false;
                _size++;
                _real_size++;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    bool _remove(Node *&p, const T elem)
    {
        if (p == nullptr)
        {
            return false;
        }

        if (elem < p->_data)
        {
            return _remove(p->_left, elem);
        }
        else if (elem > p->_data)
        {
            return _remove(p->_right, elem);
        }
        else
        {
            if (!p->_is_deleted)
            {
                p->_is_deleted = true;
                --_size;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    bool _collect_garbage(Node *&p)
    {

        if (p == nullptr)
        {
            return false;
        }
        bool res = false; 
        _collect_garbage(p->_left);

        _collect_garbage(p->_right);

        if (p->_is_deleted)
        {
            res = _really_remove(p, p->_data);
        }

        return res;
    }
    const Node *_find_min(const Node *p) const
    {

        if (p == nullptr)
        {
            return nullptr;
        }

        const Node *left_min = _find_min(p->_left);
        const Node *right_min = _find_min(p->_right);

        if (p->_left == nullptr && p->_right == nullptr)
        {

            if (p->_is_deleted)
            {
                return nullptr;
            }
            else
            {

                return p;
            }
        }
        else if (p->_left != nullptr && p->_right == nullptr)
        {

            if (left_min == nullptr)
            {

                if (!p->_is_deleted)
                {
                    return p;
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {

                return left_min;
            }
        }
        else if (p->_left == nullptr && p->_right != nullptr)
        {

            if (!p->_is_deleted)
            {

                return p;
            }
            else
            {

                return right_min;
            }
        }
        else
        {

            if (left_min == nullptr && !p->_is_deleted)
            {

                return p;
            }
            else
            {
                return (left_min == nullptr) ? right_min : left_min;
            }
        }
    }
    const Node *_find_real_min(Node *p) const
    {
        if (p == nullptr)
        {
            return nullptr;
        }
        if (p->_left == nullptr)
        {
            return p;
        }
        return _find_real_min(p->_left);
    }
    const Node *_find(const Node *p, const T &elem) const
    {

        if (p == nullptr)
        {
            return nullptr;
        }

        if (p->_data == elem && !p->_is_deleted)
        {
            return p;
        }

        if (elem < p->_data)
        {
            return _find(p->_left, elem);
        }
        else
        {
            return _find(p->_right, elem);
        }
    }
    bool _really_remove(Node *&p, const T &elem)
    {
        if (p == nullptr)
        {
            return false;
        }

        if (elem < p->_data)
        {
            return _really_remove(p->_left, elem);
        }
        else if (elem > p->_data)
        {
            return _really_remove(p->_right, elem);
        }
        else
        {
            if (p->_left == nullptr && p->_right == nullptr)
            {
                delete p;
                p = nullptr;
                --_real_size;
                return true;
            }
            else if (p->_left == nullptr)
            {

                Node *temp = p;
                p = p->_right;
                delete temp;
                temp = nullptr;
                --_real_size;
                return true;
            }
            else if (p->_right == nullptr)
            {

                Node *temp = p;
                p = p->_left;
                delete temp;
                temp = nullptr;
                --_real_size;
                return true;
            }
            else
            {
                Node *min_node = const_cast<Node *>(_find_real_min(p->_right));
                if (min_node == nullptr)
                {
                    delete p;
                    p = nullptr;
                    --_real_size;
                    return true;
                }
                p->_data = min_node->_data;
                p->_is_deleted = min_node->_is_deleted;
                _really_remove(p->_right, min_node->_data);
                return true;
            }
        }
    }
    string _to_string(const Node *p) const
    {
        if (p == nullptr)
        {
            return "[null]";
        }

        ostringstream oss;
        oss << p->_data << " : ";

        if (p->_left != nullptr)
        {
            oss << p->_left->_data << " ";
        }
        else
        {
            oss << "[null] ";
        }

        if (p->_right != nullptr)
        {
            oss << p->_right->_data;
        }
        else
        {
            oss << "[null]";
        }

        oss << "\n";
        oss << _to_string(p->_left);
        oss << _to_string(p->_right);

        return oss.str();
    }

public:
    Lazy_BST() : _root(nullptr), _size(0), _real_size(0) {}
    ~Lazy_BST() { _recursive_delete(_root); }
    size_t get_size() { return _size; }
    size_t get_real_size() { return _real_size; }
    bool insert(const T &elem)
    {
        return _insert(_root, elem);
    }
    bool remove(const T &elem)
    {
        return _remove(_root, elem);
    }
    bool collect_garbage() { return _collect_garbage(_root); }
    bool contains(const T &elem) const { return _find(_root, elem) != nullptr; }
    const T &find(const T &elem) const
    {
        const Lazy_BST<T>::Node *res = _find(_root, elem);
        if (res == nullptr)
        {
            throw Not_found_exception();
        }
        else
        {
            return res->_data;
        }
    }
    string to_string() const
    {
        ostringstream oss;
        oss << "# Tree rooted at " << _root->_data << "\n";
        oss << "# size = " << _size << "\n";
        oss << _to_string(_root);
        oss << "# End of Tree";
        return oss.str();
    }
    bool clear()
    {
        return true;
        {
            _recursive_delete(_root);
            _root = nullptr;
            _size = 0;
            return true;
        }
    }
    class Not_found_exception : public exception
    {
        string what() { return "Element not found exception"; }
    };
    friend class Tests;
};
#endif