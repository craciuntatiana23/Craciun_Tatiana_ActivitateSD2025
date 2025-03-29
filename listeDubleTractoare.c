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
	struct Nod* prev;
};
typedef struct Nod Nod;

struct listaDubla {
	Nod* first;
	Nod* last;
	Nod* nrNoduri;
};
typedef struct listaDubla listaDubla;

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

void afisareListaTractoareInceput(listaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareTractor(p->info);
		p = p->next;
	}
}
void afisareListaTractorSfarsit(listaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareTractor(p->info);
		p = p->prev;
	}
}

void adaugaTractorInceput(listaDubla* lista, Tractor tractor) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->prev = NULL;
	nodNou->info = tractor;
	nodNou->next = lista->first;
	if (lista->first) {
		lista->first->prev = nodNou;
	}
	else {
		lista->last = nodNou;
	}
	lista->first = nodNou;
	lista->nrNoduri++;
}

void adaugaTractorSfarsit(listaDubla* lista, Tractor tractor) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->prev = lista->last;
	nodNou->info = tractor;
	nodNou->next = NULL;
	if (lista->last) {
		lista->last->next = nodNou;
	}
	else {
		lista->first = nodNou;
	}
	lista->last = nodNou;
	lista->nrNoduri++;
}

listaDubla citireListaDinFisier(const char* numeFisier) {
	listaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		adaugaTractorSfarsit(&lista, citireTractorFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareTractoare(listaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		p = p->next;
		Nod* aux = p;
		if (aux->info.producator) {
			free(aux->info.producator);
		}
		if (aux->info.model) {
			free(aux->info.model);
		}
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
	
}
char* getProducatorMaxCai(listaDubla lista) {
	if (lista.first) {
		Nod* max = lista.first;
		Nod* p = lista.first->next;
		while (p) {
			if (p->info.caiPutere > max->info.caiPutere)
				max = p;
			p = p->next;
		}
		char* nume = (char*)malloc(strlen(max->info.producator) + 1);
		strcpy_s(nume, strlen(max->info.producator) + 1, max->info.producator);
		return nume;
	}
	else
		return NULL;
}
void stergereTractorDupaId(listaDubla* lista, int id) {
	if (lista->first == NULL)
		return;
	Nod* p = lista->first;
	while (p && p->info.id != id)
		p = p->next;
	if (p == NULL)
		return;
	if (p->prev == NULL) {
		lista->first = p->next;
		if (lista->first)
			lista->first->prev == NULL;

	}
	else
		p->prev->next = p->next;
	if (p->next != NULL)
		p->next->prev = p->prev;
	else
		lista->last = p->prev;

	if (p->info.producator) {
		free(p->info.producator);
	}
	if (p->info.model) {
		free(p->info.model);
	}
	free(p);
	lista->nrNoduri--;
}

int main() {
	listaDubla lista = citireListaDinFisier("tractoare.txt");
	afisareListaTractoareInceput(lista);
	printf("----------------------");
	afisareListaTractorSfarsit(lista);
	char* producator = getProducatorMaxCai(lista);
	printf("\nproducator: %s\n", producator);
	if (producator)
		free(producator);
	dezalocareTractoare(&lista);
}
