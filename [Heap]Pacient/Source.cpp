#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define DIM_BUFFER 300
struct Pacient
{
	int cod;
	char *nume;
	char *descriereProblema;
	float varsta;
	int prioritate;
	int categorie;
	int ore;
};

struct Heap
{
	Pacient **elements;
	int heapSize;
	int index;
};

void initHeap(Heap &, int);
Pacient *createPacient(int, const char *, const char *, float, int);
void displayPacient(Pacient *);
void ReheapUp(Heap, int, int);
void displayQ(Heap &);

void initHeap(Heap &heap, int size)
{
	heap.elements = (Pacient **)malloc(sizeof(Pacient *) * size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(Pacient *) * size);
}

Pacient *createPacient(int cod, const char *nume, const char *descriereProblema, float varsta, int prioritate, int ore)
{
	Pacient *nou = (Pacient *)malloc(sizeof(Pacient));
	nou->cod = cod;
	nou->nume = (char *)malloc(strlen(nume) + 1);
	strcpy(nou->nume, nume);
	nou->descriereProblema = (char *)malloc(strlen(descriereProblema) + 1);
	strcpy(nou->descriereProblema, descriereProblema);
	nou->varsta = varsta;
	nou->prioritate = prioritate;
	int categorie;
	if (prioritate == 5)
		nou->categorie = 1;
	else if (prioritate == 4)
	{
		nou->categorie = 2;
	}
	else if (prioritate == 1 || prioritate == 2 || prioritate == 3)
	{
		nou->categorie = 3;
	}
	nou->ore = ore;
	return nou;
}

void displayPacient(Pacient *p)
{
	printf("Cod:%d\nNume:%s\nDescriere problema:%s\nVarsta:%.2f\nPrioritate:%d\nCategorie:%d\nOre:%d\n\n", p->cod, p->nume, p->descriereProblema, p->varsta, p->prioritate, p->categorie, p->ore);
}

void Enqueue(Heap &heap, int cod, const char *nume, const char *descriereProblema, float varsta, int prioritate, int ore)
{
	if (heap.index < heap.heapSize)
	{
		Pacient *nou = createPacient(cod, nume, descriereProblema, varsta, prioritate, ore);
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}

void ReheapUp(Heap heap, int first, int last)
{
	int parinte;
	Pacient *temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->prioritate <
			heap.elements[last]->prioritate)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			ReheapUp(heap, first, parinte);
		}
	}
}

void ReheapDown(Heap heap, int current, int last)
{
	int leftChild, rightChild, maxChild;
	Pacient *temp = NULL;
	leftChild = 2 * current + 1;
	rightChild = 2 * current + 2;
	if (leftChild <= last)
	{
		if (leftChild == last)
			maxChild = leftChild;
		if (heap.elements[leftChild]->cod <
			heap.elements[rightChild]->cod)
			maxChild = leftChild;
		else
			maxChild = rightChild;

		if (heap.elements[current]->cod >
			heap.elements[maxChild]->cod)
		{
			temp = heap.elements[current];
			heap.elements[current] = heap.elements[maxChild];
			heap.elements[maxChild] = temp;
		}
		ReheapDown(heap, maxChild, last);
	}
}

Pacient *Dequeue(Heap &heap)
{
	Pacient *result = NULL;
	if (heap.index > 0)
	{
		result = heap.elements[0];
		heap.elements[0] = heap.elements[--heap.index];
		ReheapDown(heap, 0, heap.index - 1);
	}
	return result;
}

void displayQ(Heap &heap)
{
	for (int i = 0; i < heap.heapSize; i++)
	{
		printf("Index:%d\n", i);
		displayPacient(heap.elements[i]);
	}
}
void adaugaPacient(Heap &heap, int cod, const char *nume, const char *descriereProblema, float varsta, int prioritate, int ore, int categorie)
{
	Pacient *p = (Pacient *)malloc(sizeof(Pacient));
	p->cod = cod;
	p->nume = (char *)malloc(strlen(nume) + 1);
	strcpy(p->nume, nume);
	p->descriereProblema = (char *)malloc(strlen(descriereProblema) + 1);
	strcpy(p->descriereProblema, descriereProblema);
	p->varsta = varsta;
	p->prioritate = prioritate;
	p->ore = ore;
	p->categorie = categorie;
	heap.heapSize++;
	if (heap.index < heap.heapSize)
	{
		Pacient *nou = p;
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}
int nrPacienti(Heap &heap, int c)
{
	int nr = 0;
	for (int i = 0; i < heap.heapSize; i++)
	{
		if (heap.elements[i]->categorie == c)
		{
			nr++;
		}
	}
	return nr;
}
void cresterePrioritate(Heap &heap, int ore)
{
	for (int i = 0; i < heap.heapSize; i++)
	{
		if (heap.elements[i]->ore >= ore)
		{
			heap.elements[i]->prioritate += 1;
		}
		ReheapUp(heap, 0, i);
	}
}
void printProbleme(Heap &heap)
{
	int nr = heap.heapSize, k, l = 0;
	char **charsArr = (char **)malloc(sizeof(char *) * nr);
	int *numsArr = (int *)malloc(sizeof(int) * nr);
	char *asd = (char *)malloc(strlen("asdasd") + 1);
	for (int i = 0; i < heap.heapSize; i++)
	{
		charsArr[l] = (char *)malloc(sizeof(char));
		if (strcmp(asd, heap.elements[i]->descriereProblema) != 0)
		{
			charsArr[l] = heap.elements[i]->descriereProblema;
			asd = charsArr[l];
			l++;
		}
	}
	for (int i = 0; i < l; i++)
	{
		printf("%s - \n", charsArr[i]);
		k = 1;
		for (int j = 0; j < l; j++)
		{
			if (strcmp(heap.elements[j]->descriereProblema, charsArr[i]) == 0)
			{
				k++;
			}
		}
		printf("%d\n", k);
	}
}

void swap(Pacient *a, Pacient *b)
{
	Pacient *temp = (Pacient *)malloc(sizeof(Pacient));
	temp->cod = b->cod;
	temp->nume = (char *)malloc(strlen(b->nume) + 1);
	strcpy(temp->nume, b->nume);
	temp->descriereProblema = (char *)malloc(strlen(b->descriereProblema) + 1);
	strcpy(temp->descriereProblema, b->descriereProblema);
	temp->varsta = b->varsta;
	temp->prioritate = b->prioritate;
	temp->ore = b->ore;
	temp->categorie = b->categorie;

	b->cod = a->cod;
	b->nume = (char *)malloc(strlen(a->nume) + 1);
	strcpy(b->nume, a->nume);
	b->descriereProblema = (char *)malloc(strlen(a->descriereProblema) + 1);
	strcpy(b->descriereProblema, a->descriereProblema);
	b->varsta = a->varsta;
	b->prioritate = a->prioritate;
	b->ore = a->ore;
	b->categorie = a->categorie;

	a->cod = temp->cod;
	a->nume = (char *)malloc(strlen(temp->nume) + 1);
	strcpy(a->nume, temp->nume);
	a->descriereProblema = (char *)malloc(strlen(temp->descriereProblema) + 1);
	strcpy(a->descriereProblema, temp->descriereProblema);
	a->varsta = temp->varsta;
	a->prioritate = temp->prioritate;
	a->ore = temp->ore;
	a->categorie = temp->categorie;

	free(temp);
	//temp = a;
	//a = b;
	//b = temp;
}
Pacient *extragerePacient(Heap &heap, int index)
{
	Pacient *nou = (Pacient *)malloc(sizeof(Pacient));
	nou->cod = heap.elements[index]->cod;
	nou->nume = (char *)malloc(strlen(heap.elements[index]->nume) + 1);
	strcpy(nou->nume, heap.elements[index]->nume);
	nou->descriereProblema = (char *)malloc(strlen(heap.elements[index]->descriereProblema) + 1);
	strcpy(nou->descriereProblema, heap.elements[index]->descriereProblema);
	nou->varsta = heap.elements[index]->varsta;
	nou->prioritate = heap.elements[index]->prioritate;
	nou->ore = heap.elements[index]->ore;
	nou->categorie = heap.elements[index]->categorie;

	swap(heap.elements[index], heap.elements[heap.heapSize - 1]);
	heap.heapSize -= 1;
	for (int i = 0; i < heap.heapSize; i++)
	{
		ReheapUp(heap, 0, i);
	}
	return nou;
	free(nou);
}
void main()
{
	Heap heap;
	initHeap(heap, 6);
	FILE *f = fopen("pacienti.txt", "r");
	char *buffer = (char *)malloc(DIM_BUFFER);
	if (f)
	{
		char *token, sep[] = ",";
		int cod, prioritate, ore;
		float varsta;
		char nume[50], desc[50];
		while (fgets(buffer, DIM_BUFFER, f))
		{
			token = strtok(buffer, sep);
			cod = atoi(token);
			token = strtok(NULL, sep);
			strcpy(nume, token);
			token = strtok(NULL, sep);
			strcpy(desc, token);
			token = strtok(NULL, sep);
			varsta = atof(token);
			token = strtok(NULL, sep);
			prioritate = atoi(token);
			token = strtok(NULL, sep);
			ore = atoi(token);
			Enqueue(heap, cod, nume, desc, varsta, prioritate, ore);
		}
		adaugaPacient(heap, 9, "Harton Daniel", "Probleme de sanatate", 22, 1, 2, 3); //ex3
	}
	/*displayQ(heap);*/																	//ex2
	/*printf("Numarul de pacienti cu categoria %d este %d.", 3, nrPacienti(heap, 1));*/ //ex4
	/*cresterePrioritate(heap, 2); //ex5
	printf("\n----------------");
	displayQ(heap);*/
	/*printProbleme(heap);*/ //ex6
	displayQ(heap);
	printf("\n----------------");
	Pacient *p = NULL;
	p = extragerePacient(heap, 1); //ex7
	displayQ(heap);
	printf("\nPacientul extras din structura este:\n\n");
	displayPacient(p);
}