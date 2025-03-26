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

struct Nod {
	Tractor info;
	struct Nod* next;
};
typedef struct Nod Nod;

Tractor citireTractorFisier(FILE* fisier) {
	Tractor tractor;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, fisier);
	char* aux;

	tractor.id = atoi(strtok(buffer, sep));
	
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

void afisareTractor(Tractor tractor) {
	printf("\n");
	printf("ID: %d \n", tractor.id);
	printf("Producator: %s \n", tractor.producator);
	printf("Model: %s \n", tractor.model);
	printf("Cai putere: %d \n", tractor.caiPutere);
	printf("Nr ore: %5.2f \n", tractor.nrOre);
	printf("\n");
}

void afisareListaTractoare(Nod* cap) {
	while (cap) {
		afisareTractor(cap->info);
		cap = cap->next;
	}
}

void adaugaTractorInLista(Nod** cap, Tractor tractorNou) {
	//adaug la coada
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = tractorNou;
	nodNou->next = NULL;
	if (*cap != NULL) {
		Nod* p = *cap;
		while (p->next != NULL)
			p = p->next;
		p->next = nodNou;
	}
	else {
		*cap = nodNou;
	}
}

void adaugaLaInceputInLista(Nod** cap, Tractor tractorNou) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = tractorNou;
	nodNou->next = *cap;
	*cap = nodNou;
}

Nod* citireListaTractoareDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if(f)
	{
		while (f != NULL) {
			adaugaTractorInLista(&cap, citireTractorFisier(f));
		}
	}
	fclose(f);
	return cap;
}

void dezalocareLista(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		*cap = p->next;
		if(p->info.model)
		{
			free(p->info.model);
		}
		if (p->info.producator)
		{
			free(p->info.producator);
		}
		free(p);
	}
}


int main() {
	
	return 0;
}