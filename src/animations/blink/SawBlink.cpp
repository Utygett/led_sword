#include "SawBlink.h"

SawBlink::SawBlink(AnimationState &state) : MainAnimations(state) {

}

void SawBlink::update(StripColors &stripColors, unsigned long currentTime) {    
    if (currentTime - m_state.lastTime >= m_state.delay) {
        if (m_state.step < 40) {
            for(int i = 0; i < MAIN_STRIP_COUNT; ++i)
            {
                if(m_state.step % 2)
                {
                    if (i % 2 == 0)
                        SetColorOnMainByIndex(stripColors, i, m_state.color);
                    else
                        SetColorOnMainByIndex(stripColors, i, 0);
                }
                else
                {
                    if (i % 2 != 0)
                        SetColorOnMainByIndex(stripColors, i, m_state.color);
                    else
                        SetColorOnMainByIndex(stripColors, i, 0);
                }
                    
            }
            // SetColorOnLeftPixel(stripColors, m_state.step, m_state.color);
            
            m_state.step++;
            m_state.lastTime = currentTime;
        } else {
            endAnimation();
        }
    }
}