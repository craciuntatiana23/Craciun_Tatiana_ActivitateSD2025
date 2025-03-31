#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produs {
	int id;
	char* denumire;
	int stoc;
	char* distribuitor;
};
typedef struct Produs Produs;

struct Nod {
	Produs info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	int nrNoduri;
	Nod* first;
	Nod* last;
};
typedef struct ListaDubla ListaDubla;

Produs citireProdusDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Produs p1;
	p1.id = atoi(strtok(buffer, sep));
	aux = strtok(NULL, sep);
	p1.denumire = (char*)malloc(strlen(aux) + 1);
	strcpy(p1.denumire, aux);
	p1.stoc = atoi(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	p1.distribuitor = (char*)malloc(strlen(aux) + 1);
	strcpy(p1.distribuitor, aux);
	return p1;
}

void afisareProdus(Produs produs) {
	printf("Id: %d\n", produs.id);
	printf("Denumire: %s\n", produs.denumire);
	printf("Stoc: %d\n", produs.stoc);
	printf("Distribuitor: %s\n", produs.distribuitor);
	printf("\n");
}

void afisareListaProduse(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareProdus(p->info);
		p = p->next;
	}
}

void adaugaProdusLaSfarsit(ListaDubla* lista, Produs produs) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->next = NULL;
	nod->info = produs;
	nod->prev = lista->last;
	if (lista->last != NULL)
		lista->last->next = nod;
	else
		lista->first = nod;
	lista->last = nod;
	lista->nrNoduri++;
}
void adaugaProdusLaInceput(ListaDubla* lista, Produs produs) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->next = lista->first;
	nod->info = produs;
	nod->prev = NULL;
	if (lista->first != NULL)
		lista->first->prev = nod;
	else
		lista->last = nod;
	lista->first = nod;
	lista->nrNoduri++;
}
ListaDubla citireListaProduseDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	while (!feof(f)) {
		adaugaProdusLaSfarsit(&lista, citireProdusDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocare(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->info.denumire) {
			free(aux->info.denumire);
		}
		if (aux->info.distribuitor) {
			free(aux->info.distribuitor);
		}
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

void stergereProdusDupaId(ListaDubla* lista, int id) {
	Nod* p = lista->first;
	while (p && p->info.id != id)
		p = p->next;
	if (p == NULL)
		return;
	if (p->prev == NULL) {
		lista->first = p->next;
		if (lista->first)
			lista->first->prev = NULL;
	}
	else {
		p->prev->next = p->next;
	}
	if (p->next != NULL) {
		p->next->prev = p->prev;
	}
	else {
		lista->last = p->prev;
	}
	if (p->info.denumire) {
		free(p->info.denumire);
	}
	if (p->info.distribuitor) {
		free(p->info.distribuitor);
	}
	free(p);
	lista->nrNoduri--;
}
	
char* getNumeProdusStocMaxim(ListaDubla lista) {
	if (lista.first) {
		Nod* max = lista.first;
		Nod* p = lista.first->next;
		while (p) {
			if (p->info.stoc > max->info.stoc)
				max = p;
			p = p->next;
		}
		char* nume = (char*)malloc(strlen(max->info.denumire) + 1);
		strcpy(nume, max->info.denumire);
		return nume;
	}
}

int main() {
	ListaDubla lista = citireListaProduseDinFisier("produse.txt");
	afisareListaProduse(lista);
	char* nume = getNumeProdusStocMaxim(lista);
	printf("\n denumire: %s \n", nume);
	stergereProdusDupaId(&lista, 3);
	afisareListaProduse(lista);
}