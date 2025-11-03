#include "WaveDawn.h"

WaveDawn::WaveDawn(AnimationState &state) : MainAnimations(state) {

}

void WaveDawn::update(StripColors &stripColors, unsigned long currentTime) {    
    if (currentTime - m_state.lastTime >= m_state.delay) {
        if (m_state.step < MAIN_STRIP_COUNT / 2) {
            int currentLine = 22 - m_state.step;
            SetColorByLine(stripColors, currentLine, m_state.color);
            m_state.step++;
            m_state.lastTime = currentTime;
        } else {
            endAnimation();
        }
    }
}