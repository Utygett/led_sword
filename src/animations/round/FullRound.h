// WaveUpAnimation.h
#pragma once

#include "../MainAnimations.h"

class FullRound : public MainAnimations{
public:
    FullRound(AnimationState &state);
    //Обновить кадр
    void update(StripColors &stripColors, unsigned long currentTime);
};