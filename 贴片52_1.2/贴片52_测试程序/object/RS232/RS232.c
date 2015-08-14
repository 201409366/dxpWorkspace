#include <reg52.h>
#include "rs232.h"
#include <stdarg.h>
#include <stdio.h>

void comm_init();
void send1Byte (unsigned char value);
unsigned char read1Byte ();

RS232 rs232 = {
	comm_init,
	send1Byte,
	read1Byte
};

void comm_init() {
	//Ĭ�ϴ���ͨѶ�ǲ�������
	//��ʼ������ͨ��
	//���ô��ڹ�����ʽΪ������ʽ1,8λ�첽�շ�,�����ʿɱ�
	SM0=0;	 //������������SCON����
	SM1=1;

	TMOD=0x20;//���ö�ʱ��1Ϊ������ʽ2(����8λ�ġ�������)
	//�������Ĵ���װ��ֵ,������Ը���Ҫ���õĲ����������㡣������ ��ʽ���ĵ�
	TH1=0xfd;
	TL1=0xfd;
	//�򿪶�ʱ��
	TR1=1;//������ʱ��1

	REN=1;//����ͨ������λ

	EA=1; //�����ж�
	ES=1; //�򿪴����ж�,ES(IE.4) ���п��ж�����λ
}

void send1Byte (unsigned char value) {
	ES = 0;
	SBUF = value;
	while(!TI);
	TI = 0;	//�ǵ�Ҫ����,��Ȼ�ᷢ������
	ES = 1;
}

unsigned char read1Byte () {
	unsigned char d;
	while(RI != 1);
	d = SBUF;
	RI = 0;
	return (d);
}