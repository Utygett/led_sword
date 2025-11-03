#include "MainAnimations.h"

MainAnimations::MainAnimations(AnimationState &state) : m_state(state) {

}

void MainAnimations::endAnimation() {
    m_state.type = NO_ANIMATION;
    m_state.color = 0;
    m_state.delay = 0;
    m_state.lastTime = 0;
    m_state.startTime = 0;
    m_state.step = 0;
}

