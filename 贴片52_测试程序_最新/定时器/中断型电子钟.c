#include <reg52.h>
#include <intrins.h>

#define uint  unsigned int
#define uchar unsigned char

u8 nums [] = "0123456789";
u8 num = 0;

//-------------1602����------------------------------------------------------------------------
sbit lcdenable = P1^0;
sbit lcdRS = P1^2;
sbit lcdRW = P1^1;


void delay(uint i) { //ʵ����0.001�����ʱ
	
	uint x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void writeCommand(uchar c) {
	//RS = LΪдָ��״̬,RS = H Ϊд����״̬
	lcdRS = 0;	 //����Һ��Ϊд����״̬
	lcdRW = 0;	//����Ϊд״̬
	P0 = c;	//������
	delay(5);  //�����ֲ�,��ʱһ���
	//��һ��������,��������Ч�ı�����
	lcdenable = 1; 
	delay(5);
	lcdenable = 0;
	P0 = 0xff;//�ص�								
}

void writeData(uchar d,uchar position) {
	//RS = LΪдָ��״̬,RS = H Ϊд����״̬
	if(position != -1) //���û��postion == -1,˵��û������λ��.��û�ͽ�����һ�εĵ�ַд
		writeCommand(0x80 + position);	
	lcdRS = 1;	 //����Һ��Ϊд����״̬
	lcdRW = 0;	//����Ϊд״̬
	P0 = d;	//������
	delay(5);  //�����ֲ�,��ʱһ���
	//��һ��������,��������Ч�ı�����
	lcdenable = 1; 
	delay(5);
	lcdenable = 0;
	P0 = 0xff;//�ص�
}

void init() {
	//��ʼ���ܵĻ���			   
	lcdenable = 0;//��Һ���ܽ����ź�
	writeCommand(0x38);//����16x02��ʾ,8λ���ݿ�
	writeCommand(0x01);//�����ǰ��ʾ������
	writeCommand(0x0c);//������ʾ:��;���:��ʾ���:��;��˸:��
	writeCommand(0x06);//��дһ���ַ���ַ:�Զ���һ;�Զ�����:��  
	writeCommand(0x80);//���õ�ַΪ��һ���ַ���
}

void main()	 {	
	/*
	0001 GATE=0 ,C/T=0,M0M1=01,
	GATE��0ʱ��ֻҪ�����ʹTCON�е�TR0��TR1Ϊ1���Ϳ���������ʱ/����������
	C/T��0Ϊ��ʱģʽ
	M0M1=01ʱ,��ʾ������ʽΪ16λ��ʱ/������
		*/
	TMOD = 0x01;//�����Ч��GATE=0 ,C/T=0,M0M1=01
	TH0=(65536-50000)/256;//������װ��ֵ
	TL0=(65536-50000)%256;
	EA=1;//���ж��ܿ���
	ET0=1;//�򿪶�ʱ���ж�
	TR0=1;//��һ����ʱ����ʼ��ʱ

	while(1) {
		//��ͣ����ʾ
		writeData(nums[num],0);
		delay(10);
	}

}

void increase () {
	num ++;
	if(num > 9) 
		num = 0;
}

//�ڲ��ж�0�жϴ�����
void test1() interrupt 1 {
	//��װ��ֵ
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	increase();
}

