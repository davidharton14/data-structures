#include "stdio.h"
#include "stdlib.h"
#include<string.h>

#define DIM_BUFFER 300

struct CardAcces {
	/*char* cod;*/
	int cod;
	int durataValabilitate;
	int creditConsum;
	int nrCalatorii;
	int nrValidari;
	int* istoricValidari;
};

struct Heap {
	CardAcces** elements;
	int heapSize;
	int index;
};

void initHeap(Heap&, int);
//CardAcces* createPacient(int, const char*, const char*, float, int);
void displayPacient(CardAcces*);
void ReheapUp(Heap, int, int);
void displayQ(Heap&);

void initHeap(Heap& heap, int size) {
	heap.elements = (CardAcces**)malloc(sizeof(CardAcces*)*size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(CardAcces*)*size);
}
//
//CardAcces* createCardAcces(char* cod,int durataValabilitate,int creditConsum,int nrCalatorii,int* istoricValidari) {
//	CardAcces* nou=(CardAcces*)malloc(sizeof(CardAcces));
//	nou->cod = (char*)malloc(strlen(cod) + 1);
//
//	nou->durataValabilitate = durataValabilitate;
//	nou->creditConsum = creditConsum;
//	nou->nrCalatorii = nrCalatorii;
//	nou->istoricValidari = (int*)malloc(sizeof(int)*nrCalatorii);
//	for (int i = 0; i < nrCalatorii; i++) {
//		nou->istoricValidari[i] = istoricValidari[i];
//	}
//	return nou;
//}

void displayCardAcces(CardAcces* c) {
	printf("Cod:%d\nDurata de valabilitate:%d ZILE\nCredit de consum:%d LEI\nNr calatorii:%d\nNr validari:%d\n", c->cod, c->durataValabilitate, c->creditConsum,c->nrCalatorii,c->nrValidari);
	printf("Istoric validari: ");
	for (int i = 0; i < c->nrValidari; i++) {
		printf("%d ", c->istoricValidari[i]);
	}
	printf("\n\n");
}

void Enqueue(Heap& heap, CardAcces* c){
	if (heap.index < heap.heapSize) {
		CardAcces* nou = (CardAcces*)malloc(sizeof(CardAcces));
		nou->cod = c->cod;
		nou->durataValabilitate = c->durataValabilitate;
		nou->creditConsum = c->creditConsum;
		nou->nrCalatorii = c->nrCalatorii;
		nou->nrValidari = c->nrValidari;
		nou->istoricValidari = (int*)malloc(sizeof(int)*c->nrValidari);
		for (int i = 0; i < c->nrValidari; i++) {
			nou->istoricValidari[i] = c->istoricValidari[i];
		}
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}

void ReheapUp(Heap heap, int first, int last)
{
	int parinte;
	CardAcces* temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->cod <
			heap.elements[last]->cod)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			ReheapUp(heap, first, parinte);
		}
	}
}

void adaugaCardAcces(Heap& heap, CardAcces* c) {
	CardAcces* nou = (CardAcces*)malloc(sizeof(CardAcces));
	nou->cod = c->cod;
	nou->durataValabilitate = c->durataValabilitate;
	nou->creditConsum = c->creditConsum;
	nou->nrCalatorii = c->nrCalatorii;
	nou->nrValidari = c->nrValidari;
	nou->istoricValidari = (int*)malloc(sizeof(int)*c->nrValidari);
	for (int i = 0; i < c->nrValidari; i++) {
		c->istoricValidari[i] = c->istoricValidari[i];
	}

	heap.heapSize++;
	if (heap.index < heap.heapSize) {
		CardAcces* nou = c;
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}
void displayQ(Heap& heap) {
	for (int i = 0; i < heap.heapSize; i++) {
		printf("Index:%d\n", i);
		displayCardAcces(heap.elements[i]);
	}
}
CardAcces* validareCard(Heap& heap,int cod,int debit) {
	CardAcces* c = (CardAcces*)malloc(sizeof(CardAcces));
	for (int i = 0; i < heap.heapSize; i++) {
		if (heap.elements[i]->cod == cod) {
			heap.elements[i]->creditConsum = debit;
			c->cod = heap.elements[i]->cod;
			c->durataValabilitate = heap.elements[i]->durataValabilitate;
			c->nrCalatorii = heap.elements[i]->nrCalatorii;
			c->creditConsum = heap.elements[i]->creditConsum;
			c->nrValidari = heap.elements[i]->nrValidari;
			c->istoricValidari = (int*)malloc(sizeof(int)*c->nrValidari);
			for (int j = 0; j < heap.elements[i]->nrValidari; j++) {
				c->istoricValidari[j] = heap.elements[i]->istoricValidari[j];
			}
		}
	}
	return c;
}

int afisareCreditDeConsum(Heap& heap, int cod) {
	int credit=0;
	for (int i = 0; i < heap.heapSize; i++) {
		if (heap.elements[i]->cod == cod) {
			credit = heap.elements[i]->creditConsum;
		}
	}
	return credit;
}
void expirareaValabilitatii(Heap& heap, int nrZile) {
	for (int i = 0; i < heap.heapSize; i++) {
		if (heap.elements[i]->durataValabilitate<nrZile) {
			displayCardAcces(heap.elements[i]);
		}
	}
}

void main() {
	Heap heap;
	CardAcces* c = (CardAcces*)malloc(sizeof(CardAcces));
	initHeap(heap, 5);
	FILE* f = fopen("carduriAcces.txt", "r");
	char* buffer = (char*)malloc(DIM_BUFFER);
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			c->cod = atoi(token);
			token = strtok(NULL, sep);
			c->durataValabilitate = atoi(token);
			token = strtok(NULL, sep);
			c->creditConsum = atoi(token);
			token = strtok(NULL, sep);
			c->nrCalatorii = atoi(token);
			token = strtok(NULL, sep);
			c->nrValidari = atoi(token);
			c->istoricValidari = (int*)malloc(sizeof(int)*c->nrValidari);
			for (int i = 0; i < c->nrValidari; i++) {
				token = strtok(NULL, sep);
				c->istoricValidari[i] = atoi(token);
			}
			Enqueue(heap, c);
		}
		/*adaugaPacient(heap, 9, "Harton Daniel", "Probleme de sanatate", 22, 1, 2, 3);*/ //ex3
		fclose(f);
	}
	/*displayQ(heap);*/
	/*printf("\n");
	c=validareCard(heap, 1, 200);
	displayCardAcces(c);*/
	/*printf("Creditul de consum al cardului 12 este %d", afisareCreditDeConsum(heap, 12));*/
	/*expirareaValabilitatii(heap, 100);*/
}


