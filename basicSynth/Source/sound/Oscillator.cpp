/*
  ==============================================================================

    WTOscillator.cpp
    Created: 28 Nov 2021 2:37:41pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#include "Oscillator.h"

Oscillator::Oscillator()
{
    
}

Oscillator::~Oscillator()
{
    
}

void Oscillator::setFreq(double freq)
{
    if (freq != mFreq)
    {
        mFreq = freq;
        updatePhaseInc();
    }
}

void Oscillator::setSR(double sr)
{
    if (sr != mSamplerate)
    {
        mSamplerate = sr;
        updatePhaseInc();
    }
}

void Oscillator::setWF(int i)
{
    switch (i)
    {
        case 0:
            mWave = SINE;
            break;
        case 1:
            mWave = SAW;
            break;
        case 2:
            mWave = SQUARE;
            break;
        case 3:
            mWave = TRIANGLE;
            break;
        default:
            mWave = SINE;
    }
        
}

double Oscillator::oscillate(Waveform w)
{
    double value;
    switch (w)
    {
        case SINE:
            value = sin(mPhase);
            break;
        case SAW:
            value = (2.0 * mPhase / mTwoPi) - 1.0;
            break;
        case SQUARE:
            if (mPhase < mTwoPi) {
                value = 1.0;
            } else {
                value = -1.0;
            }
            break;
        case TRIANGLE:
            value = -1.0 + (2.0 * mPhase / mTwoPi);
            value = 2.0 * (fabs(value) - 0.5);
            break;
        default:
            value = sin(mPhase);
            break;
    }
    return value;
}

double Oscillator::polyBLEP(double t)
{
    double dt = mPhaseInc / mTwoPi;
    // 0 <= t < 1 : beginning of sample period
    if (t < dt) {
        t /= dt;
        return t+t - t*t - 1.0;
    }
    // -1 < t < 0 : right before the end of a sample period
    else if (t > 1.0 - dt) {
        t = (t - 1.0) / dt;
        return t*t + t+t + 1.0;
    }
    // 0 otherwise
    else return 0.0;
}

double Oscillator::getNextSample() {
    double value = 0;
    double t = mPhaseInc / mTwoPi;
    
    if (mWave == SINE)
    {
        value = oscillate(SINE);
    }
    else if (mWave == SAW)
    {
        value = oscillate(SAW);
        value -= polyBLEP(t);
    }
    else
    {
        value = oscillate(SQUARE);
        value += polyBLEP(t);
        value -= polyBLEP(fmod(t + 0.5, 1.0));
        if (mWave == TRIANGLE)
        {
            // Leaky integrator: y[n] = A * x[n] + (1 - A) * y[n-1]
            value = mPhaseInc * value + (1 - mPhaseInc) * lastoutput;
            lastoutput = value;
        }
    }
    mPhase += mPhaseInc;
    while (mPhase >= mTwoPi)
    {
        mPhase -= mTwoPi;
    }
    return value;
}

void Oscillator::updatePhaseInc() {
    double pitchModAsFrequency = pow(2.0, fabs(mPitchMod) * 14.0) - 1;
    if (mPitchMod < 0) {
        pitchModAsFrequency = -pitchModAsFrequency;
    }
    double frequency = fmin(fmax(mFreq + pitchModAsFrequency, 0), mSamplerate/2.0);
    mPhaseInc = frequency * 2 * mPi / mSamplerate;
}
