#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
void showmatrix(int m, int n, float*);
void matrixmult(int M, int N, int K, float* a, float* b, float* c);
void transpose(int m, int n, float*, float*);
void dotproduct(int m, float* ,float*);
void normal(int m, float*);

int main () {
    float *C = new float[64];
    float c0[8] = {1,1,1,1,1,1,1,1}; float c1[8] = {1,-1,1,-1,1,-1,1,-1};
    float c2[8] = {1, 1, -1, -1, 1, 1, -1, -1}; float c3[8] = {1, -1, -1, 1, 1, -1, -1, 1};
    float c4[8] = {1,1,1,1,1,1,1,1}; float c5[8] = {1,-1,1,-1,1,-1,1,-1};
    float c6[8] = {1, 1, -1, -1, 1, 1, -1, -1}; float c7[8] =  {1, -1, -1, 1, 1, -1, -1, 1};
    for (int i=0; i<64; i++){
        if (i/8 == 0) C[i] = c0[i]/sqrt(8);
        else if (i/8 == 1) C[i] = c1[i-8*1]/sqrt(8);
        else if (i/8 == 2) C[i] = c2[i-8*2]/sqrt(8);
        else if (i/8 == 3) C[i] = c3[i-8*3]/sqrt(8);
        else if (i/8 == 4) C[i] = c4[i-8*4]/sqrt(8);
        else if (i/8 == 5) C[i] = c5[i-8*5]/sqrt(8);
        else if (i/8 == 6) C[i] = c6[i-8*6]/sqrt(8);
        else if (i/8 == 7) C[i] = c7[i-8*7]/sqrt(8);
    }
    float CT[64], result[64];
    transpose(8, 8, C, CT); matrixmult(8, 8, 8, C, CT, result);
    cout << "check transpose of C" << endl;
    showmatrix(8, 8, CT);
    cout << "find identity matrix ?" << endl;
    showmatrix(8, 8, result);
    delete[] C;
    return 0;
}


void dotproduct(int m, float* a, float* b){
    float result = 0;
    for (int i=0; i<m; i++)  result+= a[i] * b[i];
    if (result ==0)
        cout << " They are orthogonal " << endl;
    else{
        cout << "They are not orthogonal : dot product is " << result << endl;
    }
}

void normal(int m, float* a){
    float result = 0;
    for (int i=0; i<m; i++)  result+= a[i] * a[i] ;
    if (result ==1)
        cout << " They are normal " << endl;
    else{
        cout << "They are not normal : dot product is " << result << endl;
    }
}


void showmatrix(int m, int n, float* a) {
    int ii = 0;
    for (int i = 0; i < n; i++, ii += m) {
        for (int j=0; j < m; j++)  {
            cout << setw(10) << a[ii + j];
        }
        cout << endl;
    }
}
void matrixmult(int M, int N, int K, float* a, float* b, float* c) {
    for (int m = 0; m < M; m++) {
        for (int k = 0; k < K; k++) {
            float sum = 0;
            for (int n = 0; n < N; n++) sum += a[m * N + n] * b[n * K + k];
            c[m * K + k] = sum;
        }
    }
}

void transpose(int m, int n, float*a, float*at){
    int ii = 0;
    for (int i = 0; i < m; i++, ii += n) {
        for (int j = 0; j < n; j++) {
            at[j*m+i] = a[ii + j];
        }
    }
}
