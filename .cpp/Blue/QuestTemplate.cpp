// Student ID: 20527001

#include <iostream>
using namespace std; 

#include <iostream>
// This function returns the mean the three numbers passed
// in as parameters. Note that the mean may not be a round
// number. So you must use the double datatype for it.
double mean_of_3(int n1, int n2, int n3) {
    double avg = (n1+n2+n3)/3.0;
    return avg;
}
// This function returns the maximum of the 5 given numbers
int max_of_5(int n1, int n2, int n3, int n4, int n5) {
    int greatest = n1; 
    int nums[5] = {n1, n2, n3, n4, n5};
    for(int i = 0; i < 5; i++){
        if(nums[i] > greatest){
            greatest = nums[i];
        }
    }
    return greatest;
}
// This function returns the minimum of the 5 given numbers
int min_of_5(int n1, int n2, int n3, int n4, int n5) {
    int lowest = n1; 
    int nums[5] = {n1, n2, n3, n4, n5};
    for(int i = 0; i < 5; i++){
        if(nums[i] < lowest){
            lowest = nums[i];
        }
    }
    return lowest;
}
// Given three lengths, this function should return whether they can be the
// sides of some triangle. The heuristic you code should check if the
// sum of the two smallest sides is greater than or equal to the third side.
// Treat extreme cases as valid trianges. E.g. a+b == c means valid triangle.
// The challenge is to do it without using arrays
bool sides_make_triangle(int a, int b, int c) {
    return (a + b > c && b + c > a && a + c > b) ? true : false; 

}
// Given three angles as integer degrees, this function should return whether
// they can be internal angles of some triangle. Treat extreme cases as
// valid triangles. E.g. (0, 0, 180) is a valid triangle
bool angles_make_triangle(int A, int B, int C) {
// TODO - YOUR CODE HERE
}
// Return true if the year yyyy is a leap year and false if not.
bool is_a_leap_year(int yyyy) {
// TODO - YOUR CODE HERE
}

int main(int argc, char const *argv[])
{
    cout << sides_make_triangle(3,4,5);
}
