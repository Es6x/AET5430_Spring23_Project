/*
  ==============================================================================

    Modulator.cpp
    Created: 19 Apr 2023 10:15:46pm
    Author:  Evan Kramer

  ==============================================================================
*/

#include "Modulator.h"


float Modulator::processSample(float x, const int c){
    
    // LFO (modulator)
    float m = sin(currentAngle[c]);
    
    float y = x * m;
    
    // Update currentAngle for the next sample
    updateCurrentAngle(c);
    
    return y;
}


void Modulator::setRate(float freqHz){
    
    angleChange = freqHz * piX2 / Fs;
}

//void Modulator::setDepth(float depth){
//    // note: depth is from 0-1
//    lfoAmp = depth / 2.f;
//    lfoOffset = 1.f - lfoAmp;
//    
//}


void Modulator::prepareToPlay(float sampleRate){
    Fs = sampleRate;
}


void Modulator::updateCurrentAngle(const int c){
    currentAngle[c] += angleChange;
    if (currentAngle[c] > piX2){
        currentAngle[c] -= piX2;
    }
}
