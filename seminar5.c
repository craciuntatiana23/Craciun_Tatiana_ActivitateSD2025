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

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

//creare structura pentru Lista Dubla 

struct listaDubla {
	Nod* first;
	Nod* last;
};
typedef struct listaDubla listaDubla;

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

void afisareListaMasiniDeLaInceput(listaDubla lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.first;
		while (p) {
			afisareMasina(p->info);
			p = p->next;
	}
}


void adaugaMasinaInListaLaSfarsit(listaDubla* lista ,Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;
	nodNou->prev = lista->last;
	if (lista->last != NULL) {
		lista->last->next = nodNou;
	}
	else {
		lista->first = nodNou;
	}
	lista->last = nodNou;
}

void adaugaLaInceputInLista(listaDubla* lista,  Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
	Nod* aux = (Nod*)malloc(sizeof(Nod));
	aux->info = masinaNoua;
	aux->prev = NULL;
	aux->next = lista->first;
	if(lista->first != NULL)
	{
		lista->first->prev = aux;
	}
	else {
		lista->first = aux;
	}
	lista->first = aux;

}

listaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	listaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	while (!feof(f)) {
		Masina aux = citireMasinaDinFisier(f);
		adaugaMasinaInListaLaSfarsit(&lista, aux); //shallow
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(listaDubla* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	while (lista->first != NULL) {
		Nod* aux = lista->first;
		free(aux->info.numeSofer);
		free(aux->info.model);
		lista->first = lista->first->next;
		free(aux);
	}
	lista->last = NULL;
}

float calculeazaPretMediu(listaDubla lista) {
	//calculeaza pretul mediu al masinilor din lista.
	float suma = 0;
	int k = 0;
	while (lista.first != NULL) {
		suma += lista.first->info.pret;
		k++;
		lista.first = lista.first->next;
		
	}
	if (k == 0)
		return 0;
	else
		return suma / k;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {

	listaDubla ld = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(ld);
	dezalocareLDMasini(&ld);
	float medie = calculeazaPretMediu(ld);
	printf("%f", medie);
	return 0;
}