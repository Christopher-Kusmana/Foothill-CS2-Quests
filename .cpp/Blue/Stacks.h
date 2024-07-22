// Student ID: 20527001
// TODO - Replace the number above with your actual student ID
//
#ifndef Stacks_h
#define Stacks_h
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
class Stack_Int
{
private:
    std::vector<int> _data;

public:
    // No explicit constructor or destructor
    size_t size() const
    {
        return _data.size();
    }
    bool is_empty() const
    {
        return _data.empty();
    }
    void push(int val)
    {
        _data.push_back(val);
    }
    int top(bool &success) const
    {
        if (_data.empty())
        {
            success = false;
            return 0;
        }
        success = true;
        return _data.back();
    }

    bool pop()
    {

        if (_data.empty())
        {
            return false;
        }
        _data.pop_back();
        return true;
    }
    bool pop(int &val)
    {
        if (_data.empty())
        {
            return false;
        }
        val = _data.back();
        _data.pop_back();
        return true;
    }
    std::string to_string() const
    {
        std::ostringstream oss;
        oss << "Stack (" << _data.size() << " elements):\n";
        int num_elements;
        if (_data.size() < 10)
        {
            num_elements = _data.size();
        }
        else
        {
            num_elements = 10;
        }
        for (size_t i = _data.size()-1; i >= _data.size()-num_elements; i--)
        {
            oss << _data[i] << '\n';
        }
        if (_data.size() > 10)
        {
            oss << "...\n";
        }
        oss << "Elements, if listed above, are in increasing order of age.";
        return oss.str();
    }
    // Don't remove the following line
    friend class Tests;
};
class Stack_String
{
private:
    std::vector<string> _data;

public:
    // No explicit constructor or destructor
    size_t size() const
    {
        return _data.size();
    }
    bool is_empty() const
    {
        return _data.empty();
    }
    void push(string val)
    {
        _data.push_back(val);
    }
    string top(bool &success) const
    {
        if (_data.empty())
        {
            success = false;
            return 0;
        }
        success = true;
        return _data.back();
    }

    bool pop()
    {

        if (_data.empty())
        {
            return false;
        }
        _data.pop_back();
        return true;
    }
    bool pop(string &val)
    {
        if (_data.empty())
        {
            return false;
        }
        val = _data.back();
        _data.pop_back();
        return true;
    }
    std::string to_string() const
    {
        std::ostringstream oss;
        oss << "Stack (" << _data.size() << " elements):\n";
        int num_elements;
        if (_data.size() < 10)
        {
            num_elements = _data.size();
        }
        else
        {
            num_elements = 10;
        }
        for (size_t i = _data.size()-1; i >= _data.size()-num_elements; i--)
        {
            oss << _data[i] << '\n';
        }
        if (_data.size() > 10)
        {
            oss << "...\n";
        }
        oss << "Elements, if listed above, are in increasing order of age.";
        return oss.str();
    }
    friend class Tests;
};
#endif /* Stacks_h */
