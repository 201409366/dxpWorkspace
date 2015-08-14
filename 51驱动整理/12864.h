#ifndef __LCD12864_H__
#define __LCD12864_H__

#define uchar unsigned char
#define uint unsigned int

void lcd12864Print(uchar x, uchar y, uchar *data_);
void lcd12864Init();

#endif

