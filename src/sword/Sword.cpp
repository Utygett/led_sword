#include "Sword.h"

Sword::Sword() : menuBtn(MENU_BUTTON_PIN, true, 50), touch(VIBRATION_SENSOR_PIN, 0, false, 30, true) {
}

uint32_t make_color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

uint32_t getColorByCounter(int counter) {
  switch(counter) {
    case 0:
      return make_color(255, 63, 132); break;
    case 1:
      return make_color(255, 0, 0); break;    // Красный
    case 2:
      return make_color(0, 255, 0); break;    // Зелёный
    case 3:
      return make_color(0, 0, 255); break;    // Синий
    case 4:
      return make_color(255, 255, 0); break;  // Жёлтый
    case 5:
      return make_color(255, 0, 255); break;  // Розовый
    case 6:
      return make_color(0, 255, 255); break;  // Голубой
    case 7:
      return make_color(255, 165, 0); break;  // Оранжевый
    case 8:
      return make_color(128, 0, 128); break;  // Фиолетовый
    case 9:
      return make_color(100, 100, 100); break;// Белый
    case 10:
      return make_color(128, 128, 128); break;// Серый
  }
}


void Sword::begin() {
  // Установим режимы пинов — TouchSensor.begin() не меняет pinMode для цифрового датчика
  pinMode(MENU_BUTTON_PIN, INPUT_PULLUP);
  pinMode(INCREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DECREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(VIBRATION_SENSOR_PIN, INPUT_PULLUP);

  delay(100); // Даём питанию стабилизироваться

  // Инициализация менеджера (он содержит внутренний SwordStrip)
  m_manager.begin();

  // Инициализация кнопок/датчика
  menuBtn.begin();
  touch.begin();
}

int currentAnim = 0;

void Sword::update() {
    unsigned long now = millis();
    menuBtn.update(now);
    touch.update(now);

    // триггерим анимацию только при касании (active LOW)
    if (touch.justTouched()) {
        m_manager.addAnimation(ROUND_STAR, 30, getColorByCounter(currentAnim));
        currentAnim += 1;
        if (currentAnim > 10) currentAnim = 0;
    }

    // одноразовые события меню
    if (menuBtn.justPressed()) {
      
    }
    if (menuBtn.justReleased()) {
        digitalWrite(LED_BUILTIN, LOW);
    }

    m_manager.update();
}