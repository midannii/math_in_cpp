// Author : DougnYoung Suh
// Date on July 6, 2020
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
    
    short *data;
    int n = myHeader.sampleRate *11; // 총 11초동안 재생: 44100 x 11 초
    data = new short[n * myHeader.numChannels];
    float sec = (float)(myHeader.sampleRate);
    float dt = 1. / sec; // fs = 44100
    // 필요한 음: 레, 레(#), 미, 솔, 라
    float f1 = 293.66, f2 = 311.13, f3 = 329.63, f4 =392., f5 = 440. ;
    float A = 10000.0 ;
    
    // 5마디 * 4박 = 11초 이므로, 4분음표 하나에 0.55초, 8분음표는 0.275초, 16분음표는 0.1375초
    
    // 1) 레솔레솔레솔레솔 :8분음표 7개 + 4분음표 1개 (
    for (int i = 0; i < 0.275; i++) { // 레
        float t = i*dt*0.275;
        data[i] = (short)(A * cos(2.*PI*f1*t));
    }
    cout << "레" << endl;
    for (int j=0.275; j<=1.925; j+=0.55){
        for (int i = 0; i < 0.275; i++) { // 솔
            float t = i*dt*0.275;
            data[i+j] = (short)(A * cos(2.*PI*f4*t));
        }
        cout << "솔" << endl;
        for (int i = 0.275; i < 0.55; i++) { // 레
            float t = i*dt*0.275;
            data[i+j] = (short)(A * cos(2.*PI*f1*t));
        }
        cout << "레" << endl;
    }
    for (int i = 1.925; i < 2.475; i++) { // 솔
        float t = i*dt*0.55;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl;
    
    // 2) 솔솔솔라 미미미미레(#)레: 4분음표 3개 + 점8분음표 1개 + 16분음표 3개 + 8분음표 3개
    for (int i = 2.475; i < 4.125; i++) { // 솔
            float t = i*dt*0.55;
            data[i] = (short)(A * cos(2.*PI*f4*t));
        }
        cout << "솔" << endl;
    
    for (int i = 4.125; i < 4.5375; i++) { // 라
        float t = i*dt*0.4125;
        data[i] = (short)(A * cos(2.*PI*f5*t));
    }
    cout << "라" << endl;
    
    for (int i = 4.5375; i < 4.95; i++) { // 미
        float t = i*dt*0.1375;
        data[i] = (short)(A * cos(2.*PI*f3*t));
    }
    cout << "미" << endl;
    
    for (int i = 4.5375; i < 5.0875; i++) { // 미
        float t = i*dt*0.275;
        data[i] = (short)(A * cos(2.*PI*f3*t));
    }
    cout << "미" << endl;
    
    for (int i = 5.0875; i < 5.6375; i++) { // 레
        float t = i*dt*0.275;
        data[i] = (short)(A * cos(2.*PI*f1*t));
    }
    cout << "레" << endl;
    
    for (int i = 5.6375; i < 6.2075; i++)
        data[i] = 0;
    cout << "쉼표" << endl;
    
    
    // 3) 솔솔솔라 레솔레솔레솔레솔: 4분음표 3개 + 8분음표 8개 + 4분음표 1개
    for (int n=6.2075; n<7.8575; n++){
        for (int i = 0; i < n; i++) { // 솔
            float t = i*dt*0.55;
            data[i] = (short)(A * cos(2.*PI*f4*t));
        }
        cout << "솔" << endl;
    }
    for (int n=7.8575; n<8.1325; n++){
        for (int i = 0; i < n; i++) { // 라
            float t = i*dt*0.275;
            data[i] = (short)(A * cos(2.*PI*f5*t));
        }
        cout << "라" << endl;
    }
    
    for (int i = 8.1325; i < 8.4075; i++) { // 레
        float t = i*dt*0.275;
        data[i] = (short)(A * cos(2.*PI*f1*t));
    }
    cout << "레" << endl;
    
    for (int j=8.4075; j<=10.0575; j+=0.55){
        for (int i = 0; i < 0.275; i++) { // 솔
            float t = i*dt*0.275;
            data[i+j] = (short)(A * cos(2.*PI*f4*t));
        }
        cout << "솔" << endl;
        for (int i = 0.275; i < 0.55; i++) { // 레
            float t = i*dt*0.275;
            data[i+j] = (short)(A * cos(2.*PI*f1*t));
        }
        cout << "레" << endl;
    }
    
    for (int i = 10.0575; i < 11.; i++) { // 솔
        float t = i*dt*0.55;
        data[i] = (short)(A * cos(2.*PI*f4*t));
    }
    cout << "솔" << endl << endl;
    
    cout << "Let's record now " << endl;
    // 파일 저장
    ofstream mywave("dolphin.wav", ios::binary | ios::out);
    mywave.write((char*)&myHeader, sizeof(waveHeader));
    mywave.write((char*)data, sizeof(short) * n * (myHeader.numChannels));
    mywave.close();
    getchar();
    cout << "ended! "<< endl;

    return 1;
}


