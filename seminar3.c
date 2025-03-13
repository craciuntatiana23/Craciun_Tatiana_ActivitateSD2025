#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina; //alias

void afisareMasina(Masina masina) {
	printf("id ul masinii: %d ", masina.id);
	printf("nr de usi: %d ", masina.nrUsi);
	printf("pret: %5.2f ", masina.pret);
	printf("model: %s ", masina.model);
	printf("nume sofer: %s ", masina.numeSofer);
	printf("serie: %dc ", masina.serie);

}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	Masina* temp;
	temp = malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		temp[i] = (*masini)[i];              //e ok shallow copy pt ca nu o sa sterg zona de mem unde am alocat char*
	}
	temp[(*nrMasini)] = masinaNoua;       // acceptam si aici shallow copy dar avem grija sa nu stergem 
	(*nrMasini)++;
	free((*masini));
	*masini = temp;
}

Masina citireMasinaFisier(FILE* file) {
	char sep[3] = ",\n";
	char* line[101];
	fgets(line, 100, file);
	Masina temp;
	temp.id = atoi(strtok(line, sep));
	temp.nrUsi = atoi(strtok(NULL, sep));
	temp.pret = atof(strtok(NULL, sep));
	
	char* buffer = strtok(NULL, sep);
	temp.model = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy_s(temp.model, strlen(buffer) + 1, buffer);

	buffer = strtok(NULL, sep);
	temp.numeSofer = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy_s(temp.numeSofer, strlen(buffer) + 1, buffer);

	buffer = strtok(NULL, sep);
	temp.serie = buffer[0];
	return temp;

}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* file;
	file = fopen(numeFisier, "r");
	Masina* vec = NULL;

	while (feof(file) != 0) {
		adaugaMasinaInVector(&vec, nrMasiniCitite, citireMasinaFisier(file));
	}
	fclose(file);
	return vec;

}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	for (int i = 0; i < nrMasini; i++) {
		free((*vector)[i].model); //eroare la dezalocare -> pb la alocare
		free((*vector)[i].numeSofer);
	}
	*nrMasini = 0;
	free(*vector);
	*vector = NULL;
}

int main() {
	int nr;
	nr = 0;
	Masina* vectorMasini = NULL;
	vectorMasini = citireVectorMasiniFisier("masini.txt", &nr);
	afisareVectorMasini(vectorMasini, nr);

	return 0;
}