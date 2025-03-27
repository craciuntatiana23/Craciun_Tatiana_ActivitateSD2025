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
		while (!feof(f)) {
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

float medieOre(Nod* cap) {
	float suma = 0;
	int nrTractoare = 0;
	while (cap != NULL) {
		suma += cap->info.nrOre;
		nrTractoare++;
		cap = cap->next;
	}
	if (nrTractoare == 0)
		return 0;
	else
		return suma / nrTractoare;
}

float medieCaiTractoareAcelasiProducator(Nod* cap, const char* producator) {
	int suma = 0;
	int nrTractoare = 0;
	while (cap != NULL) {
		if (strcmp(cap->info.producator, producator) == 0) {
			suma += cap->info.caiPutere;
			nrTractoare++;
		}
		cap = cap->next;
	}
	if (nrTractoare == 0)
		return 0;
	else
		return suma / nrTractoare;
}

void stergereTractorProducator(Nod** cap, const char* producator) {
	while ((*cap) && strcmp((*cap)->info.producator, producator) == 0) {
		Nod* aux = *cap;
		(*cap) = aux->next;
		if (aux->info.producator)
			free(aux->info.producator);
		if (aux->info.model)
			free(aux->info.model);
		free(aux);
	}
	if ((*cap)) {
		Nod* p = *cap;
		while (p) {
			while (p->next && strcmp(p->next->info.producator, producator) != 0) {
				p = p->next;
			}
			if (p->next) {
				Nod* aux = p->next;
				p->next = aux->next;
				if (aux->info.producator)
					free(aux->info.producator);
				if (aux->info.model)
					free(aux->info.model);
				free(aux);
			}
			else {
				p = p->next;
			}
		}
	}
}


int main() {
	Nod* cap = citireListaTractoareDinFisier("tractoare.txt");
	afisareListaTractoare(cap);
	float medie = medieOre(cap);
	printf("\nmedie ore %f \n", medie);
	float medie2 = medieCaiTractoareAcelasiProducator(cap, "Landini");
	printf("\nmedie ore landini %f \n", medie2);
	printf("\nstergere tractor\n");
	stergereTractorProducator(&cap, "Landini");
	afisareListaTractoare(cap);
	return 0;
}