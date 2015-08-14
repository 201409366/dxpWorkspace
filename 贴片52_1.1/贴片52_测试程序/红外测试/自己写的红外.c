#include <reg52.h>
#define uchar unsigned char
#define  uint unsigned int

uchar readData [4];
sbit IR = P3^3;

sbit buzz = P2^3;

sbit lcdRS = P1^2;
sbit lcdRW = P1^1;
sbit lcdenable = P1^0;

uchar code num [] = "0123456789ABCDEF";

//---------------------1602-------------------
void delay_DS1602(uint i) { //ʵ����0.001�����ʱ

	uchar x,j;

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
	delay_DS1602(5);  //�����ֲ�,��ʱһ���
	//��һ��������,��������Ч�ı�����
	lcdenable = 1; 
	delay_DS1602(5);
	lcdenable = 0;
}

void write_data(uchar d,uchar position) {
	//RS = LΪдָ��״̬,RS = H Ϊд����״̬
	if(position != -1) //���û��postion == -1,˵��û������λ��.��û�ͽ�����һ�εĵ�ַд
		write_command(0x80 + position);	
	lcdRS = 1;	 //����Һ��Ϊд����״̬
	lcdRW = 0;	//����Ϊд״̬
	P0 = d;	//������
	delay_DS1602(5);  //�����ֲ�,��ʱһ���
	//��һ��������,��������Ч�ı�����
	lcdenable = 1; 
	delay_DS1602(5);
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
			 
void main() {
	char a[] = "By 470716740";
	uchar i;
		
	EA = 1;//���ж��ܿ���
	EX1 = 1;//���ⲿ�ж�1
	IT0 = 0;//��IT0=0ʱ��Ϊ��ƽ������ʽ(�͵�ƽ)
	init_lcd();
	for(i = 0; i < 12; i++) {
		write_data(a[i],i + 3);	
	}

	while(1);
}

void delay(unsigned char x)    //x*0.14MS
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++) {}
	}
}

void IRHandle() interrupt 2 using 0{
/*
����ǽ��������������ļ��뱻�ŵ���readData[2]����

if (readData[2] == ~readData[3]) {	 //������֤��Ϊ�˱�֤����ɹ�
   	write_data(num[readData[2]/16],0);
	write_data(num[readData[2]%16],1);
	//����ŵ��Ǵ�����
}
*/
	unsigned char j,k,N=0;

	EX1 = 0; //�ر��ⲿ�ж�1  
	delay(15);//��ʱ15*0.14MS=2.1ms
	if (IR==1) { //�����ʱIRΪ��˵��ʲô�أ�������һ��ʼӦ����9ms�ĵ͵�ƽ
		EX1 =1;//�ź�û�г��֣����ء�����Ǹ���
		return;
	} 
					   //ȷ��IR�źų���
	while (!IR) {            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
		delay(1);
	}						//��ʱ0.14ms

	for (j=0;j<4;j++)  {       //�ռ���������	 
		for (k=0;k<8;k++) {       //ÿ��������8λ
			while (IR) {           //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
				delay(1);
			}
			while (!IR) {         //�� IR ��Ϊ�ߵ�ƽ
				delay(1);
			}
			while (IR) {          //����IR�ߵ�ƽʱ��
				delay(1);
				N++;           
				if (N>=30) {//������ж���,����ǧ�����Ϊ��һ�μ�ֻ������һ��
					EX1=1;
					return;
				}                  //0.14ms���������Զ��뿪��
			}                        //�ߵ�ƽ�������     		    
		//���ݴ���       
			readData[j]=readData[j] >> 1; //������λ
			if (N>=8) { //8*0.14 = 1.12  ������������ʱ�䣬��λΪ1
				readData[j] |= 0x80;
			}  
			N=0;
		}//end for k
	}//end for j

	if (readData[2] == ~readData[3]) {	 //������֤��Ϊ�˱�֤����ɹ�
		buzz = !buzz;
	   	write_data(num[readData[2]/16],0);
		write_data(num[readData[2]%16],1);
		//����ֱ�������������߼�����
		buzz = !buzz;
	}
	EX1 = 1; 
}
