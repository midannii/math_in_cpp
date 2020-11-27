// Author : DougnYoung Suh
// Date on July 6, 2020

// Revised by midan sim
// Date: Oct 31, 2020

#include <iostream>
#include <eigen/Dense>
#include <eigen/LU>
using namespace Eigen;
using namespace std;

int main() {
    Matrix <float, 3, 2> A;
    A << 1, -1, -2, 2, 2, -2;
    cout << A << endl;
    Matrix <float, 2, 3> AT = A.transpose();
    cout << AT << endl;
    
    Matrix3d AAT; Matrix3d ATA;
    AAT = A*AT; // (3x3)
    ATA = AT*A; // (2x2)
    EigenSolver<Matrix2d> Aeigen;
    EigenSolver<Matrix3d> Aeigen2;
    Aeigen.compute(ATA);
    Aeigen2.compute(AAT);
    
    Matrix3d U = Aeigen2.pseudoEigenvectors();
    Matrix2d V = Aeigen.pseudoEigenvectors();
    Matrix <float, 3, 2> sigma;
    sigma = pseudoEigenvalueMatrix();
    
    cout << "U * sigma * V = " << U * sigma * V << endl;
    return 0;
}
