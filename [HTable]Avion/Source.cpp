#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM 100
#define LINESIZE 300
struct Avion {
	char* codAvion;
	char* modelAvion;
	int nrCalatori;
	int* preturi;
};

struct Nod {
	Avion info;
	Nod* next;
};

void displayAvion(Avion a) {
	printf("Cod avion:%d\nModel avion:%s\nNr calatori:%d\n",a.codAvion,a.modelAvion,a.nrCalatori);
	printf("Preturi:\n");
	for (int i = 0; i < a.nrCalatori-1; i++) {
		printf("%d ", a.preturi[i]);
	}
	printf("\n\n");
}

Nod* adaugareNod(Nod* cap, Avion a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = cap;
	return nou;
}

int pozitieHTable(Avion a, int size) {
	int s = 0;
	for (int i = 0; i < strlen(a.codAvion); i++) {
		s += a.codAvion[i];
	}
	return s % size;
}

void inserareHTable(Nod** hTable, Avion a, int hSize) {
	int k;
	k = pozitieHTable(a, hSize);
	hTable[k] = adaugareNod(hTable[k], a);
}

void displayLista(Nod* cap) {
	Nod* temp = cap;
	while (temp) {
		displayAvion(temp->info);
		temp = temp->next;
	}
}


void displayH(Nod** h, int size) {
	for (int i = 0; i < size; i++) {
		if (h[i])
			displayLista(h[i]);
	}
}
int incasariBilete(Nod** h, int size,const char* cod,int value) {
	int incasari = 0;
	for (int i = 0; i < size; i++) {
		if (h[i]) {
			if (strcmp(h[i]->info.codAvion,cod)==0){
				for (int j = 0; j < h[i]->info.nrCalatori; j++) {
					if(h[i]->info.preturi[j]>value)
					incasari += h[i]->info.preturi[j];
				}
			}		
		}
	}
	return incasari;
}

int nrAvioane(Nod** h, int size, const char* model) {
	int nr=0;
	for (int i = 0; i < size; i++) {
		if (h[i]) {
			if (strcmp(h[i]->info.modelAvion, model) == 0) {
				nr++;
			}
		}
	}
	return nr;
}

char** salveazaAvioane(Nod** h, int size, const char* model) {
char** codesArr = (char**)malloc(sizeof(char*)*nrAvioane(h, size, model));
int j = 0;
for (int i = 0; i < size; i++) {
		if (h[i]) {
			if (strcmp(h[i]->info.modelAvion, model) == 0) {
				codesArr[j] = h[i]->info.codAvion;
				j++;
			}
		}
	}
return codesArr;
}

void main() {
	Nod** hTable = (Nod**)malloc(sizeof(Nod*)*DIM);
	Avion a;
	int nr;
	for (int i = 0; i < DIM; i++) {
		hTable[i] = 0;
	}
	FILE*f = fopen("avioane.txt", "r");
	if (f) {
		char* token, buffer[LINESIZE], sep[] = ",";
		while (fgets(buffer, sizeof(buffer), f)) {
			token = strtok(buffer, sep);
			a.codAvion = (char*)malloc(strlen(token) + 1);
			strcpy(a.codAvion, token);
			token = strtok(NULL, sep);
			a.modelAvion = (char*)malloc(strlen(token) + 1);
			strcpy(a.modelAvion, token);
			token = strtok(NULL, sep);
			a.nrCalatori = atoi(token);
			token = strtok(NULL, sep);
			a.preturi = (int*)malloc(sizeof(int)*a.nrCalatori-1);
			for (int i = 0; i < a.nrCalatori-1; i++) {
				token = strtok(NULL, sep);
				a.preturi[i] = atoi(token);
			}
			inserareHTable(hTable, a, DIM);
		}
		fclose(f);
	}
	/*displayH(hTable,DIM);*/

	/*printf("%d", incasariBilete(hTable, DIM, "12", 600));*/
	char** sir = (char**)malloc(sizeof(char*)*nrAvioane(hTable, DIM, "Boeing 757"));
	sir = salveazaAvioane(hTable, DIM, "Boeing 757");
	for (int i = 0; i < nrAvioane(hTable, DIM, "Boeing 757"); i++) {
		printf("%s ", sir[i]);
	}
}

