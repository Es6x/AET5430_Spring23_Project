/*
  ==============================================================================

    MyOscillator.cpp
    Created: 19 Apr 2023 12:43:11am
    Author:  Evan Kramer

  ==============================================================================
*/

#include "MyOscillator.h"

void MyOscillator::setModWaveSelection(int wave){
    choice = wave-1;
    switch(choice){
        case 0:
            //sine wave
            initialise([](float x) {return std::sin(x); });
            break;
            
        case 1:
            //square wave
            initialise([](float x) {return x / juce::MathConstants<float>::pi;});
            break;
            
        case 2:
            //saw wave
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
            break;
            
        default:
            //jassertfalse;
            break;
    }
}
    


