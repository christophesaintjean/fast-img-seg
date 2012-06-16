#include "oracle.h"
#include "signature.h"

#ifndef _ORACLE_HIST_H
#define _ORACLE_HIST_H
typedef struct hist_data{
	double * count;
	unsigned short nb_box;
	double nb_el;
	
} hist_data; 

void S_Hist_Union(struct Signature *,struct Signature *);
void S_Hist_Free(struct Signature *);
struct Signature * S_Hist_New(void *);

int O_Hist_Apply(Oracle *, Signature *, Signature *);
void O_Hist_Free(Oracle *);
Oracle * O_Hist_New(float);
#endif



