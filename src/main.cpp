#include <Arduino.h>
#include "colors.h"
#include "strip/SwordStrip.h"
#include "animations/AnimationManager.h"
#include "animations/wave/WaveUpAnimation.h"
#include "hardware/Button.h"
#include "hardware/TouchSensor.h"

SwordStrip g_sword;  
AnimationManager g_manager(g_sword);


// Кнопка на пине 2, используется INPUT_PULLUP, дебаунс 50 мс
Button menuBtn(MENU_BUTTON_PIN, true, 50);
TouchSensor touch(VIBRATION_SENSOR_PIN, 0, false, 30, true); // digital, active LOW

void setup() {
  pinMode(MENU_BUTTON_PIN, INPUT_PULLUP);
  pinMode(INCREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DECREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(VIBRATION_SENSOR_PIN, INPUT_PULLUP); // важен pull-up для active LOW

  delay(100); // Даём питанию стабилизироваться
  
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  g_sword.begin();
  delay(1000);
  // Затем полный тест
  // g_sword.testLeds();
  g_sword.setBrightness(150);
  menuBtn.begin();

  // инициализация сенсора
  touch.begin();
}

bool bInit = false;
int currentAnim = 0;
unsigned long prevMilis = 0;

uint32_t getColorByCounter(int counter) {
  switch(counter) {
    case 0:
      return g_sword.color(255, 63, 132); break;
    case 1:
      return g_sword.color(255, 0, 0); break;    // Красный
    case 2:
      return g_sword.color(0, 255, 0); break;    // Зелёный
    case 3:
      return g_sword.color(0, 0, 255); break;    // Синий
    case 4:
      return g_sword.color(255, 255, 0); break;  // Жёлтый
    case 5:
      return g_sword.color(255, 0, 255); break;  // Розовый
    case 6:
      return g_sword.color(0, 255, 255); break;  // Голубой
    case 7:
      return g_sword.color(255, 165, 0); break;  // Оранжевый
    case 8:
      return g_sword.color(128, 0, 128); break;  // Фиолетовый
    case 9:
      return g_sword.color(100, 100, 100); break;// Белый
    case 10:
      return g_sword.color(128, 128, 128); break;// Серый
  }
}


void loop() {
    unsigned long now = millis();
    menuBtn.update(now);
    touch.update(now);

    // теперь используем justTouched() вместо прямого digitalRead(...)
    if (touch.justTouched()) {
        g_manager.addAnimation(ROUND_STAR, 30, getColorByCounter(currentAnim));
    }

    // одноразовые события
    if (menuBtn.justPressed()) {
      currentAnim += 1;
      if (currentAnim > 10)
        currentAnim = 0;
        // g_manager.addAnimation(ROUND_STAR, 100, getColorByCounter(currentAnim));
    }
    if (menuBtn.justReleased()) {
        digitalWrite(LED_BUILTIN, LOW);
    }

    // текущее состояние и длительность удержания
    // if (menuBtn.isPressed()) {
    //     if (menuBtn.pressedDuration() > 1000)
    //     {
          
    //     }
          
    // }
    g_manager.update();
}