/*
  ==============================================================================

    Modulator.h
    Created: 19 Apr 2023 10:15:45pm
    Author:  Evan Kramer

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Modulator {
    
public:
    
    float processSample(float x, const int c);
    
    void setRate(float freqHz);
    
    void prepareToPlay(float sampleRate);
    
    void setModWaveSelection(int waveChoice);
    
private:
    
    float currentAngle[2] = {0.f}; // in radians, one angle for left and right
    
    float angleChange = 0.f;
    
//    float lfoAmp = 0.5f;
//    float lfoOffset = 0.5f;
    
    float Fs = 44100.f;
    
    float piX2 = (float) (M_PI * 2.f);
    
    void updateCurrentAngle(const int c);
    
    int waveType;
    
};
