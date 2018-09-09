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

#define SAMI_I2CADDR_DEFAULT        0x24
#define SAMI_VALID_ID               0xF3
#define SAMI_MODE_MAX               0X07
#define SAMI_MAX_ADDRESS            0X7F

#define SAMI_REG_ID                 0x00
#define SAMI_REG_ADDRESS            0x01
#define SAMI_REG_START_STOP         0x02
#define SAMI_REG_IOWPU              0x03
#define SAMI_REG_MODE               0x04
#define SAMI_REG_SAVE               0x05
#define SAMI_REG_RESET              0x06
#define SAMI_REG_GEAR_RATIO_L       0x07      
#define SAMI_REG_GEAR_RATIO_H       0x08
#define SAMI_REG_DIAMETER_L         0x09 
#define SAMI_REG_DIAMETER_H         0x0A
#define SAMI_REG_RPM_L              0x0B
#define SAMI_REG_RPM_H              0x0C
#define SAMI_REG_SPEED_L            0x0D
#define SAMI_REG_SPEED_H            0x0E
#define SAMI_REG_DISTANCE_0         0x0F
#define SAMI_REG_DISTANCE_2         0x10
#define SAMI_REG_DISTANCE_3         0x11
#define SAMI_REG_DISTANCE_4         0x12
#define SAMI_REG_RPM_PID_KP_0       0x13
#define SAMI_REG_RPM_PID_KP_1       0x14
#define SAMI_REG_RPM_PID_KP_2       0x15
#define SAMI_REG_RPM_PID_KP_3       0x16
#define SAMI_REG_RPM_PID_KD_0       0x17
#define SAMI_REG_RPM_PID_KD_1       0x18
#define SAMI_REG_RPM_PID_KD_2       0x19
#define SAMI_REG_RPM_PID_KD_3       0x1A
#define SAMI_REG_RPM_PID_KI_0       0x1B
#define SAMI_REG_RPM_PID_KI_1       0x1C
#define SAMI_REG_RPM_PID_KI_2       0x1D
#define SAMI_REG_RPM_PID_KI_3       0x1E
#define SAMI_REG_ATS_PID_KP_0       0x1F
#define SAMI_REG_ATS_PID_KP_1       0x20
#define SAMI_REG_ATS_PID_KP_2       0x21
#define SAMI_REG_ATS_PID_KP_3       0x22
#define SAMI_REG_ATS_PID_KD_0       0x23
#define SAMI_REG_ATS_PID_KD_1       0x24
#define SAMI_REG_ATS_PID_KD_2       0x25
#define SAMI_REG_ATS_PID_KD_3       0x26
#define SAMI_REG_ATS_PID_KI_0       0x27
#define SAMI_REG_ATS_PID_KI_1       0x28
#define SAMI_REG_ATS_PID_KI_2       0x29
#define SAMI_REG_ATS_PID_KI_3       0x2A


class SAMI_2BRobots {
 public:
  typedef union {
  	uint32_t i;
  	float f;
  }conv;
  SAMI_2BRobots();
  boolean begin(uint8_t a = SAMI_I2CADDR_DEFAULT);
  uint8_t getID( void );
  uint8_t getAddress( void );
  void setAddress ( uint8_t value );
  uint8_t isRunning( void );
  void Run ( uint8_t value );
  uint8_t getIOWPU( void );
  void setIOWPU ( uint8_t value );
  uint8_t getMode( void );
  void setMode ( uint8_t value );
  void SAVE ();
  void RESET ();
  int16_t getGear( void );
  void setGear ( int16_t value );
  int16_t getDiameter( void );
  void setDiameter ( int16_t value );
  int16_t getRPM( void );
  int16_t getSpeed( void );
  void setSpeed ( int16_t value );
  int32_t getDistance( void );
  void setDistance(int32_t value); 
  float getRPM_PID_KP( void );
  void setRPM_PID_KP(float value); 
  float getRPM_PID_KD( void );
  void setRPM_PID_KD(float value); 
  float getRPM_PID_KI( void );
  void setRPM_PID_KI(float value); 
  float getATS_PID_KP( void );
  void setATS_PID_KP(float value); 
  float getATS_PID_KD( void );
  void setATS_PID_KD(float value); 
  float getATS_PID_KI( void );
  void setATS_PID_KI(float value); 

  void write32(uint8_t reg, uint32_t val);
  uint32_t read32(uint8_t reg);  

  void write16(uint8_t reg, uint16_t val);
  uint16_t read16(uint8_t reg);

  void write8(uint8_t reg, uint8_t val);
  uint8_t read8(uint8_t reg);

 private:
  uint8_t _i2caddr;
};