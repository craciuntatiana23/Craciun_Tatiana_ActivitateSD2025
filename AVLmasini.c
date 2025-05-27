#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* f) {
	Masina masina;
	char buffer[100];
	char* aux;
	char sep[4] = ",\n";
	fgets(buffer, 100, f);
	masina.id = atoi(strtok(buffer, sep));
	masina.nrUsi = atoi(strtok(NULL, sep));
	masina.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	masina.model = (char*)malloc(strlen(aux) + 1);
	strcpy_s(masina.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	masina.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy_s(masina.numeSofer, strlen(aux) + 1, aux);
	masina.serie = *strtok(NULL, sep);
	return masina;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int calculeazaInaltimeArbore(Nod* nod) {
	if (nod != NULL)
	{
		int inaltimeDreapta = calculeazaInaltimeArbore(nod->dreapta);
		int inaltimeStanga = calculeazaInaltimeArbore(nod->stanga);
		if (inaltimeDreapta >= inaltimeStanga)
			return inaltimeDreapta + 1;
		else
			return inaltimeStanga + 1;
	}
	else return 0;
	
}

int calculeazaDezechilibrareArbore(Nod* nod) {
	int inaltimeStanga = calculeazaInaltimeArbore(nod->stanga);
	int inaltimeDreapta = calculeazaInaltimeArbore(nod->dreapta);
	return inaltimeStanga - inaltimeDreapta;
}

void rotireDreapta(Nod** nod) {
	Nod* aux = (*nod)->stanga;
	(*nod)->stanga = aux->dreapta;
	aux->dreapta = (*nod);
	(*nod) = aux;
}

void rotireStanga(Nod** nod) {
	Nod* aux = (*nod)->dreapta;
	(*nod)->dreapta = aux->stanga;
	aux->stanga = (*nod);
	(*nod) = aux;
}

void inserareNodInArbore(Nod** nod, Masina masina) {
	if ((*nod) != NULL) {
		if (masina.id < (*nod)->info.id)
			inserareNodInArbore(&(*nod)->stanga, masina);
		else if (masina.id > (*nod)->info.id)
			inserareNodInArbore(&(*nod)->dreapta, masina);
		if (calculeazaDezechilibrareArbore((*nod)) == 2) {
			if (calculeazaDezechilibrareArbore((*nod)->stanga) == -1)
				rotireStanga(&(*nod)->stanga);
			rotireDreapta(nod);
		}
		if (calculeazaDezechilibrareArbore((*nod)) == -2) {
			if (calculeazaDezechilibrareArbore((*nod)->dreapta) == 1)
				rotireDreapta(&(*nod)->dreapta);
			rotireStanga(nod);
		}
	}
	else{
		(*nod) = malloc(sizeof(Nod));
		(*nod)->dreapta = NULL;
		(*nod)->stanga = NULL;
		(*nod)->info = masina;
	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	Nod* nod = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		inserareNodInArbore(&nod, citireMasinaDinFisier(f));
	}
	fclose(f);
	return nod;
}

void afisareSRD(Nod* nod) {
	if (nod != NULL) {
		afisareSRD(nod->stanga);
		afisareMasina(nod->info);
		afisareSRD(nod->dreapta);
	}
}

float sumaMasini(Nod* nod) {
	float suma = 0;
	if (nod != NULL) {
		suma += nod->info.pret;
		if (nod->stanga)
			suma += sumaMasini(nod->stanga);
		if (nod->dreapta)
			suma += sumaMasini(nod->dreapta);
	}
	return suma;
}

Masina getMasinaById(Nod* nod, int id) {
	Masina masina;
	if (nod != NULL) {
		if (nod->info.id == id)
		{
			masina = nod->info;
			return masina;
		}
		if (id < nod->info.id)
			masina = getMasinaById(nod->stanga, id);
		else
			masina = getMasinaById(nod->dreapta, id);
		return masina;
	}
}

void dezalocareArbore(Nod** nod) {
	if ((*nod) != NULL) {
		dezalocareArbore(&(*nod)->dreapta);
		dezalocareArbore(&(*nod)->stanga);
		free((*nod)->info.model);
		free((*nod)->info.numeSofer);
		free((*nod));
		
	}
	(*nod) = NULL;
}

int main() {
	Nod* nod = citireArboreDinFisier("masini_arbore.txt");
	//afisareSRD(nod);
	printf("Valoarea totala: %5.2f\n", sumaMasini(nod));
	Masina masina = getMasinaById(nod, 4);
	afisareMasina(masina);
	dezalocareArbore(&nod);
}