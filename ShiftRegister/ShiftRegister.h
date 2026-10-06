#ifndef SHIFT_REGISTER_H
#define	SHIFT_REGISTER_H

#include <Arduino.h>
#include <stdint.h>

template <size_t chainSize>
class ShiftRegister
{
	private:
		uint8_t serialPin;
		uint8_t clockPin;
		uint8_t latchPin;
		uint8_t enablePin;

	public:
		uint8_t registerData[chainSize];

		ShiftRegister(uint8_t serPin, uint8_t clkPin, uint8_t rclkPin)
		:	serialPin(serPin), clockPin(clkPin), latchPin(rclkPin) {

			enablePin = NULL;

			for (uint8_t i = 0; i < chainSize; i++) {
				registerData[i] = 0b00000000;
			}
						
			pinMode(serialPin, OUTPUT);
			pinMode(clockPin, OUTPUT);
			pinMode(latchPin, OUTPUT);
		}

		ShiftRegister(uint8_t serPin, uint8_t clkPin, uint8_t rclkPin, uint8_t enblPin)
		:	serialPin(serPin), clockPin(clkPin), latchPin(rclkPin), enablePin(enblPin) {

			for (uint8_t i = 0; i < chainSize; i++) {
				registerData[i] = 0b00000000;
			}

			pinMode(serialPin, OUTPUT);
			pinMode(clockPin, OUTPUT);
			pinMode(latchPin, OUTPUT);
			pinMode(enablePin, OUTPUT);
		}

		~ShiftRegister() {}

		constexpr size_t size() const {return chainSize;}
		
		void outputData() {
			for (int i = chainSize - 1; i >= 0; i--) {
				//Sam was here
				shiftOut(serialPin, clockPin, MSBFIRST, registerData[i]);
			}

            digitalWrite(latchPin, HIGH);
            digitalWrite(latchPin, LOW);
		}

		void directOutput(uint8_t *data) {
			for (int i = chainSize - 1; i >= 0; i--) {
				//Sam was here
				shiftOut(serialPin, clockPin, MSBFIRST, data[i]);
			}

            digitalWrite(latchPin, HIGH);
            digitalWrite(latchPin, LOW);
		}

		void setBrightness(uint8_t pwmCycle) {
			analogWrite(enablePin, pwmCycle);
		}
};

#endif