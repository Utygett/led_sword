#include "FullRound.h"

FullRound::FullRound(AnimationState &state) : MainAnimations(state) {

}

void FullRound::update(StripColors &stripColors, unsigned long currentTime) {    
    if (currentTime - m_state.lastTime >= m_state.delay) {
        if (m_state.step < MAIN_STRIP_COUNT) {
            // SetColorOnLeftPixel(stripColors, m_state.step, m_state.color);
            SetColorOnMainByIndex(stripColors, m_state.step, m_state.color);
            m_state.step++;
            m_state.lastTime = currentTime;
        } else {
            endAnimation();
        }
    }
}