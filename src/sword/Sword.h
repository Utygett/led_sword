#pragma once

#include "colors.h"
#include "settings.h"
#include "strip/SwordStrip.h"
#include "animations/AnimationManager.h"
#include "animations/wave/WaveUpAnimation.h"
#include "hardware/Button.h"
#include "hardware/TouchSensor.h"
#include "SwordSettings.h"

enum SwordState {
    CHECK_BATTERY,
    PlAY_ANIMATION,
    SETTINGS
};


class Sword {
private:
    SwordState m_currentState;
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
    void update(unsigned long now);
    // update hardware
    void updateHardware(unsigned long now);
    void initSettings();
    void checkBattery(unsigned long now);
    void playAnimation(unsigned long now);
    void settingsState(unsigned long now);
};