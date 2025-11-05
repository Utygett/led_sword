#pragma once

#include "animations/AnimationManager.h"
#include "settings.h"

class SwordSettings
{
private:
    AnimationSettings m_animSettings[ANIMATIONS_SIZE];
    uint8_t  m_mainBrightness;
    uint8_t  m_downBrightness;
    uint8_t  m_upBrightness;
    Animations m_currentAnimation = NO_ANIMATION;
public:
    void begin();
    void setDefalut();
    void changeMainBrightness(int8_t val);
    void changeDownBrightness(int8_t val);
    void changeUpBrightness(int8_t val);
    void setSafetyValues(uint8_t &brightness);
    void nextDelay();
    void nextColor();
    void nextAnimation();
    Animations getCurrentAnimation() const { return m_currentAnimation; }
    AnimationSettings getAnimationSettings(Animations animation);
    void saveToEEPROM();
    void loadFromEEPROM();
};


