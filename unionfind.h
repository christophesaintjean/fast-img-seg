#include "signature.h"

#ifndef _UNIONFIND_H
#define _UNIONFIND_H
//typedef void (*data_union) (void*,void*);

typedef struct Node {
	struct Node* father;
	unsigned int rank;
	Signature * Sig;
	void * Label;
} Node;

typedef struct Node ** Forest;
Node* Node_New(Node*,Signature*);
int isRoot(const Node*);
Node* Find(Node*);
void Union(Node*, Node*);
#endif
