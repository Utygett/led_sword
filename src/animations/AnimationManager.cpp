#include "AnimationManager.h"
#include "wave/WaveUpAnimation.h"
#include "wave/WaveDawn.h"
#include "round/FullRound.h"
#include "wave/WaveStarDown.h"
#include "round/RoundStar.h"
#include "blink/SawBlink.h"
#include "blink/Police.h"

AnimationManager::AnimationManager(SwordStrip& swordStrip): m_swordStrip(swordStrip) {
    clearFrame();
}

bool AnimationManager::addAnimation(Animations animation, int delay, uint32_t color) {
    //Ищем свободный слот и занимаем его
    for (auto& slot : m_animationStates) {
        if (slot.type == Animations::NO_ANIMATION) {
            slot.type = animation;
            slot.delay = delay;
            slot.color = color;
            slot.startTime = millis();
            slot.lastTime = slot.startTime;
            return true;
        }
    }
    for (auto& slot : m_animationStates) {
        slot.type = Animations::NO_ANIMATION;
    }
    clearFrame();
    return false;
}

void AnimationManager::updateAnimation(AnimationState &state, unsigned long currentTime) {
    switch (state.type)
    {
    case WAVE_UP:
    {
        WaveUpAnimation waveUp(state);
        waveUp.update(m_currentFrame, currentTime);
        break;
    }
    case WAVE_DOWN:
    {
        WaveDawn waveDown(state);
        waveDown.update(m_currentFrame, currentTime);
        break;
    }
        
    case FULL_ROUND:
    {
        FullRound fullRound(state);
        fullRound.update(m_currentFrame, currentTime);
        break;
    }
    case SAW_BLINK:
    {
        SawBlink sawBlink(state);
        sawBlink.update(m_currentFrame, currentTime);
        break;
    }
    case WAVE_STAR_DOWN:
    {
        WaveStarDown starDown(state);
        starDown.update(m_currentFrame, currentTime);
        break;
    }
    case ROUND_STAR:
    {
        RoundStar roundStar(state);
        roundStar.update(m_currentFrame, currentTime);
        break;
    }
    case POLICE_BLINK :
    {
        Police police(state);
        police.update(m_currentFrame, currentTime);
        break;
    }
    default:
        break;
    }
}

void AnimationManager::queueState() {
    int writeIndex = 0;
    
    //перемещаем активные состояния
    for (int readIndex = 0; readIndex < MAX_ANIMATIONS; ++readIndex) {
        if (m_animationStates[readIndex].type != Animations::NO_ANIMATION) {
            if (readIndex != writeIndex) {
                m_animationStates[writeIndex] = m_animationStates[readIndex];
            }
            writeIndex++;
        }
    }
    
    // Очищаем хвост массива
    for (int i = writeIndex; i < MAX_ANIMATIONS; ++i) {
        m_animationStates[i].type = Animations::NO_ANIMATION;
        m_animationStates[i].step = 0;
    }
}

void AnimationManager::update() {
    unsigned long currentTime = millis();
    for(int i = 0; i < MAX_ANIMATIONS; ++i)
    {
        if (m_animationStates[i].type != Animations::NO_ANIMATION) {
            updateAnimation(m_animationStates[i], currentTime);
        }
    }
    
    m_swordStrip.SetColors(m_currentFrame);
    m_swordStrip.show();
    queueState();
}


void AnimationManager::clearFrame() {
    for (auto& color : m_currentFrame.main_colors) color = INT32_MAX;
    for (auto& color : m_currentFrame.upper_colors) color = INT32_MAX;
    for (auto& color : m_currentFrame.down_colors) color = INT32_MAX;
}

void AnimationManager::blendFrames(const StripColors& newFrame) {
    // Копируем цвета, кроме не инициализированных
    for(int i = 0; i < MAIN_STRIP_COUNT; ++i) {
        if(newFrame.main_colors[i] != INT32_MAX)
            m_currentFrame.main_colors[i] = newFrame.main_colors[i];
    }
    for(int i = 0; i < UPPER_STRIP_COUNT; ++i) {
        if(newFrame.upper_colors[i] != INT32_MAX)
            m_currentFrame.upper_colors[i] = newFrame.upper_colors[i];
    }
    for(int i = 0; i < DOWN_STRIP_COUNT; ++i) {
        if(newFrame.down_colors[i] != INT32_MAX)
            m_currentFrame.down_colors[i] = newFrame.down_colors[i];
    }
}