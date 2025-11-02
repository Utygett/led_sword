#include "NeoPixelStrip.h"

NeoPixelStrip::NeoPixelStrip(int pin, int count) 
    : m_strip(count, pin, NEO_GRB + NEO_KHZ800), m_pin(pin), m_count(count) {
}

void NeoPixelStrip::begin() {
    m_strip.begin();
    m_strip.setBrightness(0); // Начинаем с выключенных лент
    m_strip.clear();
    m_strip.show();
}

void NeoPixelStrip::setBrightness(uint8_t brightness) {
    m_strip.setBrightness(brightness);
}

void NeoPixelStrip::clear() {
    m_strip.clear();
}

void NeoPixelStrip::show() {
    m_strip.show();
}

void NeoPixelStrip::fill(uint32_t color) {
    m_strip.fill(color);
}

void NeoPixelStrip::setPixelColor(uint16_t n, uint32_t color) {
    m_strip.setPixelColor(n, color);
}

uint32_t NeoPixelStrip::Color(uint8_t r, uint8_t g, uint8_t b) {
    return m_strip.Color(r, g, b);
}

void NeoPixelStrip::SetArrayColors(uint32_t *colors) {
    for(int i = 0; i < m_count; ++i) {
        setPixelColor(i, colors[i]);
    }
}