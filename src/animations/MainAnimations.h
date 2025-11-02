// MainAnimations.h
#pragma once

#include "strip/template/LetTemplate.h"
#include "AnimationManager.h"

class MainAnimations : public LedTemplate {
protected:
    AnimationState &m_state;
public:
    MainAnimations(AnimationState &state);
    unsigned long getDuration() const { return millis() - m_state.startTime; }
    void endAnimation();
};