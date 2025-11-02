// NeoPixelStrip.h
#pragma once
#include "base/NeoPixelStrip.h"
#include "settings.h"

struct StripColors
{
    uint32_t main_colors[MAIN_STRIP_COUNT];
    uint32_t down_colors[DOWN_STRIP_COUNT];
    uint32_t upper_colors[UPPER_STRIP_COUNT];
};

class SwordStrip {
private:
    NeoPixelStrip m_upperStrip;
    NeoPixelStrip m_downStrip;
    NeoPixelStrip m_mainStrip;
    StripColors m_stripColors;
public:
    SwordStrip();
    //Очистить все цвета на лентах
    void clear();
    //Отобразить текущий шаблон
    void show();
    //Задать шаблон цветов на меч
    void SetColors(const StripColors& stripColors);
    //Тестирование всех светодиадов
    void testLeds();
    void simpleTest();
    //Инициализация
    void begin();
    
};