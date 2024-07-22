// Student ID: 20527001

#include "Automaton.h"
#include <vector>
#include <time.h>
#include <string>
#include <sstream>

using namespace std;

// Helper func
size_t Automaton::decimalToBinary(int n)
{
    ostringstream oss;
    int arr[11], i = 0, num = n;

    // Until the value of n becomes 0.
    while (n != 0)
    {
        arr[i] = n % 2;
        i++;
        n = n / 2;
    }
    cout << num << " in Binary is ";

    // Printing the array in Reversed Order.
    for (i = i - 1; i >= 0; i--)
    {
        oss << arr[i];
    }
    int bin_i = stoi(oss.str());
    size_t bin = static_cast<size_t>(bin_i);
    return bin;
}

size_t Automaton::translate_n_bits_starting_at(const vector<int> &bits, size_t pos, size_t n)
{
    if (pos + n > bits.size())
    {
        return 0;
    }

    size_t result = 0;

    for (size_t i = 0; i < n; i++)
    {

        result = (result << 1) + bits[pos + i];
    }
    return result;
}

string Automaton::generation_to_string(const vector<int> &gen, size_t width)
{
    // Step 1

    if (width % 2 == 0 || !_is_valid)
        return "";
    // Step 2
    string str;
    if (gen.size() > width)
    {
        size_t start_index = gen.size() / 2 - width / 2;
        size_t end_index = gen.size() / 2 + width / 2;
        for (size_t i = start_index; i <= end_index; i++)
        {
            str += (gen[i] == 0) ? ' ' : '*';
        }
    }

    else
    {
        for (size_t i = 0; i < gen.size(); i++)
        {
            str += (gen[i] == 0) ? ' ' : '*';
        }
    }

    // Step 3
    int padding = (width - str.size()) / 2;

    // Step 4
    string padded_str;
    for (int i = 0; i < padding; i++)
    {
        padded_str += (_extreme_bit == 0) ? ' ' : '*';
    }
    padded_str += str;
    for (int i = 0; i < padding; i++)
    {
        padded_str += (_extreme_bit == 0) ? ' ' : '*';
    }

    // Step 5
    return padded_str;
}

bool Automaton::set_rule(size_t rule)
{
    if (_num_parents > MAX_PARENTS)
    {
        return false;
    }

    // Calculate the maximum rule allowed by the number of parents
    size_t max_rule = pow_2(pow_2(_num_parents)) - 1;

    if (rule > max_rule)
    {
        return false;
    }

    // Fill in the _rules vector with the appropriate values for the given rule
    for (size_t i = 0; i < pow_2(_num_parents); i++)
    {
        //(pow_2(_num_parents) - 1 -
        _rules[i] = (rule >> i) & 1;
    }
    _is_valid = true;

    return true;
}

Automaton::Automaton(size_t num_parents, size_t rule)
{
    _extreme_bit = 0;
    _num_parents = num_parents;
    _rules.resize(pow_2(_num_parents));
    _is_valid = set_rule(rule);
    _rule_choice = rule;
    if (!_is_valid)
    {
        return;
    }
}

bool Automaton::equals(const Automaton &that)
{
    if (this->_is_valid != true && that._is_valid != true)
    {
        return true;
    }
    if (this->_is_valid == true && that._is_valid == true &&
        this->_num_parents == that._num_parents &&
        this->_extreme_bit == that._extreme_bit &&
        this->_rules == that._rules)
    {
        return true;
    }
    return false;
}

bool Automaton::make_next_gen(const vector<int> &current_gen, vector<int> &next_gen)
{
    next_gen.clear();
    if (this->_is_valid == false)
    {
        return false;
    }
    if (current_gen.size() % 2 == 0 && current_gen.size() != 0)
    {
        return false;
    }
    if (current_gen.size() == 0)
    {
        next_gen.push_back(1);
        return true;
    }
    vector<int> current_copy = current_gen;
    if (_num_parents == 1 && current_gen.size() != 1)
    {
        current_copy.insert(current_copy.begin(), _extreme_bit);
        current_copy.push_back(_extreme_bit);
    }
    else if (_num_parents > 1)

    {
        for (size_t i = 0; i < _num_parents - 1; i++)
        {
            current_copy.insert(current_copy.begin(), _extreme_bit);
            current_copy.push_back(_extreme_bit);
        }
    }

    if (_num_parents != 1 || current_gen.size() != 1)
    {

        for (size_t i = 0; i < current_copy.size() - 2; i++)
        {
            next_gen.push_back(_rules[translate_n_bits_starting_at(current_copy, i, _num_parents)]);
        }
    }
    else if (_num_parents == 1 && current_gen.size() == 1)
    {
        next_gen.push_back(_rules[current_copy[0]]);
    }
    vector<int> three_eb;
    for (size_t i = 0; i < _num_parents; i++)
    {
        three_eb.push_back(_extreme_bit);
    }
    _extreme_bit = _rules[translate_n_bits_starting_at(three_eb, 0, _num_parents)];
    return true;
}

string Automaton::get_first_n_generations(size_t n, size_t width)
{
    string res;
    if (width % 2 == 0 || _is_valid == false)
    {
        return "";
    }
    set_rule(_rule_choice);
    _extreme_bit = 0;
    vector<int> gen_zero = {};
    vector<int> next;
    vector<int> temp; 
    make_next_gen(gen_zero, next);
    for (size_t i = 0; i < n; i++)
    {   
        res += generation_to_string(next, width);
        res += '\n';
        make_next_gen(next, temp);
        next = temp;
        
    }

    return res;
}

