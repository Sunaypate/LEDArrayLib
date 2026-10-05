#ifndef LED_BOARD_8x16_HPP
#define LED_BOARD_8x16_HPP

#include "ShiftRegister.hpp"
#include <stdint.h>

class LEDBoard8x16
{
	private:
		ShiftRegister<3> controller;
		uint16_t screenData[8];

	public:
		LEDBoard8x16(uint8_t serPin, uint8_t clkPin, uint8_t rclkPin);

		LEDBoard8x16(uint8_t serPin, uint8_t clkPin, uint8_t rclkPin, uint8_t enblPin);

		~LEDBoard8x16();

		void playScreen();

		void setData(bool** image);

};

#endif