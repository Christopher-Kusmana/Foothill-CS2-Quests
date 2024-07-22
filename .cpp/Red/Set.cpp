// Student ID: 20527001

#include "Set.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
using namespace std;

// template <typename T>
// bool Set<T>::add_elem(size_t n)
// {
//     if (_elems.size() >= _master_ptr->size() || n >= _master_ptr->size())
//     {
//         return false;
//     }
//     _elems.push_back(n);
//     _sum = _sum + (*_master_ptr)[n];
//     return true;
// }

// template <typename T>
// bool Set<T>::add_all_elems()
// {
//     if (_elems.size() >= _master_ptr->size())
//     {
//         return false;
//     }
//     for (size_t i = 0; i < _master_ptr->size(); i++)
//     {
//         _elems.push_back(i);
//         _sum = _sum + (*_master_ptr)[i];
//     }
//     return true;
// }

// template <typename T>
// Set<T> Set<T>::find_biggest_subset_le(size_t target)
// {
//     Set<T> empty_set;
//     if (target == 0)
//     {
//         return empty_set;
//     }

//     if (target > _sum)
//     {
//         Set<T> result = *_master_ptr;
//         return result;
//     }
//     vector<Set<T>> viable_sets;
//     viable_sets.push_back(empty_set);

//     Set<T> best_set;
//     T largest_sum = 0;

//     for (size_t i = 0; i < _master_ptr->size(); i++)
//     {
//         size_t num_viable_sets = viable_sets.size();
//         for (size_t j = 0; j < num_viable_sets; j++)
//         {
//             Set<T> current_set = viable_sets[j];
//             T current_sum = current_set.get_sum();

//             Set<T> new_set = current_set;
//             if (new_set.add_elems(i))
//             {
//                 T new_sum = current_sum + (*_master_ptr)[i];

//                 if (new_sum == target)
//                 {
//                     return new_set;
//                 }
//                 else if (new_sum < target)
//                 {
//                     viable_sets.push_back(new_set);
//                     if (new_sum > largest_sum)
//                     {
//                         largest_sum = new_sum;
//                         best_set = new_set;
//                     }
//                 }
//             }
//         }
//     }

//     return best_set;
// }

// int main(int argc, char const *argv[])
// {
//     /* code */
//     return 0;
// }
