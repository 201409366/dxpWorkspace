#include "buzz.h"
#include "reg52.h"

sbit b = P2^3;
void noise ();
void quiet ();

BUZZ buzz = {
	noise,
	quiet
};

void noise () {
	b = 0;
}

void quiet () {
	b = 1;
}
