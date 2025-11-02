// WaveUpAnimation.h
#pragma once

#include "../MainAnimations.h"

class WaveUpAnimation : public MainAnimations{
public:
    WaveUpAnimation(AnimationState &state);
    //Обновить кадр
    void update(StripColors &stripColors, unsigned long currentTime);
};