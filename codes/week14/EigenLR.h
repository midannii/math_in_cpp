#pragma once
#include <Eigen/Dense>
#include <cmath>
#include <random>
#include <time.h>

using namespace std;
using namespace Eigen;

class EigenLR {
public:
    int nIn;
    int nOut;
    int minibatchSize = 50;
    
    VectorXd grad_W; // = new double[nOut][nIn];
    VectorXd grad_b; // = new double[nOut];
    VectorXd dY; // = new double[minibatchSize][nOut];
    MatrixXd W;
    VectorXd b;
    
    EigenLR(int n, int nO,int mini) {;
        VectorXd grad_W[nOut]; // = new double[nOut][nIn];
        VectorXd grad_b[nOut]; // = new double[nOut];
        VectorXd dY[minibatchSize]; // = new double[minibatchSize][nOut];
        VectorXd W[nOut];
        VectorXd b[nOut];
        // input에 대한 값에 포인터를 이용하여 할당
        this-> nIn = n;
        this-> nOut = nO;
        this->W.resize(nOut, nIn);
        this->b.resize(nOut);
        minibatchSize = mini;
        int i, j;
        for (int i = 0; i < nOut; i++){
            for (int j = 0; j < nIn; j++)
                this->W(i, j) = 1;
            this->b(i) = 0.1;
        }
        for (int i = 0; i<minibatchSize; i++) dY[i].resize(nOut);
        //LogisticRegression(n, nO);
    }

    void train(MatrixXd X, MatrixXd T, int minibatchSize, double learningRate);
    VectorXd output(VectorXd x);
    VectorXd predict(VectorXd x);
};

