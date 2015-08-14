#include <reg52.h>

sbit led1 = P0^0;
sbit led2 = P0^1;
sbit led3 = P0^4;
sbit led4 = P0^5;
sbit led5 = P2^7;
sbit led6 = P2^6;
sbit led7 = P2^3;
sbit led8 = P2^2;

void lightALed();
void blowOutALed();
