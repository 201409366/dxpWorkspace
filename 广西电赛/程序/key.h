#include <reg52.h>

sbit key1 = P1^6;
sbit key2 = P1^7;
sbit key3 = P3^2;

#define u8 unsigned char
#define u16 unsigned int

void Delay(unsigned int i);
u8 scanKey();
