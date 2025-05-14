//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//struct Nod {
//	Masina info;
//	struct Nod* dreapta;
//	struct Nod* stanga;
//};
//typedef struct Nod Nod;
//
////creare structura pentru un nod dintr-un arbore binar de cautare
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//int calculeazaInaltimeArbore(Nod* arbore) {
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	if(arbore != NULL)
//	{
//		int inaltimeStanga = calculeazaInaltimeArbore(arbore->stanga);
//		int inaltimeDreapta = calculeazaInaltimeArbore(arbore->dreapta);
//		return inaltimeStanga > inaltimeDreapta ? (inaltimeStanga + 1) : (inaltimeDreapta + 1);
//	}
//	else {
//		return 0;
//	}
//}
//
//int calculeazaGE(Nod* arbore) {
//	return calculeazaInaltimeArbore(arbore->stanga) - calculeazaInaltimeArbore(arbore->dreapta);
//}
//
//void rotireStanga(Nod** arbore) {
//	Nod* aux = (*arbore)->dreapta;
//	(*arbore)->dreapta = aux->stanga;
//	aux->stanga = (*arbore);
//	(*arbore) = aux;
//}
//
//void rotireDreapta(Nod** arbore) {
//	Nod* aux = (*arbore)->stanga;
//	(*arbore)->stanga = aux->dreapta;
//	aux->dreapta = (*arbore);
//	(*arbore) = aux;
//}
//
////ALTE FUNCTII NECESARE:
//// - aici veti adauga noile functii de care aveti nevoie.
//
//void adaugaMasinaInArboreEchilibrat(Nod** arbore, Masina masinaNoua) {
//	//adauga o noua masina pe care o primim ca parametru in arbore,
//	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
//	//dupa o anumita cheie pe care o decideti - poate fi ID
//	if ((*arbore) != NULL) {
//		if ((*arbore)->info.id < masinaNoua.id) {
//			adaugaMasinaInArboreEchilibrat(&((*arbore)->dreapta), masinaNoua);
//		}
//		else {
//			adaugaMasinaInArboreEchilibrat(&((*arbore)->stanga), masinaNoua);
//		}
//		int gradEchilibru = calculeazaGE(*arbore);
//		if (gradEchilibru == 2) {
//			if (calculeazaGE((*arbore)->stanga) == 1) {
//				rotireDreapta(arbore);
//			}
//			else {
//				rotireStanga((&(*arbore)->stanga));
//				rotireDreapta(arbore);
//			}
//		}
//		else if (gradEchilibru == -2) {
//			if (calculeazaGE((*arbore)->dreapta) != -1) {
//				rotireDreapta(&((*arbore)->dreapta));
//			}
//		}
//	}
//	else {
//		(*arbore) = (Nod*)malloc(sizeof(Nod));
//		(*arbore)->info = masinaNoua;
//		(*arbore)->dreapta = NULL;
//		(*arbore)->stanga = NULL;
//	}
//}
//
//void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	
//	FILE* f = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//	while (!feof(f)) {
//		adaugaMasinaInArboreEchilibrat(&nod, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return nod;
//}
//
//void afisareMasiniDinArborePreordine(Nod* nod) {
//	if (nod != NULL) {
//		afisareMasina(nod->info);
//		afisareMasiniDinArborePreordine(nod->stanga);
//		afisareMasiniDinArborePreordine(nod->dreapta);
//	}
//}
//
//void afisareMasiniDinArbore(/*arbore de masini*/) {
//	//afiseaza toate elemente de tip masina din arborele creat
//	//prin apelarea functiei afisareMasina()
//	//parcurgerea arborelui poate fi realizata in TREI moduri
//	//folositi toate cele TREI moduri de parcurgere
//}
//
//void dezalocareArboreDeMasini(/*arbore de masini*/) {
//	//sunt dezalocate toate masinile si arborele de elemente
//}
//
////Preluati urmatoarele functii din laboratorul precedent.
////Acestea ar trebuie sa functioneze pe noul arbore echilibrat.
//
//Masina getMasinaByID(/*arborele de masini*/int id);
//
//int determinaNumarNoduri(/*arborele de masini*/);
//
//float calculeazaPretTotal(Nod* radacina) {
//	if (radacina == NULL) {
//		return 0;
//	}
//	else {
//		float sumaStanga = calculeazaPretTotal(radacina->stanga) + radacina->info.pret;
//		float sumaDreapta = calculeazaPretTotal(radacina->dreapta);
//		return sumaDreapta + sumaStanga;
//	}
//
//}
//
//float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);
//
//int main() {
//	Nod* radacina = citireArboreDeMasiniDinFisier("masini.txt");
//	afisareMasiniDinArborePreordine(radacina);
//
//	return 0;
//}