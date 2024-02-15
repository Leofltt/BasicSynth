/*
  ==============================================================================

    WTOscillator.h
    Created: 28 Nov 2021 2:37:56pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#pragma once

#include <cmath>

class Oscillator
{

public:
    enum Waveform
    {
        SINE,
        SAW,
        SQUARE,
        TRIANGLE
    };
    Oscillator();
    ~Oscillator();
    void setWF(int i);
    void setFreq(double freq);
    void setSR(double sr);
    void phasereset() { mPhase = 0.;};
    void process( double *buffer);
    double getNextSample();
    double oscillate(Waveform w);
private:
    double mFreq = 440.;
    double mPitchMod;
    double mPhase = 0.;
    double mPhaseInc;
    double mSamplerate = 44100.;
    Waveform mWave = SINE;
    void updatePhaseInc();
    static constexpr double mPi = M_PI;
    static constexpr double mTwoPi = 2 * mPi;
    double lastoutput = 0.;
    double polyBLEP(double t);
};
