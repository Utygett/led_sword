// LedTemplate.h
#pragma once
#include "settings.h"
#include "../SwordStrip.h"



class LedTemplate {
private:
    StripColors m_stripColors;
public:
    LedTemplate();
    //Инициализируем шаблон значениями которые не будут передаваться на меч
    void init();
    //Задаём цвет на линии
    void SetColorByLine(int line, uint32_t color);
    //Задать цвет на левой стороне по номеру линии
    void SetColorOnLeftPixel(int line, uint32_t color);
    //Задать цвет на правой стороне по номеру линии
    void SetColorOnRightPixel(int line, uint32_t color); 
};