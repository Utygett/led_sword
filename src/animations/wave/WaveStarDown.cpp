#include "WaveStarDown.h"

WaveStarDown::WaveStarDown(AnimationState &state) : MainAnimations(state) {

}

// Максимально простая функция затухания
uint32_t dimColorSimple(uint32_t color, uint8_t divisor) {
    if (divisor ==  50)
        return 0;
    // divisor: 1 = полная яркость, 2 = 50%, 3 = 33%, и т.д.
    uint8_t r = ((color >> 16) & 0xFF) / divisor;
    uint8_t g = ((color >> 8) & 0xFF) / divisor;
    uint8_t b = (color & 0xFF) / divisor;
    
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

// Упрощенные уровни затухания
const uint8_t simpleFade[] = {1, 2, 3, 4, 6, 8, 12, 20, 50};
const int simpleTailLength = sizeof(simpleFade) / sizeof(simpleFade[0]);
// Коэффициенты затухания (от 1.0 до 0.0)

void WaveStarDown::update(StripColors &stripColors, unsigned long currentTime) {    
    if (currentTime - m_state.lastTime >= m_state.delay) {
        if (m_state.step < (MAIN_STRIP_COUNT / 2) + 8) {
            for (int i = 0; i < simpleTailLength; i++) {
                int pos = m_state.step - i;
                if (pos >= 0 && pos < MAIN_STRIP_COUNT / 2) {
                    SetColorByLine(stripColors, pos, dimColorSimple(m_state.color, simpleFade[i]));
                }
            }
            stripColors.upper_colors[m_state.step % DOWN_STRIP_COUNT] = m_state.color;
            m_state.step++;
            m_state.lastTime = currentTime;
        } else {
            endAnimation();
        }
    }

    

}