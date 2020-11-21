#include <iostream>
#include <fstream>
#include <random>
using namespace std;
#include "perceptron.h"
// extra assigment
//
#define train_N  5688  // number of training data (8124 * 0.7)
#define test_N   2436   // number of test data (8124 * 0.3)
#define nIn  23       // dimensions of input data
// Declare (Prepare) variables and constants for perceptrons
double train_X[train_N][nIn];  // input data for training
int train_T[train_N];               // output data (label) for training
double test_X[test_N][nIn];  // input data for test
int test_T[test_N];               // label of inputs
void get_data();
int * shuffle(int N);
int main() {
        //
        int predicted_T[test_N];          // output data predicted by the model
        int * shuffled = shuffle(train_N);
        int epochs = 3000;   // maximum training epochs
        double learningRate = 1.;  // learning rate can be 1 in perceptrons
        // Create training data and test data for demo.
        get_data();
        // Build SingleLayerNeuralNetworks model
        int epoch = 0;  // training epochs
                        // construct perceptrons
        Perceptrons classifier(nIn);
        // train models
        while (true) {
            int classified_ = 0;
            for (int i = 0; i < train_N; i++) {
                classified_ += classifier.train(train_X[shuffled[i]], train_T[shuffled[i]], learningRate);
            }
            if (classified_ == train_N) break;  // when all data classified correctly
            epoch++;
            if (epoch > epochs) break;
        }
        std::cout << "iteration " << epoch << " of " << epochs << endl;
        std::cout << "w " ;
        for (int i=0; i<nIn; i++) std::cout << classifier.w[i] << " " ;
        std::cout << endl;
        // test
        for (int i = 0; i < test_N; i++) {
            predicted_T[i] = classifier.predict(test_X[i]);
        }
        //
        // Evaluate the model
        //
        int confusionMatrix[2][2];
        double accuracy = 0.;
        double precision = 0.;
        double recall = 0.;
        // Javaø°º≠¥¬ √ ±‚∞™¿Ã 0¿∏∑Œ µ«æÓ¿÷¿∏≥™ C++ø°º≠¥¬ ¡§«ÿ¡÷æÓæﬂ«‘
        confusionMatrix[0][0] = confusionMatrix[0][1] = confusionMatrix[1][0] = confusionMatrix[1][1] = 0;
        for (int i = 0; i < test_N; i++) {

            if (predicted_T[i] > 0) {
                if (test_T[i] > 0) {
                    accuracy += 1;
                    precision += 1;
                    recall += 1;
                    confusionMatrix[0][0] += 1;
                }
                else {
                    confusionMatrix[1][0] += 1;
                }
            }
            else {
                if (test_T[i] > 0) {
                    confusionMatrix[0][1] += 1;
                }
                else {
                    accuracy += 1;
                    confusionMatrix[1][1] += 1;
                }
            }
        }
        accuracy /= test_N;
        precision /= confusionMatrix[0][0] + confusionMatrix[1][0];
        recall /= confusionMatrix[0][0] + confusionMatrix[0][1];


        std::cout << " confusion" << endl;
        std::cout << confusionMatrix[0][0] << " " << confusionMatrix[0][1] << " " << endl;
        std::cout << confusionMatrix[1][0] << " " << confusionMatrix[1][1] << " " << endl;
        
        std::cout << "----------------------------" << endl;
        std::cout << "Perceptrons model evaluation" << endl;
        std::cout << "----------------------------" << endl;
        std::cout << "Accuracy:  "<< accuracy * 100 << endl;
        std::cout << "Precision: "<< precision * 100 << endl;
        std::cout << "Recall: "<< recall * 100 << endl;

    return 0;
}

// read mushroom data
void get_data() {
    ifstream data("mushroom2.txt"); /* dataset from https://www.kaggle.com/uciml/mushroom-classification */
    if (!data) std::cout << " no input file \n";
    int it;
    int patterns = 3;
    for (int k = 0; k<patterns; k++) {
        int m = k * 1896;
        for (int i = 0; i < 1896; i++, m++) {
            data >> it;  // it = 0, or 1
            data >> train_X[m][0] >> train_X[m][1] >> train_X[m][2] >> train_X[m][3] >> train_X[m][4] >> train_X[m][5] >> train_X[m][6] >> train_X[m][7] >> train_X[m][8] >> train_X[m][9] >> train_X[m][10] >> train_X[m][11] >> train_X[m][12] >> train_X[m][13] >> train_X[m][14] >> train_X[m][15] >> train_X[m][16] >> train_X[m][17] >> train_X[m][18] >> train_X[m][19] >> train_X[m][20] >> train_X[m][21];
            if (it == 0) train_T[m] = -1; else train_T[m] = 1;
        }
        m = k * 812;
        for (int i = 0; i < 812; i++, m++) {
            data >> it;
            data >> test_X[m][0] >> test_X[m][1] >> test_X[m][2] >> test_X[m][3] >> test_X[m][4] >> test_X[m][5] >> test_X[m][6] >> test_X[m][7] >> test_X[m][8] >> test_X[m][9] >> test_X[m][10] >> test_X[m][11] >> test_X[m][12] >> test_X[m][13] >> test_X[m][14] >> test_X[m][15] >> test_X[m][16] >> test_X[m][17] >> test_X[m][18] >> test_X[m][19] >> test_X[m][20] >> test_X[m][21];
            if (it == 0) test_T[m] = -1; else test_T[m] = 1;
        }
    }
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
