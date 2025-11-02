#include "SwordStrip.h"
#include "colors.h"
SwordStrip::SwordStrip() : m_downStrip(DOWN_STRIP_PIN, DOWN_STRIP_COUNT),
                           m_upperStrip(UPPER_STRIP_PIN, UPPER_STRIP_COUNT),
                           m_mainStrip(MAIN_STRIP_PIN, MAIN_STRIP_COUNT)
{
    // Инициализируем массивы нулями (черный цвет)
    clear();
}

//Очистить все цвета на лентах
void SwordStrip::clear() {
    m_downStrip.clear();
    m_upperStrip.clear();
    m_mainStrip.clear();
}

//Отобразить текущий шаблон
void SwordStrip::show() {
    m_mainStrip.show();
    m_upperStrip.show();
    m_downStrip.show();
}

//Задать шаблон цветов на меч
void SwordStrip::SetColors(const StripColors& stripColors) {
    //Очищаем
    clear();
    // Копируем цвета, кроме не инициализированных
    for(int i = 0; i < MAIN_STRIP_COUNT; ++i) {
        if(stripColors.main_colors[i] != INT32_MAX)
            m_mainStrip.setPixelColor(i, stripColors.main_colors[i]);
    }
    for(int i = 0; i < UPPER_STRIP_COUNT; ++i) {
        if(stripColors.upper_colors[i] != INT32_MAX)
            m_upperStrip.setPixelColor(i,stripColors.upper_colors[i]);
    }
    for(int i = 0; i < DOWN_STRIP_COUNT; ++i) {
        if(stripColors.down_colors[i] != INT32_MAX)
            m_downStrip.setPixelColor(i, stripColors.down_colors[i]);
    }
}
//Устанавливаем яркость
void SwordStrip::setBrightness(int val) {
    m_downStrip.setBrightness(val);
    m_upperStrip.setBrightness(val);
    m_mainStrip.setBrightness(val);
}

//Инициализация
void SwordStrip::begin() {
    m_downStrip.begin();
    m_upperStrip.begin();
    m_mainStrip.begin();
}
