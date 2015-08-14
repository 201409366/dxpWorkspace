#include <reg52.h>
#include <intrins.h>

#define uint  unsigned int
#define uchar unsigned char

//-------------1602����------------------------------------------------------------------------
sbit lcdenable = P1^0;
sbit lcdRS = P1^2;
sbit lcdRW = P1^1;
//-------------ԭʼ����------------------------------------------------------------------------------
 
//����ʱ��ģʽ��ʾ������ܵ��±�
uint indexOfMs0 = 0;
uint indexOfMs1 = 0;
uint indexOfS0 = 0;
uint indexOfS1 = 0;
uint indexOfM0 = 0;
uint indexOfM1 = 0;
uint indexOfH0 = 0;
uint indexOfH1 = 0;

//���嶨ʱģʽ��ʾ������ܵ��±�
uint indexOfTimerOfMs0 = 0;
uint indexOfTimerOfMs1 = 0;
uint indexOfTimerOfS0 = 0;
uint indexOfTimerOfS1 = 0;
uint indexOfTimerOfM0 = 0;
uint indexOfTimerOfM1 = 0;
uint indexOfTimerOfH0 = 0;
uint indexOfTimerOfH1 = 0;


//����ʱ��ģʽ��ʱ���˶�����
uchar count = 0;
//������ʱ��ģʽ��ʱ���˶�����
uchar count2 = 0;


//������ʱ��
uchar temp1 = 0;
//ɨ��ʱ���ʱ��
uchar temp2 = 0;

//������ʶ�����Ƿ񱻰���
uchar bPress = 0;

//����3������
sbit key1 = P2^0;
sbit key2 = P2^1;
sbit key3 = P2^2;

//��ʱ�� �����жϰ������µ�ʱ���
uchar isTimer = 0;

//��ʶ��ʱ���Ŀ�ʼ�����
uchar isStarted = 0;
uchar isStoped = 0;

uchar code initDate [] = "2011-11-11";
uchar code initTime [] = "00:00:00";
uchar code numbers [] = "01234567890";
uchar index;

//��������������
void keyInterruptHandle();
void updateLED(uint i0, uint i1, uint i2, uint i3, uint i4, uint i5, uint i6, uint i7);

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
  //��ʼ��ʱ����ʾ
  writeCommand(0x80+0x03);
  for(index = 0; index < 10; index++) {
  	   writeData(initDate[index],-1);
  }

  writeCommand(0x80+0x40+0x04);
  for(index = 0; index < 8; index++) {
  	   writeData(initTime[index],-1);
  }

}


void main()	 {	
	TMOD = 0x01;
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	EA=1;//���ж��ܿ���
	ET0=1;//�򿪶�ʱ���ж�
	TR0=1;//��һ����ʱ����ʼ��ʱ

   //�������˿ڳ�ʼ��
   key1 = 1;
   key2 = 1;
   key3 = 1;
   init();
    
	while(1) {
		//����Ƶ����ķ�������ⰴ����Ҳ������������������Ϊ���ڵİ����������Ƿǳ�������
		keyInterruptHandle();

	}

}

//�ڲ��ж�0�жϴ�����
void timeInterruptHandle() interrupt 1 {  
	//����ֱ�۵ķ�����ʵ�����ǵ�ʱ�ӹ��ܣ��ں������㷨��ʵ�֡��ó�60ȡ�ࡣ������ʵ��
	//��ǰʱ���ж�1ms����һ��
   	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	count++;
	if(isTimer) {
		count2++;
	}

	if(count >= 10) { //�ж�10ms;
		 indexOfMs0++;
		 count = 0;
		 if(indexOfMs0 >= 10) {
		 	indexOfMs0 = 0;
			 indexOfMs1++;
			if(indexOfMs1 >= 10) { //�ж�ʱ�䶼һ��
				indexOfS0++;
				indexOfMs1 = 0;
				writeData(numbers[indexOfS0],0x40+0x0b);
				if(indexOfS0 >= 10) {
					indexOfS0 = 0;//�����һλ��9����0
					indexOfS1++;//����λ�ĵ�һλ��9����ڶ�λ��һ
					writeData(numbers[indexOfS1],0x40+0x0a);
					if(indexOfS1 > 5) {
						indexOfS1 = 0; //����ڶ�λ��5����0
						indexOfM0++;//���λ��һ
						writeData(numbers[indexOfS1],0x40+0x0a);
						writeData(numbers[indexOfM0],0x40+0x08);
						if(indexOfM0 >= 10) {
							indexOfM0 = 0;//���ֵ�һλ��9����0
							indexOfM1++;//����λ�ĵ�һλ��9����ڶ�λ��һ	
							writeData(numbers[indexOfM0],0x40+0x08);
							writeData(numbers[indexOfM1],0x40+0x07);
							if(indexOfM1 > 5) {
								indexOfM1 = 0; //���ֵڶ�λ��5����0
								indexOfH0++;//��ʱλ��һ
								writeData(numbers[indexOfM1],0x40+0x07);
								writeData(numbers[indexOfH0],0x40+0x05);
								if(indexOfH0 >= 10) {
									indexOfH0 = 0;//��ʱ��һλ��9����0
									if(indexOfH0 ==4 && indexOfH1 == 2) {
										 indexOfH0 = 0;	 //��24Сʱʱȫ������
										 indexOfH1 = 0;
									}else {
										indexOfH1++;//��ʱλ�ĵ�һλ��9����ڶ�λ��һ	
										writeData(numbers[indexOfH0],0x40+0x05);
										writeData(numbers[indexOfH1],0x40+0x04);
									}						
								}
							}
						}		
					}
				}
			}

		}
	  }
	
	if(isTimer) { //���������ʱ���� ��ô��ʾһ�׶���
		if(isStarted && !isStoped) { //�����ʼ�˲���û��ֹͣ�����ǾͿ�ʼ�仯����
			if(count2 >= 10) { //�ж�10ms;
			 indexOfTimerOfMs0++;
			 count2 = 0;
			 if(indexOfTimerOfMs0 >= 10) {
			 	indexOfTimerOfMs0 = 0;
				 indexOfTimerOfMs1++;
				if(indexOfTimerOfMs1 >= 10) { //�ж�ʱ�䶼һ��
					indexOfTimerOfS0++;
					indexOfTimerOfMs1 = 0;
					if(indexOfTimerOfS0 >= 10) {
						indexOfTimerOfS0 = 0;//�����һλ��9����0
						indexOfTimerOfS1++;//����λ�ĵ�һλ��9����ڶ�λ��һ
						if(indexOfTimerOfS1 > 5) {
							indexOfTimerOfS1 = 0; //����ڶ�λ��5����0
							indexOfTimerOfM0++;//���λ��һ
							if(indexOfTimerOfM0 >= 10) {
								indexOfTimerOfM0 = 0;//���ֵ�һλ��9����0
								indexOfTimerOfM1++;//����λ�ĵ�һλ��9����ڶ�λ��һ	
								if(indexOfTimerOfM1 > 5) {
									indexOfTimerOfM1 = 0; //���ֵڶ�λ��5����0
									indexOfTimerOfH0++;//��ʱλ��һ
									if(indexOfTimerOfH0 >= 10) {
										indexOfTimerOfH0 = 0;//��ʱ��һλ��9����0
										if(indexOfTimerOfH0 ==4 && indexOfH1 == 2) {
											 indexOfTimerOfH0 = 0;	 //��24Сʱʱȫ������
											 indexOfTimerOfH1 = 0;
										}else {
											indexOfTimerOfH1++;//��ʱλ�ĵ�һλ��9����ڶ�λ��һ	
										}						
									}
								}
							}		
						}
					}
				}
			}
	 	  }	
		}
		//updateLED(indexOfTimerOfMs0, indexOfTimerOfMs1, indexOfTimerOfS0, indexOfTimerOfS1, indexOfTimerOfM0, indexOfTimerOfM1, indexOfTimerOfH0, indexOfTimerOfH1);	

		//writeData(''+indexOfTimerOfH1,-1);
			//�������
	}else {	  //�����ʱ��ģʽ ������ʾʱ��
	 	 //�����ʵ�ֿ��ܾ�Ҫ�ô������ĺ���������
		//updateLED(indexOfMs0, indexOfMs1, indexOfS0, indexOfS1, indexOfM0, indexOfM1, indexOfH0, indexOfH1);
		//�������
	 }

	if(bPress) { //���������һ�α����¡���ô��ʼ��ʱ
		temp1++;
	}								  
	temp2++;
	 
}


void keyInterruptHandle() {
	if(!key1 || !key2 || !key3) {
		bPress = 1;	
	}

	if(temp1 > 15) {	//�������µ�ʱ�䳬��5ms�Ŵ���
		if(key1 == 0) { //��ʾ��һ������������	,����涨Ϊʱ
			if(isTimer) {
				 //���¿�ʼ���ٰ�һ��ֹͣ
				 if(isStarted) {	 
				 	isStoped = 1;
					isStarted = 0;
				 }else {
				 	isStarted = 1;
					isStoped = 0;
				 }
			}else if(indexOfH0 == 3 && indexOfH1 == 2) { //��ʱ����23ʱ
				indexOfH0 = 0;	 //ȫ������
				indexOfH1 = 0;
				}else if (indexOfH0 >= 9) {
					indexOfH0 = 0;
					indexOfH1++;	
				}else {
					indexOfH0++;
			}	
		   while(!key1);//�ȴ�����������
		}
		
	if(key2 == 0) { //��ʾ��һ������������ ������涨Ϊ��
		if(isTimer && isStoped) {
			 //	�����timer ��ô ��ʱ����
			 indexOfTimerOfMs0 = 0;
			 indexOfTimerOfMs1 = 0;
			 indexOfTimerOfS0 = 0;
			 indexOfTimerOfS1 = 0;
			 indexOfTimerOfM0 = 0;
			 indexOfTimerOfM1 = 0;
			 indexOfTimerOfH0 = 0;
			 indexOfTimerOfH0 = 0;

		}else if(indexOfM0 >= 9 && indexOfM1 >= 5) {
			indexOfM0 = 0;
			indexOfM1	= 0;
			indexOfH0++;
			}else if(indexOfM0 >= 9) {
				indexOfM0 = 0;
				indexOfM1++;
			}else {
				indexOfM0++;
		}							 
	   while(!key2);
	}
	
	//���ﰴ������ʵ�ּ�����Ҫԭ�������ڱ�д����key2��if����м���...������һ��bug������汾����
	if(key3 == 0) { //��ʾ��һ������������	  ����涨Ϊ��
		 //��ʱ������ ����������䵱ģʽ�л�����
		 isTimer = !isTimer;
		 while(!key3);
	}

	temp1 = 0;
	}
}
