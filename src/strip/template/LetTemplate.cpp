#include "LetTemplate.h"

LedTemplate::LedTemplate() {}

int getRightLedByIndex(int index) {
  if (index == 0)
    return MAIN_STRIP_COUNT - 1;
  return (index - 1) % (MAIN_STRIP_COUNT / 2);
}

int getLeftLedByIndex(int index) {
  return ((MAIN_STRIP_COUNT- 2) - index) % (MAIN_STRIP_COUNT + 1);
}

//Задать цвет на левой стороне по номеру линии
void LedTemplate::SetColorOnLeftPixel(StripColors &stripColors, int line, uint32_t color) {
    stripColors.main_colors[getLeftLedByIndex(line)] = color;
  
}
//Задать цвет на правой стороне по номеру линии
void LedTemplate::SetColorOnRightPixel(StripColors &stripColors, int line, uint32_t color) {
    stripColors.main_colors[getRightLedByIndex(line)] = color;
}
//Задаём цвет на линии
void LedTemplate::SetColorByLine(StripColors &stripColors, int line, uint32_t color)
{
    SetColorOnLeftPixel(stripColors, line, color);
    SetColorOnRightPixel(stripColors, line, color);
}