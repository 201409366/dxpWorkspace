#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit DS1302_SCLK = P2^2;
sbit DS1302_IO = P2^1;
sbit DS1302_RST = P2^0;

sbit lcdRS = P1^2;
sbit lcdRW = P1^1;
sbit lcdenable = P1^0;

uchar sec;
uchar min;
uchar h;
uchar date;
uchar month;
uchar day;
uchar year;

//��Ϊʱ���룬�����գ����ڵĶ�����д������һ����������ȫ����װ�ɷ���
//uchar code readMap [] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};
//uchar code writeMap [] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
//sec min h date month day year

//unsigned char code ledNumbers[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar code num [] = "0123456789";

uchar code initData0 [] = "2011-12-23 Day:5";
uchar code initData1 [] = "00:00:00";

void delay(uint i) { //ʵ����0.001�����ʱ

	uchar x,j;

	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}
////-----------------DS1602---------------------------------------
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

void writeLcd(uchar d,uchar position) {
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

void initLcd() {
	uchar i;
	//��ʼ���ܵĻ���			   
	lcdenable = 0;//��Һ���ܽ����ź�
	write_command(0x38);//����16x02��ʾ,8λ���ݿ�
	write_command(0x01);//�����ǰ��ʾ������
	write_command(0x0f);//������ʾ:��;���:��ʾ���:��;��˸:��
	write_command(0x06);//��дһ���ַ���ַ:�Զ���һ;�Զ�����:��  
	write_command(0x80);//���õ�ַΪ��һ���ַ���

		//��ʼ����ʾ
	for(i = 0; i < 16; i ++) {
		writeLcd(initData0[i],-1);
	}
	write_command(0x80 + 0x40 + 0x04);//���õڶ��ŵ�ַ
	for(i = 0; i < 8; i++) {
		writeLcd(initData1[i],-1);
	}

}
//------------------------------------------DS1302----------------------------

void writeDS1302(uchar command, uchar parameter) {
	uchar i;
	DS1302_SCLK = 0;
	DS1302_RST = 0;
	DS1302_RST = 1;
	for(i = 0; i < 8; i++) { //дָ��
		DS1302_IO = command & 0x01;	//ȡcommand�����λ
		DS1302_SCLK = 1;
		command >>= 1;
		DS1302_SCLK = 0;
		
	}
	for(i = 0; i < 8; i++) { //д����
		DS1302_IO = parameter & 0x01;
		DS1302_SCLK = 1;
		parameter >>= 1;
		DS1302_SCLK = 0;		
	}
	DS1302_RST = 0;	
}

uchar readDs1302(uchar command) {
	uchar i,d;
	DS1302_RST = 0;
	DS1302_SCLK = 0;
	DS1302_RST = 1;
	for(i = 0; i < 8; i++) { //дָ��
		DS1302_SCLK = 0;
		DS1302_IO = command & 0x01;//ȡcommand�����λ
		DS1302_SCLK = 1;	//����ֻ�ܱ��ָߣ���Ȼ�����һ��;;���������������ͻ����
		command >>=	1;
	}
	/*
	ע�������ｻ�紦��д��,�м�ʱ�Ӳ������仯��ע�����datasheet��д����Ȼ�ͻ�����
	*/
	for(i = 0; i < 8; i++) { //������
		DS1302_SCLK = 0;  //һ���;��ܶ�ȡ������
		if(DS1302_IO) //��������
			d |=  0x01 << i;
		DS1302_SCLK = 1;
	}

	DS1302_RST = 0;
	d = (d / 16 * 10) + (d % 16);
	return d;
}

void initDS1302() {


	writeDS1302(0x8E,0x00);//�򿪱������ǼĴ����ɶ���д
	writeDS1302(0x84,0x00);//ʱ�Ĵ���ȫ������,�Ǽ�ʱ����Ϊ24Сʱ��
	
	/*
	if(readDs1302(0xC1)) {
		//���DS1302�Ѿ�����ʼ����ֱ�ӹرձ��������ؼ���
		writeDS1302(0x8E,0x80);//�رձ���
		return;
	}
   	 
	*/
	//д���� min h date month day year
	writeDS1302(0x82,0x00);
	writeDS1302(0x84,0x12);
	writeDS1302(0x86,0x23);
	writeDS1302(0x88,0x12);
	writeDS1302(0x8a,0x05);
	writeDS1302(0x8c,0x11);//11�� ��Ϊ���оƬֻ����ĺ�����λ
	
	writeDS1302(0x80,0x00); //��λȫ������,����ʱ��
	//��DS1302��ram��дһ��������ʾDS1302�Ѿ���������
	//ram��дָ��:0xc0.��ָ����:0xc1
	writeDS1302(0xc0,0x01);	//���д������ʾDS1302�Ѿ�����ʼ��
	writeDS1302(0x8E,0x80);//�رձ���
	
}


void main() {
	initDS1302();
	initLcd();
	while(1) {
		sec = readDs1302(0x81);//��
		writeLcd(num[sec % 10],0x4b);//��λ
		writeLcd(num[sec / 10],0x4a);//ʮλ
			
		min = readDs1302(0x83);//��
		writeLcd(num[min % 10],0x48);
		writeLcd(num[min / 10],0x47);

		h = readDs1302(0x85);
		writeLcd(num[h % 10],0x45);
		writeLcd(num[h / 10],0x44);
		
		date = readDs1302(0x87);
		writeLcd(num[date % 10],0x09);
		writeLcd(num[date / 10],0x08);
		
		month = readDs1302(0x89);
		writeLcd(num[month % 10],0x06);
		writeLcd(num[month / 10],0x05);

		day = readDs1302(0x8b);
		writeLcd(num[day % 10],0x0f);

		year = readDs1302(0x8d);
		writeLcd(num[year % 10],0x03);
		writeLcd(num[year / 10],0x02);
	   	
		//��ȡ������λ�����Ϊ1�Ļ�˵��DS1302û�б���ʼ�������߳����˱�Ĺ��ϡ����ǾͰѳ�ʼ����ʶȥ��
		
		/*	
		if(year == 0 && sec >= 60) {
			writeDS1302(0x8E,0x00);//�򿪱������ǼĴ����ɶ���д	
			writeDS1302(0xc0,0x00);	
			writeDS1302(0x8E,0x80);//�رձ���
			while(1);
		}
		*/
	}
	

}

 