
#include <iostream>
#include "bmpOld.h"
#include <vector>
using namespace std;

int main() {
// interlaced
    unsigned char *mybmp = new unsigned char[200*400*3];
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



/*
int main() {
    // interlaced
    unsigned char *mybmp = new unsigned char[200*300*3];
    int red = -1;
    for (int i = 0; i < 60000; i++) {
        if (i%200==0 and red!=255) red++;
        mybmp[i * 3] = 0;       // B
        mybmp[i * 3 + 1] = 0;   // G
        mybmp[i * 3 + 2] = red; // R
    }
    // make a bmp image
    SaveBmp("mybmp.bmp", mybmp, 200, 300);
    // read a bmp image
    int x, y;
    // return raw image pointer
    unsigned char *bmpB = ReadBmp("sunflower.bmp", &x, &y); // 24bits bmp
    if (!bmpB) {
        std::cout << " cannot find image file" << std::endl;
        return 666;
    }
    unsigned char *newbmp = new unsigned char[x*y*3];
    // 격자무늬 만들기
    for (int i=0; i<x*y; i++){
        if (i%2 == 0){
            newbmp[i*3] = 0;
            newbmp[i*3+1] = 0;
            newbmp[i*3+2] = 0;
        }
        else{
            newbmp[i*3] = bmpB[i*3];
            newbmp[i*3+1] = bmpB[i*3+1];
            newbmp[i*3+2] = bmpB[i*3+2];
        }
    }
    SaveBmp("newsunflower.bmp", newbmp, x, y);
    return 0;
}

*/
