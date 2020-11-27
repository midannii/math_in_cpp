// Author : DougnYoung Suh
// Date on July 6, 2020

// Revised by midan sim
// Date: Sep 20, 2020

#include <iostream>
#include "bmpOld.h" // SaveBmp()
// #include "bmpNew.h"
#include <vector> 
using namespace std;

int main() {
// interlaced
    unsigned char *mybmp = new unsigned char[200*400*3];
    
// RGB of rainbow colors
    vector <vector <int>> rainbow {
        {0,0,225}, {5,89,255}, {0,225,225}, {0,225,0}, {225,0,0}, {144,0,0}, {225,0,128}
    };
    
    int color = 0;
    int temp = 0;
    for (int i = 0; i < 200*400; i++) {
        if (temp==200*50) {
            color++; temp = 0;
        }
        else temp++;
        mybmp[i * 3] = rainbow[color][0];       // B
        mybmp[i * 3 + 1] = rainbow[color][1];   // G
        mybmp[i * 3 + 2] = rainbow[color][2]; // R
    }
    
    // make a bmp image
    SaveBmp("myrainbow.bmp", mybmp, 200, 300);
    
    return 0;
}
