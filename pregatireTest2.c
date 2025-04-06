#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Franciza {
	char* nume;
	char* taraOrigine;
	int anInfiintare;
	int nrAniMonitorizati;
	float* venitAnual;
};
typedef struct Franciza Franciza;

void afisareFranciza(Franciza franciza) {
	printf("\n");
	printf("Nume franciza: %s\n", franciza.nume);
	printf("Tara origine: %s\n", franciza.taraOrigine);
	printf("Venit anual: ");
	for (int i = 0; i < franciza.nrAniMonitorizati; i++)
		printf("%5.2f ", franciza.venitAnual[i]);
	printf("\n");
	printf("\n");
}

void afisareVectorFrancize(Franciza* vectorFrancize, int nrFrancize) {
	for (int i = 0; i < nrFrancize; i++)
		afisareFranciza(vectorFrancize[i]);
}

void adaugaFrancizaInVector(Franciza** vectorFrancize, int* nrFrancize, Franciza franciza) {
	Franciza* aux = (Franciza*)malloc(((*nrFrancize) + 1) * sizeof(Franciza));
	for (int i = 0; i < (*nrFrancize); i++)
		aux[i] = (*vectorFrancize)[i];
	aux[(*nrFrancize)] = franciza;
	free(*vectorFrancize);
	(*vectorFrancize) = aux;
	(*nrFrancize)++;
}



Franciza citireFrancizaDinFisier(FILE* file) {
	Franciza franciza;
	char buffer[100];
	char sep[4] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	aux = strtok(buffer, sep);
	franciza.nume = (char*)malloc(strlen(aux) + 1);
	strcpy(franciza.nume, aux);
	aux = strtok(NULL, sep);
	franciza.taraOrigine = (char*)malloc(strlen(aux) + 1);
	strcpy(franciza.taraOrigine, aux);
	franciza.anInfiintare = atoi(strtok(NULL, sep));
	franciza.nrAniMonitorizati = atoi(strtok(NULL, sep));
	franciza.venitAnual = (float*)malloc(franciza.nrAniMonitorizati * sizeof(float));
	for (int i = 0; i < franciza.nrAniMonitorizati; i++)
		franciza.venitAnual[i] = atof(strtok(NULL, sep));
	return franciza;

}



Franciza* citireVectorFrancizeDinFisier(const char* numeFisier, int* nrFrancizeCitite) {
	FILE* f = fopen(numeFisier, "r");
	Franciza* francize = NULL;
	(*nrFrancizeCitite) = 0;
	while (!feof(f)) {
		adaugaFrancizaInVector(&francize, nrFrancizeCitite, citireFrancizaDinFisier(f));
	}
	fclose(f);
	return francize;
}


void dezalocareVectorObiecte(Franciza** vectorObiecte, int* nrObiecte) {
	for (int i = 0; i < (*nrObiecte); i++) {
		if ((*vectorObiecte)[i].nume) {
			free((*vectorObiecte)[i].nume);
			(*vectorObiecte)[i].nume = NULL;
		}
		if ((*vectorObiecte)[i].taraOrigine) {
			free((*vectorObiecte)[i].taraOrigine);
			(*vectorObiecte)[i].taraOrigine = NULL;
		}
		if ((*vectorObiecte)[i].venitAnual) {
			free((*vectorObiecte)[i].venitAnual);
			(*vectorObiecte)[i].venitAnual = NULL;
		}
	}
	free(*vectorObiecte);
	(*vectorObiecte) = NULL;
	(*nrObiecte) = 0;
}

int main() {
	int nr = 0;
	Franciza* vector = citireVectorFrancizeDinFisier("francize.txt", &nr);
	afisareVectorFrancize(vector, nr);
	dezalocareVectorObiecte(&vector, &nr);
	return 0;
}