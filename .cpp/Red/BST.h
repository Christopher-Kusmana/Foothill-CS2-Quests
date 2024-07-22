// Student ID: 20527001
#ifndef BST_H
#define BST_H
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
class BST
{
private:
    struct Node
    {
        T _data;
        Node *_left, *_right;
        Node(const T &d, Node *l = nullptr, Node *r = nullptr) : _data(d), _left(l), _right(r) {}
    };

    Node *_root;
    size_t _size;

    // Helpers
    static Node *_deep_copy(const Node *p)
    {
        if (p == nullptr)
        {
            return nullptr;
        }
        BST<T>::Node *copy = new Node(p->_data);
        copy->_left = _deep_copy(p->_left);
        copy->_right = _deep_copy(p->_right);
        return copy;
    }
    bool _insert(Node *&p, const T &elem)
    {
        if (p == nullptr)
        {
            p = new BST<T>::Node(elem);
            _size++;
            return true;
        }
        if (elem == p->_data)
        {
            return false;
        }
        if (elem < p->_data)
        {
            return _insert(p->_left, elem);
        }
        else
        {
            return _insert(p->_right, elem);
        }
    }
    bool _remove(Node *&p, const T &elem)
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
            if (p->_left == nullptr && p->_right == nullptr)
            {
                delete p;
                --_size;
                p = nullptr;
            }
            else if (p->_left == nullptr || p->_right == nullptr)
            {
                BST<T>::Node *temp = p;
                p = (p->_left != nullptr) ? p->_left : p->_right;
                delete temp;
                --_size;
            }
            else
            {
                const BST<T>::Node *successor = _find_min(p->_right);
                p->_data = successor->_data;
                _remove(p->_right, successor->_data);
            }

            return true;
        }
    }
    bool _recursive_delete(Node *&p)
    {
        if (p == nullptr)
        {
            return false;
        }
        _recursive_delete(p->_left);
        _recursive_delete(p->_right);
        delete p;
        p = nullptr;
        --_size;
        return true;
    }
    const Node *_find_min(Node *p) const
    {
        if (p == nullptr)
        {
            return nullptr;
        }
        while (p->_left != nullptr)
        {
            p = p->_left;
        }
        return p;
    }
    Node *_find(Node *p, const T &elem) const
    {
        if (p == nullptr)
        {
            return nullptr;
        }
        else if (elem < p->_data)
        {
            return _find(p->_left, elem);
        }
        else if (p->_data < elem)
        {
            return _find(p->_right, elem);
        }
        else
        {
            return p;
        }
    }
    string _to_string(const Node *p) const
    {
        ostringstream oss;

        if (p != nullptr)
        {
            if (p->_left != nullptr || p->_right != nullptr)
                oss << p->_data << " : ";

            if (p->_left != nullptr)
            {
                oss << p->_left->_data << " ";
            }
            else
            {
                if (p->_left != nullptr || p->_right != nullptr)
                    oss << "[null] ";
            }

            if (p->_right != nullptr)
            {
                oss << p->_right->_data;
            }
            else
            {
                if (p->_left != nullptr || p->_right != nullptr)
                    oss << "[null]";
            }
            if (p->_left != nullptr || p->_right != nullptr)
            {
                oss << "\n";
            }
            oss << _to_string(p->_left);
            oss << _to_string(p->_right);
        }

        return oss.str();
    }

public:
    BST() : _root(nullptr), _size(0) {}
    virtual ~BST() { _recursive_delete(_root); }
    virtual size_t get_size() const { return _size; }
    virtual bool insert(const T &elem)
    {

        return _insert(_root, elem);
    }
    virtual bool remove(const T &elem) { return _remove(_root, elem); }
    virtual string to_string() const
    {
        ostringstream os;
        os << "# Tree rooted at " << _root->_data << "\n";
        os << "# size = " << _size << "\n";
        os << _to_string(_root);
        os << "# End of Tree";
        return os.str();
    };

    virtual const Node *find(const T &elem) const
    {
        BST<T>::Node *res = _find(_root, elem);
        if (res == nullptr)
        {
            throw Not_found_exception();
        }
        else
        {
            return res;
        }
    }

    class Not_found_exception : public exception
    {
    public:
        string to_string() { return "Not found exception"; }
    };
    friend class Tests;
    
    friend class Tx;
};

#endif