
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
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	Nod** vector;
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
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod** cap,  Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* temp = (Nod*)malloc(sizeof(Nod));
	temp->info = masinaNoua;
	temp->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = temp;
	}
	else {
		Nod* aux = (*cap);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = temp;
	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	ht.dim = dimensiune;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	
	return ht;
}

int calculeazaHash(const char* cheieSofer, int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii
	int suma = 0;
	for (int i = 0; i < strlen(cheieSofer); ++i) {
		suma += (int)cheieSofer[i];
	}
	if(dimensiune != 0)
		return suma %= dimensiune;
	else
		return -1;
}

void inserareMasinaInTabela(HashTable hash, Masina masina) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	int poz = calculeazaHash(masina.numeSofer, hash.dim);
	if (hash.vector[poz] == NULL) {  //nu avem coliziune
		adaugaMasinaInLista(&(hash.vector[poz]), masina);
	}
	else {
		// avem coliziune
		adaugaMasinaInLista(&(hash.vector[poz]), masina);
	}
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dim) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	HashTable hash = initializareHashTable(dim);
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
		printf("lantul %d\n ", i + 1);
		afisareListaMasini(ht.vector[i]);
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	//sunt dezalocate toate masinile din tabela de dispersie
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	//calculeaza pretul mediu al masinilor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin masini
	return NULL;
}

Masina getMasinaDupaCheie(HashTable ht, const char* numeSofer) {
	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei 
	Masina m;
	m.id = -1;
	int pozitie = calculeazaHash(numeSofer, ht.dim);
	if (!(pozitie >= 0 && pozitie < ht.dim && ht.vector[pozitie] != NULL))
		return m;
	Nod* aux = ht.vector[pozitie];
	while (aux != NULL && strcmp(aux->info.numeSofer, numeSofer) != 0)
		aux = aux->next;
	if (aux != NULL) {
		m.numeSofer = (char*)malloc(strlen(numeSofer) + 1);
		strcpy(m.numeSofer, numeSofer);
		m.model = (char*)malloc(strlen(aux->info.model) + 1);
		strcpy(m.model, aux->info.model);
		m.id = aux->info.id;
		m.nrUsi = aux->info.nrUsi;
		m.pret = aux->info.pret;
		m.serie = aux->info.serie;
		
	}
	return m;
}

int main() {
	HashTable hash;
	hash = citireMasiniDinFisier("masini.txt", 5);
	afisareTabelaDeMasini(hash);
	printf("masina lui ionescu este: \n");
	Masina masina;
	masina = getMasinaDupaCheie(hash, "Ionescu");
	afisareMasina(masina);
	free(masina.model);
	free(masina.numeSofer);
	return 0;
}
