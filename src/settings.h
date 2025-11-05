#pragma once
#include <Arduino.h>
#include "colors.h"
/*
 * Основные настройки программы
 */

// Настройки светодиодных лент
#define MAIN_STRIP_PIN 6
#define MAIN_STRIP_COUNT 46
#define UPPER_STRIP_PIN 7  
#define UPPER_STRIP_COUNT 7
#define DOWN_STRIP_PIN 8
#define DOWN_STRIP_COUNT 7

// Настройки кнопок
#define MENU_BUTTON_PIN 3
#define INCREMENT_BUTTON_PIN 4
#define DECREMENT_BUTTON_PIN 5

// Настройки датчика касания
#define VIBRATION_SENSOR_PIN 2
// Настройки батареи
#define BATTERY_PIN A0

// структура настроек анимации
struct AnimationSettings {
    uint8_t delay = 100;
    uint32_t color = COLOR_RED;
    float hue = 0.0f;
    AnimationSettings() {}
    AnimationSettings(uint8_t d, uint32_t c) : delay(d), color(c) {}
};

enum Animations {
    NO_ANIMATION,
    WAVE_UP,
    WAVE_DOWN,
    FULL_ROUND,
    SAW_BLINK,
    WAVE_STAR_DOWN,
    ROUND_STAR,
    POLICE_BLINK,
    ANIMATIONS_SIZE
};

enum SwordState {
    CHECK_BATTERY,
    PlAY_ANIMATION,
    SETTINGS,
    STATE_SIZE
};