#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 100
#define LINESIZE 256

struct Examen {
	char* id;
	char* denumire;
	char* data;
	int nrStudenti;
	char** listaStudenti;
	float* nota;
	float notaTrecere;
};

struct Node {
	Examen info;
	Node* next;
};

void displayExamen(Examen e) {
	printf("Id:%s\nDenumire:%s\nData:%s\nNr studenti:%i\n", e.id, e.denumire, e.data, e.nrStudenti);
	printf("Lista studenti:\n");
	for (int i = 0; i < e.nrStudenti; i++) {
		printf("\n%s", e.listaStudenti[i]);
		printf("\nNota:%.2f\n", e.nota[i]);
	}
	printf("\nNota trecere:%.2f", e.notaTrecere);
	printf("\n\n");
}

Node* adaugareNod(Node* cap, Examen e) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->info.id = e.id;
	nou->info.denumire = (char*)malloc(strlen(e.denumire) + 1);
	strcpy(nou->info.denumire, e.denumire);
	nou->info.data = (char*)malloc(strlen(e.data) + 1);
	strcpy(nou->info.data, e.data);
	nou->info.nrStudenti = e.nrStudenti;
	nou->info.listaStudenti = e.listaStudenti;
	nou->info.nota = e.nota;
	nou->info.notaTrecere = e.notaTrecere;
	nou->next = cap;
	return nou;
}

int pozitieHTable(Examen e, int size) {
	int s = 0;
	for (int i = 0; i < strlen(e.id); i++) {
		s += e.id[i];
	}
	return s % size;
}

void inserareHTable(Node** hTable, Examen e, int hSize) {
	int k;
	k = pozitieHTable(e, hSize);
	hTable[k] = adaugareNod(hTable[k], e);
}

void displayLista(Node* cap) {
	Node* temp = cap;
	while (temp) {
		displayExamen(temp->info);
		temp = temp->next;
	}
}
float parcurgereExamen(Examen e) {
	int k = 0;
	float m, s = 0;
	float media;
	int sw = 0;
	for (int i = 0; i < e.nrStudenti; i++) {
		if (e.nota[i] <= e.notaTrecere) {
			sw = 1;
		}
	}
	if (sw == 1) {
		for (int i = 0; i < e.nrStudenti; i++) {
			if (e.nota[i] <= e.notaTrecere) {
				s += e.nota[i];
				k++;
			}
		}
		m = s / k;
		media = m;
	}
	return media;
}
void adaugarePunctExamen(Examen e,const char* id) {
	
		if (strcmp(e.id, id) == 0) {
			for (int j = 0; j < e.nrStudenti; j++) {
				e.nota[j] += 1;
			}
	}
}

void adaugarePunctLista(Node* cap,const char* id) {
	if (cap) {
		adaugarePunctExamen(cap->info, id);
		cap = cap->next;
	}
}
void displayListaPunct(Node* cap,const char* id) {
	Node* temp = cap;
	while (temp) {
			displayExamen(temp->info);
		temp = temp->next;
	}
}
void adaugarePunct(Node** h, int size,const char* id) {
	for (int i = 0; i < size; i++) {
		if (h[i]) {
			adaugarePunctLista(h[i],id);
		}
	}
}
float parcurgereLista(Node* cap) {
	float media;
	if(cap){
		media = parcurgereExamen(cap->info);
		cap = cap->next;
	}
	return media;
}


void displayH(Node** h, int size) {
	for (int i = 0; i < size; i++) {
		if (h[i])
			displayLista(h[i]);
	}
}
void displayMedia(float media) {
	printf("%.2f ", media);
	
}
void displayH1(Node** h, int size,float* media) {
	media = (float*)malloc(sizeof(float)*size);
	for (int i = 0; i < size; i++) {
		if (h[i])
			displayLista(h[i]);
	}
}
float graduationPercentages(Node** h, int i,int dim) {
	float* media = (float*)malloc(sizeof(float)*dim);
		for (int i = 0; i < dim; i++) {
			if (h[i]) {
				media[i] = parcurgereLista(h[i]);
			}
			
		}
		return media[i];
}

void stergereExamene(Node** h,float value,int size) {
	Node** newH= (Node**)malloc(sizeof(Node*)*size);
	int j = 0,nr=0;
	for (int i = 0; i < size; i++) {
		if (h[i]) {
			if (h[i]->info.notaTrecere > value) {
				newH[j] = h[i];
				j++;
				nr++;
			}
		}
	}
	for (int i = 0; i < nr; i++) {
		displayLista(newH[i]);
	}
}

int nrExamene(Node** h, int dim,float value) {
	int nr = 0;
	for (int i = 0; i < dim; i++) {
		if (h[i]) {
			if (h[i]->info.notaTrecere > value) {
				nr++;
			}
		}
	}
	return nr;
}
void displayListaWithClauza(Node** h, int dim, float value) {
	for (int i = 0; i < dim; i++) {
		if (h[i]) {
			if (h[i]->info.notaTrecere > value) {
				displayLista(h[i]);
			}
		}
	}
}
void main() {

	Node** hTable = (Node**)malloc(sizeof(Node*)*DIM);
	float* media = (float*)malloc(sizeof(float)*DIM);
	Examen e;
	int nr;
	for (int i = 0; i < DIM; i++) {
		hTable[i] = 0;
	}
	FILE*f;
	f = fopen("Examene.txt", "r");
	char* token, buffer[LINESIZE], sep[] = ",";
	while (fgets(buffer, sizeof(buffer), f)) {
		token = strtok(buffer, sep);
		e.id = (char*)malloc(strlen(token) + 1);
		strcpy(e.id, token);
		token = strtok(NULL, sep);
		e.denumire = (char*)malloc(strlen(token) + 1);
		strcpy(e.denumire, token);
		token = strtok(NULL, sep);
		e.data = (char*)malloc(strlen(token) + 1);
		strcpy(e.data, token);
		token = strtok(NULL, sep);
		e.nrStudenti = atoi(token);
		e.listaStudenti = (char**)malloc(sizeof(char*)*e.nrStudenti);
		e.nota = (float*)malloc(sizeof(float)*e.nrStudenti);

		for (int i = 0; i < e.nrStudenti; i++) {
			token = strtok(NULL, sep);
			e.listaStudenti[i] = (char*)malloc(sizeof(char)*strlen(token) + 1);
			strcpy(e.listaStudenti[i], token);
		}
		for (int i = 0; i < e.nrStudenti; i++) {
			token = strtok(NULL, sep);
			e.nota[i] = atof(token);
		}
		token = strtok(NULL, sep);
		e.notaTrecere = atof(token);
		inserareHTable(hTable, e, DIM);
	}
	fclose(f);
	//ex 1, ex 2, ex 3
	//displayH(hTable, DIM);

	//ex 4
	/*nr = nrExamene(hTable, DIM, 4.5);
	printf("Numarul de examene este:%i\n\n", nr);
	displayListaWithClauza(hTable, DIM, 4.5);*/
	
	//ex 5
	/*printf("Sirul de medii ale studentilor este:");
	for (int i = 0; i < DIM; i++) {
		if (hTable[i]) {
			media[i] = graduationPercentages(hTable, i, DIM);
			printf("%.2f ", media[i]);
		}
	}*/
	
	//ex 6
	//adaugarePunct(hTable, DIM,"43");
	//displayH(hTable, DIM);

	//ex 7
	//stergereExamene(hTable, 4.50, DIM);
}











