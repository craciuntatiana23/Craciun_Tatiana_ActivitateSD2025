//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Avion {
//	int id;
//	char* model;
//	int nrLocuri;
//	int nrLocuriOcupate;
//	int nrTipuriBilete;
//	float* preturiBilete;
//};
//typedef struct Avion Avion;
//
//struct Nod {
//	Avion info;
//	struct Nod* stanga;
//	struct Nod* dreapta;
//};
//typedef struct Nod Nod;
//
//Avion citireAvionFisier(FILE* f) {
//	Avion avion;
//	char buffer[100];
//	char sep[4] = ";,\n";
//	char* aux;
//	fgets(buffer, 100, f);
//	avion.id = atoi(strtok(buffer, sep));
//	aux = strtok(NULL, sep);
//	avion.model = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(avion.model, strlen(aux) + 1, aux);
//	avion.nrLocuri = atoi(strtok(NULL, sep));
//	avion.nrLocuriOcupate = atoi(strtok(NULL, sep));
//	avion.nrTipuriBilete = atoi(strtok(NULL, sep));
//	avion.preturiBilete = (float*)malloc(sizeof(float) * avion.nrTipuriBilete);
//	for (int i = 0; i < avion.nrTipuriBilete; i++)
//		avion.preturiBilete[i] = atof(strtok(NULL, sep));
//	return avion;
//}
//
//void afisareAvion(Avion avion) {
//	printf("Id: %d\n", avion.id);
//	printf("Model: %s\n", avion.model);
//	printf("Nr locuri: %d\n", avion.nrLocuri);
//	printf("Nr locuri ocupate: %d\n", avion.nrLocuriOcupate);
//	printf("Preturi: ");
//	for (int i = 0; i < avion.nrTipuriBilete; i++) {
//		printf("%5.2f ", avion.preturiBilete[i]);
//	}
//	printf("\n");
//}
//
//void adaugaAvionInArbore(Nod** nod, Avion avion) {
//	if ((*nod) != NULL) {
//		if (avion.id > (*nod)->info.id) {
//			adaugaAvionInArbore(&(*nod)->dreapta, avion);
//		}
//		else if (avion.id < (*nod)->info.id)
//		{
//			adaugaAvionInArbore(&(*nod)->stanga, avion);
//		}
//	}
//	else{
//		(*nod) = (Nod*)malloc(sizeof(Nod));
//		(*nod)->info = avion;
//		(*nod)->dreapta = NULL;
//		(*nod)->stanga = NULL;
//	}
//}
//
//Nod* citesteArboreDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//	while (!feof(f)) {
//		adaugaAvionInArbore(&nod, citireAvionFisier(f));
//	}
//	fclose(f);
//	return nod;
//}
//
//void afisareArboreRSD(Nod* nod) {
//	if (nod != NULL) {
//		afisareAvion(nod->info);
//		afisareArboreRSD(nod->stanga);
//		afisareArboreRSD(nod->dreapta);
//	}
//}
//void afisareArboreSRD(Nod* nod) {
//	if (nod != NULL) {
//		afisareArboreSRD(nod->stanga);
//		afisareAvion(nod->info);
//		afisareArboreSRD(nod->dreapta);
//	}
//}
//void afisareArboreSDR(Nod* nod) {
//	if (nod != NULL) {
//		afisareArboreSDR(nod->stanga);
//		afisareArboreSDR(nod->dreapta);
//		afisareAvion(nod->info);
//	}
//}
//
//void dezalocareArboreMasini(Nod* nod) {
//	if (nod != NULL) {
//		dezalocareArboreMasini(nod->stanga);
//		dezalocareArboreMasini(nod->dreapta);
//		free(nod->info.model);
//		free(nod);
//	}
//	nod = NULL;
//}
//Avion getAvionById(Nod* nod, int id) {
//	Avion avion;
//	if (nod != NULL) {
//		if (nod->info.id == id) {
//			avion = nod->info;
//		}
//		else {
//			if (nod->info.id > id)
//				avion = getAvionById(nod->stanga, id);
//			else
//				avion = getAvionById(nod->dreapta, id);
//		}
//	}
//	return avion;
//}
//
//int determinaNumarNoduri(Nod* nod, int nrNoduri) {
//	if (nod != NULL) {
//		nrNoduri++;
//		if (nod->dreapta != NULL) {
//			nrNoduri = determinaNumarNoduri(nod->dreapta, nrNoduri);
//		}
//		if (nod->stanga != NULL) {
//			nrNoduri = determinaNumarNoduri(nod->stanga, nrNoduri);
//		}
//	}
//	return nrNoduri;
//}
//
//int calculeazaInaltimeArbore(Nod* nod) {
//	if (nod != NULL) {
//		int inaltimeStanga = calculeazaInaltimeArbore(nod->stanga);
//		int inaltimeDreapta = calculeazaInaltimeArbore(nod->dreapta);
//		if (inaltimeStanga > inaltimeDreapta) {
//			return 1 + inaltimeStanga;
//		}
//		else {
//			return 1 + inaltimeDreapta;
//		}
//	}
//	else {
//		return 0;
//	}
//}
//
//int calculeazaNrAvioaneDeAcelasiTip(const char* tip, Nod* nod) {
//	if (nod == NULL)
//		return 0;
//	int nr = 0;
//	if (strcmp(nod->info.model, tip) == 0)
//		nr++;
//	nr += calculeazaNrAvioaneDeAcelasiTip(tip, nod->stanga);
//	nr += calculeazaNrAvioaneDeAcelasiTip(tip, nod->dreapta);
//	return nr;
//}
//
//int main() {
//	Nod* nod = citesteArboreDinFisier("Avion.txt");
//	/*printf("=====RSD========");
//	afisareArboreRSD(nod);
//	printf("=====SRD========");
//	afisareArboreSRD(nod);
//	printf("=====SDR========");
//	afisareArboreSDR(nod);*/
//	/*Avion avion = getAvionById(nod, 4);
//	afisareAvion(avion);*/
//	printf("Nr avioane Airbus: %d", calculeazaNrAvioaneDeAcelasiTip("Airbus A320", nod));
//}