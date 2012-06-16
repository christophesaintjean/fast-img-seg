#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "io_png.h"
#include "unionfind.h"
#include "seg.h"
#include "oracle_moy.h"
#include "oracle_hist.h"



int main(int argc, char* argv[]){
	char in[100] = "lenna_gray.png";
	char out[100] = "seg_out.png";
	float thres = 0.5;
	
	if (argc > 1) {	
		sscanf(argv[1],"%s",in);
		sscanf(argv[2],"%s",out);
		sscanf(argv[3], "%f", &thres);
	}
	
	Image* imagein = malloc(sizeof(Image));
	imagein->data = read_png_f32_gray(in, &(imagein->w), &(imagein->h));
	
	if(imagein->data != NULL){
		printf("%zd %zd\n", imagein->w, imagein->h);
		Oracle * O = O_Moy_New(thres);
		//Oracle * O = O_Hist_New(thres);
		//Forest forest = SegIter(imagein, O);
		Forest forest = SegRec(imagein, O);
		//Forest forest = SegIter2(imagein, O);
		Image* imageout = colorize(forest,imagein->w,imagein->h);
		//int temp = 
		write_png_f32(out, imageout->data, imageout->w, imageout->h, 3);
		//printf("Ecriture : %d\n", temp);
		free(imageout->data);
		free(imageout);
	}
	else {
		printf("ERREUR\n");
		return EXIT_FAILURE;
	}
	
	free(imagein->data);
	free(imagein);
	
	return EXIT_SUCCESS;
}




