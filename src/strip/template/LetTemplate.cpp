#include "LetTemplate.h"

LedTemplate::LedTemplate() {}
//Инициализируем шаблон значениями которые не будут передаваться на меч
void LedTemplate::init() {
    for(int i = 0; i < MAIN_STRIP_COUNT; ++i) {
        m_stripColors.main_colors[i] = INT32_MAX;
    }
    for(int i = 0; i < UPPER_STRIP_COUNT; ++i) {
        m_stripColors.upper_colors[i] = INT32_MAX;
    }
    for(int i = 0; i < DOWN_STRIP_COUNT; ++i) {
        m_stripColors.down_colors[i] = INT32_MAX;
    }
}

int getRightLedByIndex(int index) {
  if (index == 0)
    return MAIN_STRIP_COUNT - 1;
  return (index - 1) % (MAIN_STRIP_COUNT / 2);
}

int getLeftLedByIndex(int index) {
  return ((MAIN_STRIP_COUNT- 2) - index) % (MAIN_STRIP_COUNT + 1);
}

//Задать цвет на левой стороне по номеру линии
void LedTemplate::SetColorOnLeftPixel(int line, uint32_t color) {
    m_stripColors.main_colors[getLeftLedByIndex(line)] = color;
  
}
//Задать цвет на правой стороне по номеру линии
void LedTemplate::SetColorOnRightPixel(int line, uint32_t color) {
    m_stripColors.main_colors[getRightLedByIndex(line)] = color;
}
//Задаём цвет на линии
void LedTemplate::SetColorByLine(int line, uint32_t color)
{
    SetColorOnLeftPixel(line, color);
    SetColorOnRightPixel(line, color);
}