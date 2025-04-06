#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Franciza {
	char* nume;
	char* taraOrigine;
	int anInfiintare;
	int nrAniMonitorizati;
	float* venitAnual;
};
typedef struct Franciza Franciza;

struct Nod {
	Franciza info;
	struct Nod* next;
};
typedef struct Nod Nod;

void afisareFranciza(Franciza franciza) {
	printf("\n");
	printf("Nume franciza: %s\n", franciza.nume);
	printf("Tara origine: %s\n", franciza.taraOrigine);
	printf("Venit anual: ");
	for (int i = 0; i < franciza.nrAniMonitorizati; i++)
		printf("%5.2f ", franciza.venitAnual[i]);
	printf("\n");
	printf("\n");
}

void afisareListaFrancize(Nod* cap) {
	while (cap != NULL) {
		afisareFranciza(cap->info);
		cap = cap->next;
	}
}

Franciza citireFrancizaDinFisier(FILE* f) {
	Franciza franciza;
	char buffer[101];
	char sep[4] = ",\n";
	fgets(buffer, 100, f);
	char* aux;
	aux = strtok(buffer, sep);
	franciza.nume = (char*)malloc(strlen(aux) + 1);
	strcpy(franciza.nume, aux);
	aux = strtok(NULL, sep);
	franciza.taraOrigine = (char*)malloc(strlen(aux) + 1);
	strcpy(franciza.taraOrigine, aux);
	franciza.anInfiintare = atoi(strtok(NULL, sep));
	franciza.nrAniMonitorizati = atoi(strtok(NULL, sep));
	franciza.venitAnual = (float*)malloc(franciza.nrAniMonitorizati * sizeof(float));
	for (int i = 0; i < franciza.nrAniMonitorizati; i++) {
		franciza.venitAnual[i] = atof(strtok(NULL, sep));
	}
	return franciza;
}

void adaugaMasinaInListaLaInceput(Nod** cap, Franciza francizaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = francizaNoua;
	nodNou->next = (*cap);
	*cap = nodNou;
}

void adaugaMasinaInListaLaSfarsit(Nod** cap, Franciza francizaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = francizaNoua;
	nodNou->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = nodNou;
	}
	else {
		Nod* p = (*cap);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nodNou;
	}
}

Nod* citireListaFrancizeDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* cap = NULL;
	while(!feof(f))
	{
		adaugaMasinaInListaLaSfarsit(&cap, citireFrancizaDinFisier(f));
	}
	fclose(f);
	return cap;
}



void dezalocareListaMasini(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		(*cap) = (*cap)->next;
		if (p->info.nume)
			free(p->info.nume);
		if (p->info.taraOrigine)
			free(p->info.taraOrigine);
		if (p->info.venitAnual)
			free(p->info.venitAnual);
		free(p);
	}
}

float maximVenitAnual(Nod* cap) {
	float maxim = -1;
	int suma;
	while (cap) {
		suma = 0;
		for (int i = 0; i < cap->info.nrAniMonitorizati; i++)
			suma += cap->info.venitAnual[i];
		suma /= cap->info.nrAniMonitorizati;
		if (suma > maxim)
			maxim = suma;
		cap = cap->next;
	}
	return maxim;
}

void stergereFrancizaDupaNume(Nod** cap, const char* nume) {
	while ((*cap) && strcmp((*cap)->info.nume, nume) == 0) {
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.nume)
			free(p->info.nume);
		if (p->info.taraOrigine)
			free(p->info.taraOrigine);
		if (p->info.venitAnual)
			free(p->info.venitAnual);
		free(p);
	}
	if (*cap) {
		Nod* p = (*cap);
		while (p) {
			while (p->next && strcmp(p->next->info.nume, nume) != 0)
				p = p->next;
			if (p->next) {
				Nod* aux = p->next;
				p->next = aux->next;
				if (aux->info.nume)
					free(aux->info.nume);
				if (aux->info.taraOrigine)
					free(aux->info.taraOrigine);
				if (aux->info.venitAnual)
					free(aux->info.venitAnual);
				free(aux);
			}
			else
				p = NULL;
		}
	}
}

int main() {
	Nod* lista = citireListaFrancizeDinFisier("francize.txt");
	afisareListaFrancize(lista);
	float maxim = maximVenitAnual(lista);
	printf("venit maxim %5.2f \n", maxim);
	stergereFrancizaDupaNume(&lista, "lidl");
	printf("==============");
	afisareListaFrancize(lista);
}