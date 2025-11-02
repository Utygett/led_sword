// NeoPixelStrip.h
#pragma once
#include <Adafruit_NeoPixel.h>

class NeoPixelStrip {
private:
    Adafruit_NeoPixel m_strip;
    int m_pin;
    int m_count;
public:
    NeoPixelStrip(int pin, int count);
    void begin();
    void setBrightness(uint8_t brightness);
    void clear();
    void show();
    void fill(uint32_t color);
    void setPixelColor(uint16_t n, uint32_t color);
    uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
    int getCount() const { return m_count; }
    void SetArrayColors(uint32_t *colors);
};