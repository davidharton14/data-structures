#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
#define DIM_BUFFER 300

enum Stare {
	rezervat,
	disponibil
};

struct LocAutocar {
	char* indicativLoc;
	int nrRand;
	float pret;
	enum Stare s;
};

struct CursaAutocar {
	LocAutocar loc;
	int capacitateLocuri;
	float distantaKm;
};


struct Heap {
	CursaAutocar** elements;
	int heapSize;
	int index;
};

Stare convertToStare(const string& str)
{
	if (str == "rezervat") return rezervat;
	else if (str == "disponibil") return disponibil;

}
void initHeap(Heap&, int);
void displayCursaAutocar(CursaAutocar*);
void ReheapUp(Heap, int, int);
void displayQ(Heap&);

void initHeap(Heap& heap, int size) {
	heap.elements = (CursaAutocar**)malloc(sizeof(CursaAutocar*)*size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(CursaAutocar*)*size);
}

void displayCursaAutocar(CursaAutocar* c) {
	printf("Indicativ loc:%s\nNr rand:%d\nPret:%.2f\nStare:%d\nCapacitate locuri:%d\nDistanta km:%.2f\n\n",c->loc.indicativLoc, c->loc.nrRand, c->loc.pret,c->loc.s, c->capacitateLocuri, c->distantaKm);
}

void Enqueue(Heap& heap, CursaAutocar* c) {
	if (heap.index < heap.heapSize) {
		CursaAutocar* nou = (CursaAutocar*)malloc(sizeof(CursaAutocar));
		nou->loc.indicativLoc = (char*)malloc(strlen(c->loc.indicativLoc) + 1);
		strcpy(nou->loc.indicativLoc, c->loc.indicativLoc);
		nou->loc.nrRand = c->loc.nrRand;
		nou->loc.pret = c->loc.pret;
		nou->loc.s = c->loc.s;
		nou->capacitateLocuri = c->capacitateLocuri;
		nou->distantaKm = c->distantaKm;
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}

void ReheapUp(Heap heap, int first, int last)
{
	int parinte;
	CursaAutocar* temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->loc.nrRand <
			heap.elements[last]->loc.nrRand)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			ReheapUp(heap, first, parinte);
		}
	}
}

void displayQ(Heap& heap) {
	for (int i = 0; i < heap.heapSize; i++) {
		printf("Index:%d\n", i);
		displayCursaAutocar(heap.elements[i]);
	}
}

void marirePrioritate(Heap& heap) {
	for (int i = 0; i < heap.heapSize; i++) {
		if (heap.elements[i]->loc.s == 0) {
			heap.elements[i]->loc.nrRand++;
		}
		ReheapUp(heap, 0, i);
	}

}

float determinareCostMediu(Heap& heap, const char* id) {
	float cost = 0;
	for (int i = 0; i < heap.heapSize; i++) {
		if (strcmp(heap.elements[i]->loc.indicativLoc, id) == 0) {
			cost = heap.elements[i]->distantaKm / heap.elements[i]->capacitateLocuri;
		}
	}
	return cost;
}
float incasariTotale(Heap& heap) {
	float incasari = 0;
	for (int i = 0; i < heap.heapSize; i++) {
		if (heap.elements[i]->loc.s == 0) {
			incasari += heap.elements[i]->loc.pret;
		}
	}
	return incasari;
}

int nrRanduri(Heap& heap) {
	int nr = 0;
	int sw = 0;
	for (int i = 0; i < heap.heapSize; i++) {
		for (int j = 0; j < heap.heapSize; j++) {
			if (heap.elements[i]->loc.nrRand == heap.elements[j]->loc.nrRand) {
				sw = 1;	
			}
		}
		if (sw == 1)
			nr++;
		else
			nr++;
	}
	return nr;
}
int cautareString(int* sir, int j, int value) {
	int sw = 0;
	for (int i = 0; i < j; i++) {
		if (sir[i] == value) {
			sw = 1;
			break;
		}
	}
	if (sw == 1) {
		return sw;
	}
	else
		return sw;
}
void determinareLocuriLibere(Heap& heap) {
	int nr = 0;
	int k = 0,j=0;
	int rand = 0;
	int* randuri=(int*)malloc(sizeof(int)*nrRanduri(heap));
	int* nrLocuriLibere = (int*)malloc(sizeof(int)*nrRanduri(heap));
	for (int i = 0; i < heap.heapSize; i++) {
			if (cautareString(randuri, j, heap.elements[i]->loc.nrRand) == 0) {
				randuri[j] = heap.elements[i]->loc.nrRand;
			    j++;
			}
	}
	for (int i = 0; i < j; i++) {
		nr = 0;
		for (int k = 0; k < heap.heapSize; k++) {
			if (randuri[i] == heap.elements[k]->loc.nrRand) {
				if (heap.elements[k]->loc.s == 1) {
					nr++;
				}
			}
		}
		nrLocuriLibere[i] = nr;
		printf("Pe randul %d mai sunt %d locuri disponibile\n", randuri[i], nrLocuriLibere[i]);
	}
}

void main() {
	Heap heap;
	CursaAutocar* c=(CursaAutocar*)malloc(sizeof(CursaAutocar));
	initHeap(heap, 10);
	FILE* f = fopen("locuri.txt", "r");
	char* buffer = (char*)malloc(DIM_BUFFER);
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			c->loc.indicativLoc = (char*)malloc(strlen(token) + 1);
			strcpy(c->loc.indicativLoc, token);
			token = strtok(NULL, sep);
			c->loc.nrRand = atoi(token);
			token = strtok(NULL, sep);
			c->loc.pret = atof(token);
			token = strtok(NULL, sep);
			c->loc.s = convertToStare(token);
			token = strtok(NULL, sep);
			c->capacitateLocuri = atoi(token);
			token = strtok(NULL, sep);
			c->distantaKm = atof(token);
			token = strtok(NULL, sep);
			Enqueue(heap, c);
		}
	}
	/*displayQ(heap);*/
	/*printf("----------\n");
	marirePrioritate(heap);
	displayQ(heap);*/
	/*printf("Costul mediu este:%.2f LEI",determinareCostMediu(heap, "A2"));*/
	//printf("Incasarile totale sunt:%.2f", incasariTotale(heap));
	/*printf("%d", nrRanduri(heap));*/
	determinareLocuriLibere(heap);

}

