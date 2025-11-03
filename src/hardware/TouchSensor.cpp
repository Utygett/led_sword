#include "TouchSensor.h"

TouchSensor::TouchSensor(uint8_t pin, int threshold, bool useAnalog, unsigned long debounceMs, bool activeLow)
: _pin(pin), _threshold(threshold), _useAnalog(useAnalog), _debounceMs(debounceMs), _activeLow(activeLow) {}

void TouchSensor::begin(){
    if(_useAnalog){
        // Если используем аналог — надо выставить пин в INPUT и прочитать значение
        pinMode(_pin, INPUT);
        _lastValue = analogRead(_pin);
        _stableState = (_lastValue > _threshold);
    } else {
        // Для цифрового сенсора НЕ меняем pinMode — предполагаем, что caller
        // уже установил INPUT_PULLUP или другой режим в setup(), чтобы не затирать его.
        _lastValue = digitalRead(_pin);
        _stableState = (_activeLow ? (_lastValue == LOW) : (_lastValue == HIGH));
    }
    _lastRaw = _lastValue;
    _touchStart = _stableState ? millis() : 0;
    _lastBounce = millis();
    _justTouched = _justReleased = false;
}

void TouchSensor::update(unsigned long now){
    int raw;
    if(_useAnalog){
        raw = analogRead(_pin);
        _lastValue = raw;
    } else {
        raw = digitalRead(_pin);
        _lastValue = raw;
    }

    bool rawTouched = _useAnalog ? (raw > _threshold) : (_activeLow ? (raw == LOW) : (raw == HIGH));

    if(raw != _lastRaw){
        // изменение уровня — пометим время
        _lastBounce = now;
        _lastRaw = raw;

        // Для коротких импульсов (vibration) — триггерим моментальный touch,
        // если уровень перешёл в состояние "touched" (например LOW при activeLow).
        // Это позволяет ловить краткие импульсы без ожидания полного дебаунса.
        if(rawTouched && !_stableState){
            _justTouched = true;
            _stableState = true;
            _touchStart = now;
        }
        return;
    }

    // если уровень не изменился — проверяем стабильность по дебаунсу
    if((now - _lastBounce) < _debounceMs) return;

    // уровень устоялся и дебаунс прошёл — обработка релиза/нового устойчивого касания
    if(rawTouched != _stableState){
        if(rawTouched){
            // устойчивое касание
            _justTouched = true;
            _touchStart = now;
        } else {
            // устойчивый релиз
            _justReleased = true;
            _touchStart = 0;
        }
        _stableState = rawTouched;
    }
}

bool TouchSensor::isTouched() const {
    return _stableState;
}

bool TouchSensor::justTouched(){
    if(_justTouched){
        _justTouched = false;
        return true;
    }
    return false;
}

bool TouchSensor::justReleased(){
    if(_justReleased){
        _justReleased = false;
        return true;
    }
    return false;
}

unsigned long TouchSensor::touchDuration() const {
    if(!_stableState) return 0;
    return millis() - _touchStart;
}

int TouchSensor::lastValue() const {
    return _lastValue;
}