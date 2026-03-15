/*
    FILE: PCF8573.cpp
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

	This library was inspired by the PCF8574 Arduino library by MSZ98:
	https://github.com/MSZ98/pcf8574
*/

#include "PCF8573.h"

PCF8573::PCF8573(TwoWire &wire, int address) {
    this->address = address;
    this->wire = &wire;
}

PCF8573::PCF8573(int address) {
    this->address = address;
    this->wire = &Wire;
}

#ifdef STICKBREAKER
PCF8573::PCF8573(int SDA, int SCL, int address) {
    this->address = address;
    this->wire = &Wire;
}
#endif


// CONVERTING METHODS:

uint8_t PCF8573::decToBcd(uint8_t value) {
    return ((value / 10) << 4) | (value % 10);
}

uint8_t PCF8573::bcdToDec(uint8_t value) {
    return (value & 0x0F) + ((value >> 4) * 10);
}

// TRANSMISSION METHODS:

int PCF8573::write(int reg) {
    wire->beginTransmission(address);
    wire->write(reg);
    int result = wire->endTransmission();
    if(result == 0) this->reg = reg;
    return result;
}

int PCF8573::writeRegister(uint8_t reg, uint8_t value) {
    wire->beginTransmission(address);
    wire->write(reg);
    wire->write(value);
    return wire->endTransmission();
}

int PCF8573::read() {
    int result = wire->requestFrom(address, 1);
    if(result == 0) return -1;
    return wire->read();
}

int PCF8573::getReg() {
    return reg;
}

// METHODS OF OPERATING THE MODULE:

void PCF8573::setTime(time mode_pointer, uint8_t value) {
    writeRegister(static_cast<uint8_t>(mode_pointer), decToBcd(value));
}

void PCF8573::setAlarmTime(time mode_pointer, uint8_t value) {
    writeRegister(static_cast<uint8_t>(mode_pointer) + 0x04, decToBcd(value));
}

uint8_t PCF8573::readTime(time mode_pointer) {
    write(static_cast<uint8_t>(mode_pointer));
    return bcdToDec(read());
}

uint8_t PCF8573::readAlarmTime(time mode_pointer) {
    write(static_cast<uint8_t>(mode_pointer) + 0x04);
    return bcdToDec(read());
}

bool PCF8573::readFlag(flag flag_pointer) {
    write(static_cast<uint8_t>(function::READ_FLAGS));
    return read() & static_cast<uint8_t>(flag_pointer);
}

void PCF8573::resetPrescaler() {
    write(static_cast<uint8_t>(function::RESET_PRESCALER));
}

void PCF8573::resetNODAflag() {
    write(static_cast<uint8_t>(function::RESET_NODA));
}

void PCF8573::setNODAflag() {
    write(static_cast<uint8_t>(function::SET_NODA));
}

void PCF8573::resetCOMPflag() {
    write(static_cast<uint8_t>(function::RESET_COMP));
}