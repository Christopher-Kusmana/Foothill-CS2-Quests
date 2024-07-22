// Student ID: 20527001
#ifndef TREE_ALGORITHMS_H
#define TREE_ALGORITHMS_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <list>
#include "BST.h"
using namespace std;

class Tx
{
private:
    template <typename T>
    static void _rotate_with_left_child(typename BST<T>::Node *&p)
    {

        if (p == nullptr || p->_left == nullptr)
        {
            return;
        }

        typename BST<T>::Node *B = p->_left;

        p->_left = B->_right;
        B->_right = p;

        p = B;
    }
    template <typename T>
    static void _rotate_with_right_child(typename BST<T>::Node *&p)
    {

        if (p == nullptr || p->_right == nullptr)
        {
            return;
        }

        typename BST<T>::Node *B = p->_right;
        p->_right = B->_left;
        B->_left = p;

        p = B;
    }
    template <typename T>
    static void _splay(typename BST<T>::Node *&root, const T &key)
    {
        if (!root)
            return;
        typename BST<T>::Node header(0);
        header._right = header._left = nullptr;
        typename BST<T>::Node *L = &header;
        typename BST<T>::Node *R = &header;
        while (true)
        {
            if (key < root->_data)
            {
                if (!root->_left)
                    break;
                if (key < root->_left->_data)
                {
                    _rotate_with_left_child<T>(root);
                    if (!root->_left)
                        break;
                }
                R->_left = root;
                R = root;
                root = root->_left;
            }
            else if (key > root->_data)
            {
                if (!root->_right)
                    break;
                if (key > root->_right->_data)
                {
                    _rotate_with_right_child<T>(root);
                    if (!root->_right)
                        break;
                }
                L->_right = root;
                L = root;
                root = root->_right;
            }
            else
            {
                break;
            }
        }
        L->_right = root->_left;
        R->_left = root->_right;
        root->_left = header._right;
        root->_right = header._left;
    }

public:
    template <typename T>
    static const T &splay_find(BST<T> &tree, const T &x)
    {
        try
        {
            tree.find(x);
        }
        catch (const typename BST<T>::Not_found_exception &e)
        {

            throw typename BST<T>::Not_found_exception();
        }

        Tx::_splay(tree._root, x);
        return x;
    }

    template <typename T>
    static bool splay_contains(BST<T> &tree, const T &x)
    {
        try
        {

            tree.find(x);
        }
        catch (const typename BST<T>::Not_found_exception &e)
        {

            return false;
        }

        Tx::_splay(tree._root, x);
        return true;
    }
    template <typename T>
    static bool splay_insert(BST<T> &tree, const T &x)
    {
        if (tree._root == nullptr)
        {
            tree._root = new typename BST<T>::Node(x);
            tree._size += 1;
            return true;
        }

        Tx::_splay(tree._root, x);

        if (tree._root->_data == x)
        {
            return false;
        }

        typename BST<T>::Node *newNode = new typename BST<T>::Node(x);

        if (x < tree._root->_data)
        {
            newNode->_left = tree._root->_left;
            newNode->_right = tree._root;
            tree._root->_left = nullptr;
            tree._root = newNode;
            tree._size += 1;
        }
        else
        {
            newNode->_right = tree._root->_right;
            newNode->_left = tree._root;
            tree._root->_right = nullptr;
            tree._root = newNode;
            tree._size += 1;
        }

        return true;
    }
    template <typename T>
    static bool splay_remove(BST<T> &tree, const T &x)
    {
        if (!tree._root)
        {
            return false;
        }

        Tx::_splay(tree._root, x);

        if (tree._root->_data != x)
        {
            return false;
        }

        typename BST<T>::Node *newRoot = nullptr;
        if (tree._root->_left)
        {
            newRoot = tree._root->_left;
            Tx::_splay(newRoot, x);
            newRoot->_right = tree._root->_right;
        }
        else
        {
            newRoot = tree._root->_right;
        }
        delete tree._root;
        tree._size-=1;
        tree._root = newRoot;

        return true;
    }

    friend class Tests;
};

#endif