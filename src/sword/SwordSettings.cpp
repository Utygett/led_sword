#include "SwordSettings.h"

void SwordSettings::begin() {
	setDefalut();
	//TODO read data from flash
}

void SwordSettings::setDefalut() {
	m_mainBrightness = 200;
	m_downBrightness = 200;
	m_upBrightness = 200;
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