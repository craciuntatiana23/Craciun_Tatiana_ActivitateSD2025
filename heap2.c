//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//struct Masina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct Masina Masina;
//
//struct Heap {
//	Masina* vector;
//	int lungime;
//	int nrMasini;
//};
//typedef struct Heap Heap;
//
//Masina citireMasinaFisier(FILE* file) {
//	char buffer[100];
//	char sep[4] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina masina;
//	aux = strtok(buffer, sep);
//	masina.id = atoi(aux);
//	masina.nrUsi = atoi(strtok(NULL, sep));
//	masina.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	masina.model = malloc(strlen(aux) + 1);
//	strcpy_s(masina.model, strlen(aux) + 1, aux);
//	aux = strtok(NULL, sep);
//	masina.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(masina.numeSofer, strlen(aux) + 1, aux);
//	masina.serie = atoi(strtok(NULL, sep));
//	return masina;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrMasini = 0;
//	heap.vector = (Masina*)malloc(sizeof(Masina) * lungime);
//	return heap;
//}
//
//void filtreazHeap(Heap heap, int pozitie) {
//	int pozFiuSt = 2 * pozitie + 1;
//	int pozFiuDr = 2 * pozitie + 2;
//	int pozMax = pozitie;
//	if (pozFiuSt < heap.nrMasini && heap.vector[pozMax].id < heap.vector[pozFiuSt].id)
//		pozMax = pozFiuSt;
//	if (pozFiuDr < heap.nrMasini && heap.vector[pozMax].id < heap.vector[pozFiuDr].id)
//		pozMax = pozFiuDr;
//	if (pozMax != pozitie) {
//		Masina aux = heap.vector[pozMax];
//		heap.vector[pozMax] = heap.vector[pozitie];
//		heap.vector[pozitie] = aux;
//		if (pozMax <= (heap.nrMasini - 2) / 2)
//			filtreazHeap(heap, pozMax);
//	}
//}
//
//Heap citireHeapFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(10);
//	while (!feof(f)) {
//		heap.vector[heap.nrMasini++] = citireMasinaFisier(f);
//	}
//	fclose(f);
//	for (int i = (heap.nrMasini - 2) / 2; i >= 0; i--)
//		filtreazHeap(heap, i);
//	return heap;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrMasini; i++)
//		afisareMasina(heap.vector[i]);
//}
//
//void afisareHeapAscuns(Heap heap) {
//	for (int i = heap.nrMasini; i < heap.lungime; i++)
//		afisareMasina(heap.vector[i]);
//}
//Masina extragereMasina(Heap* heap) {
//	if (heap->nrMasini > 0) {
//		Masina aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrMasini - 1];
//		heap->vector[heap->nrMasini - 1] = aux;
//		heap->nrMasini--;
//		for (int i = (heap->nrMasini - 2) / 2; i >= 0; i--)
//			filtreazHeap(*heap, i);
//		return aux;
//	}
//}
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->nrMasini; i++) {
//		free(heap->vector[i].model);
//		free(heap->vector[i].numeSofer);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->nrMasini = 0;
//	heap->lungime = 0;
//}
//int main() {
//	Heap heap = citireHeapFisier("masini_arbore.txt");
//	afisareHeap(heap);
//	printf("===========");
//	afisareMasina(extragereMasina(&heap));
//	printf("===========");
//	afisareHeapAscuns(heap);
//	dezalocareHeap(&heap);
//}