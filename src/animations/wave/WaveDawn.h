// WaveUpAnimation.h
#pragma once

#include "../MainAnimations.h"

class WaveDawn : public MainAnimations{
public:
    WaveDawn(AnimationState &state);
    //Обновить кадр
    void update(StripColors &stripColors, unsigned long currentTime);
};