#pragma once
#include <Eigen/Dense>
using namespace Eigen;

class EigenActivation {
public:
    static int step(double x);
    static double sigmoid(double x);
    static VectorXd softmax(VectorXd x, int n);
};
