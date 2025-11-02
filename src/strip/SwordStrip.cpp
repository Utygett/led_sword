#include "SwordStrip.h"

SwordStrip::SwordStrip() : m_downStrip(DOWN_STRIP_PIN, DOWN_STRIP_COUNT),
                           m_upperStrip(UPPER_STRIP_PIN, UPPER_STRIP_COUNT),
                           m_mainStrip(MAIN_STRIP_PIN, MAIN_STRIP_COUNT)
{
    // Инициализируем массивы нулями (черный цвет)
    clear();
}

//Очистить все цвета на лентах
void SwordStrip::clear() {
    for(int i = 0; i < MAIN_STRIP_COUNT; ++i) {
        m_stripColors.main_colors[i] = 0;
    }
    for(int i = 0; i < UPPER_STRIP_COUNT; ++i) {
        m_stripColors.upper_colors[i] = 0;
    }
    for(int i = 0; i < DOWN_STRIP_COUNT; ++i) {
        m_stripColors.down_colors[i] = 0;
    }
    
    m_downStrip.clear();
    m_upperStrip.clear();
    m_mainStrip.clear();
}

//Отобразить текущий шаблон
void SwordStrip::show() {
    m_mainStrip.SetArrayColors(m_stripColors.main_colors);
    m_upperStrip.SetArrayColors(m_stripColors.upper_colors);
    m_downStrip.SetArrayColors(m_stripColors.down_colors);
    
    m_mainStrip.show();
    m_upperStrip.show();
    m_downStrip.show();
}

//Задать шаблон цветов на меч
void SwordStrip::SetColors(const StripColors& stripColors) {
    // Копируем ВСЕ цвета, не проверяя на 0
    for(int i = 0; i < MAIN_STRIP_COUNT; ++i) {
        m_stripColors.main_colors[i] = stripColors.main_colors[i];
    }
    for(int i = 0; i < UPPER_STRIP_COUNT; ++i) {
        m_stripColors.upper_colors[i] = stripColors.upper_colors[i];
    }
    for(int i = 0; i < DOWN_STRIP_COUNT; ++i) {
        m_stripColors.down_colors[i] = stripColors.down_colors[i];
    }
}

void SwordStrip::testLeds() {
    // Устанавливаем яркость
    m_downStrip.setBrightness(100);
    m_upperStrip.setBrightness(100);
    m_mainStrip.setBrightness(100);
    
    // Очищаем предыдущие цвета
    clear();
    
    // Устанавливаем тестовые цвета
    for(int i = 0; i < MAIN_STRIP_COUNT; ++i) {
        m_stripColors.main_colors[i] = m_mainStrip.Color(255, 0, 0); // Красный
    }
    for(int i = 0; i < UPPER_STRIP_COUNT; ++i) {
        m_stripColors.upper_colors[i] = m_upperStrip.Color(0, 255, 0); // Зеленый
    }
    for(int i = 0; i < DOWN_STRIP_COUNT; ++i) {
        m_stripColors.down_colors[i] = m_downStrip.Color(0, 0, 255); // Синий
    }
    
    // Показываем цвета
    show();
}

//Инициализация
void SwordStrip::begin() {
    m_downStrip.begin();
    m_upperStrip.begin();
    m_mainStrip.begin();
}
