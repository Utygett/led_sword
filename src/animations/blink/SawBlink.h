// WaveUpAnimation.h
#pragma once

#include "../MainAnimations.h"

class SawBlink : public MainAnimations{
public:
    SawBlink(AnimationState &state);
    //Обновить кадр
    void update(StripColors &stripColors, unsigned long currentTime);
};