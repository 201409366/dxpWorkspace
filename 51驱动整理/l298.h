#ifndef _L298_h_
#define _L298_h_//��Сд������

#include <reg52.h>

/*********���ת��ת�Ϳ�ʹ�ܶˣ�Ҳ���Ǹ��Ĵ�����ת�ÿ�*********/
/*****���ģ��*****/
//��L298�ܽŽӷ�
sbit in1 = P2^0;//����
sbit in2 = P2^1; 
sbit in3 = P2^2;
sbit in4 = P2^3;
sbit en1 = P2^4;
sbit en2 = P2^6; //L293������ʹ�ܶ�

void waterIn();

void waterOut();
	
void stop ();

#endif