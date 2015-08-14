#ifndef _L298_h_
#define _L298_h_//大小写都行了

#include <reg52.h>

/*********电机转不转就看使能端，也就是给的次数多转得快*********/
/*****电机模块*****/
//、L298管脚接法
sbit in1 = P2^0;//输入
sbit in2 = P2^1; 
sbit in3 = P2^2;
sbit in4 = P2^3;
sbit en1 = P2^4;
sbit en2 = P2^6; //L293的两个使能端

void waterIn();

void waterOut();
	
void stop ();

#endif