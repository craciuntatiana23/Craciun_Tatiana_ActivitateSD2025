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
////creare structura pentru un nod dintr-un arbore binar de cautare
//
//struct Nod {
//	Masina info;
//	struct Nod* stanga;
//	struct Nod* dreapta;
//};
//typedef struct Nod Nod;
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
//	m1.pret= atof(strtok(NULL, sep));
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
//
//void adaugaMasinaInArbore(Nod** nod, Masina masinaNoua) {
//	if ((*nod) != NULL) {
//		if (masinaNoua.id < (*nod)->info.id)
//			adaugaMasinaInArbore(&(*nod)->stanga, masinaNoua);
//		else if (masinaNoua.id > (*nod)->info.id)
//			adaugaMasinaInArbore(&(*nod)->dreapta, masinaNoua);
//	}
//	else {
//		(*nod) = (Nod*)malloc(sizeof(Nod));
//		(*nod)->info = masinaNoua;
//		(*nod)->stanga = NULL;
//		(*nod)->dreapta = NULL;
//	}
//
//}
//
//void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//	while(!feof(f))
//	{
//		adaugaMasinaInArbore(&nod, citireMasinaDinFisier(f));
//	}
//	fclose(f);
//	return nod;
//}
//
//void afisareArboreSRD(Nod* nod) {
//	if (nod != NULL) {
//		afisareArboreSRD(nod->stanga);
//		afisareMasina(nod->info);
//		afisareArboreSRD(nod->dreapta);
//	}
//}
//void afisareArboreSDR(Nod* nod) {
//	if (nod != NULL) {
//		afisareArboreSDR(nod->stanga);
//		afisareArboreSDR(nod->dreapta);
//		afisareMasina(nod->info);
//	}
//}
//void afisareArboreRSD(Nod* nod) {
//	if (nod != NULL) {
//		afisareMasina(nod->info);
//		afisareArboreRSD(nod->stanga);
//		afisareArboreRSD(nod->dreapta);
//	}
//}
//
//void dezalocareArboreDeMasini(Nod* nod) {
//	if (nod != NULL) {
//		dezalocareArboreDeMasini(nod->stanga);
//		dezalocareArboreDeMasini(nod->dreapta);
//		free(nod->info.model);
//		free(nod->info.numeSofer);
//		free(nod);
//	}
//	nod = NULL;
//}
//
//Masina getMasinaByID(Nod* nod, int id) {
//	Masina m;
//	if(nod != NULL)
//	{
//		if (nod->info.id == id)
//			m = nod->info;
//		else if (nod->info.id > id)
//			m = getMasinaByID(nod->stanga, id);
//		else
//			m = getMasinaByID(nod->dreapta, id);
//	}
//	return m;
//}
//
//int determinaNumarNoduri(Nod* nod) {
//	int nrNoduri = 0;
//	if (nod == NULL)
//		return 0;
//	else {
//		nrNoduri++;
//		if (nod->stanga != NULL)
//			nrNoduri += determinaNumarNoduri(nod->stanga);
//		if (nod->dreapta != NULL)
//			nrNoduri += determinaNumarNoduri(nod->dreapta);
//	}
//	return nrNoduri;
//}
//
//int calculeazaInaltimeArbore(Nod* nod) {
//	if (nod != NULL)
//	{
//		int inaltimeStanga = calculeazaInaltimeArbore(nod->stanga);
//		int inaltimeDreapta = calculeazaInaltimeArbore(nod->dreapta);
//		if (inaltimeDreapta >= inaltimeStanga)
//			return inaltimeDreapta + 1;
//		else
//			return inaltimeStanga + 1;
//	}
//	else
//		return 0;
//}
//
//float calculeazaPretTotal(Nod* nod) {
//	int pret = 0;
//	if (nod != NULL) {
//		pret += nod->info.pret;
//		if (nod->dreapta != NULL)
//			pret += calculeazaPretTotal(nod->dreapta);
//		if (nod->stanga != NULL)
//			pret += calculeazaPretTotal(nod->stanga);
//	}
//	return pret;
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* nod,  const char* numeSofer) {
//	float pret = 0;
//	if (nod != NULL) {
//		if (strcmp(nod->info.numeSofer, numeSofer) == 0)
//			pret += nod->info.pret;
//		if (nod->dreapta != NULL)
//			pret += calculeazaPretulMasinilorUnuiSofer(nod->dreapta, numeSofer);
//		if (nod->stanga != NULL)
//			pret += calculeazaPretulMasinilorUnuiSofer(nod->stanga, numeSofer);
//	}
//	return pret;
//}
//
//int main() {
//	Nod* nod = citireArboreDeMasiniDinFisier("masini_arbore.txt");
//	/*afisareArboreRSD(nod);
//	printf("inaltime: %d\n", calculeazaInaltimeArbore(nod));
//	printf("nr noduri: %d\n", determinaNumarNoduri(nod));
//	Masina masina = getMasinaByID(nod, 3);
//	printf("\n");
//	afisareMasina(masina);*/
//	printf("pret total: %5.2f\n", calculeazaPretulMasinilorUnuiSofer(nod, "Gheorghe"));
//	return 0;
//}