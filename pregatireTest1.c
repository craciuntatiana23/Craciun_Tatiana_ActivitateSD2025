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

Franciza initializare(const char* nume, const char* taraOrigine, int anInfiintare, int nrAniMonitorizati, float* venitAnual) {
	Franciza franciza;
	franciza.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(franciza.nume, nume);
	franciza.taraOrigine = (char*)malloc(strlen(taraOrigine) + 1);
	strcpy(franciza.taraOrigine, taraOrigine);
	franciza.anInfiintare = anInfiintare;
	franciza.nrAniMonitorizati = nrAniMonitorizati;
	franciza.venitAnual = (float*)malloc(nrAniMonitorizati * sizeof(float));
	for (int i = 0; i < nrAniMonitorizati; i++)
		franciza.venitAnual[i] = venitAnual[i];
	return franciza;
}

void setNume(Franciza* franciza, const char* nume) {
	if (franciza->nume)
		free(franciza->nume);
	franciza->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(franciza->nume, nume);
}

void setVenitAnual(Franciza* franciza, int nrAniMonitorizati, float* venitAnual) {
	if (franciza->venitAnual)
	{
		free(franciza->venitAnual);
		franciza->venitAnual = NULL;
			
	}
	franciza->venitAnual = (float*)malloc(nrAniMonitorizati * sizeof(float));
	franciza->nrAniMonitorizati = nrAniMonitorizati;
	for (int i = 0; i < nrAniMonitorizati; i++)
		franciza->venitAnual[i] = venitAnual[i];
}
const char* getNume(Franciza franciza)
{
	return franciza.nume;
}

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



void dezalocare(Franciza* franciza) {
	if (franciza->nume)
	{
		free(franciza->nume);
		franciza->nume = NULL;
	}
	if (franciza->taraOrigine)
	{
		free(franciza->taraOrigine);
		franciza->taraOrigine = NULL;
	}
	if (franciza->venitAnual)
	{
		free(franciza->venitAnual);
		franciza->venitAnual = NULL;
	}
}

void afisareVectorObiecte(Franciza* vectorObiecte, int nrObiecte) {
	for (int i = 0; i < nrObiecte; i++) {
		afisareFranciza(vectorObiecte[i]);
		printf("\n");
	}
}
void dezalocareVectorObiecte(Franciza** vectorObiecte, int nrObiecte) {
	for (int i = 0; i < nrObiecte; i++) {
		if (vectorObiecte[i]->nume) {
			free(vectorObiecte[i]->nume);
			vectorObiecte[i]->nume = NULL;
		}
		if (vectorObiecte[i]->taraOrigine) {
			free(vectorObiecte[i]->taraOrigine);
			vectorObiecte[i]->taraOrigine = NULL;
		}
		if (vectorObiecte[i]->venitAnual) {
			free(vectorObiecte[i]->venitAnual);
			vectorObiecte[i]->venitAnual = NULL;
		}
	}
	free(vectorObiecte);
	vectorObiecte = NULL;
}
void copiazaFrancizeDinAceeasiTara(Franciza* vectorFrancize, int nrFrancize, const char* tara, int* nrFrancizeCopiate, Franciza** vectorNou) {
	(*nrFrancizeCopiate) = 0;
	for (int i = 0; i < nrFrancize; i++) {
		if (strcmp(vectorFrancize[i].taraOrigine, tara) == 0)
			(*nrFrancizeCopiate)++;
	}
	int contor = 0;
	if ((*vectorNou) != NULL)
		free((*vectorNou));
	*vectorNou = (Franciza*)malloc((*nrFrancizeCopiate) * sizeof(Franciza));
	for (int i = 0; i < nrFrancize; i++) {
		if (strcmp(vectorFrancize[i].taraOrigine, tara) == 0) {
			(*vectorNou)[contor] = vectorFrancize[i];
			(*vectorNou)[contor].nume = (char*)malloc(strlen(vectorFrancize[i].nume) + 1);
			strcpy((*vectorNou)[contor].nume, vectorFrancize[i].nume);
			(*vectorNou)[contor].taraOrigine = (char*)malloc(strlen(vectorFrancize[i].taraOrigine) + 1);
			strcpy((*vectorNou)[contor].taraOrigine, vectorFrancize[i].taraOrigine);
			(*vectorNou)[contor].venitAnual = (float*)malloc(vectorFrancize[i].nrAniMonitorizati * sizeof(float));
			for (int j = 0; j < vectorFrancize[i].nrAniMonitorizati; j++)
				(*vectorNou)[contor].venitAnual[j] = vectorFrancize[i].venitAnual[j];
			contor++;

		}
	}
}

float calculVenitMediu(Franciza franciza) {
	int suma = 0;
	for (int i = 0; i < franciza.nrAniMonitorizati; i++)
		suma += franciza.venitAnual[i];
	if (suma != 0)
		return suma / franciza.nrAniMonitorizati;
	else
		return 0;
}

void venitMediu(Franciza* vectorFrancize, int nrFrancize, Franciza** vectorNou, int* nrFrancizeCopiate) {
	(*nrFrancizeCopiate) = 0;
	if ((*vectorNou) != NULL)
		free((*vectorNou));
	int contor = 0;
	for (int i = 0; i < nrFrancize; i++) {
		if (calculVenitMediu(vectorFrancize[i]) < 10000) {
			(*nrFrancizeCopiate)++;
		}
	}
	*vectorNou = (Franciza*)malloc((*nrFrancizeCopiate) * sizeof(Franciza));

	for (int i = 0; i < nrFrancize; i++) {
		if (calculVenitMediu(vectorFrancize[i]) < 10000) {
			(*vectorNou)[contor] = vectorFrancize[i];
			(*vectorNou)[contor].nume = (char*)malloc(strlen(vectorFrancize[i].nume) + 1);
			strcpy((*vectorNou)[contor].nume, vectorFrancize[i].nume);
			(*vectorNou)[contor].taraOrigine = (char*)malloc(strlen(vectorFrancize[i].taraOrigine) + 1);
			strcpy((*vectorNou)[contor].taraOrigine, vectorFrancize[i].taraOrigine);
			(*vectorNou)[contor].venitAnual = (float*)malloc(vectorFrancize[i].nrAniMonitorizati * sizeof(float));
			for (int j = 0; j < vectorFrancize[i].nrAniMonitorizati; j++)
				(*vectorNou)[contor].venitAnual[j] = vectorFrancize[i].venitAnual[j];
			contor++;

		}
	}

}


int main() {

	float venit1[3] = { 4000, 9000, 5000 };
	float venit10[3] = { 4000, 400, 5000 };
	Franciza franciza1 = initializare("Profi", "Belgia", 2009, 3, venit1);
	setNume(&franciza1, "Lidl");
	float venit2[4] = { 179000, 90880, 24060, 3333};
	setVenitAnual(&franciza1, 4, venit2);
//	afisareFranciza(franciza1);
	float venit3[3] = { 564000, 60230, 9960};
	Franciza franciza2 = initializare("Profi", "Olanda", 2009, 3, venit1);
	Franciza franciza3 = initializare("Carrefour", "USA", 2001, 3, venit10);
	Franciza franciza4 = initializare("Lidl", "USA", 2001, 3, venit3);
	Franciza franciza5 = initializare("MC", "USA", 2001, 3, venit3);
	int nrFrancize = 5;
	Franciza* vectorFrancize = malloc(nrFrancize * sizeof(Franciza));
	vectorFrancize[0] = franciza1;
	vectorFrancize[1] = franciza2;
	vectorFrancize[2] = franciza3;
	vectorFrancize[3] = franciza4;
	vectorFrancize[4] = franciza5;
	afisareVectorObiecte(vectorFrancize, 5);
//	dezalocareVectorObiecte(vectorFrancize, 5);
	printf("=========francize USA===========\n");
	Franciza* vectorNou = NULL;
	int nr = 0;
	copiazaFrancizeDinAceeasiTara(vectorFrancize, 5, "USA", &nr, &vectorNou);
	afisareVectorObiecte(vectorNou, nr);
	printf("=========francize cu venit scazut===========\n");
	Franciza* vectorNou2 = NULL;
	int nr2 = 0;
	venitMediu(vectorFrancize, 5, &vectorNou2, &nr2);
	afisareVectorObiecte(vectorNou2, nr2);
}