#pragma once

#include "../strip/SwordStrip.h"
#include "colors.h"

struct AnimationSettings
{
    uint8_t delay = 100;
    uint32_t color = COLOR_RED;
};


enum Animations {
    NO_ANIMATION,
    WAVE_UP,
    WAVE_DOWN,
    FULL_ROUND,
    SAW_BLINK,
    WAVE_STAR_DOWN,
    ROUND_STAR,
    POLICE_BLINK,
    ANIMATIONS_SIZE
};

//Структура для хранения данных состояний 
struct AnimationState
{
    Animations type = NO_ANIMATION;           //тип анимации
    uint8_t delay = 0;          
    uint16_t step  = 0;        //текущий шаг
    unsigned long startTime  = 0;    //время начала
    unsigned long lastTime  = 0;     //время время последнего шага
    uint32_t color = 0;         
};

class AnimationManager {
private:
    static const uint8_t MAX_ANIMATIONS = 50;
    AnimationState m_animationStates[MAX_ANIMATIONS];
    SwordStrip m_swordStrip;
    StripColors m_currentFrame;
    uint8_t m_activeCount = 0;
    
public:
    AnimationManager();
    void begin();                      // <-- добавлено: инициализация внутренней ленты
    bool addAnimation(Animations animation, int delay, uint32_t color);
    void updateAnimation(AnimationState &state, unsigned long currentTime);
    void update();
    uint8_t getActiveCount() const { return m_activeCount; }
    uint8_t getMaxCapacity() const { return MAX_ANIMATIONS; }
    void queueState();
private:
    void clearFrame();
    void blendFrames(const StripColors& newFrame);
};