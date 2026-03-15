/*
    FILE: PCF8573.h
	AUTHOR: Ignacy110 (github.com/Ignacy110)

	PCF8573 Arduino Library
    https://github.com/Ignacy110/PCF8573

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

	This library was inspired by the PCF8574 Arduino library by :
	https://github.com/MSZ98/pcf8574
*/

#ifndef PCF8573_H
#define PCF8573_H

#include <Arduino.h>
#include <Wire.h>

enum class time_mode_pointer {
    HOURS   = 0x00,
    MINUTES = 0x01,
    DAYS    = 0x02,
    MONTHS  = 0x03,
    // ALARM_HOURS   = 0x04,
    // ALARM_MINUTES = 0x05,
    // ALARM_DAYS    = 0x06,
    // ALARM_MONTHS  = 0x07,
};

enum function_mode_pointer {
    READ_FLAGS = 0x10,
    RESET_PRESCALER = 0x20,
    //TIME_ADJUST = 0x30,
    RESET_NODA = 0x40,
    SET_NODA = 0x50,
    RESET_COMP = 0x60,
};

enum class flags_mode_pointer {
    POWF = 0x01,
    COMP = 0x02,
    NODA = 0x04,
};

class PCF8573 {

private:
    int address;
    int reg = 255;
    TwoWire *wire;

    uint8_t decToBcd(uint8_t value);
    uint8_t bcdToDec(uint8_t value);

    int write(int reg);
    int writeRegister(uint8_t reg, uint8_t value);
    int read();
    int getReg();

public:

    PCF8573(TwoWire &wire, int address);
    PCF8573(int address);
	#ifdef STICKBREAKER
    PCF8573(int SDA, int SCL, int address);
	#endif

    void setTime(time_mode_pointer mode_pointer, uint8_t value);
    void setAlarmTime(time_mode_pointer mode_pointer, uint8_t value);
    uint8_t readTime(time_mode_pointer mode_pointer);
    uint8_t readAlarmTime(time_mode_pointer mode_pointer);

    bool readFlag(flags_mode_pointer flag_pointer);

    void resetPrescaler();

    void resetNODAflag();
    void setNODAflag();
    void resetCOMPflag();
};

#endif /* PCF8573_H */