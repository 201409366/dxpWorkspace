#ifndef LED_H
#define LED_H

#define LED0 (0x01)
#define LED1 (0x02)

void turnOn (unsigned char no);
void turnOff (unsigned char no);
void toggle (unsigned char no);

#endif
