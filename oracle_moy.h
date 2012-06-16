#include "oracle.h"
#include "signature.h"

#ifndef _ORACLE_MOY_H
#define _ORACLE_MOY_H
typedef struct moy_data{
	unsigned long nb;
	unsigned long sum;
} moy_data; 

void S_Moy_Union(struct Signature *,struct Signature *);
void S_Moy_Free(struct Signature *);
struct Signature * S_Moy_New(void *);

int O_Moy_Apply(Oracle *, Signature *, Signature *);
void O_Moy_Free(Oracle *);
Oracle * O_Moy_New(float);
#endif



