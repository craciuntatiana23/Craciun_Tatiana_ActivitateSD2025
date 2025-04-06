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

struct Nod {
	Franciza info;
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


void afisareFranciza(Franciza franciza) {
	printf("\n");
	printf("Nume franciza: %s\n", franciza.nume);
	printf("Tara origine: %s\n", franciza.taraOrigine);
	printf("An infiintare: %d\n", franciza.anInfiintare);
	printf("Venit anual: ");
	for (int i = 0; i < franciza.nrAniMonitorizati; i++)
		printf("%5.2f ", franciza.venitAnual[i]);
	printf("\n");
	printf("\n");
}

Franciza citireFrancizaDinFisier(FILE* f) {
	Franciza franciza;
	char buffer[101];
	char sep[4] = ",\n";
	fgets(buffer, 100, f);
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
	for (int i = 0; i < franciza.nrAniMonitorizati; i++) {
		franciza.venitAnual[i] = atof(strtok(NULL, sep));
	}
	return franciza;
}

void afisareListaFrancize(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareFranciza(p->info);
		p = p->next;
	}
}

void adaugaFrancizaInListaLaInceput(ListaDubla* lista, Franciza franciza) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = franciza;
	nodNou->prev = NULL;
	nodNou->next = lista->first;
	if (lista) {
		lista->first->prev = nodNou;
	}
	else {
		lista->last = nodNou;
	}
	lista->first = nodNou;
	lista->nrNoduri++;
}

void adaugaFrancizaInListaLaSfarsit(ListaDubla* lista, Franciza franciza) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = franciza;
	nodNou->prev = lista->last;
	nodNou->next = NULL;
	if (lista->last != NULL) {
		lista->last->next = nodNou;
	}
	else {
		lista->first = nodNou;
	}
	lista->last = nodNou;
	lista->nrNoduri++;
}

ListaDubla citireListaDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = NULL;
	while (!feof(f)) {
		adaugaFrancizaInListaLaSfarsit(&lista, citireFrancizaDinFisier(f));
	}
	fclose(f);
	return lista;
}



void dezalocareLista(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->info.nume)
			free(aux->info.nume);
		if (aux->info.taraOrigine)
			free(aux->info.taraOrigine);
		if (aux->info.venitAnual)
			free(aux->info.venitAnual);
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

float venitMediuAnual(ListaDubla lista) {
	Nod* p = lista.first;
	float medie = 0;
	int contor = 0;
	while (p) {
		if (p->info.nrAniMonitorizati > 0) {
			for (int i = 0; i < p->info.nrAniMonitorizati; i++)
			{
				medie += p->info.venitAnual[i];
				contor++;
			}
		}
		p = p->next;
	}
	if (contor > 0)
		return medie / contor;
	else
		return 0;
	
}

void stergereFrancizaDupaAnInfiintare(ListaDubla* lista, int anInfiintare) {
	if (lista->first == NULL)
		return;
	Nod* p = lista->first;
	while (p != NULL && p->info.anInfiintare != anInfiintare) {
		p = p->next;
	}
	if (p == NULL) {
		return;
	}
	if (p->prev == NULL) {
		lista->first = p->next;
		if (lista->first)
			lista->first->prev = NULL;
	}
	else
		p->prev->next = p->next;
	if (p->next != NULL)
		p->next->prev = p->prev;
	else
		lista->last = p->prev;
	if (p->info.nume)
		free(p->info.nume);
	if (p->info.taraOrigine)
		free(p->info.taraOrigine);
	if (p->info.venitAnual)
		free(p->info.venitAnual);
	free(p);
	lista->nrNoduri--;

}

int main() {
	ListaDubla lista = citireListaDinFisier("francize.txt");
	afisareListaFrancize(lista);
	float medie = venitMediuAnual(lista);
	printf("======medie====\n");
	printf("%5.2f ", medie);
	stergereFrancizaDupaAnInfiintare(&lista, 2000);
	afisareListaFrancize(lista);
	dezalocareLista(&lista);
}