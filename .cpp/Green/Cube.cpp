#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <Eigen/Dense>

using namespace std; 

//makes life easier for angle rotation
const float PI = M_PI;

//modify the vertices as user's liking (using eigen's matrix class)

Eigen::Matrix<float, 8, 3> v {{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1}, {1,0,0}, {1,  0,1}, {1,1,0}, {1,1,1}};

//rot matrix about y axis

Eigen::Matrix3f yRotationMatrix(float theta){
    Eigen::AngleAxisf rotation(theta* PI/ 180.0f, Eigen::Vector3f::UnitY());
    Eigen::Matrix3f R = rotation.toRotationMatrix();
    return R;
}

Eigen::Matrix<float, 8 ,3> rotateVertex(Eigen::Matrix<float, 8 ,3> m1, Eigen::Matrix3f m2){
    return m1*m2;
}


int main(int argc, char const *argv[])
{
    Eigen::Matrix<float, 8, 3> rotatedVertices = rotateVertex(v, yRotationMatrix(45));
    cout << rotatedVertices;
    return 0;
}
