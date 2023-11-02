#include <stdio.h>
#include <stdlib.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

long double* convolve(long double* h, long double* x, int lenH, int lenX, int* lenY)
{
	int nconv = lenH+lenX-1;
	(*lenY) = nconv;
	int i,j,h_start,x_start,x_end;

	long double *y = (long double*) calloc(nconv, sizeof(long double));

	for (i=0; i<nconv; i++)
	{
		x_start = MAX(0,i-lenH+1);
		x_end   = MIN(i+1,lenX);
		h_start = MIN(i,lenH-1);
		for(j=x_start; j<x_end; j++)
		{
		y[i] += h[h_start--]* x[j];
		}
	}
	return y;
}

int quantidadeLinhas(char *path){
	char letra;
	int countLinhas = -1;
	FILE *file = fopen(path, "r");
		
	while((letra = fgetc(file)) != EOF){
		if(letra == '\n'){
		countLinhas++;
		}
	}

	rewind(file);

	return countLinhas;
}

long double* lerDados(char *path){
	FILE *file = fopen(path, "r");
	int tamArq = quantidadeLinhas(path);
	long double *data = (long double*)malloc(tamArq * sizeof(long double));

	for (int i = 0; i <= tamArq; i++){
		fscanf(file, "%Lf", &data[i]);
	}

	rewind(file);

	return data;
}

int main(int argc, char *argv[])
{
	//Primeiro o arquivo dos coeficientes, segundo o sinal de entrada e terceiro 
	// o arquivo de saida
	char *coeficientes = argv[1];
	char *signalIN = argv[2];
	char *arqOut = argv[3];

	long double *h = lerDados(coeficientes);
	long double *x = lerDados(signalIN);
	int tamH = quantidadeLinhas(coeficientes);
	int tamX = quantidadeLinhas(signalIN);

	
	int lenY;
	long double *y = convolve(h,x,tamH,tamX,&lenY);

	FILE *arqSaida = fopen(arqOut, "w");

	if(arqSaida == NULL){
		printf("Error!");   
		exit(1);             
	}

	for(int i=0;i<lenY;i++) {
		fprintf(arqSaida, "%Lf\n",y[i]);
	}
	puts("");
	free(y);
	free(h);
	free(x);
	return 0;
}