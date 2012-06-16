#include <stdlib.h>
#include <math.h>
#include "oracle_hist.h"
#include "signature.h"

struct Signature * S_Hist_New(void * ptr_value) {
	Signature * S = (Signature *) malloc(sizeof(Signature));
	hist_data * data =  (hist_data*) malloc(sizeof(hist_data));
	data->nb_box = 8;
	data->count = (double *)malloc(data->nb_box*sizeof(double)); // est bien rempli de zeros ?
	unsigned int i = 0;
	for (i = 0; i < data->nb_box; i++)
		data->count[i] = 0.;
	data->nb_el = 1.;	
	float value = * ((float *) ptr_value);
	int i_val = (int) floor((value * data->nb_box) / 256.);
	data->count[i_val] = 1.;
	S->data = (void *) data;
	S->Union = S_Hist_Union;
	S->Free = S_Hist_Free;
	return S;
}

void S_Hist_Union(struct Signature * S1, struct Signature * S2){
	hist_data * data1 = (hist_data*) S1->data;
	hist_data * data2 = (hist_data*) S2->data;
	unsigned int i = 0;
	for (i = 0; i < data1->nb_box; i++)
		data1->count[i] += data2->count[i];
	data1->nb_el += data2->nb_el;
}

void S_Hist_Free(struct Signature * This) {
	hist_data * data = (hist_data*) This->data;
	free(data->count);
	free(data);
	free(This);
}

int O_Hist_Apply(Oracle * This, Signature * S1, Signature * S2) {
	float thres = *((float *) This->Theta);
	hist_data * data1 = (hist_data*) S1->data;
	hist_data * data2 = (hist_data*) S2->data;
	unsigned int i = 0;
	// Critere de Hellinger
	double crit = 0.;
	for (i=0; i< data1-> nb_box; i++) {
		crit += sqrt((data1->count[i]/(data1->nb_el)) * (data2->count[i]/(data2->nb_el)));
	}
	crit = sqrt(1-crit);
	int fusion = crit <= thres ? 1 : 0;
	return fusion;	
}

void O_Hist_Free(Oracle * This) {
	free((float *) This->Theta);
	free(This);
}

Oracle * O_Hist_New(float thres){
	Oracle* oracle =  malloc(sizeof(Oracle));
	float * p_thres = malloc(sizeof(float));
	*p_thres=thres;
	oracle->Theta = (void *) p_thres;
	oracle->Sig_New = S_Hist_New;
	oracle->Apply = O_Hist_Apply;
	oracle->Free = O_Hist_Free;
    return oracle;
}



