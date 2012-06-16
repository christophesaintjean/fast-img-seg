#include <stdlib.h>
#include "unionfind.h"

Node* Node_New(Node* father, Signature * S){
	Node * node = (Node *) malloc(sizeof(Node));
	node->father = father == NULL ? node : father;
	node->rank = 0;
	node->Sig = S;
	node->Label = NULL;
	return node;
}

int isRoot(const Node* node){
	return node->father == node ? 1 : 0;
}

Node* Find(Node* node){
	node->father = node->father == node ? node : Find(node->father);
	return node->father;
}

void Union(Node* tree1, Node* tree2){
	Node* root1 = Find(tree1);
	Node* root2 = Find(tree2);
	Signature* S1 = root1->Sig;
	Signature* S2 = root2->Sig;
	
	if(root1->rank > root2->rank){
		root2->father = root1;
	    if (S1->Union != NULL) {
			S1->Union(S1,S2);
			S2->Free(S2);
			root2->Sig = NULL;
		}
		return;
	}
	if(root1->rank < root2->rank){
		root1->father = root2;
		if (S2->Union != NULL) {
			S2->Union(S2,S1);
			S1->Free(S1);
			root1->Sig = NULL;
		}
		return;
	}
	if(root1 != root2){
		root2->father = root1;
		if (S1->Union != NULL) {
			S1->Union(S1,S2);
			S2->Free(S2);
			root2->Sig = NULL;
		}
		return;
	}
}
