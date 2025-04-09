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
	ContBancar cont;
	struct Nod* next;
};
typedef struct Nod Nod;

struct HashTable {
	Nod** tabela;
	int dim;
};
typedef struct HashTable HashTable;

void afisareCont(ContBancar cont) {
	printf("\n");
	printf("Titular: %s\n", cont.titular);
	printf("Tranzactii: ");
	for (int i = 0; i < cont.nrTranzactii; i++)
		printf("%5.2f ", cont.tranzactii[i]);
	printf("\n");
}

ContBancar citireContDinFisier(FILE* f) {
	ContBancar cont;
	char sep[4] = ",\n";
	char buffer[101];
	fgets(buffer, 100, f);
	char* aux;
	aux = strtok(buffer, sep);
	cont.titular = (char*)malloc(strlen(aux) + 1);
	strcpy(cont.titular, aux);
	cont.nrTranzactii = atoi(strtok(NULL, sep));
	cont.tranzactii = (float*)malloc(cont.nrTranzactii * sizeof(float));
	for (int i = 0; i < cont.nrTranzactii; i++)
		cont.tranzactii[i] = atof(strtok(NULL, sep));
	return cont;
}

void afisareListaSimpla(Nod* cap) {
	while (cap) {
		afisareCont(cap->cont);
		cap = cap->next;
	}
}

void adaugareContInLista(Nod** cap, ContBancar cont) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->cont = cont;
	nodNou->next = NULL;
	if ((*cap) != NULL) {
		Nod* p = *cap;
		while (p->next)
			p = p->next;
		p->next = nodNou;
	}
	else {
		(*cap) = nodNou;
	}
}

Nod* citireListaDinFisier(const char* numeFisier) {
	Nod* lista = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		adaugareContInLista(&lista, citireContDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocare(Nod** cap) {
	while (*cap) {
		Nod* p = (*cap);
		(*cap) = (*cap)->next;
		if (p->cont.titular)
			free(p->cont.titular);
		if (p->cont.tranzactii)
			free(p->cont.tranzactii);
		free(p);
	}
}

int calculHash(int lungime, int dimensiune) {
	return lungime % dimensiune;
}

HashTable initializareTabela(int dimensiune) {
	HashTable hash;
	hash.dim = dimensiune;
	hash.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++)
		hash.tabela[i] = NULL;
	return hash;
}

void inserareInTabela(HashTable hash, ContBancar cont) {
	int pozitie = calculHash(strlen(cont.titular), hash.dim);
	if (hash.tabela[pozitie] == NULL) {
		adaugareContInLista(&(hash.tabela[pozitie]), cont);
	}
	else {
		adaugareContInLista(&(hash.tabela[pozitie]), cont);
	}
}

HashTable citireTabelaDinFisier(const char* numeFisier, int dim) {
	HashTable hash = initializareTabela(dim);
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		inserareInTabela(hash, citireContDinFisier(f));
	}
	fclose(f);
	return hash;
}
void afisareTabela(HashTable hash) {
	for (int i = 0; i < hash.dim; i++) {
		if (hash.tabela[i] != NULL)
		{
			printf("pe pozitia %d se afla nodurile:\n", i);
			afisareListaSimpla(hash.tabela[i]);
		}
		else {
			printf("pe pozitia %d nu se afla noduri:\n", i);
		}
	}
}

void dezalocareTabela(HashTable* hash) {
	for (int i = 0; i < hash->dim; i++) {
		if (hash->tabela[i] != NULL)
		{
			dezalocare(&(hash->tabela[i]));
		}	
	}
	free(hash->tabela);
	hash->tabela = NULL;
	hash->dim = 0;
}



int main() {
	HashTable hash = citireTabelaDinFisier("contBancar.txt", 5);
	afisareTabela(hash);
	dezalocare(&hash);
}