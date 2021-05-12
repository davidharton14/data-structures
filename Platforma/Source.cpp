#include <stdio.h>
#include <stdlib.h>
#include<string.h>
using namespace std;
#define DIM_BUFFER 300

struct Platforma {
	char* firma;
	char* denumire;
	float pret;
	int nrVersiuni;
	float* versiuni;
};

struct MinHeap {
	Platforma** elements;
	int heapSize;
	int index;
};

void initMinHeap(MinHeap&, int);
void displayPlatforma(Platforma*);
void ReheapUp(MinHeap, int, int);
void displayQ(MinHeap&);

void initMinHeap(MinHeap& heap, int size) {
	heap.elements = (Platforma**)malloc(sizeof(Platforma*)*size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(Platforma*)*size);
}

void displayPlatforma(Platforma* p) {
	printf("Firma:%s\nDenumire:%s\nPret:%.2f\nNr versiuni:%d\n", p->firma, p->denumire, p->pret, p->nrVersiuni);
	printf("Versiuni:");
	for (int i = 0; i < p->nrVersiuni; i++) {
		printf("%.2f ", p->versiuni[i]);
	}
	printf("\n\n");
}

void Enqueue(MinHeap& heap, Platforma* p) {
	if (heap.index < heap.heapSize) {
		Platforma* nou = (Platforma*)malloc(sizeof(Platforma));
		nou->firma = (char*)malloc(strlen(p->firma) + 1);
		strcpy(nou->firma, p->denumire);
		nou->denumire = (char*)malloc(strlen(p->denumire) + 1);
		strcpy(nou->denumire, p->denumire);
		nou->pret = p->pret;
		nou->nrVersiuni = p->nrVersiuni;
		nou->versiuni = (float*)malloc(sizeof(float)*nou->nrVersiuni);
		for (int i = 0; i < p->nrVersiuni; i++) {
			nou->versiuni[i] = p->versiuni[i];
		}
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}

void ReheapUp(MinHeap heap, int first, int last)
{
	int parinte;
	Platforma* temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->pret >
			heap.elements[last]->pret)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			ReheapUp(heap, first, parinte);
		}
	}
}


void displayQ(MinHeap& heap) {
	for (int i = 0; i < heap.heapSize; i++) {
		printf("Index:%d\n", i);
		displayPlatforma(heap.elements[i]);
	}
}

float pretMin(MinHeap& heap) {
	float min = heap.elements[0]->pret;
	for (int i = 0; i < heap.heapSize; i++) {
		if (heap.elements[i]->pret < min)
			min = heap.elements[i]->pret;
	}
	return min;
}

void modificarePret(MinHeap& heap, const char* nume) {
	for (int i = 0; i < heap.heapSize; i++) {
		if (strcmp(heap.elements[i]->denumire, nume) == 0)
			heap.elements[i]->pret = pretMin(heap);
	}
}

struct NodArb {
	Platforma* info;
	NodArb* left;
	NodArb* right;
};

NodArb* inserareArb(NodArb* rad, Platforma* p) {
	if (rad) {
		if (p->pret < rad->info->pret) {
			rad->left = inserareArb(rad->left, p);
		}
		else
			rad->right = inserareArb(rad->right, p);
		return rad;
	}
	else {
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->info = p;
		nou->left = NULL;
		nou->right = NULL;
	}
}

NodArb* insertElementsToArb(MinHeap& heap,int n) {
	NodArb* nod = NULL;
	for (int i = 0; i < n; i++) {
		nod = inserareArb(nod, heap.elements[i]);
	}
	return nod;
}
void afisareArb(NodArb* rad) {
	if (rad) {
		displayPlatforma(rad->info);
		afisareArb(rad->right);
		afisareArb(rad->left);
	}
}
void freeTree(NodArb* root) {               //Tree's root note is passed as argument
	while (root != NULL)
	{
		NodArb* n = root;
		while (n != NULL)
		{
			if (n->left)
				n = n->left;
			else
				if (n->right)
					n = n->right;
				else
				{
					if (n == root)
						root = NULL;
					free(n);
					break;
				}
		}
	}
}

NodArb* minValueNode(NodArb* node)
{
	NodArb* current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

void freeBST(NodArb* t) //get root
{
	if (t == NULL)
		return;
	if (t->left != NULL)
		freeBST(t->left);
	if (t->right != NULL)
		freeBST(t->right);

	delete t;       /* free(t) if c */

	return;
}

void delete_queue(MinHeap& heap)
{
	for (int i = 0; i < heap.heapSize; i++) {
		/*Platforma* nou = (Platforma*)malloc(sizeof(Platforma));
		nou->firma = (char*)malloc(strlen(heap.elements[i]->firma) + 1);
		strcpy(	nou->firma,heap.elements[i]->firma);
		nou->denumire = (char*)malloc(strlen(heap.elements[i]->denumire) + 1);
		strcpy(nou->denumire, heap.elements[i]->denumire);
		nou->pret = heap.elements[i]->pret;
		nou->nrVersiuni = heap.elements[i]->nrVersiuni;
		nou->versiuni = (float*)malloc(sizeof(float)*nou->nrVersiuni);
		for (int j = 0; j < nou->nrVersiuni; j++) {
			nou->versiuni[i] = heap.elements[i]->versiuni[j];
		}*/
		free(heap.elements[i]);
		heap.heapSize--;
	}
	
}


//void deletion(MinHeap& heap) {
//	for (int i = 0; i < heap.heapSize; i++) {
//		heap.elements[i] = heap.elements[--heap.index];
//		ReheapDown(heap, i, heap.index-1);
//	}
//}
void main() {
	MinHeap heap;
	Platforma* p = (Platforma*)malloc(sizeof(Platforma));;
	initMinHeap(heap, 10);
	FILE* f = fopen("platforme.txt", "r");
	char* buffer = (char*)malloc(DIM_BUFFER);
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			/*p = (Platforma*)malloc(sizeof(Platforma));*/
			token = strtok(buffer, sep);
			p->firma = (char*)malloc(strlen(token) + 1);
			strcpy(p->firma, token);
			token = strtok(NULL, sep);
			p->denumire = (char*)malloc(strlen(token) + 1);
			strcpy(p->denumire, token);
			token = strtok(NULL, sep);
			p->pret = atof(token);
			token = strtok(NULL, sep);
			p->nrVersiuni = atoi(token);
			p->versiuni = (float*)malloc(sizeof(float)*p->nrVersiuni);
			for (int i = 0; i < p->nrVersiuni; i++) {
				token = strtok(NULL, sep);
				p->versiuni[i] = atof(token);
			}
			Enqueue(heap, p);
		}
	}
	/*displayQ(heap);*/
	/*modificarePret(heap, "Adobe Premiere");*/
	/*displayQ(heap);*/
	NodArb* rad = insertElementsToArb(heap,5);
	/*afisareArb(rad);*/
	/*freeBST(rad);*/
	/*afisareArb(rad);*/
	delete_queue(heap);
	displayQ(heap);
	
}

