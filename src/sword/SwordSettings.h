#pragma once

#include "animations/AnimationManager.h"

class SwordSettings
{
private:
    AnimationSettings m_animSettings[ANIMATIONS_SIZE];
    uint8_t  m_mainBrightness;
    uint8_t  m_downBrightness;
    uint8_t  m_upBrightness;
public:
    void begin();
    void setDefalut();
    void changeMainBrightness(int8_t val);
    void changeDownBrightness(int8_t val);
    void changeUpBrightness(int8_t val);
    void setSafetyValues(uint8_t &rightness);
};


