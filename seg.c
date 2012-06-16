#include <stdio.h>
#include "seg.h"
#include "unionfind.h"
#include "image.h"
#include "oracle.h"


void SegRec_aux(Image*,int,int, unsigned int,Oracle *,Forest);

static inline unsigned int max(unsigned int a, unsigned int b) {
	if (a>b) return a;
	return b;
}


Forest SegIter(Image* I, Oracle * O){
	int i, j;
	size_t w = I->w;
	size_t h = I->h;
	int sz = w*h;
	
	float* pData = I->data;
	
	Forest forest = (Forest) malloc(sz*sizeof(Node*));
	for(i=0; i<sz; i++) {
		forest[i] = Node_New(NULL, O->Sig_New(&pData[i]));
	}
	
	Node* left;
	Node* top;
	Node* curr;
	
	for(j=1; j<w; j++){ // First line
		left = Find(forest[(j-1)]);
		curr = Find(forest[j]);
		if(O->Apply(O,left->Sig, curr->Sig)) Union(left, curr);
	}
	
	for(j=0; j<w; j++) Find(forest[j]);
	
	for(i=1; i<h; i++){
		top = Find(forest[(i-1)*w]);
		curr = Find(forest[i*w]);
		if(O->Apply(O,top->Sig, curr->Sig)) Union(top, curr);
		
		for(j=1; j<w; j++){
			left = Find(forest[i*w + (j-1)]);
			curr = Find(forest[i*w + j]);
			if(O->Apply(O,left->Sig, curr->Sig)) Union(left, curr);
			top = Find(forest[(i-1)*w + j]);
			curr = Find(forest[i*w + j]);
			if(O->Apply(O,top->Sig, curr->Sig)) Union(top, curr);
		}

		for(j=0; j<w; j++) Find(forest[i*w + j]);
	}
	return forest;
}



Forest SegRec(Image* I, Oracle * O){
	int i;
	size_t w = I->w;
	size_t h = I->h;
	int sz = w*h;
	
	float* pData = I->data;
	
	Forest forest = (Forest) malloc(sz*sizeof(Node*));
	for(i=0; i<sz; i++) {
		forest[i] = Node_New(NULL, O->Sig_New(&pData[i]));
	}
	// w = 2^k
	SegRec_aux(I,0,0,w,O,forest);
	return forest;
}

void SegRec_aux(Image* I, int itl, int jtl, unsigned int pow2k,Oracle * O, Forest forest){
	if (pow2k>1) {  // k > 0
		unsigned int i,j;
		Node* left;
		Node* right;
		Node* top;
		Node* bottom;
		
	    unsigned int hplus = pow2k/2;
		unsigned int hmoins = hplus-1;
		
		SegRec_aux(I, itl,       jtl,       pow2k/2,O,forest);   // NO
		SegRec_aux(I, itl,       jtl+hplus, pow2k/2,O,forest);   // NE
		SegRec_aux(I, itl+hplus, jtl+hplus, pow2k/2,O,forest);   // SE
		SegRec_aux(I, itl+hplus, jtl,       pow2k/2,O,forest);   // SO
			
		for(i=0; i<pow2k; i++) {
			left  = Find(forest[(itl+i)*I->w + (jtl+hmoins)]);
			right = Find(forest[(itl+i)*I->w + (jtl+hplus)]);
			if(O->Apply(O,left->Sig, right->Sig)) Union(left, right);
		}
		for(j=0; j<pow2k; j++) {
			top   = Find(forest[(itl+hmoins)*I->w + (jtl+j)]);
			bottom = Find(forest[(itl+hplus) *I->w + (jtl+j)]);
			if(O->Apply(O,top->Sig, bottom->Sig)) Union(top, bottom);
		}
    }
}

Forest SegIter2(Image* I, Oracle * O){
	unsigned int i=0,j=0,k=0,pow2k=0;
	unsigned int hmoins=0,hplus=0;
	size_t w = I->w;
	size_t h = I->h;
	int sz = w*h;
	
	float* pData = I->data;
	
	Forest forest = (Forest) malloc(sz*sizeof(Node*));
	for(i=0; i<sz; i++) {
		forest[i] = Node_New(NULL, O->Sig_New(&pData[i]));
	}
	Node* left = NULL;
	Node* right = NULL;
	Node* top = NULL;
	Node* bottom = NULL;
	
	
	for (pow2k=2;pow2k < 2*max(w,h);pow2k=pow2k*2) {
		hplus =  pow2k/2;
		hmoins =  hplus-1;
		
		for (j=0; j<w; j+=pow2k) {
		    for (k=0;k<h;k++) {
				left  = Find(forest[k*w + (j+hmoins)]);
				right = Find(forest[k*w + (j+hplus)]);
				if(O->Apply(O,left->Sig, right->Sig)) Union(left, right);
			}
		}
		
		for (i=0; i<h; i+=pow2k) {
		    for (k=0;k<w;k++) {
				top  = Find(forest[(i+hmoins)*w + k]);
				bottom = Find(forest[(i+hplus)*w + k]);
				if(O->Apply(O,top->Sig, bottom->Sig)) Union(top, bottom);
			}
		}
	}	
	
	return forest;
}


Image * colorize(Node ** forest, int w, int h) 	{
	Image* imageout = malloc(sizeof(Image));
	imageout->w = w; 
	imageout->h = h;
	
	float * img = malloc(3 * w * h * sizeof(float));
	
	float *img_r = img;
	float *img_g = img + w * h;
	float *img_b = img + 2 * w *h;
	
	unsigned int k;
	unsigned int reg=0;
	
	for(k=0; k<w*h; k++){	
		Node * curr = Find(forest[k]);
		if (curr->Label == NULL) { 
			float * col = (float *) malloc(3*sizeof(float));
			col[0] = (float) (rand() % 256);
			col[1] = (float) (rand() % 256);
			col[2] = (float) (rand() % 256);
			curr->Label = (void*)col;
			reg++;
		}
		
		img_r[k] = ((float *) curr->Label)[0];
		img_g[k] = ((float *) curr->Label)[1];
		img_b[k] = ((float *)curr->Label)[2];
	}
	for(k=0; k<w*h; k++)
		if (isRoot(forest[k]) == 1) free(forest[k]->Label);
	printf("Nombre de régions : %u\n",reg);
	imageout->data=img;
	return imageout;
}
