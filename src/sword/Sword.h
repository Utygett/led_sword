#pragma once

#include "colors.h"
#include "settings.h"
#include "strip/SwordStrip.h"
#include "animations/AnimationManager.h"
#include "animations/wave/WaveUpAnimation.h"
#include "hardware/Button.h"
#include "hardware/TouchSensor.h"
#include "SwordSettings.h"

class Sword {
private:
    SwordSettings m_settings;
    //Менеджер анимаций
    AnimationManager m_manager;
    //Кнопка переключения меню
    Button m_menuBtn;
    //Кнопка увелечения параметра
    Button m_incBtn;
    //Кнопка уменьшения параметра
    Button m_decBtn;
    //Датчик касания
    TouchSensor m_touch;
public:
    Sword();
    //Initaliaze
    void begin();
    //update state
    void update();
    // update hardware
    void updateHardware(unsigned long now);
    void initSettings();
};