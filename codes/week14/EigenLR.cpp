#include "EigenLR.h"
#include "EigenActivation.h"


//void LogisticRegression::train(double **X, int **T, int minibatchSize, double learningRate)
void EigenLR::train(MatrixXd X, MatrixXd T, int minibatchSize, double learningRate){
        // train with SGD
    // 할당 및 초기화
    MatrixXd grad_W(this->nOut, this->nIn);
    MatrixXd dY(minibatchSize, this->nOut);
    VectorXd grad_B(this->nOut);
    for (int i = 0; i < this->nOut; i++){
        for (int j = 0; j < this->nIn; j++){
            grad_W(i,j) = 0.;
        }
        grad_B(i) = 0.0;
    }
    for (int i = 0; i < minibatchSize; i++){
        for (int j = 0; j < this->nOut; j++){
            dY(i,j) = 0.;
        }
    }
    // W,b의 gradient 계산
    VectorXd predicted_Y_;
    for (int n = 0; n < minibatchSize; n++){
        predicted_Y_ = output(X.row(n));
        dY.row(n) = predicted_Y_ - T.row(n).transpose();
    }
    grad_W = dY.transpose() * X;
    for (int n = 0; n < minibatchSize; n++)
        for (int j = 0; j < this->nOut; j++)
            grad_B[j] += dY(n, j);
    // params update
    this->W -= (learningRate / minibatchSize)*grad_W;
    this->b -= (learningRate / minibatchSize)*grad_B;
}

    //double * LogisticRegression::output(double *x)
    VectorXd EigenLR::output(VectorXd x){
        EigenActivation myAct;
        VectorXd preActivation(this->nOut);
        for (int i = 0; i < nOut; i++) preActivation[i] = 0;
        for (int j = 0; j < nOut; j++) {
            for (int i = 0; i < nIn; i++)
                preActivation(j) += W(j,i) * x(i);
            preActivation(j) += b(j);  // linear output
        }

        return myAct.softmax(preActivation, nOut);
    }

    //int*  LogisticRegression::predict(double *x)
    VectorXd EigenLR::predict(VectorXd x){
        VectorXd y = this->output(x);  // activate input data through learned networks
        VectorXd t(this->nOut); // output is the probability, so cast it to label

        int argmax = -1;
        double max = 0.;
        for (int i = 0; i < this->nOut; i++) {
            if (max < y(i)) {
                max = y(i);
                argmax = i;
            }
        }
        for (int i = 0; i < this->nOut; i++) {
            if (i == argmax)
                t(i) = 1;
            else
                t(i) = 0;
        }
        return t;
    }


