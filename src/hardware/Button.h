#pragma once
#include <Arduino.h>

class Button {
public:
    Button(uint8_t pin, bool usePullup = true, unsigned long debounceMs = 50);
    void begin();
    // Нужно вызывать регулярно, передавая millis() (по умолчанию использует millis())
    void update(unsigned long now = millis());

    bool isPressed() const;
    bool justPressed();    // одноразовый флаг — сбрасывается при вызове
    bool justReleased();   // одноразовый флаг — сбрасывается при вызове
    unsigned long pressedDuration() const; // время удержания, 0 если не удерживается

private:
    uint8_t _pin;
    bool _usePullup;
    unsigned long _debounceMs;

    bool _stableState = false; // текущее стабильное состояние (pressed = true)
    bool _lastRaw = false;
    unsigned long _lastBounce = 0;

    bool _justPressed = false;
    bool _justReleased = false;
    unsigned long _pressStart = 0;
};