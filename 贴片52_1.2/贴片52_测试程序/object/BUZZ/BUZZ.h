#ifndef BUZZ_H
#define BUZZ_H

typedef struct {
	void (* noise) ();
	void (* quiet) ();
}BUZZ;

extern BUZZ buzz;

#endif