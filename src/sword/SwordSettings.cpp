#include "SwordSettings.h"
#include <EEPROM.h>
#include <string.h>
#include <Arduino.h>

namespace {
    constexpr int EEPROM_BASE_ADDR = 0;
    constexpr uint32_t SETTINGS_MAGIC = 0xA5A55A5A;

    struct StoredSettings {
        uint32_t magic;
        AnimationSettings anim[ANIMATIONS_SIZE];
        uint8_t mainBrightness;
        uint8_t downBrightness;
        uint8_t upBrightness;
    };
}

void SwordSettings::begin() {
	setDefalut();
	loadFromEEPROM();
}

void SwordSettings::setDefalut() {
    // присваиваем через временный объект (явный вызов конструктора)
    m_animSettings[WAVE_UP]        = AnimationSettings(100, COLOR_RED);
    m_animSettings[WAVE_DOWN]      = AnimationSettings(100, COLOR_BLUE);
    m_animSettings[FULL_ROUND]     = AnimationSettings(50, COLOR_GREEN);
    m_animSettings[SAW_BLINK]      = AnimationSettings(150, COLOR_YELLOW);
    m_animSettings[WAVE_STAR_DOWN] = AnimationSettings(100, COLOR_CORAL);
    m_animSettings[ROUND_STAR]     = AnimationSettings(80, COLOR_PURPLE);
    m_animSettings[POLICE_BLINK]   = AnimationSettings(120, COLOR_WHITE);

    // default brightness values
    m_mainBrightness = 230;
    m_downBrightness = 230;
    m_upBrightness   = 230;
}

// save to EEPROM (avoids writing if identical)
void SwordSettings::saveToEEPROM() {
    StoredSettings current;
    EEPROM.get(EEPROM_BASE_ADDR, current);

    StoredSettings s;
    s.magic = SETTINGS_MAGIC;
    memcpy(s.anim, m_animSettings, sizeof(m_animSettings));
    s.mainBrightness = m_mainBrightness;
    s.downBrightness = m_downBrightness;
    s.upBrightness   = m_upBrightness;

    // если EEPROM уже содержит такие же данные — не писать
    if (current.magic == SETTINGS_MAGIC &&
        memcmp(&current, &s, sizeof(StoredSettings)) == 0) {
        return;
    }

    EEPROM.put(EEPROM_BASE_ADDR, s);
}

// load from EEPROM (if signature ok)
void SwordSettings::loadFromEEPROM() {
    StoredSettings s;
    EEPROM.get(EEPROM_BASE_ADDR, s);
    if (s.magic == SETTINGS_MAGIC) {
        memcpy(m_animSettings, s.anim, sizeof(m_animSettings));
        m_mainBrightness = s.mainBrightness;
        m_downBrightness = s.downBrightness;
        m_upBrightness   = s.upBrightness;
    } else {
        setDefalut();
        saveToEEPROM();
    }
}

void SwordSettings::setSafetyValues(uint8_t &brightness) {
	if (brightness > 230)
		brightness = 230;
	if (brightness < 10)
		brightness = 10;
}

void SwordSettings::changeMainBrightness(int8_t val) {
	m_mainBrightness += val;
	setSafetyValues(m_mainBrightness);
}

void SwordSettings::changeDownBrightness(int8_t val) {
	m_downBrightness += val;
	setSafetyValues(m_downBrightness);
}

void SwordSettings::changeUpBrightness(int8_t val) {
	m_upBrightness += val;
	setSafetyValues(m_upBrightness);
}

void setSafetyValues(uint8_t &brightness) {
	if (brightness > 230)
		brightness = 230;
	if (brightness < 10)
		brightness = 10;
}

AnimationSettings SwordSettings::getAnimationSettings(Animations animation) {
	if (animation < ANIMATIONS_SIZE) {
		return m_animSettings[animation];
	}
	return AnimationSettings();
}

void SwordSettings::nextDelay() {
	AnimationSettings &animSettings = m_animSettings[m_currentAnimation];
	if (animSettings.delay >= 1000) {
		animSettings.delay = 25;
	} else {
		if (animSettings.delay >= 500)
			animSettings.delay += 100;
		else
			animSettings.delay += 25;
	}
}

uint32_t hsvToRgb(float h, uint8_t s, uint8_t v) {
  float r, g, b;
  float C = (v / 255.0f) * (s / 255.0f);
  float X = C * (1 - fabs(fmod(h / 60.0f, 2) - 1));
  float m = (v / 255.0f) - C;

  if (h < 60)       { r = C; g = X; b = 0; }
  else if (h < 120) { r = X; g = C; b = 0; }
  else if (h < 180) { r = 0; g = C; b = X; }
  else if (h < 240) { r = 0; g = X; b = C; }
  else if (h < 300) { r = X; g = 0; b = C; }
  else              { r = C; g = 0; b = X; }

  uint8_t R = (r + m) * 255;
  uint8_t G = (g + m) * 255;
  uint8_t B = (b + m) * 255;

  return ((uint32_t)R << 16) | ((uint32_t)G << 8) | B;
}

void SwordSettings::nextColor() {
	AnimationSettings &animSettings = m_animSettings[m_currentAnimation];

  const float step = 2.0f;
  animSettings.hue += step;
  if (animSettings.hue >= 360.0f) animSettings.hue -= 360.0f;

  uint8_t saturation = 255;
  uint8_t value = 255;

  animSettings.color = hsvToRgb(animSettings.hue, saturation, value);
}

void SwordSettings::nextAnimation() {
	m_currentAnimation = static_cast<Animations>(static_cast<int>(m_currentAnimation) + 1);
	if (static_cast<int>(m_currentAnimation) >= ANIMATIONS_SIZE)
		m_currentAnimation = NO_ANIMATION;
}