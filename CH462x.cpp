#include "CH462x.h"
#include <ctype.h>
#include <string.h>
const CH462x::Digit CH462x::digits[6]={{4,5},{6,7},{8,9},{10,11},{12,13},{14,15}};
const uint8_t CH462x::digitMap[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
CH462x::CH462x(uint8_t a,uint8_t b,uint8_t c,uint8_t d){_bl=a;_cs=b;_wr=c;_data=d;}
void CH462x::begin(){pinMode(_bl,OUTPUT);pinMode(_cs,OUTPUT);pinMode(_wr,OUTPUT);pinMode(_data,OUTPUT);digitalWrite(_bl,HIGH);digitalWrite(_cs,HIGH);digitalWrite(_wr,HIGH);memset(_ram,0,sizeof(_ram));delay(50);sendCommand(0b000000010);sendCommand(0b001010010);sendCommand(0b000000110);clear();}
void CH462x::blOn(){digitalWrite(_bl,LOW);} void CH462x::blOff(){digitalWrite(_bl,HIGH);} void CH462x::clear(){for(uint8_t i=0;i<32;i++){_ram[i]=0;writeFrame(i,0);}} void CH462x::allOn(){for(uint8_t i=0;i<32;i++){_ram[i]=0x0F;writeFrame(i,0x0F);}}
void CH462x::writeRam(uint8_t a,uint8_t v){if(a>31)return;_ram[a]=v&0x0F;writeFrame(a,_ram[a]);}
void CH462x::setSegment(uint8_t a,uint8_t b,bool s){if(a>31||b>3)return; if(s)_ram[a]|=(1<<b); else _ram[a]&=~(1<<b); writeFrame(a,_ram[a]);}
void CH462x::setKg(bool s){setSegment(1,2,s);setSegment(3,3,s);} void CH462x::setLb(bool s){setSegment(1,1,s);} void CH462x::setOz(bool s){setSegment(1,0,s);} void CH462x::setPCS(bool s){setSegment(3,1,s);} void CH462x::setPercent(bool s){setSegment(3,2,s);} void CH462x::setNet(bool s){setSegment(16,3,s);} void CH462x::setBattery(bool s){setSegment(16,0,s);} void CH462x::clearIndicators(){setKg(false);setLb(false);setOz(false);setPCS(false);setPercent(false);setNet(false);setBattery(false);} 
void CH462x::clearDecimals(){const uint8_t dp[5]={6,8,10,12,14}; for(uint8_t i=0;i<5;i++) setSegment(dp[i],3,false);} 
void CH462x::setDecimal(uint8_t p,bool s){const uint8_t dp[5]={14,12,10,8,6}; if(p<5) setSegment(dp[p],3,s);} 
void CH462x::clearDigit(uint8_t p){writeRam(digits[p].addrABC,0);writeRam(digits[p].addrFGED,0);} 
void CH462x::writeSegments(uint8_t p,uint8_t seg){uint8_t abc=0,f=0; if(seg&1)abc|=1; if(seg&2)abc|=2; if(seg&4)abc|=4; if(seg&8)f|=8; if(seg&16)f|=4; if(seg&32)f|=1; if(seg&64)f|=2; writeRam(digits[p].addrABC,abc); writeRam(digits[p].addrFGED,f);} 
void CH462x::writeDigit(uint8_t p,uint8_t v){if(v<10)writeSegments(p,digitMap[v]);}
uint8_t CH462x::encodeChar(char c){switch(toupper(c)){case 'A':return 0x77;case 'B':return 0x7C;case 'C':return 0x39;case 'D':return 0x5E;case 'E':return 0x79;case 'F':return 0x71;case 'H':return 0x76;case 'I':return 0x06;case 'L':return 0x38;case 'N':return 0x54;case 'O':return 0x3F;case 'P':return 0x73;case 'R':return 0x50;case 'S':return 0x6D;case 'U':return 0x3E;case 'Y':return 0x6E;case '-':return 0x40;default:return 0;}}
void CH462x::show(const char*t){clearDecimals();for(uint8_t i=0;i<6;i++)clearDigit(i); if(!t)return; int len=strlen(t); int pos=5; for(int i=len-1;i>=0;i--){char c=t[i]; if(c=='.'){if(pos<5)setDecimal(4-pos,true); continue;} if(pos<0)break; if(c>='0'&&c<='9')writeDigit(pos,c-'0'); else writeSegments(pos,encodeChar(c)); pos--;}}
void CH462x::beginFrame(){digitalWrite(_cs,LOW);} void CH462x::endFrame(){digitalWrite(_cs,HIGH);} void CH462x::sendBit(bool v){digitalWrite(_data,v);delayMicroseconds(2);digitalWrite(_wr,LOW);delayMicroseconds(2);digitalWrite(_wr,HIGH);delayMicroseconds(2);} void CH462x::sendBits(uint16_t v,uint8_t c){for(int8_t i=c-1;i>=0;i--)sendBit((v>>i)&1);} void CH462x::sendCommand(uint16_t c){beginFrame();sendBits(0b100,3);sendBits(c,9);endFrame();} void CH462x::writeFrame(uint8_t a,uint8_t v){beginFrame();sendBits(0b101,3);sendBits(a&0x3F,6);sendBits(v&0x0F,4);endFrame();}
