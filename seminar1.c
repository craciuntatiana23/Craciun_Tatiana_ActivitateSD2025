#include<stdio.h>
#include<stdlib.h>

struct Masina {
	int id;
	int nrKm;
	char* model;
	float pret;
	char tipMotor;
};

struct Masina initializare(int id, int nrKm, char* model, float pret, char tipMotor) {
	struct Masina m;
	m.id = id;
	m.nrKm = nrKm;
	m.model = (char*)malloc(strlen(model) + 1);
	strcpy(m.model, model);
	m.pret = pret;
	m.tipMotor = tipMotor;
	return m;
}
void afisare(struct Masina m) {
	printf("id: %d, \n nr km: %d, \n model: %s, \n pret: %5.2f, \n tip motor: %c \n", m.id, m.nrKm, m.model, m.pret, m.tipMotor);
}

void modifica_pret(struct Masina* m, int pretNou) {
	if (pretNou > 0)
		m->pret = pretNou;
}

void dezalocare(struct Masina* m) {
	free(m->model);
	m->model = NULL;
}

int main() {
	struct Masina masina;
	masina = initializare(1, 12000, "c4", 17000, 'B');
	afisare(masina);
	modifica_pret(&masina, 16500);
	afisare(masina);
	return 0;
}