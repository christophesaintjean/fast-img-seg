#include <stdlib.h>
#include <math.h>
#include "oracle_moy.h"
#include "signature.h"

struct Signature * S_Moy_New(void * ptr_value) {
	Signature * S = (Signature *) malloc(sizeof(Signature));
	moy_data * data =  (moy_data*) malloc(sizeof(moy_data));
	data->nb = 1;
	data->sum = * ((float *) ptr_value);
	S->data = (void *) data;
	S->Union = S_Moy_Union;
	S->Free = S_Moy_Free;
	return S;
}

void S_Moy_Union(struct Signature * S1, struct Signature * S2){
	moy_data * data1 = (moy_data*) S1->data;
	moy_data * data2 = (moy_data*) S2->data;
	data1->nb += data2->nb;
	data1->sum += data2->sum;
}

void S_Moy_Free(struct Signature * This) {
	free((moy_data*) This->data);
	free(This);
}

int O_Moy_Apply(Oracle * This, Signature * S1, Signature * S2) {
	float thres = *((float *) This->Theta);
	moy_data * data1 = (moy_data*) S1->data;
	moy_data * data2 = (moy_data*) S2->data;
	int fusion = fabs(data1->sum/(double)data1->nb - data2->sum/(double)data2->nb) <= thres ? 1 : 0;
	return fusion;	
}

void O_Moy_Free(Oracle * This) {
	free((float *) This->Theta);
	free(This);
}

Oracle * O_Moy_New(float thres){
	Oracle* oracle =  malloc(sizeof(Oracle));
	float * p_thres = malloc(sizeof(float));
	*p_thres=thres;
	oracle->Theta = (void *) p_thres;
	oracle->Sig_New = S_Moy_New;
	oracle->Apply = O_Moy_Apply;
	oracle->Free = O_Moy_Free;
    return oracle;
}
	


