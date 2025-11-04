#include <Arduino.h>

#include "sword/Sword.h"

Sword g_sword;

void setup() {
  g_sword.begin();
}




void loop() {
  g_sword.update();
}