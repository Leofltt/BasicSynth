/*
  ==============================================================================

    SynthSound.h
    Created: 19 Nov 2019 2:26:38pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote(int)
    {
        return true;
    }
    bool appliesToChannel(int)
    {
        return true;
    }
    
};
