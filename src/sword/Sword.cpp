#include "Sword.h"

Sword::Sword() : m_menuBtn(MENU_BUTTON_PIN, true, 50),
                 m_touch(VIBRATION_SENSOR_PIN, 0, false, 30, true),
                 m_incBtn(INCREMENT_BUTTON_PIN, true, 50),
                 m_decBtn(DECREMENT_BUTTON_PIN, true, 50) {
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
  m_manager.begin();
  m_manager.setSettingsPointer(&m_settings);
  // Инициализация кнопок/датчика
  m_menuBtn.begin();
  m_incBtn.begin();
  m_decBtn.begin();
  m_touch.begin();
  m_settings.begin();

  m_currentState = CHECK_BATTERY;
  m_currentAnimation = NO_ANIMATION;
}

void Sword::update() {
    unsigned long now = millis();
    updateHardware(now);

    switch (m_currentState)
    {
    case CHECK_BATTERY:
		checkBattery(now);
		break;
    case PlAY_ANIMATION:
		playAnimation(now);
		break;
    case SETTINGS:
		settingsState(now);
		break;
    default:
		break;
    }
	if (m_menuBtn.pressedDuration() > 1000) {
		m_menuBtn.release();
		changeState();
	}
    m_manager.update();
}

void Sword::updateHardware(unsigned long now) {
  m_menuBtn.update(now);
  m_touch.update(now);
  m_incBtn.update(now);
  m_decBtn.update(now);
}

void Sword::checkBattery(unsigned long now) {
	if (m_touch.justTouched()) {
        m_manager.addAnimation(WAVE_STAR_DOWN);
    }
}

void Sword::playAnimation(unsigned long now) {
    if (m_touch.justTouched()) {
        m_manager.addAnimation(m_currentAnimation);
    }
	if (m_menuBtn.justPressed()) {
		changeAnimation();
		m_manager.addAnimation(m_currentAnimation);
    }
	if (m_incBtn.justPressed()) {
		m_settings.changeMainBrightness(10);
	}
	if (m_decBtn.justPressed()) {
		m_settings.changeMainBrightness(-10);
	}
}

void Sword::settingsState(unsigned long now) {
	if (m_touch.justTouched()) {
        m_manager.addAnimation(m_settings.getCurrentAnimation());
    }
	if (m_menuBtn.justPressed()) {
		m_manager.clearStates();
		m_manager.clearFrame();
		m_settings.nextAnimation();
		m_manager.addAnimation(m_settings.getCurrentAnimation());
	}
	if (m_incBtn.justPressed()) {
		m_manager.clearStates();
		m_manager.clearFrame();
		m_settings.nextDelay();
		m_manager.addAnimation(m_settings.getCurrentAnimation());
	}
	if (m_decBtn.justPressed()) {
		m_manager.clearStates();
		m_manager.clearFrame();
		m_settings.nextColor();
		m_manager.addAnimation(m_settings.getCurrentAnimation());
	}
}

void Sword::changeState() {
	if (m_currentState == SETTINGS) {
		m_settings.saveToEEPROM();
	}
	m_currentState = static_cast<SwordState>(static_cast<int>(m_currentState) + 1);
	if (static_cast<int>(m_currentState) >= STATE_SIZE)
		m_currentState = CHECK_BATTERY;
	m_manager.showUpLeds(static_cast<int>(m_currentState), COLOR_GREEN);
}

void Sword::changeAnimation() {
	m_currentAnimation = static_cast<Animations>(static_cast<int>(m_currentAnimation) + 1);
	if (static_cast<int>(m_currentAnimation) >= ANIMATIONS_SIZE)
		m_currentAnimation = NO_ANIMATION;
	m_manager.showDownLeds(static_cast<int>(m_currentAnimation), COLOR_ORANGE);
}