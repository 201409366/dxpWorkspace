#include "rs232.h"
#include "reg52.h"
#include <stdio.h>

void main() {
	unsigned char d = 0;
	rs232.comm_init();

	while(1) {
		d = rs232.read1Byte();
		rs232.send1Byte(d);
	}
}