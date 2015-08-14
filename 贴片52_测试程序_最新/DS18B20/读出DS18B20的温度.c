#include <reg52.h>
#include <intrins.h>//�������������_nop_�������

#define uchar unsigned char
#define uint unsigned int

sbit lcdenable = P1^0;
sbit lcdRS = P1^2;
sbit lcdRW = P1^1;

sbit DS18B20_DQ = P1^3;

uchar code num [] = "0123456789";

uchar DS18B20_ID [6];

//--------------------------------------DS1602--------------------------

void delay(uint i) { //ʵ����0.001�����ʱ
	
	uint x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void write_command(uchar c) {
	//RS = LΪдָ��״̬,RS = H Ϊд����״̬
	lcdRS = 0;	 //����Һ��Ϊд����״̬
	lcdRW = 0;	//����Ϊд״̬
	P0 = c;	//������
	delay(5);  //�����ֲ�,��ʱһ���
	//��һ��������,��������Ч�ı�����
	lcdenable = 1; 
	delay(5);
	lcdenable = 0;
}

void write_data(uchar d,uchar position) {
	//RS = LΪдָ��״̬,RS = H Ϊд����״̬
	if(position != -1) //���û��postion == -1,˵��û������λ��.��û�ͽ�����һ�εĵ�ַд
		write_command(0x80 + position);	
	lcdRS = 1;	 //����Һ��Ϊд����״̬
	lcdRW = 0;	//����Ϊд״̬
	P0 = d;	//������
	delay(5);  //�����ֲ�,��ʱһ���
	//��һ��������,��������Ч�ı�����
	lcdenable = 1; 
	delay(5);
	lcdenable = 0;
	
}

void init_lcd() {
	//��ʼ���ܵĻ���			   
	lcdenable = 0;//��Һ���ܽ����ź�
	write_command(0x38);//����16x02��ʾ,8λ���ݿ�
	write_command(0x01);//�����ǰ��ʾ������
	write_command(0x0c);//������ʾ:��;���:��ʾ���:��;��˸:��
	write_command(0x06);//��дһ���ַ���ַ:�Զ���һ;�Զ�����:��  
	write_command(0x80);//���õ�ַΪ��һ���ַ���
}
//--------------------------------DS18B20--------------------------

void flash(uchar i) {
	while(-- i);
}

bit ResetDS18B20() {//����0˵������
	DS18B20_DQ = 1;
	DS18B20_DQ = 0;
	flash(247);
	DS18B20_DQ = 1;
	flash(27);
	if(DS18B20_DQ == 0) {
		while(DS18B20_DQ == 0);//�ȴ�DQ������
		return 0;
	}
	return 1;
	
}

void writeDS18B20(uchar d) {
	uchar i = 0;
	for(i = 0; i < 8; i ++)
		{
			DS18B20_DQ = 1;
			DS18B20_DQ = 0;
			flash(5);			
			DS18B20_DQ = d & 0x01;
			flash(20);
			DS18B20_DQ = 1;
			d >>= 1;
		}
}

uchar readDS18B20 () {
	uchar i = 0;   //��һ����ʼ�������⡣������������ô�á���������fuck
	uchar d = 0;
	for(i = 0; i < 8; i ++) {
		DS18B20_DQ = 1;
		DS18B20_DQ = 0;
		flash(1);//7us
		DS18B20_DQ = 1;
		flash(1);
		if(DS18B20_DQ) {//������
			d |= 0x01 << i;
		}
		flash(17);//45us
		DS18B20_DQ = 1;
		_nop_();
	}
	return d;
}

uchar getTemperatur () {
	uchar tempL;
	uchar tempH;
	uchar temperature;//temperature
	
	ResetDS18B20();	//DS18B20��λ
	writeDS18B20(0xCC);	//����ROM 0xcc
	writeDS18B20(0x44);	//��ʼ�¶�ת��
	ResetDS18B20();	//DS18B20��λ
	writeDS18B20(0xCC);		//����ROM
	writeDS18B20(0xBE);	//��ȡ�¶�ֵ.��Ϊ�¶�ֵ���ݴ������档�������Ƕ�ȡ�ݴ�������Ķ�����
	//��Ϊ���˶�ȡָ���ȥ�������ݴ�������Ķ�����ȫ�������Ƿ�����.�������Ľṹ��
	//����ֻҪ����������
	tempL = readDS18B20();	//�ȶ���8λ����
	tempH = readDS18B20();	//�ٶ���8λ����
	//�ϳ��¶�����.���Կ��洢�ṹͼ�뵽�㷨
	
	tempL >>= 4;
	tempH <<= 4;
	temperature = tempH | tempL;//�õ���������
	//�¶���ʾ

	return temperature;
}

void main() {
	uchar t;
	init_lcd();
	while(1) {
		t = getTemperatur();
		write_data(num[t % 10],1);//��λ
		write_data(num[t / 10],0);//ʮλ
	}
}