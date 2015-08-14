#ifndef LED_H
#define LED_H

typedef struct {
	void (* light) (unsigned char num);
	void (* blow) (unsigned char num);
} LED;

extern LED led;

#endif