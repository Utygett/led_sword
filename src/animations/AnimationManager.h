#pragma once

#include "../strip/SwordStrip.h"
#include "colors.h"
#include "settings.h"

// Forward declaration — достаточно, чтобы хранить указатель в классе
class SwordSettings;
//Структура для хранения данных состояний 
struct AnimationState
{
    Animations type = NO_ANIMATION;           //тип анимации
    uint8_t delay = 100;      //задержка между шагами       
    uint16_t step  = 0;    //текущий шаг
    unsigned long startTime  = 0;    //время начала
    unsigned long lastTime  = 0;     //время время последнего шага
    uint32_t color = COLOR_CORAL;          //цвет анимации     
};

class AnimationManager {
private:
    static const uint8_t MAX_ANIMATIONS = 20;
    AnimationState m_animationStates[MAX_ANIMATIONS];
    SwordStrip m_swordStrip;
    StripColors m_currentFrame;
    uint8_t m_activeCount = 0;
    SwordSettings *m_pSettings = nullptr;
public:
    AnimationManager();
    void begin();
    bool addAnimation(Animations animation);
    void clearStates();
    void updateAnimation(AnimationState &state, unsigned long currentTime);
    void update();
    uint8_t getActiveCount() const { return m_activeCount; }
    uint8_t getMaxCapacity() const { return MAX_ANIMATIONS; }
    void queueState();
    void showDownLeds(int count, uint32_t color);
    void showUpLeds(int count, uint32_t color);
    void setSettingsPointer(SwordSettings *pSettings) { m_pSettings = pSettings; }
    void clearFrame();
private:

    void blendFrames(const StripColors& newFrame);
};