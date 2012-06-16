#ifndef _SIGNATURE_H
#define _SIGNATURE_H
typedef struct Signature {
	void * data;
	void (*Union) (struct Signature*,struct Signature*);
	void (*Free) (struct Signature*);
} Signature;
#endif

