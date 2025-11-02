// StripColors.h
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
    //Инициализация
    void begin();\
    //Устанавливаем яркость
    void setBrightness(int val);
    uint32_t color(uint8_t r, uint8_t g, uint8_t b) { return m_mainStrip.Color(r,g,b);};
};