#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ContBancar {
	char* titular;
	int nrTranzactii;
	float* tranzactii;
};
typedef struct ContBancar ContBancar;

struct Nod {
	ContBancar info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

void afisareContBancar(ContBancar cont) {
	printf("\n");
	printf("Titular cont: %s\n", cont.titular);
	printf("Tranzactii: ");
	for (int i = 0; i < cont.nrTranzactii; i++)
		printf("%5.2f ", cont.tranzactii[i]);
	printf("\n");
}

ContBancar citireContBancarDinFisier(FILE* f) {
	ContBancar cont;
	char sep[4] = ",\n";
	char buffer[101];
	char* aux;
	fgets(buffer, 100, f);
	aux = strtok(buffer, sep);
	cont.titular = (char*)malloc(strlen(aux) + 1);
	strcpy(cont.titular, aux);
	cont.nrTranzactii = atoi(strtok(NULL, sep));
	cont.tranzactii = (float*)malloc(cont.nrTranzactii * sizeof(float));
	for (int i = 0; i < cont.nrTranzactii; i++)
		cont.tranzactii[i] = atof(strtok(NULL, sep));
	return cont;

}

void afisareListaDubla(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareContBancar(p->info);
		p = p->next;
	}
}

void afisareListaDublaCoada(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareContBancar(p->info);
		p = p->prev;
	}
}

void adaugaNodInLista(ListaDubla* lista, ContBancar cont) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = cont;
	nodNou->next = NULL;
	nodNou->prev = lista->last;
	if (lista->last) {
		lista->last->next = nodNou;
	}
	else {
		lista->first = nodNou;
	}
	lista->last = nodNou;
	lista->nrNoduri++;
}
void adaugaNodInListaInceput(ListaDubla* lista, ContBancar cont) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = cont;
	nodNou->next = lista->first;
	nodNou->prev = NULL;
	if (lista != NULL) {
		lista->first->prev = nodNou;
	}
	else {
		lista->last = nodNou;
	}
	lista->first = nodNou;
	lista->nrNoduri++;
}

ListaDubla citireListaDublaFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		adaugaNodInLista(&lista, citireContBancarDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareListaDubla(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->info.titular)
			free(aux->info.titular);
		if (aux->info.tranzactii)
			free(aux->info.tranzactii);
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

int main() {
	ListaDubla lista = citireListaDublaFisier("contBancar.txt");
	afisareListaDubla(lista);
	dezalocareListaDubla(&lista);
}