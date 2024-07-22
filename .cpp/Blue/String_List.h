// Student ID: 20527001
// TODO - Type in your student ID after the colon above.
// String_List.h
//
#ifndef String_List_h
#define String_List_h
#include <iostream>
#include <sstream>
using namespace std;
// Important implementation note: With the exception of to_string(),
// find*() and clear(), all list methods below should operate in a constant amount
// of time regardless of the size of the String_List instance.
//
// The semantics of _prev_to_current is such that it always points to the
// node *BEFORE* the current one. This makes the manipulations easy because
// we can only look forward (and not back) in singly linked lists.
//
// I've included some method header comments below where there's likely to
// be confusion.
//
class String_List
{
private:
    struct Node
    {
        std::string data;
        Node *next;
        Node(std::string s = "") : data(s), next(nullptr) {}
    };
    Node *_head, *_tail, *_prev_to_current;
    size_t _size = 0;

public:
    String_List()
    {
        _head = new Node;
        _head->data = "_SENTINEL_";
        _tail = _head;
        _prev_to_current = _head;
    }
    ~String_List()
    {
        Node *current = _head;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }
    String_List *insert_at_current(std::string s)
    {
        Node *new_node = new Node;
        new_node->data = s;
        new_node->next = _prev_to_current->next;
        _prev_to_current->next = new_node;
        if (new_node->next == nullptr)
        {
            _tail = new_node;
        }
        _size += 1;
        return this;
    }
    String_List *push_back(std::string s)
    {
        Node *temp = _prev_to_current;
        _prev_to_current = _tail;
        insert_at_current(s);
        _tail = _prev_to_current->next;
        _prev_to_current = temp;
        return this;
    }
    String_List *push_front(std::string s)
    {
        Node *temp = _prev_to_current;
        _prev_to_current = _head;
        insert_at_current(s);
        _prev_to_current = temp;
        return this;
    }
    String_List *advance_current()
    {
        if (_prev_to_current == _tail)
        {
            return nullptr;
        }
        else
        {
            _prev_to_current = _prev_to_current->next;
            return this;
        }
    }
    std::string get_current() const
    {
        if (_prev_to_current != nullptr)
        {
            return _prev_to_current->next->data;
        }
        else
        {
            return _head->data;
        }
    }
    String_List *remove_at_current()
    {
        if (_prev_to_current->next != nullptr)
        {
            Node *temp = _prev_to_current->next;
            _prev_to_current->next = temp->next;
            delete temp;
            if (_prev_to_current->next == nullptr)
            {
                _tail = _prev_to_current;
            }
            _size -= 1;
        }
        return this;
    }
    size_t get_size() const
    {
        if (_head == _tail)
        {
            return 0;
        }
        return _size;
    }
    String_List *rewind()
    {
        _prev_to_current = _head;
        return this;
    }
    void clear()
    {
        Node *temp = _head->next;
        while (temp != nullptr)
        {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
        _prev_to_current = _head;
        _tail = _head;
        _head->next = nullptr;
        _size = 0;
    }

    std::string &find_item(std::string s) const
    {
        Node *temp = _head->next;
        while (temp != nullptr)
        {
            if (temp->data == s)
            {
                return temp->data;
            }
            else
            {
                temp = temp->next;
            }
        }
        return _head->data;
    }

    std::string to_string() const
    {
        std::ostringstream oss;
        oss << "# String_List - " << get_size() << " entries total. Starting at cursor:\n";
        Node *temp = _head->next;
        size_t j;
        if (get_size() > 25)
        {
            j = 25;
        }
        else
        {
            j = get_size();
        }
        for (size_t i = 0; i < j; i++)
        {
            oss << temp->data << "\n";
            temp = temp->next;
        }
        if (get_size() > 25)
        {
            oss << "...\n";
        }
        return oss.str();
    }
    friend class Tests; // Don't remove this line
};
#endif /* String_List_h */
