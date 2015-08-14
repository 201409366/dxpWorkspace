#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit led0 = P2^6;
sbit led1 = P2^5;
sbit led2 = P2^4;
sbit led3 = P2^7;

sbit ADC0832CS = P1^4;
sbit ADC0832CLK = P1^5;
sbit ADC0832D0_D1 = P1^6;

//�޵�
unsigned char code numbers[10] = {0x5f,0x0a,0x9d,0xd5,0xc6,0xd3,0xdb,0x45,0xdf,0xd7};

//�е�
unsigned char code numbers2[10] = {0x5f,0x0a,0x9d,0xd5,0xc6,0xd3,0xdb,0x45,0xdf,0xd7};

void delay(unsigned int i) { //ʵ����0.001�����ʱ
	
	unsigned int x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

uchar ADC0832ReadInfo() {
	uchar i = 0;
	uchar Value1 = 0;
	uchar Value2 = 0;
	

	
	ADC0832CS = 1;//�ص�AD;
	ADC0832CLK = 0;
	ADC0832D0_D1 = 0;
	
	ADC0832CS = 0;//����оƬ
	
	ADC0832D0_D1 = 1;//��ʼλ
	ADC0832CLK = 0;
	ADC0832CLK = 1;
	
	ADC0832D0_D1 = 0;//����/��ͨ��
	ADC0832CLK =0;
	ADC0832CLK = 1;
	
	ADC0832D0_D1 = 0;//ͨ��ѡ��λ
	ADC0832CLK = 0;
	ADC0832CLK = 1;
	
	ADC0832D0_D1 = 1;//����λ
	ADC0832CLK = 0;
	ADC0832CLK = 1;
	
	for(i = 0;i <8 ;i++)			//����һ������
	{
		ADC0832CLK = 1;
		ADC0832CLK = 0;
		if(ADC0832D0_D1)
		{
			Value1 |= 0x80 >> i;
		}
	}
	
	for(i = 0; i < 8; i++)			//���ڶ�������
	{
		if(ADC0832D0_D1)
		{
			Value2 |= 0x01 << i;
		}
		ADC0832CLK = 1;
		ADC0832CLK = 0;
	}
	
	ADC0832CS = 1;					//�ص�оƬ
	
	if(Value1 == Value2)			//����У��
	{
		return Value1;
	}
	else
	{
		return 0;
	}
}

void main() {
	uchar i;
	uint r;

	r =  ADC0832ReadInfo() * 215;

	while(1) {
		//��ʾ��һλ
		led0 = 0; 
		P0 = numbers2[r/10000];
		delay(3);
		led0 = 1;
		//��ʾ�ڶ�λ
		led1 = 0;
		P0 = numbers[r/1000%10];
		delay(3);
		led1 = 1;
		//��ʾ����λ
		led2 = 0;
		P0 = numbers[r/100%100%10];
		delay(3);
		led2 = 1;

		
		//��ʾ����λ
		led3 = 0;
		P0 = numbers[r/10%1000%100%10];
		delay(3);
		led3 = 1;

		if(i > 100) {
			r =  ADC0832ReadInfo()* 215;
			i = 0;
		}
		i++;
	}
}