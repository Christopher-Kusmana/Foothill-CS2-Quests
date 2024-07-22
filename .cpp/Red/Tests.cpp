#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <unordered_map>
#include "Set.h"
#include "Sparse_Matrix.h"
#include "Matrix_Algorithms.h"
#include "BST.h"
#include "Tree_Algorithms.h"
#include "Hash_Table_LP.h"
#include "Hash_Table_QP.h"
#include "Pivoting.h"
#include "Graph.h"
#include "Graph_Algorithms.h"
#include "Heap.h"
#include "Graph.cpp"
#include "Special_Heap.h"
using namespace std;

class Tests
{
    // to_string butterfly and other (4) , to_string mouse (2)

public:
    static int longestConsecutive(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        auto uniqueEnd = std::unique(nums.begin(), nums.end());
        nums.erase(uniqueEnd, nums.end());
        int i = 0;
        int j = 1;
        int maxCount = 0;
        int count = 1;
        while (j != nums.size())
        {
            if (nums[j] == nums[j - 1] + 1)
            {
                cout << count << nums[j - 1] << " " << nums[j] << " count++" << endl;
                count++;
                j++;
            }
            else
            {
                count = 1;
                i++;
                j++;
            }

            if (count > maxCount)
            {
                maxCount = count;
            }
        }
        return maxCount;
    }
};
int main(int argc, char const *argv[])
{
    vector<int> nums = {1, 2, 0, 1};
    cout << Tests::longestConsecutive(nums);

    return 0;
}