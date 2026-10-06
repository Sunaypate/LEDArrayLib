#include <ShiftRegister.h>
#include "LEDBoard8x16.h"
#include <stdint.h>

LEDBoard8x16::LEDBoard8x16(uint8_t serPin, uint8_t clkPin, uint8_t rclkPin)
:	controller(serPin, clkPin, rclkPin) {
	for (uint8_t i = 0; i < 8; i++) {
		screenData[i] = 0;
	}
}

LEDBoard8x16::LEDBoard8x16(uint8_t serPin, uint8_t clkPin, uint8_t rclkPin, uint8_t enblPin)
:	controller(serPin, clkPin, rclkPin, enblPin) {
	for (uint8_t i = 0; i < 8; i++) {
		screenData[i] = 0;
	}

	controller.setBrightness(200);
}

LEDBoard8x16::~LEDBoard8x16() {}

// Test if this works
void LEDBoard8x16::playScreen() {
	for (uint8_t row = 0; row < 8; row++) {
		controller.directOutput((uint8_t[3])
		{0b00000001 << row, (uint8_t)(screenData[row] >> 8), (uint8_t)(screenData[row])});
	}
}

void LEDBoard8x16::setData(bool** image) {
	for (uint8_t row = 0; row < 8; row++) {
		screenData[row] = 0;
		for (uint8_t column = 0; column < 16; column++) {
			screenData[row] |= image[row][column] << 15 - column;
		}
	}
}
