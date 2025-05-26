#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tractor {
	int id;
	char* producator;
	char* model;
	int caiPutere;
	float nrOre;
};
typedef struct Tractor Tractor;

struct Nod {
	Tractor info;
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct Nod Nod;

Tractor citireTractorFisier(FILE* fisier) {
	Tractor tractor;
	char buffer[100];
	char sep[4] = ",\n";
	if (!fgets(buffer, sizeof(buffer), fisier)) {
		// linie goală sau EOF
		tractor.id = -1; // semnal că e invalid
		return tractor;
	}

	char* aux;

	aux = strtok(buffer, sep);
	if (!aux) { tractor.id = -1; return tractor; }
	tractor.id = atoi(aux);

	aux = strtok(NULL, sep);
	if (!aux) { tractor.id = -1; return tractor; }
	tractor.producator = malloc(strlen(aux) + 1);
	strcpy(tractor.producator, aux);

	aux = strtok(NULL, sep);
	if (!aux) { tractor.id = -1; return tractor; }
	tractor.model = malloc(strlen(aux) + 1);
	strcpy(tractor.model, aux);

	aux = strtok(NULL, sep);
	if (!aux) { tractor.id = -1; return tractor; }
	tractor.caiPutere = atoi(aux);

	aux = strtok(NULL, sep);
	if (!aux) { tractor.id = -1; return tractor; }
	tractor.nrOre = atof(aux);

	return tractor;
}
void afisareTractor(Tractor tractor) {
	printf("\n");
	printf("ID: %d \n", tractor.id);
	printf("Producator: %s \n", tractor.producator);
	printf("Model: %s \n", tractor.model);
	printf("Cai putere: %d \n", tractor.caiPutere);
	printf("Nr ore: %5.2f \n", tractor.nrOre);
	printf("\n");
}

void adaugaTractorInArbore(Nod** nod, Tractor tractor) {
	if ((*nod) != NULL) {
		if (tractor.id < (*nod)->info.id)
			adaugaTractorInArbore(&(*nod)->stanga, tractor);
		else if (tractor.id > (*nod)->info.id)
			adaugaTractorInArbore(&(*nod)->dreapta, tractor);
	}
	else {
		(*nod) = (Nod*)malloc(sizeof(Nod));
		(*nod)->dreapta = NULL;
		(*nod)->stanga = NULL;
		(*nod)->info = tractor;
	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* nod = NULL;
	while (!feof(f)) {
		adaugaTractorInArbore(&nod, citireTractorFisier(f));
	}
	fclose(f);
	return nod;
}

void afisareArboreSDR(Nod* nod) {
	if (nod != NULL) {
		afisareArboreSDR(nod->stanga);
		afisareArboreSDR(nod->dreapta);
		afisareTractor(nod->info);
	}
}

void afisareArboreSRD(Nod* nod) {
	if (nod != NULL) {
		afisareArboreSRD(nod->stanga);
		afisareTractor(nod->info);
		afisareArboreSRD(nod->dreapta);
	}
}

void afisareArboreRSD(Nod* nod) {
	if (nod != NULL) {
		afisareTractor(nod->info);
		afisareArboreRSD(nod->stanga);
		afisareArboreRSD(nod->dreapta);
	}
}

int nrNoduriArbore(Nod* nod) {
	int nrNoduri = 0;
	if (nod != NULL) {
		nrNoduri++;
		if (nod->stanga != NULL)
			nrNoduri += nrNoduriArbore(nod->stanga);
		if (nod->dreapta != NULL)
			nrNoduri += nrNoduriArbore(nod->dreapta);
	}
	return nrNoduri;
}

int inaltimeArbore(Nod* nod) {
	if(nod != NULL)
	{
		int inaltimeStanga = inaltimeArbore(nod->stanga);
		int inaltimeDreapta = inaltimeArbore(nod->dreapta);
		if (inaltimeStanga > inaltimeDreapta)
			return inaltimeStanga + 1;
		else
			return inaltimeDreapta + 1;
	}
}

void dezalocare(Nod* nod) {
	if (nod != NULL) {
		free(nod->info.model);
		free(nod->info.producator);
		dezalocare(nod->stanga);
		dezalocare(nod->dreapta);
	}
	else {
		nod = NULL;
	}
}

Tractor cautareCelMaiPuternicTractor(Nod* nod) {
	int maxPutere = 0;
	Tractor tractor;
	if (nod != NULL) {
		if (nod->info.caiPutere > maxPutere)
			tractor = nod->info;
		if (nod->stanga != NULL)
			tractor = cautareCelMaiPuternicTractor(nod->stanga);
		if (nod->dreapta != NULL)
			tractor = cautareCelMaiPuternicTractor(nod->dreapta);
	}
	return tractor;
}
int nrTractoareLandini(Nod* nod) {
	int nr = 0;
	if (nod != NULL) {
		if (strcmp(nod->info.producator, "Landini") == 0)
			nr++;
		if (nod->stanga != NULL)
			nr += nrTractoareLandini(nod->stanga);
		if (nod->dreapta != NULL)
			nr += nrTractoareLandini(nod->dreapta);
	}
	return nr;
}

int main() {
	Nod* nod = citireArboreDinFisier("tractoare.txt");
	/*printf("=========SDR");
	afisareArboreSDR(nod);*/
	//printf("=========SRD");
	//afisareArboreSRD(nod);
	//printf("=========RSD");
	//afisareArboreRSD(nod);
	printf("nr noduri: %d\n", nrNoduriArbore(nod));
	printf("inaltime: %d\n", inaltimeArbore(nod));
	Tractor tractor = cautareCelMaiPuternicTractor(nod);
	afisareTractor(tractor);
	printf("nr tr landini: %d\n", nrTractoareLandini(nod));
}