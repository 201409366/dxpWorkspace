#ifndef RS232_H
#define RS232_H
#include <reg52.h>

typedef struct {
	void (* comm_init) ();
	void (* send1Byte) (unsigned char value);
	unsigned char (* read1Byte) ();
} RS232;

extern RS232 rs232;

#endif

/*
//写中断
void handler() interrupt 4 {
//中断种类一个5个
flag = 1;
P0 = SBUF;
_data = P0;
   RI = 0;
 
}
*/

/*
printf();用法
ES = 0;
TI = 1;
printf("abc");
while(!TI);
ES = 1;
*/