#include <reg52.h>
#include <intrins.h>

//_crol_
sbit buzz = P2^3;
unsigned char noise = 0;
//_cror_
void Delay (int time)  {//ʵ����0.01�����ʱ

	int i,j;
	 for(i = 0; i < time; i++) {
	 	for(j = 0; j < 1872; j++) {
		}
	 } 

}

void repeattion1() {	//ѭ���ƶ�����

	unsigned int i;

	for(i = 0; i< 7; i++) {
	 //����
	 Delay(20);
	 P0 = _crol_(P0,1);
	}
	 Delay(30);

	for(i = 0; i< 7; i++) {
	 //����
	 P0 = _cror_(P0,1);
	 Delay(30);
	}

	 Delay(30);	
}

void flash() {			//��˸����
	char oldP0_ = P0;

	P0 = 0x0;
	Delay(30);
	P0 = 0xff;
	Delay(30);

	P0 = oldP0_;
}

void buzzs() {
	if(noise) {
		buzz = !buzz;
	}
}

void main()	 {
	unsigned int i;

	//�жϲ���
	EA = 1;//���ж��ܿ���
	EX0 = 1;//���ⲿ�жϿ���
	IT0 = 1;//���ô����¼��ķ�ʽΪ������

	while(1) {
	   	P0 = 0xfe;	//������һ����
		 //��������
		for(i = 0; i < 2; i++) {
			repeattion1();		
			buzzs();
		}
	
		P0 = 0xff;//ȫ�����ʱ0.5s
		Delay(50);
		//ȫ������5��
	 
		for(i = 0; i < 5; i++) {
			flash();
			buzzs();
		}
				
	}
}

//�жϴ�����

void test1() interrupt 0 {
	noise = !noise;	
}

