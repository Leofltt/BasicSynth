/*
  ==============================================================================

    PolyBLEPOscillator.cpp
    Created: 28 Nov 2021 2:37:41pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#include "PolyBLEPOscillator.h"

template<typename T>
inline int64_t bitwiseOrZero(const T &t) {
    return static_cast<int64_t>(t) | 0;
}

template<typename T>
inline T square_number(const T &x) {
    return x * x;
}

double PolyBLEPOscillator::polyBLEP(double t) {
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


// Adapted from "Phaseshaping Oscillator Algorithms for Musical Sound
// Synthesis" by Jari Kleimola, Victor Lazzarini, Joseph Timoney, and Vesa
// Valimaki.
// http://www.acoustics.hut.fi/publications/papers/smc2010-phaseshaping/
inline double blep(double t, double dt) {
    if (t < dt) {
        return -square_number(t / dt - 1);
    } else if (t > 1 - dt) {
        return square_number((t - 1) / dt + 1);
    } else {
        return 0;
    }
}

// Derived from blep().
inline double blamp(double t, double dt) {
    if (t < dt) {
        t = t / dt - 1;
        return -1 / 3.0 * square_number(t) * t;
    } else if (t > 1 - dt) {
        t = (t - 1) / dt + 1;
        return 1 / 3.0 * square_number(t) * t;
    } else {
        return 0;
    }
}

PolyBLEPOscillator::PolyBLEPOscillator()
{}

PolyBLEPOscillator::~PolyBLEPOscillator(){}

void PolyBLEPOscillator::setFreq(double freq) {
    if (freq != mFreq)
    {
        mFreq = freq;
        updatePhaseInc();
    }
}

void PolyBLEPOscillator::setSR(double sr) {
    if (sr != mSamplerate)
    {
        mSamplerate = sr;
        updatePhaseInc();
    }
}

void PolyBLEPOscillator::setWF(int i) {
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
        case 4: 
            mWave = COSINE; 
        case 5:
            mWave = RAMP;
        default:
            mWave = SINE;
    }
        
}

double PolyBLEPOscillator::sinOsc() {
    return sin(mPhase * mTwoPi);
}

double PolyBLEPOscillator::cosOsc() {
    return cos(mPhase * mTwoPi);
}

double PolyBLEPOscillator::sqrOsc() {
    double t2 = mPhase + 0.5;
    t2 -= bitwiseOrZero(t2); // 0 <= t2 < 1

    double y = mPhase < 0.5 ? 1. : -1.;
    y += blep(mPhase, mPhaseInc) - blep(t2, mPhaseInc);
    return y;
}

double PolyBLEPOscillator::sawOsc() {
    double _t = mPhase + 0.5;
    _t -= bitwiseOrZero(_t);
    double y = 2. * _t - 1.;
    y -= blep(_t, mPhaseInc);
    return y;
}

double PolyBLEPOscillator::triOsc() {
    double t1 = mPhase + 0.25;
    t1 -= bitwiseOrZero(t1);
    double t2 = mPhase + 0.75;
    t2 -= bitwiseOrZero(t2);
    double y = mPhase * 4.;
    if (y >= 3.){
        y -= 4.;
    } else if (y > 1) {
        y = 2 - y;
    }
    y += 4 * mPhaseInc * (blamp(t1, mPhaseInc) - blamp(t2, mPhaseInc));
    return y;
}

double PolyBLEPOscillator::rampOsc() {
    double _t = mPhase + 0.5;
    _t -= bitwiseOrZero(_t);
    double y = 2 * _t - 1.;
    y += blep(_t, mPhaseInc);
    return y;
}

double PolyBLEPOscillator::rectOsc() {
    double t2 = mPhase + 1 - mPulseWidth;
    t2 -= bitwiseOrZero(t2);
    double y = -2 * mPulseWidth;
    if (mPhase < mPulseWidth) {
        y += 2;
    }
    y += blep(mPhase, mPhaseInc) - blep(t2, mPhaseInc);
    return y;
}

double PolyBLEPOscillator::getNextSample() {

    double value = 0;

    if (mFreq >= mSamplerate / 4) {
        value == sinOsc();
    } else switch (mWave) {
        case SINE: 
            value = sinOsc();
            break;
        case COSINE:
            value = cosOsc();
            break;
        case SQUARE:
            value = sqrOsc();
            break;
        case SAW:
            value = sawOsc();
            break;
        case TRIANGLE:
            value = triOsc();
            break;
        case RAMP:
            value = rampOsc();
            break;
        case RECTANGLE:
            value = rectOsc();
            break;
        default:
            break;
    } 
    mPhase += mPhaseInc;
    mPhase -= bitwiseOrZero(mPhase);
    return value;
}

void PolyBLEPOscillator::updatePhaseInc() {
    double pitchModAsFrequency = pow(2.0, fabs(mPitchMod) * 14.0) - 1;
    if (mPitchMod < 0) {
        pitchModAsFrequency = -pitchModAsFrequency;
    }
    double frequency = fmin(fmax(mFreq + pitchModAsFrequency, 0), mSamplerate/2.0);
    mPhaseInc = frequency / mSamplerate;
}

void PolyBLEPOscillator::setPulseWidth(double pw) {
    if (pw != mPulseWidth) mPulseWidth = pw;
}

void PolyBLEPOscillator::sync(double phase) {
    mPhase = phase;
    if (mPhase >= 0) {
        mPhase -= bitwiseOrZero(mPhase);
    } else {
        mPhase += 1 - bitwiseOrZero(mPhase);
    }
}
