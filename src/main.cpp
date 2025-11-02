#include <Arduino.h>
#include "strip/SwordStrip.h"


SwordStrip g_sword;  

void setup() {
  pinMode(MENU_BUTTON_PIN, INPUT_PULLUP);
  pinMode(INCREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DECREMENT_BUTTON_PIN, INPUT_PULLUP);
    // Пробуем оба варианта подключения через тест
  pinMode(VIBRATION_SENSOR_PIN, INPUT_PULLUP);

  delay(100); // Даём питанию стабилизироваться
  
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
    g_sword.begin();
  delay(1000);
  
  // Сначала простой тест
  g_sword.simpleTest();
  delay(2000);
  
  // Затем полный тест
  // g_sword.testLeds();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
}
