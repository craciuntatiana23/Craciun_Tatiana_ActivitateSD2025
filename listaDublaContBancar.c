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

void afisareLista(ListaDubla lista) {
	Nod* nod = lista.first;
	while (nod) {
		afisareContBancar(nod->info);
		nod = nod->next;
	}
}
void afisareListaInvers(ListaDubla lista) {
	Nod* nod = lista.last;
	while (lista.last)
	{
		afisareContBancar(nod->info);
		nod = nod->prev;
	}

}

void insereazaNodLaInceput(ListaDubla* lista, ContBancar cont) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = cont;
	nodNou->prev = NULL;
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

void insereazaNodLaSfarsit(ListaDubla* lista, ContBancar cont) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = cont;
	nodNou->prev = lista->last;
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

ListaDubla citireListaDinFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	FILE* f = fopen(numeFisier, "r");
	while(!feof(f))
		insereazaNodLaSfarsit(&lista, citireContBancarDinFisier(f));
	fclose(f);
	return lista;
}

void dezalocareLista(ListaDubla* lista) {
	Nod* aux = lista->first;
	while (aux) {
		Nod* p = aux;
		if (p->info.titular)
			free(p->info.titular);
		if (p->info.tranzactii)
			free(p->info.tranzactii);
		free(p);
		aux = aux->next;
	}1
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

int main() {
	ListaDubla lista = citireListaDinFisier("contBancar.txt");
	afisareLista(lista);
	dezalocareLista(&lista);
}