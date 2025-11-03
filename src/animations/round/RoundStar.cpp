#include "RoundStar.h"

RoundStar::RoundStar(AnimationState &state) : MainAnimations(state) {

}

// Максимально простая функция затухания
uint32_t dimColorSimple(uint32_t color, uint8_t divisor);

// Упрощенные уровни затухания
const uint8_t simpleFade[] = {1, 2, 3, 4, 6, 8, 12, 20, 50};
const int simpleTailLength = sizeof(simpleFade) / sizeof(simpleFade[0]);
// Коэффициенты затухания (от 1.0 до 0.0)

void RoundStar::update(StripColors &stripColors, unsigned long currentTime) {    
    if (currentTime - m_state.lastTime >= m_state.delay) {
        if (m_state.step < MAIN_STRIP_COUNT + 8) {
            for (int i = 0; i < simpleTailLength; i++) {
                int pos = m_state.step - i;
                if (pos >= 0 && pos < MAIN_STRIP_COUNT) {
                    SetColorOnMainByIndex(stripColors, pos, dimColorSimple(m_state.color, simpleFade[i]));
                }
            }
            m_state.step++;
            m_state.lastTime = currentTime;
        } else {
            endAnimation();
        }
    }

    

}