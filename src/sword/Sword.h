#pragma once

#include "colors.h"
#include "settings.h"
#include "strip/SwordStrip.h"
#include "animations/AnimationManager.h"
#include "animations/wave/WaveUpAnimation.h"
#include "hardware/Button.h"
#include "hardware/TouchSensor.h"

class Sword {
private:
    
    AnimationManager m_manager;
    Button menuBtn;
    // Button incBtn(INCREMENT_BUTTON_PIN, true, 50);
    // Button decBtn(DECREMENT_BUTTON_PIN, true, 50);
    TouchSensor touch; // digital, active LOW

public:
    Sword();
    void begin();
    void update(); 
};