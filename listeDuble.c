#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	Masina masina;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

//creare structura pentru Lista Dubla 
struct listaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
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
		afisareMasina(p->masina);
		p = p->next;
	}
}
void afisareListaMasiniDeLaSfarsit(listaDubla lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = lista.last;
	while (p) {
		afisareMasina(p->masina);
		p = p->prev;
	}
}

void adaugaMasinaInListaLaFinal(listaDubla* lista, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->masina = masinaNoua;
	nodNou->next = NULL;
	nodNou->prev = lista->last;
	if(lista->last)
		lista->last->next = nodNou;
	else
	{
		lista->first = nodNou;
	}
	lista->last = nodNou;
	lista->nrNoduri++;
}

void adaugaLaInceputInLista(listaDubla* lista, Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->masina = masinaNoua;
	nodNou->next = lista->first;
	nodNou->prev = NULL;
	if (lista->first) {
		lista->first->prev = nodNou;
	}
	else {
		lista->last = nodNou;
	}
	lista->first = nodNou;
	lista->nrNoduri++;
}

listaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	listaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	while (!feof(f)) {
		adaugaMasinaInListaLaFinal(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(listaDubla* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if(aux->masina.numeSofer)
			free(aux->masina.numeSofer);
		if (aux->masina.model)
			free(aux->masina.model);
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

float calculeazaPretMediu(listaDubla lista) {
	//calculeaza pretul mediu al masinilor din lista.
	float suma = 0;
	Nod* p = lista.first;
	while (p) {
		suma += p->masina.pret;
		p = p->next;
	}
	if (lista.nrNoduri)
		return suma / lista.nrNoduri;
	else
		return 0;
}

void stergeMasinaDupaID(listaDubla* lista, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	if (lista->first == NULL)
		return 0;
	Nod* p = lista->first;
	while (p && p->masina.id != id) {
		p = p->next;
	}
	if (p == NULL)
		return 0;
	// avem ce sa stergem
	if (p->prev == NULL) {
		lista->first = p->next;
		if (lista->first) {
			lista->first->prev = NULL;
		}
	}
	else {
		p->prev->next = p->next;
	}
	if (p->next) {
		p->next->prev = p->prev;
	}
	else {
		lista->last = p->prev;
	}
	if (p->masina.numeSofer)
		free(p->masina.numeSofer);
	if (p->masina.model)
		free(p->masina.model);
	free(p);
	lista->nrNoduri--;
}

char* getNumeSoferMasinaScumpa(listaDubla lista) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	if (lista.first)
	{
		Nod* max = lista.first;
		Nod* p = lista.first;
		while (p) {
			if (p->masina.pret > max->masina.pret) {
				max = p;
			}
			p = p->next;
		}
		char* nume = (char*)malloc(strlen(max->masina.numeSofer) + 1);
		strcpy(nume, max->masina.numeSofer);
		return nume;
	}
	else
		return NULL;
}

int main() {
	listaDubla lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(lista);
	printf("-----------------------------\n");
	stergeMasinaDupaID(&lista, 10);
	afisareListaMasiniDeLaSfarsit(lista);
	float pret = calculeazaPretMediu(lista);
	printf("\npret mediu %5.2f \n", pret);
	char* nume = getNumeSoferMasinaScumpa(lista);
	printf("soferul : %s\n", nume);
	if (nume)
		free(nume);
	dezalocareLDMasini(&lista);
	return 0;
}