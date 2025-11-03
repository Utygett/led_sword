#pragma once
#include <Arduino.h>

// TouchSensor:
// - useAnalog=true  -> analogRead(pin) > threshold считается касанием
// - useAnalog=false -> digitalRead(pin) (activeLow == true -> LOW = касание)
// Конструктор: (pin, threshold, useAnalog, debounceMs, activeLow)
class TouchSensor {
public:
    TouchSensor(uint8_t pin, int threshold = 50, bool useAnalog = true, unsigned long debounceMs = 30, bool activeLow = true);
    void begin();
    void update(unsigned long now = millis());

    bool isTouched() const;
    bool justTouched();    // одноразовый флаг, сбрасывается при чтении
    bool justReleased();   // одноразовый флаг, сбрасывается при чтении
    unsigned long touchDuration() const;
    int lastValue() const;

private:
    uint8_t _pin;
    int _threshold;
    bool _useAnalog;
    unsigned long _debounceMs;
    bool _activeLow;

    int _lastRaw = 0;
    unsigned long _lastBounce = 0;
    bool _stableState = false;
    bool _justTouched = false;
    bool _justReleased = false;
    unsigned long _touchStart = 0;
    int _lastValue = 0;
};