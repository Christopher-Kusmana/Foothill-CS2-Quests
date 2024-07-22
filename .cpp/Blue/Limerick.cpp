// Student ID: 20527001
// Limerick.cpp
// 2a-Lab-01

#include <iostream>
#include <cmath>
#include <sstream> 
#include <cstdlib>

using namespace std; 

double eval_limerick(int dozen, int gross, int score){
    return ((dozen + gross + score) + (3 * sqrt(4))) / 7 + (5 * 11);
}


int main(int argc, char const *argv[])
{
    int dozen, gross, score;
    if (argc < 4) {
        cerr <<"Usage: limerick dozen-val gross-val score-val\n";
        exit(1);
    }
    istringstream(argv[1]) >>dozen;
    istringstream(argv[2]) >>gross;
    istringstream(argv[3]) >>score;
    cout << eval_limerick(dozen, gross, score) << endl;
    return 0;
}
