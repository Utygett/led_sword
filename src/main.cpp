#include <Arduino.h>
#include "colors.h"
#include "strip/SwordStrip.h"
#include "animations/AnimationManager.h"
#include "animations/wave/WaveUpAnimation.h"

SwordStrip g_sword;  
AnimationManager g_manager(g_sword);
void setup() {
  pinMode(MENU_BUTTON_PIN, INPUT_PULLUP);
  pinMode(INCREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DECREMENT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(VIBRATION_SENSOR_PIN, INPUT_PULLUP);

  delay(100); // Даём питанию стабилизироваться
  
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  g_sword.begin();
  delay(1000);
  // Затем полный тест
  // g_sword.testLeds();
  g_sword.setBrightness(150);
}

bool bInit = false;
int currentAnim = 0;
int prevMilis = 0;

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
  if (!bInit)
  {
    bInit = true;
    g_manager.addAnimation(WAVE_UP, 50, getColorByCounter(currentAnim));
  }

  if (currentAnim > 10)
    currentAnim = 0;
    
  if(millis() - prevMilis > 600)
  {
    prevMilis = millis();
    ++currentAnim;
    bInit = false;
  }
  g_manager.update();
  
  // put your main code here, to run repeatedly:
}