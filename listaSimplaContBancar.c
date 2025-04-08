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
};
typedef struct Nod Nod;


void afisareContBancar(ContBancar cont){
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

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		afisareContBancar(cap->info);
		cap = cap->next;
	}
}

void insereazaNodLaInceput(Nod** cap, ContBancar cont) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = cont;
	nodNou->next = (*cap);
	(*cap) = nodNou;
}

void insereazaNodLaSfarsit(Nod** cap, ContBancar cont) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = cont;
	nodNou->next = NULL;
	if ((*cap)) {
		Nod* p = (*cap);
		while (p->next != NULL)
			p = p->next;
		p->next = nodNou;
	}
	else {
		(*cap) = nodNou;
	}
}

Nod* citireListaDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		insereazaNodLaSfarsit(&cap, citireContBancarDinFisier(f));
	}
	fclose(f);
	return cap;
}

void dezalocareLista(Nod** cap) {
	while ((*cap) != NULL) {
		Nod* aux = (*cap);
		(*cap) = (*cap)->next;
		if (aux->info.titular)
			free(aux->info.titular);
		if (aux->info.tranzactii)
			free(aux->info.tranzactii);
		free(aux);
	}
}

ContBancar afisareContCuCeaMaiMareMedie(Nod* cap) {
	ContBancar cont;
	float medieMax = 0;
	while (cap) {
		float medieLocala = 0;
		for (int i = 0; i < cap->info.nrTranzactii; i++)
			medieLocala += cap->info.tranzactii[i];
		medieLocala /= cap->info.nrTranzactii;
		if (medieLocala > medieMax) {
			cont = cap->info;
			cont.titular = (char*)malloc(strlen(cap->info.titular) + 1);
			strcpy(cont.titular, cap->info.titular);
			cont.tranzactii = (float*)malloc(cap->info.nrTranzactii * sizeof(float));
			for (int i = 0; i < cap->info.nrTranzactii; i++)
				cont.tranzactii[i] = cap->info.tranzactii[i];
			medieMax = medieLocala;
		}
		cap = cap->next;
	}
	return cont;
}

void stergereElementDinLista(Nod** cap, const char* titular) {
	while((*cap) && strcmp((*cap)->info.titular, titular) == 0) {  //nu merge
		Nod* aux = *cap;
		(*cap) = aux->next;
		if (aux->info.titular)
			free(aux->info.titular);
		if (aux->info.tranzactii)
			free(aux->info.tranzactii);
		free(aux);
	}
	Nod* p = *cap;
	while (p && p->next) {
		if (strcmp(p->info.titular, titular) == 0) {
			Nod* aux = p;
			p->next = aux->next;
			if (aux->info.titular)
				free(aux->info.titular);
			if (aux->info.tranzactii)
				free(aux->info.tranzactii);
			free(aux);
		}
		else {
			p = p->next;
		}
	}
}



int main() {

	Nod* lista = citireListaDinFisier("contBancar.txt");
	afisareLista(lista);
	dezalocareLista(&lista);
}