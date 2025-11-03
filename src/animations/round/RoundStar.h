// WaveUpAnimation.h
#pragma once

#include "../MainAnimations.h"

class RoundStar : public MainAnimations{
public:
    RoundStar(AnimationState &state);
    //Обновить кадр
    void update(StripColors &stripColors, unsigned long currentTime);
};