#include "MainAnimations.h"

MainAnimations::MainAnimations(AnimationState &state) : m_state(state) {

}

void MainAnimations::endAnimation() {
    m_state.type = NO_ANIMATION;
}