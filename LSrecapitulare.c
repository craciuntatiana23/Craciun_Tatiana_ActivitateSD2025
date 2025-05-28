//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina 
//{
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//struct Stiva {
//	Masina info;
//	struct Stiva* next;
//};
//typedef struct Stiva Stiva;
//
//Masina citireMasinaFisier(FILE* f) {
//	Masina masina;
//	char buffer[100];
//	char* aux;
//	char sep[4] = ",\n";
//	fgets(buffer, 100, f);
//	masina.id = atoi(strtok(buffer, sep));
//	masina.nrUsi = atoi(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	masina.model = (char*)malloc(strlen(aux) + 1);
//	strcpy(masina.model, aux);
//	aux = strtok(NULL, sep);
//	masina.numeSofer = (char*)malloc(strlen(aux) + 1);
//	strcpy(masina.numeSofer, aux);
//	masina.serie = *strtok(NULL, sep);
//	return masina;
//}
//
//void afisareMasina(Masina masina) 
//{
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//void pushStack(Stiva** stiva, Masina masina) {
//	Stiva* aux = (Stiva*)malloc(sizeof(Stiva));
//	aux->info = masina;
//	aux->next = (*stiva);
//	(*stiva) = aux;
//}
//
//Masina popStack(Stiva** stiva) {
//	Masina masina;
//	if ((*stiva) != NULL) {
//		Stiva* aux = (*stiva);
//		masina = (*stiva)->info;
//		(*stiva) = (*stiva)->next;
//		free(aux);
//	}
//	else {
//		masina.id = -1;
//	}
//	return masina;
//}
//
//Stiva* citireStackDinFisier(const char* numeFisier) {
//	Stiva* stiva = NULL;
//	FILE* f = fopen(numeFisier, "r");
//	while (!feof(f)) {
//		pushStack(&stiva, citireMasinaFisier(f));
//	}
//	fclose(f);
//	return stiva;
//}
//
//unsigned int isEmptyStack(Stiva* stiva) {
//	return stiva == NULL;
//}
//
//void afisareStack(Stiva* stiva) {
//	while (stiva != NULL)
//	{
//		afisareMasina(stiva->info);
//		stiva = stiva->next;
//	}
//}
//
//void dezalocareStack(Stiva** stiva) {
//	while (isEmptyStack((*stiva))) {
//		Masina m = popStack((*stiva));
//		free(m.model);
//		free(m.numeSofer);
//	}
//}
//
////coadaaaa
//
//struct Nod{
//	Masina info;
//	struct Nod* prev;
//	struct Nod* next;
//};
//typedef struct Nod Nod;
//
//struct Coada {
//	Nod* first;
//	Nod* last;
//};
//typedef struct Coada Coada;
//
//void enqueue(Coada* coada, Masina masina) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masina;
//	nou->prev = NULL;
//	nou->next = coada->first;
//	if (coada->first == NULL) {
//		coada->first = nou;
//		coada->last = nou;
//	}
//	else {
//		coada->first->prev = nou;
//		coada->first = nou;
//	}
//}
//
//Masina dequeue(Coada* coada) {
//	Masina masina;
//	if (coada->last == NULL) {
//		masina.id = -1;
//		return masina;
//	}
//	else {
//		masina = coada->last->info;
//		if (coada->last->prev == NULL) {
//			coada->last = NULL;
//			coada->first = NULL;
//		}
//		else {
//			coada->last->prev->next = NULL;
//			coada->last = coada->last->prev;
//		}
//	}
//	return masina;
//}
//
//Coada citireCoadaMasiniFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Coada coada;
//	coada.first = NULL;
//	coada.last = NULL;
//	while (!feof(f)) {
//		enqueue(&coada, citireMasinaFisier(f));
//	}
//	fclose(f);
//	return coada;
//
//}
//
//void afisareCoada(Coada coada) {
//	while (coada.last != NULL) {
//		afisareMasina(coada.last->info);
//		coada.last = coada.last->prev;
//	}
//}
//
//int main() {
//	/*Stiva* stiva = citireStackDinFisier("masini.txt");
//	afisareStack(stiva);
//	dezalocareStack(&stiva);*/
//	Coada coada = citireCoadaMasiniFisier("masini.txt");
//	afisareCoada(coada);
//}