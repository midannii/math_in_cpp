#include <iostream> // for cout
#include <iomanip> // for setw()
#include <cmath>
using namespace std;
#include "GDlinearFn.h"
float linearFn::dist(float a, float b, float xx, float yy) { // 각 점에서 직선에 projection한 거리
    float p;
    p = (xx + a * yy - a * b)/(1+a*a); //projection의 식이 들어가있음
    //cout << "the projection point is : (x,y) = ( " << p << ", " << b+p*a << " )" << endl;
    return (xx - p)*(xx - p) + (yy - b - p * a)*(yy - b - p * a);
}
float linearFn::f(float a, float b){//우리가 최소화하고 싶은 loss function
    float sum = 0.0;
    for (int i = 0; i < N; i++)
        sum += dist(a,b, datax[i],datay[i]);
    return sum;
}

float EE(float x0, float y0, float x1, float y1) { return sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1)); }
float linearFn::dfabda(float a, float b, float da) {
    cout << "dfabda "<< f(a + da, b) << endl;
    cout << "dfabda " << f(a, b) << endl;
    return (f(a+da,b) - f(a,b)) / da;
}
float linearFn::dfabdb(float a, float b, float db) {
    cout << "dfabdb " << f(a, b+db) << endl;
    cout << "dfabdb " << f(a, b) << endl;
    return (f(a, b+db) - f(a, b)) / db;
}

int main() {
    linearFn ab;
        // psi: learning rate
   // float psi = 0.1, eta = 0.0000001;
   // float psi = 0.001, eta = 0.0001;
    float psi = 0.1, eta = 0.0001;
    float da = 0.01, db = 0.01;
    float a0 = -4, b0 = 6;
    float a1 = 2.1, b1 = -0.8;  // answer (a, b) = (1, 1)
    //float a1 = 1.1, b1 = 80.0;  // answer (a, b) = (1.2, 100)
    int iteration = 0;
    
    while (EE(a0,b0,a1,b1)>eta && iteration < 1000) {
        a0 = a1;
        b0 = b1;
        a1 -= psi * ab.dfabda(a0, b0, da);
        b1 -= psi * ab.dfabdb(a0, b0, db);
        cout << setw(10) << a0 << setw(10) << b0 << " >> " << setw(10) << a1 << setw(10) << b1 << endl;
        iteration++;
    }
    cout << iteration << "-th  E = " << EE(a0, b0, a1, b1) << endl;
    getchar();
    return 1;
}

/*
 int main(){
     linearFn ab;
     float a0 = 2.3, b0 = 2.7;
     cout << ab.f(a0, b0) << endl;
     return 0;
 }

*/
