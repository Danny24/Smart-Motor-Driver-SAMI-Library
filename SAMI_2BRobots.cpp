#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
#include "TinyWireM.h"
#define Wire TinyWireM
#else
#include <Wire.h>
#endif

#include "SAMI_2BRobots.h"

SAMI_2BRobots::SAMI_2BRobots() {
}

boolean SAMI_2BRobots::begin(uint8_t addr) {
	_i2caddr = addr;
	Wire.begin();

	if (getID() != SAMI_VALID_ID) return false;

	return true;
}

uint8_t SAMI_2BRobots::getID(void) {
	return read8(SAMI_REG_ID);
}

void SAMI_2BRobots::inverted(bool value) {
     _reversed = value;
}

uint8_t SAMI_2BRobots::getAddress(void) {
	return read8(SAMI_REG_ADDRESS);
}

void SAMI_2BRobots::setAddress(uint8_t value) {
	write8(SAMI_REG_ADDRESS, value & SAMI_MAX_ADDRESS);
}

uint8_t SAMI_2BRobots::isRunning(void) {
	return read8(SAMI_REG_START_STOP);
}

void SAMI_2BRobots::Run(uint8_t value) {
	write8(SAMI_REG_START_STOP, value & 0X01);
}

uint8_t SAMI_2BRobots::getIOWPU(void) {
	return read8(SAMI_REG_IOWPU);
}

void SAMI_2BRobots::setIOWPU(uint8_t value) {
	write8(SAMI_REG_IOWPU, value & 0X01);
}

uint8_t SAMI_2BRobots::getMode(void) {
	return read8(SAMI_REG_MODE);
}

void SAMI_2BRobots::setMode(uint8_t value) {
	write8(SAMI_REG_MODE, value & SAMI_MODE_MAX);
}

void SAMI_2BRobots::SAVE() {
	write8(SAMI_REG_SAVE, 0X01);
}

void SAMI_2BRobots::RESET() {
	write8(SAMI_REG_RESET, 0X01);
}

void SAMI_2BRobots::setGear(int16_t value) {
	write16(SAMI_REG_GEAR_RATIO_L, value);
}

int16_t SAMI_2BRobots::getGear(void) {
	return read16(SAMI_REG_GEAR_RATIO_L);
}

void SAMI_2BRobots::setDiameter(int16_t value) {
	write16(SAMI_REG_DIAMETER_L, value);
}

int16_t SAMI_2BRobots::getDiameter(void) {
	return read16(SAMI_REG_DIAMETER_L);
}

int16_t SAMI_2BRobots::getSpeed(void) {
     if(_reversed) {
        return read16(SAMI_REG_SPEED_L) * -1;
     }
     else {
	   return read16(SAMI_REG_SPEED_L);
     }
}

void SAMI_2BRobots::setSpeed(int16_t value) {
     if(_reversed) {
        value = value * -1;
     }
	write16(SAMI_REG_SPEED_L, value);
}

int16_t SAMI_2BRobots::getRPM(void) {
     if(_reversed) {
        return read16(SAMI_REG_RPM_L) * -1;
     }
     else {
	   return read16(SAMI_REG_RPM_L);
     }
}

int32_t SAMI_2BRobots::getDistance(void) {
   	int32_t value = (int32_t)read32(SAMI_REG_DISTANCE_0);
     	value = (int32_t) ((double)(3.1416*(double)  		     			getDiameter())*((double)(((double)value)/
           (3*(double)getGear()))));
      if(_reversed) {
        value = value * -1;
      }
	return value;
}

void SAMI_2BRobots::setDistance(int32_t value) {
     if(_reversed) {
        value = value * -1;
     }
     value = (int32_t) (3*(double)getGear()*((double)(((double)		     value)/(3.1416*(double)getDiameter()))));
     	write32(SAMI_REG_DISTANCE_0, (uint32_t)value);
}

int32_t SAMI_2BRobots::getAngle(void) {
   	int32_t value = (int32_t)read32(SAMI_REG_DISTANCE_0);
     	value = (int32_t) ((double)(360*(double)value)/(3*(double)          getGear()));
      if(_reversed) {
        value = value * -1;
      }
	return value;
}

void SAMI_2BRobots::setAngle(int32_t value) {
     if(_reversed) {
        value = value * -1;
     }
     value = (int32_t) (((double)(3*(double)getGear())/360)*(double)value);
     	write32(SAMI_REG_DISTANCE_0, (uint32_t)value);
}

float SAMI_2BRobots::getRPM_PID_KP(void) {
	conv temp;
     	temp.i = read32(SAMI_REG_RPM_PID_KP_0);
	return temp.f;
}

void SAMI_2BRobots::setRPM_PID_KP(float value) {
     	conv temp;
     	temp.f = value;
	write32(SAMI_REG_RPM_PID_KP_0, temp.i);
}

float SAMI_2BRobots::getRPM_PID_KD(void) {
	conv temp;
     	temp.i = read32(SAMI_REG_RPM_PID_KD_0);
	return temp.f;
}

void SAMI_2BRobots::setRPM_PID_KD(float value) {
     	conv temp;
     	temp.f = value;
	write32(SAMI_REG_RPM_PID_KD_0, temp.i);
}

float SAMI_2BRobots::getRPM_PID_KI(void) {
	conv temp;
     	temp.i = read32(SAMI_REG_RPM_PID_KI_0);
	return temp.f;
}

void SAMI_2BRobots::setRPM_PID_KI(float value) {
     	conv temp;
     	temp.f = value;
	write32(SAMI_REG_RPM_PID_KI_0, temp.i);
}

float SAMI_2BRobots::getATS_PID_KP(void) {
	conv temp;
     	temp.i = read32(SAMI_REG_ATS_PID_KP_0);
	return temp.f;
}

void SAMI_2BRobots::setATS_PID_KP(float value) {
     	conv temp;
     	temp.f = value;
	write32(SAMI_REG_ATS_PID_KP_0, temp.i);
}

float SAMI_2BRobots::getATS_PID_KD(void) {
	conv temp;
     	temp.i = read32(SAMI_REG_ATS_PID_KD_0);
	return temp.f;
}

void SAMI_2BRobots::setATS_PID_KD(float value) {
     	conv temp;
     	temp.f = value;
	write32(SAMI_REG_ATS_PID_KD_0, temp.i);
}

float SAMI_2BRobots::getATS_PID_KI(void) {
	conv temp;
     	temp.i = read32(SAMI_REG_ATS_PID_KI_0);
	return temp.f;
}

void SAMI_2BRobots::setATS_PID_KI(float value) {
     	conv temp;
     	temp.f = value;
	write32(SAMI_REG_ATS_PID_KI_0, temp.i);
}

void SAMI_2BRobots::write32(uint8_t reg, uint32_t value) {
	Wire.beginTransmission(_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.write(value & 0xFF);
	Wire.write(value >> 8);
     	Wire.write(value >> 16);
	Wire.write(value >> 24);
     	Wire.endTransmission();
}

uint32_t SAMI_2BRobots::read32(uint8_t reg) {
	uint32_t val;

	Wire.beginTransmission(_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();

	Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)4);
		
     	uint8_t buffer[4];
     	for (uint8_t i = 0; i < sizeof(uint32_t); i++){
         buffer[i] = Wire.read();
	}
 	val = (uint32_t)buffer[3]<<24;
	val |= (uint32_t)buffer[2]<<16;
     	val |= (uint32_t)buffer[1]<<8;
	val |= (uint32_t)buffer[0]&0xFF;
   	return val;
}

void SAMI_2BRobots::write16(uint8_t reg, uint16_t value) {
	Wire.beginTransmission(_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.write(value & 0xFF);
	Wire.write(value >> 8);
     	Wire.endTransmission();
}

uint16_t SAMI_2BRobots::read16(uint8_t reg) {
	uint16_t val;

	Wire.beginTransmission(_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();

	Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)2);
	val = Wire.read();
	val |= Wire.read() <<8;
	return val;
}

void SAMI_2BRobots::write8(uint8_t reg, uint8_t value) {
	Wire.beginTransmission(_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.write(value);
	Wire.endTransmission();
}

uint8_t SAMI_2BRobots::read8(uint8_t reg) {
	uint8_t val;

	Wire.beginTransmission(_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();

	Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
	val = Wire.read();
	return val;
}