#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	Masina masina;
	struct Nod* next;
};
typedef struct Nod Nod;

//creare structura pentru tabela de dispersie

// aceasta este un vector de liste
struct HashTable {
	Nod** tabela;
	int dim;
};
typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	//afiseaza toate elemente de tip masina din lista simpla inlantuita
	//prin apelarea functiei afisareMasina()
	while (cap) {
		afisareMasina(cap->masina);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod* cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* p = cap;
	while (p->next) {
		p = p->next;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->next = NULL;
	p->next = nou;
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++)
		ht.tabela[i] = NULL;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	return ht;
}

int calculeazaHash(const char* nume ,int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii
	int suma = 0;
	for (int i = 0; i < strlen(nume); i++) {
		suma += nume[i];
	}
	return suma % dimensiune;
}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	int pozitie = calculeazaHash(masina.numeSofer, hash.dim);
	if (hash.tabela[pozitie] == NULL) {
		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->masina = masina;
		hash.tabela[pozitie]->next = NULL;
	}
	else {
		adaugaMasinaInLista(hash.tabela[pozitie], masina);
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		inserareMasinaInTabela(hash, masina);
	}
	fclose(f);
	return hash;
}

void afisareTabelaDeMasini(HashTable ht) {
	//sunt afisate toate masinile cu evidentierea clusterelor realizate
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			printf("masinile de pe poz %d sunt: \n", i);
			afisareListaMasini(ht.tabela[i]);
		}
		else {
			printf("pe poz %d nu avem masini\n", i);
		}
	}
}

void dezalocareListaMasini(Nod** cap) {
	Nod* p = (*cap);
	while (p) {
		Nod* temp = p;
		p = p->next;
		if (temp->masina.model != NULL)
			free(temp->masina.model);
		if (temp->masina.numeSofer != NULL)
			free(temp->masina.numeSofer);
		free(temp);
	}
	*cap = NULL;
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	//sunt dezalocate toate masinile din tabela de dispersie
	for (int i = 0; i < ht->dim; i++) {
		dezalocareListaMasini(&(ht->tabela[i]));
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;
}
float calculeazaMedieLista(Nod* cap) {
	float suma = 0;
	int nrElemente = 0;
	while (cap != NULL) {
		suma += cap->masina.pret;
		nrElemente++;
		cap = cap->next;
	}
	if (nrElemente > 0)
		return suma / nrElemente;
	else
		return 0;
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	//calculeaza pretul mediu al masinilor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin masini
	*nrClustere = 0;
	float* preturi = NULL;
	for (int i = 0; i < ht.dim; i++)
		if (ht.tabela[i] != NULL)
			(*nrClustere)++;
	preturi = (float*)malloc(sizeof(float) * (*nrClustere));
	int contor = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL)
			preturi[contor] = calculeazaMedieLista(ht.tabela[i]);
		contor++;
	}
	return preturi;
}

Masina getMasinaDinLista(Nod* cap, const char* nume) {
	Masina m;
	m.id = -1;
	while (cap && strcmp(cap->masina.numeSofer, nume) != 0)
		cap = cap->next;
	if (cap)
	{
		m = cap->masina;
		m.model = (char*)malloc(sizeof(char) * strlen(cap->masina.model) + 1);
		strcpy(m.model, cap->masina.model);
		m.numeSofer = (char*)malloc(sizeof(char) * strlen(cap->masina.numeSofer) + 1);
		strcpy(m.numeSofer, cap->masina.numeSofer);
	}
	return m;
}

Masina getMasinaDupaNumeSofer(HashTable ht, const char* numeCautat) {
	Masina m;
	m.id = -1;
	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei 
	int poz = calculeazaHash(numeCautat, ht.dim);
	if (poz >= 0 && poz < ht.dim) {
		return getMasinaDinLista(ht.tabela[poz], numeCautat);
	}
	else
		return m;
}

int main() {

	HashTable ht = citireMasiniDinFisier("masini.txt", 7);
	afisareTabelaDeMasini(ht);
	int nrClustere = 0;
	float* preturi = calculeazaPreturiMediiPerClustere(ht, &nrClustere);
	printf("preturile medii \n");
	for (int i = 0; i < nrClustere; i++)
		printf("%5.2f  ", preturi[i]);
	Masina m = getMasinaDupaNumeSofer(ht, "Ionescu");
	printf("masina cautata: \n");
	afisareMasina(m);
	if (m.model != NULL)
		free(m.model);
	if (m.numeSofer != NULL)
		free(m.numeSofer);
	dezalocareTabelaDeMasini(&ht);

	return 0;
}