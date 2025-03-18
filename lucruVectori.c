#include <malloc.h>
#include <stdio.h>
#include <string>

struct Produs {

	int id;
	char* denumire;
	float pret;

};

struct Produs initializare(int id, const char* denumire, float pret) {
	struct Produs produs;
	produs.id = id;
	produs.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(produs.denumire, strlen(denumire) + 1, denumire);
	produs.pret = pret;
	return produs;
}

void afisare(struct Produs produs) {
	printf("\n");
	printf("Produsul %s are id-ul %d si costa %5.2f lei ", produs.denumire, produs.id, produs.pret);
	printf("\n");
}

void modificaPret(struct Produs* produs, float pretNou) {
	if (pretNou > 0)
	{
		(*produs).pret = pretNou;
	}
}

void modificaNume(struct Produs* produs, const char* numeNou) {
	strcpy_s((*produs).denumire, strlen(numeNou) + 1, numeNou);
}

void dezalocare(struct Produs* produs) {
	if ((*produs->denumire) != NULL) {
		free((*produs).denumire);
		(*produs).denumire = NULL;
	}
}

void afisareVector(struct Produs* produse, int nrProduse) {
	for (int i = 0; i < nrProduse; i++)
		afisare(produse[i]);
}

void dezalocare(struct Produs** produse, int* nrProduse) {
	for (int i = 0; i < (*nrProduse); i++) {
		free((*produse)[i].denumire);
	}
	free(*produse);
	(*produse) = NULL;
	*nrProduse = 0;
}

void copiazaProduseScumpe(struct Produs* produse, int nrProduse, struct Produs** produseNoi, int* nrProduseNoi) {

	*nrProduseNoi = 0;
	if ((*produseNoi) != NULL)
		free(*produseNoi);

	for (int i = 0; i < nrProduse; i++) {
		if (produse[i].pret > 10)
			(*nrProduseNoi)++;
	}
	*produseNoi = (struct Produs*)malloc(sizeof(struct Produs) * (*nrProduseNoi));
	int k = 0;
	for (int i = 0; i < nrProduse; i++) {
		if (produse[i].pret > 10) {
			(*produseNoi)[i] = produse[i];
			(*produseNoi)[k].denumire = (char*)malloc(strlen(produse[i].denumire) + 1);
			strcpy_s((*produseNoi)[k].denumire, strlen(produse[i].denumire) + 1, produse[i].denumire);
			k++;
		}
	}


}

int main() {
	struct Produs produs1;
	produs1 = initializare(1, "Rosii", 5.5);
	afisare(produs1);
	modificaPret(&produs1, 4.75);
	afisare(produs1);
	modificaNume(&produs1, "Mustar");
	afisare(produs1);
	struct Produs produs2 = initializare(2, "Fasole", 11);
	struct Produs produs3 = initializare(3, "Ulei", 15);
	afisare(produs2);
	afisare(produs3);
	struct Produs* produse = NULL;
	int nrProduse = 3;
	produse = (struct Produs*)malloc(sizeof(struct Produs) * nrProduse);
	produse[0] = initializare(1, "Rosii", 5.5);
	produse[1] = initializare(2, "Fasole", 11);
	produse[2] = initializare(3, "Ulei", 15);
	afisareVector(produse, 3);
	struct Produs* produseNoi = NULL;
	int nrProduseScumpe = 0;
	copiazaProduseScumpe(produse, nrProduse, &produseNoi, &nrProduseScumpe);
	afisareVector(produseNoi, nrProduseScumpe);
	dezalocare(&produseNoi, &nrProduseScumpe);



}
