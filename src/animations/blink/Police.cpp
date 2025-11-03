#include "Police.h"
#include "colors.h"
Police::Police(AnimationState &state) : MainAnimations(state) {

}

void Police::update(StripColors &stripColors, unsigned long currentTime) {    
    if (currentTime - m_state.lastTime >= m_state.delay) {
        if (m_state.step < 40) {
            if (m_state.step % 2 == 0)
            {
                for(int i = 0; i < MAIN_STRIP_COUNT / 2; ++i)
                    SetColorOnLeftPixel(stripColors, i, COLOR_RED);
                for(int i = 0; i < MAIN_STRIP_COUNT / 2; ++i)
                    SetColorOnRightPixel(stripColors, i, COLOR_BLUE);
            } else {
                for(int i = 0; i < MAIN_STRIP_COUNT / 2; ++i)
                    SetColorOnLeftPixel(stripColors, i, COLOR_BLUE);
                for(int i = 0; i < MAIN_STRIP_COUNT / 2; ++i)
                    SetColorOnRightPixel(stripColors, i, COLOR_RED);
            }
            m_state.step++;
            m_state.lastTime = currentTime;
        } else {
            endAnimation();
        }
    }
}