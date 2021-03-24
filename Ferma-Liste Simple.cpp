
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Ferma {
	char* nume;
	int nrAnimale;
};

struct node {
	Ferma info;
	node* next;
};

Ferma createFerma(const char* nume, int nrAnimale) {
	Ferma f;
	f.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.nrAnimale = nrAnimale;
	return f;
}

node* createNode(Ferma f, node* next) {
	node* nou = (node*)malloc(sizeof(node));
	nou->info = f;
	nou->next = next;
	return nou;
}

node* inserareSfarsit(node* cap, Ferma f) {
	node* nou = createNode(f, NULL);
	if (cap) {
		node* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		cap = nou;
	}
	return cap;
}

void afisareFerma(Ferma f) {
	printf("Ferma %s are %d animale.\n", f.nume, f.nrAnimale);
}
void afisareListaFerme(node* cap) {
	while (cap) {
		afisareFerma(cap->info);
		cap = cap->next;
	}
}

node* inserareInceput(node* cap, Ferma f) {
	node* nou = createNode(f, cap);
	return nou;
}

float medieAnimale(node* cap) {
	if (cap) {
		int nr = 0, s = 0;
		while (cap) {
			nr++;
			s += cap->info.nrAnimale;
			cap = cap->next;
		}
		return s / nr;
	}
	else {
		return 0;
	}
}

node* stergereLista(node* cap) {
	while (cap) {
		node* aux = cap;
		cap = cap->next;
		free(aux->info.nume);
		free(aux);
	}
	return cap;
}


void main() {
	/*Ferma f = createFerma("faraAnimale", 1);
	node* nod = createNode(f, NULL);*/
	node* cap = NULL;
	cap = inserareSfarsit(cap, createFerma("Cocosul vesel", 200));
	cap = inserareSfarsit(cap, createFerma("Avicola", 400));
	cap = inserareSfarsit(cap, createFerma("Crevedia", 600));
	afisareListaFerme(cap);
}








