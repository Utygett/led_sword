// WaveUpAnimation.h
#pragma once

#include "../MainAnimations.h"

class Police : public MainAnimations{
public:
    Police(AnimationState &state);
    //Обновить кадр
    void update(StripColors &stripColors, unsigned long currentTime);
};