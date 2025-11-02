#include "WaveUpAnimation.h"

WaveUpAnimation::WaveUpAnimation(AnimationState &state) : MainAnimations(state) {

}

void WaveUpAnimation::update(StripColors &stripColors, unsigned long currentTime) {    
    if (currentTime - m_state.lastTime >= m_state.delay) {
        if (m_state.step < MAIN_STRIP_COUNT / 2) {
            SetColorByLine(stripColors, m_state.step, m_state.color);
            m_state.step++;
            m_state.lastTime = currentTime;
        } else {
            endAnimation();
        }
    }
}