#ifndef __COMM_H__
#define __COMM_H__

#include <reg52.h>
void comm_init();

void sendMsg(unsigned char d);

void sendMessgae(unsigned char *d);
#endif

/*
//д�ж�
void handler() interrupt 4 {
//�ж�����һ��5��
   flag = 1;
   P0 = SBUF;
   _data = P0;
   RI = 0;
 
}
*/
