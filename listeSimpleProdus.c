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
};
typedef struct Nod Nod;

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

void afisareListaProduse(Nod* cap) {

	while (cap != NULL) {
		afisareProdus(cap->info);
		cap = cap->next;
	}
}

void adaugaProdusLaSfarsitInLista(Nod** cap, Produs produs) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = produs;
	nodNou->next = NULL;
	if ((*cap)) {
		Nod* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nodNou;
	}
	else {
		(*cap) = nodNou;
	}
}

void adaugaProdusLaInceputInLista(Nod** cap, Produs produs) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = produs;
	nodNou->next = *cap;
	*cap = nodNou;
}
Nod* citireListaProduseDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		adaugaProdusLaSfarsitInLista(&cap, citireProdusDinFisier(f));
	}
	fclose(f);
	return cap;
}

void dezalocareListaMasini(Nod** cap) {
	while ((*cap)) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.denumire)
			free(p->info.denumire);
		if (p->info.denumire)
			free(p->info.denumire);
		free(p);
	}
}

char* numeProdusCuCelMaiMareStoc(Nod* cap) {
	int stocMax = 0;
	char* denumireProdus = NULL;
	while (cap) {
		if (cap->info.stoc > stocMax)
		{
			stocMax = cap->info.stoc;
			denumireProdus = (char*)malloc(strlen(cap->info.denumire) + 1);
			strcpy(denumireProdus, cap->info.denumire);
		}
		cap = cap->next;
	}
	return denumireProdus;
}

void stergeProdusDeLaDistribuitor(Nod** cap, const char* distribuior) {
	while ((*cap) && strcmp((*cap)->info.distribuitor, distribuior) == 0) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.denumire)
			free(p->info.denumire);
		if (p->info.distribuitor)
			free(p->info.distribuitor);
		free(p);
	}
	if ((*cap)) {
		Nod* aux = *cap;
		while (aux) {
			while (aux->next && strcmp(aux->info.distribuitor, distribuior) != 0)
				aux = aux->next;
			if (aux->next) {
				Nod* p = aux->next;
				aux->next = p->next;
				if (p->info.denumire)
					free(p->info.denumire);
				if (p->info.distribuitor)
					free(p->info.distribuitor);
				free(p);
			}
			else
				aux = NULL;
		}

	}
}

int main() {
	Nod* cap = citireListaProduseDinFisier("produse.txt");
	afisareListaProduse(cap);
	//char* nume = numeProdusCuCelMaiMareStoc(cap);
	//printf("nume produs %s ", nume);
	stergeProdusDeLaDistribuitor(&cap, "Plasty");
	afisareListaProduse(cap);
}
