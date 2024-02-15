# BasicSynth
A basic synth built exploring the Juce framework and the Maximilian c++ library.

- a simple PolyBlep Oscillator
- ADSR built using  juce::ADSR 
- State variable filter built using juce dsp module.


## Building and running the project

To build and run with Cmake use:
```
cmake . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release --config Release
```