#ifndef CH462x_H
#define CH462x_H
#include <Arduino.h>
class CH462x{public: struct Digit{uint8_t addrABC;uint8_t addrFGED;}; CH462x(uint8_t,uint8_t,uint8_t,uint8_t); void begin(); void blOn(); void blOff(); void clear(); void allOn(); void writeRam(uint8_t,uint8_t); void setSegment(uint8_t,uint8_t,bool); void setKg(bool=true); void setLb(bool=true); void setOz(bool=true); void setPCS(bool=true); void setPercent(bool=true); void setNet(bool=true); void setBattery(bool=true); void clearIndicators(); void clearDecimals(); void setDecimal(uint8_t,bool=true); void clearDigit(uint8_t); void writeDigit(uint8_t,uint8_t); void writeSegments(uint8_t,uint8_t); uint8_t encodeChar(char); void show(const char*); private: static const Digit digits[6]; static const uint8_t digitMap[10]; uint8_t _bl,_cs,_wr,_data,_ram[32]; void beginFrame(); void endFrame(); void sendBit(bool); void sendBits(uint16_t,uint8_t); void sendCommand(uint16_t); void writeFrame(uint8_t,uint8_t);};
#endif
