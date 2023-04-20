/*
  ==============================================================================

    Modulator.cpp
    Created: 19 Apr 2023 10:15:46pm
    Author:  Evan Kramer

  ==============================================================================
*/

#include "Modulator.h"


float Modulator::processSample(float x, const int c){
    
    float wavevalue;
    
    switch (waveType) {
        case 0:{ //sine wave
            wavevalue = sin(currentAngle[c]);
            break;
        }
        case 1:{ //square wave
            if (currentAngle[c] < M_PI){
                wavevalue = 1.f;
            }
                else{
                wavevalue = -1.f;
            }
            break;
        }
            
//        case 2:{
//            if (currentAngle[c] < M_PI/2)
//                {
//                    wavevalue = 2 * currentAngle[c];
//                }
//            else if (currentAngle[c] < M_PI)
//                {
//                    wavevalue = 2 * currentAngle[c] - 2.f;
//                }
//            else if (currentAngle[c] < 3*M_PI/4){
//                wavevalue = 0;
//            }
//            else
//                wavevalue = 0;
//            break;
//        }
    }
    
    //modulate the sample by the respective value in the selected wave
    float y = x * wavevalue;
    
    // Update currentAngle for the next sample
    updateCurrentAngle(c);
    
    return y;
}

void Modulator::setRate(float freqHz){
    
    angleChange = freqHz * piX2 / Fs;
}

void Modulator::prepareToPlay(float sampleRate){
    Fs = sampleRate;
}

void Modulator::updateCurrentAngle(const int c){
    currentAngle[c] += angleChange;
    if (currentAngle[c] > piX2){
        currentAngle[c] -= piX2;
    }
}

void Modulator::setModWaveSelection(int waveChoice){
    
    waveType = waveChoice-1;
}
