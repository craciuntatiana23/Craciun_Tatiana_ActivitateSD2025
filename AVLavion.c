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
//	printf("\n");
//}
//
//int inaltimeArbore(Nod* nod) {
//	if (nod != NULL) {
//		int inaltimeStanga = inaltimeArbore(nod->stanga);
//		int inaltimeDreapta = inaltimeArbore(nod->dreapta);
//		if (inaltimeStanga >= inaltimeDreapta)
//			return inaltimeStanga + 1;
//	}
//	else
//		return 0;
//}
//
//int calcueazaGradAsimetrie(Nod* nod) {
//	int gradStanga = inaltimeArbore(nod->stanga);
//	int gradDreapta = inaltimeArbore(nod->dreapta);
//	return (gradStanga - gradDreapta);
//}
//
//void rotireLaDreapta(Nod** nod) {
//	Nod* aux = (*nod)->stanga;
//	(*nod)->stanga = aux->dreapta;
//	aux->dreapta = (*nod);
//	(*nod) = aux;
//}
//
//void rotireStanga(Nod** nod) {
//	Nod* aux = (*nod)->dreapta;
//	(*nod)->dreapta = aux->stanga;
//	aux->stanga = (*nod);
//	(*nod) = aux;
//}
//
//
//void inserareNodInArboreEchilibrat(Nod** nod, Avion avion) {
//	if ((*nod) != NULL) {
//		if (avion.id > (*nod)->info.id) {
//			inserareNodInArboreEchilibrat(&(*nod)->dreapta, avion);
//		}
//		else if (avion.id < (*nod)->info.id) {
//			inserareNodInArboreEchilibrat(&(*nod)->stanga, avion);
//		}
//		if (calcueazaGradAsimetrie(*nod) == 2) {
//			if (calcueazaGradAsimetrie((*nod)->stanga) == -1)
//				rotireStanga(&(*nod)->stanga);
//			rotireLaDreapta(nod);
//		}
//		else if (calcueazaGradAsimetrie(*nod) == -2) {
//			if (calcueazaGradAsimetrie((*nod)->dreapta) == 1)
//				rotireLaDreapta(&(*nod)->dreapta);
//			rotireStanga(nod);
//		}
//	}
//	else {
//		(*nod) = malloc(sizeof(Nod));
//		(*nod)->info = avion;
//		(*nod)->dreapta = NULL;
//		(*nod)->stanga = NULL;
//		
//	}
//
//}
//
//
//Nod* citireArboreDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* nod = NULL;
//	while (!feof(f)) {
//		inserareNodInArboreEchilibrat(&nod, citireAvionFisier(f));
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
//void dezalocareArbore(Nod** nod) {
//	if ((*nod) != NULL) {
//		dezalocareArbore(&(*nod)->stanga);
//		dezalocareArbore(&(*nod)->dreapta);
//		free((*nod)->info.model);
//		free(*nod);
//	}
//	(*nod) = NULL;
//}
//
//int main() {
//	Nod* nod = citireArboreDinFisier("Avion.txt");
//	afisareArboreSRD(nod);
//	printf("Inaltime: %d\n", inaltimeArbore(nod));
//	dezalocareArbore(&nod);
//}