#include "signature.h"

#ifndef _ORACLE_H
#define _ORACLE_H
typedef struct Oracle {
	void * Theta;
	struct Signature* (*Sig_New)(void*);
	int (*Apply) (struct Oracle*, struct Signature*, struct Signature*);
	void (*Free) (struct Oracle*);
} Oracle;
#endif
