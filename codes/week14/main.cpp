// no eigen
#include <iostream>
#include <fstream>
#include <list>
#include <random>
#include "time.h"
#include "LogisticRegression.h"
using namespace std;

int patterns = 2;   // number of classes(poison or not)
int train_N = 5688;
int test_N = 2436;
int nIn = 22;       // 22 features
int nOut = patterns;      //
int * shuffle(int N);
void get_data(double **, int **, double **, int **);
int main() {
    clock_t start = clock();
  // Declare variables and constants
    double **train_X = new double*[train_N]; for(int i=0;i<train_N;i++) train_X[i] = new double[nIn];
    int** train_T = new int*[train_N];  for (int i = 0; i<train_N; i++) train_T[i] = new int[nOut];
    // shuffle the input data
    double **shuffled_train_X = new double*[train_N];
    int **shuffled_train_T = new int*[train_N];
    int * shuffled = shuffle(train_N);
    for (int i = 0; i < train_N; i++) {
        shuffled_train_X[i] = train_X[shuffled[i]];
        shuffled_train_T[i] = train_T[shuffled[i]];
    }

    double **test_X = new double*[test_N]; for (int i = 0; i<test_N; i++) test_X[i] = new double[nIn];
    int** test_T = new int*[test_N];  for (int i = 0; i<test_N; i++) test_T[i] = new int[nOut];
    int** predicted_T = new int*[test_N];  //for (int i = 0; i<test_N; i++) predicted_T[i] = new int[nOut];

    get_data(train_X, train_T, test_X, test_T);

    int epochs = 2000;
    double learningRate = 0.1;

    int minibatchSize = 12;  //  number of data in each minibatch
    int minibatch_N = train_N / minibatchSize; //  number of minibatches
    //
    // Build Logistic Regression model
    //
    // construct logistic regression
    LogisticRegression classifier = LogisticRegression(nIn, nOut, minibatchSize);
    
    cout << "(nIn nOut mini)" << classifier.nIn << " " << classifier.nOut << " " << classifier.minibatchSize << "\n";
    /*for (int i = 0; i < nOut; i++) {
        for (int j = 0; j < nIn; j++) cout << classifier.W[i][j] << "  ";
        cout << " W  b = " << classifier.b[i] << endl;
    }*/
    
    // train
    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int n = 0; n < train_N; n += minibatchSize) {
            classifier.train(shuffled_train_X+n, shuffled_train_T+n, minibatchSize, learningRate);
        }
        learningRate *= 0.99;
    }

    // test
    for (int i = 0; i < test_N; i++) {
        predicted_T[i] = classifier.predict(test_X[i]);

    }
    //
    // Evaluate the model
    //
    int **confusionMatrix = new int*[patterns]; for(int i=0;i<patterns;i++)confusionMatrix[i]=new int[patterns];
    double accuracy = 0.;
    double *precision = new double[patterns];
    double *recall = new double[patterns];
    for (int i = 0; i < patterns; i++) {
        precision[i] = recall[i] = 0;
        for (int j = 0; j < patterns; j++) confusionMatrix[i][j] = 0;
    }

    for (int i = 0; i < test_N; i++) {
        int predicted_,actual_;
        for (predicted_ = 0; predicted_<patterns; predicted_++) if (predicted_T[i][predicted_] == 1) break;
        for (actual_ = 0; actual_<patterns; actual_++) if (test_T[i][actual_] == 1) break;

        if (actual_ == patterns || predicted_ == patterns) {
            cout << "no decision " << predicted_ << " " << actual_ << endl;
            cout << "Learning Rate: " << learningRate << endl;
            exit(123);
        }
        confusionMatrix[actual_][predicted_] += 1;
    }

    for (int i = 0; i < patterns; i++) {
        double col_ = 0.;
        double row_ = 0.;

        for (int j = 0; j < patterns; j++) {

            if (i == j) {
                accuracy += confusionMatrix[i][j];
                precision[i] += confusionMatrix[j][i];
                recall[i] += confusionMatrix[i][j];
            }

            col_ += confusionMatrix[j][i];
            row_ += confusionMatrix[i][j];
        }
        precision[i] /= col_;
        recall[i] /= row_;
    }

    accuracy /= test_N;

    cout << "------------------------------------\n";
    cout << "Logistic Regression model evaluation\n";
    cout << "------------------------------------\n";
    cout << "Accuracy: " << accuracy * 100 << "%\n";
    cout << "Precision:\n";
    for (int i = 0; i < patterns; i++) {
        cout << " class "<< i+1<< ":"  << precision[i] * 100 << "%\n";
    }
    cout << "Recall:\n";
    for (int i = 0; i < patterns; i++) {
        cout << " class " << i + 1 << ":" << recall[i] * 100 << "%\n";
    }
    
    clock_t end = clock(); // 코드가 끝난 시간 저장
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

    return 0;
}
// return an int array of random-shuffled positions
int * shuffle(int N) {
    int *aa = new int[N];
    int i, left, j;

    for (i = 0; i < N; i++) aa[i] = -1;
    for (i = 0; i < N; i++) {
        left = rand() % (N - i);
        for (j = 0; j < N; j++) if (aa[j] == -1) {
            if (left == 0) break; else left--;
        }
        aa[j] = i;
    }
    return aa;
}
// read data
void get_data(double **tnx, int **tnt, double **tex, int **tet) {
    ifstream data("mushroom2.txt");
    int it;
    for(int k = 0;k<patterns;k++){
        int m = k * test_N/nOut;
        for (int i = 0; i < (test_N/nOut); i++,m++) {
            data >> it;
            data >> tnx[m][0] >> tnx[m][1] >> tnx[m][2] >> tnx[m][3] >> tnx[m][4] >> tnx[m][5] >> tnx[m][6] >> tnx[m][7] >> tnx[m][8] >> tnx[m][9] >> tnx[m][10] >> tnx[m][11] >> tnx[m][12] >> tnx[m][13] >> tnx[m][14] >> tnx[m][15] >> tnx[m][16] >> tnx[m][17] >> tnx[m][18] >> tnx[m][19] >> tnx[m][20] >> tnx[m][21];
            for (int j = 0; j < patterns; j++) {
                if (j==it) tnt[m][j] = 1;
                else tnt[m][j] = 0;
            }
            
        }
        m = k * test_N/nOut;
        for (int i = 0; i < (test_N/nOut); i++,m++) {
            data >> it;
            data >> tex[m][0] >> tex[m][1] >> tex[m][2] >> tex[m][3] >> tex[m][4] >> tex[m][5] >> tex[m][6] >> tex[m][7] >> tex[m][8] >> tex[m][9] >> tex[m][10] >> tex[m][11] >> tex[m][12] >> tex[m][13] >> tex[m][14] >> tex[m][15] >> tex[m][16] >> tex[m][17] >> tex[m][18] >> tex[m][19] >> tex[m][20] >> tex[m][21];
            for (int j = 0; j < patterns; j++) {
                if (j==it) tet[m][j] = 1;
                else tet[m][j] = 0;
            }
        }
    }
}

/*
// with eigen
#include <iostream>
#include <eigen/Dense>
#include <eigen/LU>
#include <fstream>
#include "EigenLR.h"
#include "time.h"
#include <random>
using namespace Eigen;
using namespace std;

int patterns = 2;   // number of classes
int total_N = 8124;
int train_N = 5688;  // number of training data (8124 * 0.7)
int test_N = 2436;   // number of test data (8124 * 0.3)
int nIn = 22;       // 22 features
int nOut = patterns;      //
VectorXd shuffle(int N);
VectorXd Combination(int N, int R);

int main() {
    clock_t start = clock();
    // Declare variables and constants
        // VectorXd로 선언 후, 각 행마다 resize가 아니라 MatrixXd로 변경
    MatrixXd total_X(total_N, nIn);
    MatrixXd total_T(total_N, nOut);
    
    MatrixXd train_X(train_N, nIn);
    MatrixXd train_T(train_N, nOut);
    
    MatrixXd test_X(test_N,nIn);
    MatrixXd test_T(test_N,nOut);
    MatrixXd predicted_T(test_N, nOut);
    //for (int i = 0; i<test_N; i++) predicted_T[i] = new int[nOut];

    
    int epochs = 1000;
    double learningRate = 0.2;

    int minibatchSize = 50;  //  number of data in each minibatch
    int minibatch_N = train_N / minibatchSize; //  number of minibatches
 
 
    //Collections.shuffle(minibatchIndex, rng);  // shuffle data index for SGD
    //
    // Training data for demo
    //   class 1 : x1 ~ N( -2.0, 1.0 ), y1 ~ N( +2.0, 1.0 )
    //   class 2 : x2 ~ N( +2.0, 1.0 ), y2 ~ N( -2.0, 1.0 )
    //   class 3 : x3 ~ N(  0.0, 1.0 ), y3 ~ N(  0.0, 1.0 )
    //

    ifstream data("mushroom2.txt");

    int label; double value;
    // data for training
    for (int i = 0; i < test_N ; i++) {
        for (int j=0; j<nIn; j++){
            data >> value;
            train_X(i,j) = value;
        }
        data >> label;
        for (int j = 0; j < nOut; j++){
            if (j == label)train_T(i, j) = 1;
            else train_T(i, j) = 0;
        }
    }
    // data for test
    for (int i = 0; i < test_N ; i++) {
        for (int j=0; j<nIn; j++){
            data >> value;
            test_X(i,j) = value;
        }
        data >> label;
        for (int j = 0; j < nOut; j++){
            if (j == label)test_T(i, j) = 1;
            else test_T(i, j) = 0;
        }
    }



    data.close();
    
    
    // minibatch for Data - Deallocation
    MatrixXd train_X_minibatch[minibatch_N];
    for (int i = 0; i < minibatch_N; i++) train_X_minibatch[i].resize(minibatchSize, nIn);

    // minibatch for label - Deallocation
    MatrixXd train_T_minibatch[minibatch_N];
    for (int i = 0; i < minibatch_N; i++) train_T_minibatch[i].resize(minibatchSize, nOut);
    
    
    // shuffle the input data
    VectorXd shuffled_train_X(train_N); //new double*[train_N];
    VectorXd shuffled_train_T(train_N); //= new int*[train_N];
    
    VectorXd MiniBatchIndex = shuffle(train_N);
    for (int i = 0; i < minibatch_N; i++){
        for (int j = 0; j < minibatchSize; j++){
            for (int k = 0; k < nIn; k++)train_X_minibatch[i](j,k) = train_X(MiniBatchIndex(i * minibatchSize + j),k);
            for (int k = 0; k < nOut; k++)train_T_minibatch[i](j,k) = train_T(MiniBatchIndex(i * minibatchSize + j),k);
        }
    }
    
    // Build Logistic Regression model
    //
    // construct logistic regression
    EigenLR classifier = EigenLR(nIn, nOut, minibatchSize);

    cout << "(nIn nOut mini)" << classifier.nIn << " " << classifier.nOut << " " << classifier.minibatchSize << "\n";
    //for (int i = 0; i < nOut; i++) {
    //    for (int j = 0; j < nIn; j++) cout << classifier.W[i][j] << "  ";
    //    cout << " W  b = " << classifier.b[i] << endl;
    //}
    
    // train
    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int batch = 0; batch < minibatch_N; batch++){
            classifier.train(train_X_minibatch[batch], train_T_minibatch[batch], minibatchSize, learningRate);
        }
        learningRate *= 0.95;
    }
    cout << "learningRate: " << learningRate << endl;
    //    for (int i = 0; i < nOut; i++) {
    //    for (int j = 0; j < nIn; j++) cout << classifier.W[i][j] << "  ";
    //    cout <<  " W  b = " << classifier.b[i] <<  endl;
    //}

    
    // test
    for (int i = 0; i < test_N; i++){
        predicted_T.row(i) = classifier.predict(test_X.row(i));
    }
    //
    // Evaluate the model
    //
    MatrixXd confusionMatrix(patterns, patterns);
    for (int i = 0; i < patterns; i++)
    for (int j = 0; j < patterns; j++)
    confusionMatrix(i,j) = 0;
    double accuracy = 0.;
    VectorXd precision(patterns);
    for (int i = 0; i < patterns; i++)precision(i) = 0;
    VectorXd recall(patterns);
    for (int i = 0; i < patterns; i++)recall(i) = 0;

    for (int i = 0; i < test_N; i++) {
        int predicted_ = 0;
        int actual_ = 0;
        for (int j = 0; j < nOut; j++){
            if (predicted_T(i,j) == 1)predicted_ = j;
            if (test_T(i,j))actual_ = j;
        }
        confusionMatrix(actual_,predicted_) += 1;
    }

    for (int i = 0; i < patterns; i++) {
        double col_ = 0.;
        double row_ = 0.;

        for (int j = 0; j < patterns; j++) {

            if (i == j) {
                accuracy += confusionMatrix(i, j);
                precision[i] += confusionMatrix(j,i);
                recall[i] += confusionMatrix(i,j);
            }

            col_ += confusionMatrix(j, i);
            row_ += confusionMatrix(i, j);
        }
        precision[i] /= col_;
        recall[i] /= row_;
    }

    accuracy /= test_N;

    cout << "------------------------------------\n";
    cout << "Logistic Regression model evaluation\n";
    cout << "------------------------------------\n";
    cout << "Accuracy: " << accuracy * 100 << "\n";
    cout << "Precision:\n";
    for (int i = 0; i < patterns; i++) {
        cout << " class "<< i+1<< ":"  << precision[i] * 100 << "\n";
    }
    cout << "Recall:\n";
    for (int i = 0; i < patterns; i++) {
        cout << " class " << i + 1 << ":" << recall[i] * 100 << "\n";
    }
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
    return 0;
}
// return an int array of random-shuffled positions
VectorXd shuffle(int N) {
    VectorXd aa(N);
    int i, left, j;

    for (i = 0; i < N; i++) aa(i) = -1;
    for (i = 0; i < N; i++) {
        left = rand() % (N - i);
        for (j = 0; j < N; j++) if (aa(j) == -1) {
            if (left == 0) break; else left--;
        }
        aa(j) = i;
    }
    
    return aa;
    
}

VectorXd Combination(int N, int R){
    VectorXd Result(N);
    for (int i = 0; i < N; i++)Result[i] = 0;
    for (int i = 0; i < R; i++){
        int get, index;
        index = rand() % N;
        while (Result(index)){
            index = rand() % N;
        }
        Result(index) = 1;
    }
    return Result;
}
*/
