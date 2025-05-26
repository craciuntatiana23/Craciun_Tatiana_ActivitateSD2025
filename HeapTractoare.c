#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tractor {
	int id;
	char* producator;
	char* model;
	int caiPutere;
	float nrOre;
};
typedef struct Tractor Tractor;

struct Heap {
	Tractor* vector;
	int nrTractoare;
	int lungime;
};
typedef struct Heap Heap;

Tractor citireTractorFisier(FILE* fisier) {
	Tractor tractor;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, fisier);
	char* aux;

	tractor.id = atoi(strtok(buffer, sep));
	
	aux = strtok(NULL, sep);
	tractor.producator = malloc(strlen(aux) + 1);
	strcpy(tractor.producator, aux);

	aux = strtok(NULL, sep);
	tractor.model = malloc(strlen(aux) + 1);
	strcpy(tractor.model, aux);

	tractor.caiPutere = atoi(strtok(NULL, sep));
	tractor.nrOre = atof(strtok(NULL, sep));

	return tractor;
}

void afisareTractor(Tractor tractor) {
	printf("\n");
	printf("ID: %d \n", tractor.id);
	printf("Producator: %s \n", tractor.producator);
	printf("Model: %s \n", tractor.model);
	printf("Cai putere: %d \n", tractor.caiPutere);
	printf("Nr ore: %5.2f \n", tractor.nrOre);
	printf("\n");
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrTractoare = 0;
	heap.vector = malloc(sizeof(Tractor) * lungime);
	return heap;
}

void filtrareHeap(Heap heap, int pozitie) {
	int pozCopilSt = 2 * pozitie + 1;
	int pozCopilDr = 2 * pozitie + 2;
	int pozMax = pozitie;
	if (pozCopilSt < heap.nrTractoare && heap.vector[pozitie].id < heap.vector[pozCopilSt].id)
		pozMax = pozCopilSt;
	if (pozCopilDr < heap.nrTractoare && heap.vector[pozitie].id < heap.vector[pozCopilDr].id)
		pozMax = pozCopilDr;
	if (pozMax != pozitie) {
		Tractor aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitie];
		heap.vector[pozitie] = aux;
		if (pozMax < (heap.nrTractoare - 2) / 2)
			filtrareHeap(heap, pozMax);
	}
}
Heap citireHeapDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);
	while (!feof(f)) {
		heap.vector[heap.nrTractoare++] = citireTractorFisier(f);
	}
	fclose(f);
	for (int i = (heap.nrTractoare - 2) / 2; i >= 0; i--)
		filtrareHeap(heap, i);
	return heap;
}
void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrTractoare; i++)
		afisareTractor(heap.vector[i]);
}
Tractor extragereTractor(Heap* heap) {
	if (heap->nrTractoare > 0) {
		Tractor tractor = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrTractoare - 1];
		heap->vector[heap->nrTractoare - 1] = tractor;
		heap->nrTractoare--;
		for (int i = (heap->nrTractoare - 2) / 2; i > 0; i--)
			filtrareHeap(*heap, i);
		return tractor;
	}
}
void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->nrTractoare; i++)
	{
		free(heap->vector[i].producator);
		free(heap->vector[i].model);
	}
	heap->nrTractoare = 0;
	heap->lungime = 0;
	free(heap->vector);
	heap->vector = NULL;
}

int main() {
	Heap heap = citireHeapDinFisier("tractoare.txt");
	afisareHeap(heap);
}
