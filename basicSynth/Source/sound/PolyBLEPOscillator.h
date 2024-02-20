/*
  ==============================================================================

    PolyBLEPOscillator.h
    Created: 28 Nov 2021 2:37:56pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#pragma once

#include <cmath>

class PolyBLEPOscillator
{

public:
    enum Waveform
    {
        SINE,
        SAW,
        SQUARE,
        TRIANGLE,
        COSINE,
        RAMP,
        RECTANGLE
    };
    PolyBLEPOscillator();
    virtual ~PolyBLEPOscillator();
    void setWF(int i);
    void setFreq(double freq);
    void setSR(double sr);
    void setPulseWidth(double pw);
    void phasereset() { mPhase = 0.;};
    void process( double *buffer);
    double getNextSample();
    void sync(double phase);

private:
    double mFreq = 440.;
    double mPitchMod;
    double mPhase = 0.;
    double mPulseWidth = 0.5;
    double mPhaseInc;
    double mSamplerate = 44100.;
    Waveform mWave = SINE;
    
    void updatePhaseInc();
    
    void inc();
    
    static constexpr double mPi = M_PI;
    static constexpr double mTwoPi = 2 * mPi;
    
    double lastoutput = 0.;
    double polyBLEP(double t);

    double sinOsc();
    double cosOsc();
    double triOsc();
    double sawOsc();
    double sqrOsc();
    double rectOsc();
    double rampOsc();

};
