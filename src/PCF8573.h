/*
    FILE: PCF8573.h
	AUTHOR: Ignacy110 (github.com/Ignacy110)
	DATE: 12.03.2026

	PCF8573 Arduino Library

	Copyright (C) 2026 Ignacy110

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	The Library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
	See the GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with the GNU C Library; if not, see <http://www.gnu.org/licenses/>.

	This library was inspired by the PCF8574 Arduino library by MSZ98:
	https://github.com/MSZ98/pcf8574
*/

#ifndef PCF8573_H
#define PCF8573_H

#include <Arduino.h>
#include <Wire.h>

enum mode_pointer {
    HOURS   = 0,
    MINUTES = 1,
    DAYS    = 2,
    MONTHS  = 3,
    ALARM_HOURS   = 4,
    ALARM_MINUTES = 5,
    ALARM_DAYS    = 6,
    ALARM_MONTHS  = 7,
    RESET_SECONDS = 32,
};

class PCF8573 {

private:
    int address;
    int reg = 255;
    TwoWire *wire;

    uint8_t decToBcd(uint8_t value);
    uint8_t bcdToDec(uint8_t value);

public:

    PCF8573(TwoWire &wire, int address);
    PCF8573(int address);
	#ifdef STICKBREAKER
    PCF8573(int SDA, int SCL, int address);
	#endif

    int write(int reg);
    int writeRegister(uint8_t reg, uint8_t value);
    int read();
    int getReg();

    void setTime(uint8_t mode_pointer, uint8_t value);
    uint8_t readTime(uint8_t mode_pointer);
};

#endif /* PCF8573_H */