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

/*
 int main() {
     float A[6] = {1,2,3,4,5,6};
     float B[4] = {1,2,3,4};
     float C[6];
     cout<< "sprint 1 >> " << endl;
     showmatrix(2,3,A);
     cout << endl;
     showmatrix(3,2,A);
     cout<< endl << "sprint 2 >> " << endl;
     matrixmult(3,2,2,A,B,C);
     showmatrix(2, 2, C);
     
     return 0;
 }
 */


/*
 int main(){
     float C[16] = { 0.5, 0.5, 0.5, 0.5,
                   0.5, 0.5, -0.5, -0.5,
                   0.5, -0.5, -0.5, 0.5,
                   0.5, -0.5, 0.5, -0.5}; // 4X4
     float *c0, *c1, *c2, *c3;
     c0 = C; c1= C+4; c2 = C+8; c3 = C+12;
     float delta[16];
     cout << "sprint 3 >>" << endl;
     matrixmult(1, 4, 1, c0, c0, delta);
     cout << delta[0] << endl;
     matrixmult(1, 4, 1, c0, c1, delta+1);
     cout << delta[1] << endl;
     cout << "sprint 4 >>" << endl;
     float tC[16], i4[16];
     transpose(4, 4, C, tC);
     matrixmult(4, 4, 4, C, tC, i4);
     showmatrix(4, 4, i4);
     return 0;
 }
 */


/*
 int main(){
     float C[16] = { 0.5, 0.5, 0.5, 0.5,
                   0.5, 0.5, -0.5, -0.5,
                   0.5, -0.5, -0.5, 0.5,
                   0.5, -0.5, 0.5, -0.5}; // 4X4
     float A1[4], A2[4], A3[4];
     float a1[4] = {100, 120, -4, 2};
     float a2[4] = {100, 20, 120, 32};
     float a3[4] = {10, 120, 108, 8};
     cout << "sprint 5 >>" << endl;
     matrixmult(4, 4, 1, C, a1, A1);
     cout << "for (100, 120, -4, 2): " ;
     showmatrix(4, 1, A1);
     cout << "for (100, 20, 120, 32): " ;
     matrixmult(4, 4, 1, C, a2, A2);
     showmatrix(4, 1, A2);
     cout << "for (10, 120, 108, 28): " ;
     matrixmult(4, 4, 1, C, a3, A3);
     showmatrix(4, 1, A3);
     cout << "sprint 6 >>" << endl;
     float CT[16], result1[16], result2[16], result3[16];
     transpose(4, 4, C, CT);
     cout << "for A1: " ;
     matrixmult(4, 4, 1, CT, A1, result1);
     showmatrix(4, 1, result1);
     cout << "for A2: " ;
     matrixmult(4, 4, 1, CT, A2, result2);
     showmatrix(4, 1, result2);
     cout << "for A3: " ;
     matrixmult(4, 4, 1, CT, A3, result3);
     showmatrix(4, 1, result3);
     return 0;
 }
 */


/*
 int main(){
     float C[16] = { 0.5, 0.5, 0.5, 0.5,
                   0.5, 0.5, -0.5, -0.5,
                   0.5, -0.5, -0.5, 0.5,
                   0.5, -0.5, 0.5, -0.5}; // 4X4
     float A1[4], A2[4], A3[4];
     float a1[4] = {100, 120, -4, 2};
     float a2[4] = {100, 20, 120, 32};
     float a3[4] = {10, 120, 108, 8};
     cout << "sprint 7 >>" << endl;
     matrixmult(4, 4, 1, C, a1, A1);
     matrixmult(4, 4, 1, C, a2, A2);
     matrixmult(4, 4, 1, C, a3, A3);
     A1[2] = A1[3] = 0;
     A2[1] = A2[2] = 0;
     A3[1] = A3[3] = 0;
     float CT[16], result1[16], result2[16], result3[16];
     transpose(4, 4, C, CT);
     cout << "for A1: " ;
     matrixmult(4, 4, 1, CT, A1, result1);
     showmatrix(4, 1, result1);
     cout << "for A2: " ;
     matrixmult(4, 4, 1, CT, A2, result2);
     showmatrix(4, 1, result2);
     cout << "for A3: " ;
     matrixmult(4, 4, 1, CT, A3, result3);
     showmatrix(4, 1, result3);
     return 0;
 }
 */


/*
 int main(){
     float C[16] = { 0.5, 0.5, 0.5, 0.5,
                   0.5, 0.5, -0.5, -0.5,
                   0.5, -0.5, -0.5, 0.5,
                   0.5, -0.5, 0.5, -0.5}; // 4X4
     float A1[4], A2[4], A3[4];
     float a1[4] = {100, 120, -4, 2};
     float a2[4] = {100, 20, 120, 32};
     float a3[4] = {10, 120, 108, 8};
     matrixmult(4, 4, 1, C, a1, A1);
     matrixmult(4, 4, 1, C, a2, A2);
     matrixmult(4, 4, 1, C, a3, A3);
     cout << "sprint 8 >>" << endl;
     //    binary file write/read
     ofstream xx("dat.wav", ios::out | ios::binary);
     if (!xx) {
         cout << " can't open dat.wav \n";
         return 777;
     }
     xx.write((char*)A1, 4 * sizeof(float));
     xx.write((char*)A2, 4 * sizeof(float));
     xx.write((char*)A3, 4 * sizeof(float));
     xx.close();
     
     cout << "sprint 9 >>" << endl;
     float AA[4];
     ifstream yy("dat.wav", ios::in | ios::binary);
     if (!yy) {
         cout << " can't open dat.bin \n";
         return 666;
     }
     yy.read((char*)AA, 4 * sizeof(float));
     yy.close();
     showmatrix(4, 1, AA);
     float CT[16];
     transpose(4, 4, C, CT);
     float aa[4];
     matrixmult(4, 4, 1, CT, A1, aa);
     showmatrix(4, 1, aa);
     matrixmult(4, 4, 1, CT, A2, aa);
     showmatrix(4, 1, aa);
     matrixmult(4, 4, 1, CT, A3, aa);
     showmatrix(4, 1, aa);
     return 0;
 }

 */

/*
 int main () {
     float c0[8] = {1,1,1,1,1,1,1,1};
     float c1[8] = {1,1,1,1,-1,-1,-1,-1};
     float c2[8] = {1,1,-1,-1,-1,-1,1,1};
     float c3[8] = {1,-1,1,-1,1,-1,1,-1};
     float c4[8], c5[8] , c6[8] ,c7[8];
     dotproduct(8, c0, c1);  dotproduct(8, c0, c2); dotproduct(8, c0, c3);
     dotproduct(8, c1, c2);  dotproduct(8, c1, c3); dotproduct(8, c2, c3);
     cout << "Are they orthonormal? " << endl;
     normal(8, c0); normal(8, c1); normal(8, c2); normal(8, c3);
     return 0;
 }
 */
