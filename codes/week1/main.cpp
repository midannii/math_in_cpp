// Author : DougnYoung Suh
// Date on July 6, 2020

// Revised by midan sim
// Date: Sep 9, 2020
#include <iostream>
#include <fstream>
#include <cmath> // sin( )
#define PI 3.141592
using namespace std;

class waveHeader {
public:
    waveHeader() {};
    int chunkID, chunkSize, Format, subChunkID, subChunk1size;
    short    audioFormat, numChannels;
    int sampleRate, byteRate;
    short blockAlign, bitsPerSample;
    int subChunk2ID, subChunk2size;
};

int main() {
    // Beatles.wav 읽기
    ifstream xx("./Beatles.wav", ios::binary | ios::in);
    if (!xx) return 999; // 종료
    waveHeader myHeader;
    xx.read((char*)&myHeader, sizeof(waveHeader)); //44100(1초)
    myHeader.numChannels = 1;
    xx.close();
    cout << "Let's start !" << endl;
    short *data;
    int n = myHeader.sampleRate *12; // 총 11초동안 재생: 44100 x 11 초
    data = new short[n * myHeader.numChannels];
    float sec = (float)(myHeader.sampleRate);
    float dt = 1. / sec; // fs = 44100
    // 필요한 음: 레, 레(#), 미, 솔, 라
    float f1 = 587.33, f2 = 622.25, f3 = 659.26, f4 =783.99, f5 = 880. ;
    float A = 10000.0 ;
    
    
    // int여야 하니까 16분음표는 0.15, 8분음표는 0.3, 점 8분음표는 0.45, 4분음표는 0.6초로 하자 ! 그러면 총 12초!
    cout << "Let's playing !" << endl;
    // 1) 레솔레솔레솔레솔 :8분음표 7개 + 4분음표 1개 (
    for (int i = 0; i < myHeader.sampleRate *0.3; i++) { // 레
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f1*t));
        //cout << i << endl;
    }
    cout << "레" << endl;
        for (int i = myHeader.sampleRate *0.3; i < myHeader.sampleRate * 0.6; i++) { // 솔
            float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f4*t));
        }
        cout << "솔" << endl;
        for (int i = myHeader.sampleRate * 0.6; i < myHeader.sampleRate *0.9; i++) { // 레
            float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f1*t));
        }
        cout << "레" << endl;
    
    for (int i = myHeader.sampleRate *0.9; i < myHeader.sampleRate*1.2; i++) { // 솔
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    for (int i = myHeader.sampleRate*1.2; i < myHeader.sampleRate *1.5; i++) { // 레
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f1*t));
    }
    cout << "레" << endl;
    
    for (int i = myHeader.sampleRate *1.5; i < myHeader.sampleRate * 1.8; i++) { // 솔
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    for (int i = myHeader.sampleRate * 1.8; i < myHeader.sampleRate *2.1; i++) { // 레
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f1*t));
    }
    cout << "레" << endl;
    for (int i = myHeader.sampleRate *2.1; i < myHeader.sampleRate *2.3; i++) { // 솔
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    
    
    
    
    // 2) 솔솔솔라 미미미미레(#)레: 4분음표 3개 + 점8분음표 1개 + 16분음표 3개 + 8분음표 3개
    for (int i = myHeader.sampleRate *2.6; i < myHeader.sampleRate *3.1; i++) { // 솔
        float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    
    for (int i = myHeader.sampleRate *3.2; i < myHeader.sampleRate *3.7; i++) { // 솔
        float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    
    for (int i = myHeader.sampleRate *3.8; i < myHeader.sampleRate *4.3; i++) { // 솔
        float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    
    for (int i = myHeader.sampleRate *4.3; i < myHeader.sampleRate *4.75; i++) { // 라
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f5*t));
    }
    cout << "라" << endl;
    
    for (int i = myHeader.sampleRate *4.75; i < myHeader.sampleRate *4.9; i++) { // 미
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f3*t));
    }
    cout << "미" << endl;
    
    for (int i = myHeader.sampleRate *5.; i < myHeader.sampleRate *5.15; i++) { // 미
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f3*t));
    }
    cout << "미" << endl;
    for (int i = myHeader.sampleRate *5.25; i < myHeader.sampleRate *5.4; i++) { // 미
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f3*t));
    }
    cout << "미" << endl;
    for (int i = myHeader.sampleRate *5.5; i < myHeader.sampleRate *5.65; i++){ // 미
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f3*t));
    }
    cout << "미" << endl;
    for (int i = myHeader.sampleRate *5.75; i < myHeader.sampleRate *6.05; i++) { // 레
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f2*t));
    }
    cout << "레#" << endl;
    
    for (int i = myHeader.sampleRate *6.05; i < myHeader.sampleRate *6.35; i++) { // 레
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f1*t));
    }
    cout << "레" << endl;

    
    // int여야 하니까 16분음표는 0.15, 8분음표는 0.3, 점 8분음표는 0.45, 4분음표는 0.6초로 하자 !
    // 3) 솔솔솔라 레솔레솔레솔레솔: 4분음표 3개 + 8분음표 8개 + 4분음표 1개
    for (int i = myHeader.sampleRate* 6.95; i < myHeader.sampleRate *7.45; i++) { // 솔
            float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f4*t));
        }
        cout << "솔" << endl;
    for (int i = myHeader.sampleRate*7.55; i <myHeader.sampleRate* 8.05; i++) { // 솔
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    for (int i = myHeader.sampleRate*8.15; i < myHeader.sampleRate*8.65; i++) { // 솔
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;

    for (int i = myHeader.sampleRate*8.65; i < myHeader.sampleRate*8.95; i++) { // 라
            float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f5*t));
        }
        cout << "라" << endl;
    
    for (int i = myHeader.sampleRate*8.95; i < myHeader.sampleRate *9.25; i++) { // 레
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f1*t));
        //cout << i << endl;
    }
    cout << "레" << endl;
    for (int i = myHeader.sampleRate *9.25; i < myHeader.sampleRate * 9.55; i++) { // 솔
            float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f4*t));
        }
        cout << "솔" << endl;
    for (int i = myHeader.sampleRate * 9.55; i < myHeader.sampleRate *9.85; i++) { // 레
            float t = i*dt;
            data[i] = (short)(A * cos(2.*PI*f1*t));
        }
        cout << "레" << endl;
    
    for (int i = myHeader.sampleRate * 9.85; i < myHeader.sampleRate*10.15; i++) { // 솔
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    for (int i = myHeader.sampleRate*10.15; i < myHeader.sampleRate *10.45; i++) { // 레
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f1*t));
    }
    cout << "레" << endl;
    
    for (int i = myHeader.sampleRate *10.45; i < myHeader.sampleRate * 10.75; i++) { // 솔
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    for (int i = myHeader.sampleRate * 10.75; i < myHeader.sampleRate *11.05; i++) { // 레
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f1*t));
    }
    cout << "레" << endl;
    for (int i = myHeader.sampleRate *11.05; i < myHeader.sampleRate *11.65; i++) { // 솔
        float t = i*dt;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    
    
    cout << "Let's record now " << endl;
    // 파일 저장
    ofstream mywave("Dolphin2.wav", ios::binary | ios::out);
    mywave.write((char*)&myHeader, sizeof(waveHeader));
    mywave.write((char*)data, sizeof(short) * n * (myHeader.numChannels));
    mywave.close();
    getchar();
    cout << "ended! "<< endl;

    return 1;
}


