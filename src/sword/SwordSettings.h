#pragma once

#include "animations/AnimationManager.h"

class SwordSettings
{
private:
    AnimationSettings m_animSettings[ANIMATIONS_SIZE];
    uint8_t  m_mainBrigness;
    uint8_t  m_downBrigness;
    uint8_t  m_upBrigness;
public:
    void begin();
    void setDefalut();
};
