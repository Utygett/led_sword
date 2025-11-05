#include "Button.h"

Button::Button(uint8_t pin, bool usePullup, unsigned long debounceMs)
: _pin(pin), _usePullup(usePullup), _debounceMs(debounceMs) {}

void Button::begin(){
    pinMode(_pin, _usePullup ? INPUT_PULLUP : INPUT);
    // Инициализируем текущее состояние
    bool raw = digitalRead(_pin);
    _stableState = _usePullup ? (raw == LOW) : (raw == HIGH);
    _lastRaw = raw;
    _pressStart = _stableState ? millis() : 0;
}

void Button::update(unsigned long now){
    bool raw = digitalRead(_pin);
    if(raw != _lastRaw){
        _lastBounce = now;
        _lastRaw = raw;
    } else {
        if((now - _lastBounce) >= _debounceMs){
            bool readingPressed = _usePullup ? (raw == LOW) : (raw == HIGH);
            if(readingPressed != _stableState){
                // состояние изменилось и устоялось
                if(readingPressed){
                    _justPressed = true;
                    _pressStart = now;
                } else {
                    _justReleased = true;
                    _pressStart = 0;
                }
                _stableState = readingPressed;
            }
        }
    }
}

bool Button::isPressed() const {
    return _stableState;
}

bool Button::justPressed(){
    if(_justPressed){
        _justPressed = false;
        return true;
    }
    return false;
}

bool Button::justReleased(){
    if(_justReleased){
        _justReleased = false;
        return true;
    }
    return false;
}

unsigned long Button::pressedDuration() const {
    if(!_stableState) return 0;
    return millis() - _pressStart;
}

void Button::release() {
    _stableState = false;
    _pressStart = 0;
}