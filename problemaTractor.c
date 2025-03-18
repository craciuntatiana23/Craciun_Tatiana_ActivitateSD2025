#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


struct Tractor {
	int id;
	char* producator;
	char* model;
	int caiPutere;
	float nrOre;
};
typedef struct Tractor Tractor;

Tractor initializare(int id, const char* producator, const char* model, int caiPutere, float nrOre) {
	Tractor tractor;
	tractor.id = id;
	tractor.caiPutere = caiPutere;
	tractor.nrOre = nrOre;
	tractor.producator = (char*)malloc(strlen(producator) + 1);
	strcpy(tractor.producator, producator);
	tractor.model = (char*)malloc(strlen(model) + 1);
	strcpy(tractor.model, model);
	return tractor;
}
void afisare(Tractor tractor) {
	printf("\n");
	printf("ID: %d \n", tractor.id);
	printf("Producator: %s \n", tractor.producator);
	printf("Model: %s \n", tractor.model);
	printf("Cai putere: %d \n", tractor.caiPutere);
	printf("Nr ore: %5.2f \n", tractor.nrOre);
	printf("\n");
}

void modificaNrOre(Tractor* tractor, float nrOreNou) {
	if (nrOreNou > 0) {
		tractor->nrOre = nrOreNou;
	}
}

void modificaProducator(Tractor* tractor, const char* producatorNou) {

	if (producatorNou != NULL) {
		free(tractor->producator);
		tractor->producator = (char*)malloc(strlen(producatorNou) + 1);
		if (tractor->producator)
			strcpy(tractor->producator, producatorNou);
	}
		
}

void afisareVector(Tractor* tractoare, int nrTractoare) {
	for (int i = 0; i < nrTractoare; i++) {
		afisare(tractoare[i]);
	}
}

void copiereCeleMaiTractoarePuternice(Tractor* tractoare, int nrTractoare, Tractor** tractoarePuternice, int* nrTractoarePuternice) {
	int putereMax = -1;
	*nrTractoarePuternice = 0;
	for (int i = 0; i < nrTractoare; i++) {
		if (tractoare[i].caiPutere > putereMax)
		{
			putereMax = tractoare[i].caiPutere;
		}
	}
	for (int i = 0; i < nrTractoare; i++) {
		if (putereMax == tractoare[i].caiPutere) {
			(*nrTractoarePuternice)++;
		}
	}
	if ((*tractoarePuternice) != NULL) {
		free(*tractoarePuternice);
	}
	*tractoarePuternice = (Tractor*)malloc(sizeof(Tractor) * (*nrTractoarePuternice));
	int dimensiune = 0;
	for (int i = 0; i < nrTractoare; i++) {
		if (tractoare[i].caiPutere == putereMax) {
			(*tractoarePuternice)[dimensiune] = tractoare[i];

			(*tractoarePuternice)[dimensiune].producator = (char*)malloc(strlen(tractoare[i].producator) + 1);
			strcpy((*tractoarePuternice)[dimensiune].producator, tractoare[i].producator);

			(*tractoarePuternice)[dimensiune].model = (char*)malloc(strlen(tractoare[dimensiune].model) + 1);
			strcpy((*tractoarePuternice)[dimensiune].model, tractoare[i].model);
			dimensiune++;
		}
	}

}

void copiazaCeleMaiNoiTractoare(Tractor* tractoare, int nrTractoare, Tractor** tractoareNoi, int* nrTractoareNoi) {
	int minOre = tractoare[0].nrOre;
	for (int i = 0; i < nrTractoare; i++) {
		if (tractoare[i].nrOre < minOre)
			minOre = tractoare[i].nrOre;
	}
	(*nrTractoareNoi) = 0;
	for (int i = 0; i < nrTractoare; i++) {
		if (tractoare[i].nrOre == minOre)
			(*nrTractoareNoi)++;
	}
	if ((*tractoareNoi) != NULL)
		free(*tractoareNoi);
	
	*tractoareNoi = (Tractor*)malloc(sizeof(Tractor) * (*nrTractoareNoi));
	int k = 0;
	for (int i = 0; i < nrTractoare; i++) {
		if (tractoare[i].nrOre == minOre) {
			(*tractoareNoi)[k] = tractoare[i];
			(*tractoareNoi)[k].producator = (char*)malloc(strlen(tractoare[i].producator) + 1);
			strcpy((*tractoareNoi)[k].producator, tractoare[i].producator);
			(*tractoareNoi)[k].model = (char*)malloc(strlen(tractoare[i].model) + 1);
			strcpy((*tractoareNoi)[k].model, tractoare[i].model);
			k++;
		}
	}
}

void dezalocare(Tractor* tractor) {
	if (tractor->producator != NULL) {
		free(tractor->producator);
		tractor->producator = NULL;
	}
	

	if (tractor->model != NULL) {
		free(tractor->model);
		tractor->model = NULL;
	}
	
}

void dezalocareVector(Tractor** tractoare, int* nrTractoare) {
	for (int i = 0; i < nrTractoare; i++) {
		if ((*tractoare)[i].producator != NULL) {
			free((*tractoare)[i].producator);
		}
		if ((*tractoare)[i].model != NULL) {
			free((*tractoare)[i].model);
		}
	}
	free(*tractoare);
	*tractoare = NULL;
	*nrTractoare = 0;
}

void adaugaTractorInVector(Tractor** tractoare, int* nrTractoare, Tractor tractorNou) {
	Tractor* aux = (Tractor*)malloc(sizeof(Tractor) * ((*nrTractoare) + 1));
	for (int i = 0; i < (*nrTractoare); i++) {
		aux[i] = (*tractoare)[i];
	}
	aux[(*nrTractoare)] = tractorNou;
	free(*tractoare);
	(*tractoare) = aux;
	(*nrTractoare)++;
}

Tractor citireTractorFisier(FILE* fisier) {
	Tractor tractor;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, fisier);
	tractor.id = atoi(strtok(buffer, sep));
	char* aux;
	aux = strtok(NULL, sep);
	tractor.producator = (char*)malloc(strlen(aux) + 1);
	strcpy(tractor.producator, aux);

	char* aux1;
	aux1 = strtok(NULL, sep);
	tractor.model = (char*)malloc(strlen(aux1) + 1);
	strcpy(tractor.model, aux1);

	tractor.caiPutere = atoi(strtok(NULL, sep));
	tractor.nrOre = atof(strtok(NULL, sep));

	return tractor;
}

Tractor* citireVectorTractoareFisier(const char* numeFisier, int* nrTractoareCitite) {
	FILE* file = fopen(numeFisier, "r");
	Tractor* tractoare = NULL;
	(*nrTractoareCitite) = 0;
	while (!feof(file)) {
		adaugaTractorInVector(&tractoare, nrTractoareCitite, citireTractorFisier(file));
	}
	fclose(file);
	return tractoare;
}

voidDezalocareVectorMasini(Tractor** tractoare, int* nrTractoare) {
	for (int i = 0; i < nrTractoare; i++) {
		if ((*tractoare)[i].producator != NULL)
			free((*tractoare)[i].producator);
		if ((*tractoare)[i].model != NULL)
			free((*tractoare)[i].model);
	}
	free(*tractoare);
	(*tractoare) = NULL;
	(*nrTractoare) = 0;
}

int main() {
	
	/*afisare(tractor1);
	modificaNrOre(&tractor1, 980);*/
//	modificaProducator(&tractor1, "Massey Ferguson");
	/*afisare(tractor1);
	dezalocare(&tractor1);*/
	
	/*Tractor* tractoare = NULL;
	int nrTractoare = 6;
	tractoare = (Tractor*)malloc(sizeof(Tractor) * nrTractoare);
	tractoare[0] = initializare(1, "Landini", "Power Farm", 120, 1200);
	tractoare[1] = initializare(2, "Case", "Puma", 250, 700);
	tractoare[2] = initializare(3, "John Deere", "8R", 156, 3210);
	tractoare[3] = initializare(4, "Massey Ferguson", "7726S", 302, 15);
	tractoare[4] = initializare(5, "New Holland", "T6", 145, 114);
	tractoare[5] = initializare(6, "Claas", "Power", 302, 0);*/
//	afisareVector(tractoare, 6);
//	printf("\n");
	/*Tractor* tractoarePuternice = NULL;
	int nrTractoarePuternice = 0;*/
//	copiereCeleMaiTractoarePuternice(tractoare, nrTractoare, &tractoarePuternice, &nrTractoarePuternice);
//	afisareVector(tractoarePuternice, nrTractoarePuternice);
	/*Tractor* tractoareNoi = NULL;
	int nrTractoareNoi = 0;
	copiazaCeleMaiNoiTractoare(tractoare, nrTractoare, &tractoareNoi, &nrTractoareNoi);
	afisareVector(tractoareNoi, nrTractoareNoi);*/

	//lucru cu fisiere
	int nrTractoare = 0;
	Tractor* tractoare = citireVectorTractoareFisier("tractoare.txt", &nrTractoare);
	afisareVector(tractoare, nrTractoare);
}