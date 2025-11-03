// WaveUpAnimation.h
#pragma once

#include "../MainAnimations.h"

class WaveStarDown : public MainAnimations{
public:
    WaveStarDown(AnimationState &state);
    //Обновить кадр
    void update(StripColors &stripColors, unsigned long currentTime);
};