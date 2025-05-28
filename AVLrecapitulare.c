#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

struct StructuraMasina 
{
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
Masina citireMasinaFisier(FILE* f) {
	Masina masina;
	char buffer[100];
	char* aux;
	char sep[4] = ",\n";
	fgets(buffer, 100, f);
	masina.id = atoi(strtok(buffer, sep));
	masina.nrUsi = atoi(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	masina.model = (char*)malloc(strlen(aux) + 1);
	strcpy(masina.model, aux);
	aux = strtok(NULL, sep);
	masina.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(masina.numeSofer, aux);
	masina.serie = *strtok(NULL, sep);
	return masina;
}

void afisareMasina(Masina masina) 
{
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int inaltimeArbore(Nod* nod) {
	if (nod != NULL)
	{
		int inaltimeDreapta = inaltimeArbore(nod->dreapta);
		int inaltimeStanga = inaltimeArbore(nod->stanga);
		if (inaltimeStanga > inaltimeDreapta)
			return inaltimeStanga + 1;
		else
			return inaltimeDreapta + 1;
	}
	else
		return 0;
}

int echilibru(Nod* nod) {
	return inaltimeArbore(nod->stanga) - inaltimeArbore(nod->dreapta);
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
		if (echilibru(*nod) == 2) {
			if (echilibru((*nod)->stanga) == -1)
				rotireStanga(&(*nod)->stanga);
			rotireDreapta(nod);
		}
		if (echilibru(*nod) == -2) {
			if (echilibru((*nod)->dreapta) == 1) {
				rotireDreapta(&(*nod)->dreapta);
			}
			rotireStanga(nod);
		}
	}
	else {
		(*nod) = (Nod*)malloc(sizeof(Nod));
		(*nod)->info = masina;
		(*nod)->stanga = NULL;
		(*nod)->dreapta = NULL;
	}
}

Nod* citireDinFisier(const char* numeFisier) {
	Nod* nod = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		inserareNodInArbore(&nod, citireMasinaFisier(f));
	}
	fclose(f);
	return nod;
}

void afisareArboreSRD(Nod* nod) {
	if (nod != NULL) {
		afisareArboreSRD(nod->stanga);
		afisareMasina(nod->info);
		afisareArboreSRD(nod->dreapta);
	}
}

void dezalocare(Nod** nod) {
	if ((*nod) != NULL) {
		dezalocare(&(*nod)->stanga);
		dezalocare(&(*nod)->dreapta);
		free((*nod)->info.model);
		free((*nod)->info.numeSofer);
		free(*nod);
	}
	(*nod) = NULL;
}

float calculeazaPretulMasinilorUnuiSofer(Nod* nod,  const char* numeSofer) {
	float pret = 0;
	if (nod != NULL) {
		if (strcmp(nod->info.numeSofer, numeSofer) == 0)
			pret += nod->info.pret;
		if (nod->dreapta != NULL)
			pret += calculeazaPretulMasinilorUnuiSofer(nod->dreapta, numeSofer);
		if (nod->stanga != NULL)
			pret += calculeazaPretulMasinilorUnuiSofer(nod->stanga, numeSofer);
	}
	return pret;
}

int main() {
	Nod* nod = citireDinFisier("masini_arbore.txt");
	//afisareArboreSRD(nod);
	printf("valoare masini %.2f ", calculeazaPretulMasinilorUnuiSofer(nod, "Gigel"));
	dezalocare(&nod);
	
}