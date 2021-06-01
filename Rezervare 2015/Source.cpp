#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300

enum status {
	CONFIRMATA,
	IN_ASTEPTARE
};

enum canal{
	APEL_TELEFONIC,
	APLICATIE_MOBILA
};

status convertToStatus(const char* str)
{
	if (strcmp(str, "CONFIRMATA") == 0) return CONFIRMATA;
	else if (strcmp(str, "IN_ASTEPTARE") == 0) return IN_ASTEPTARE;
}

canal convertToCanal(const char* str)
{
	if (strcmp(str, "APEL_TELEFONIC") == 0) return APEL_TELEFONIC;
	else if (strcmp(str, "APLICATIE_MOBILA") == 0) return APLICATIE_MOBILA;
}

const char* convertToString(status s)
{

	if (s == 0) return "CONFIRMATA";
	else if (s == 1) return "IN_ASTEPTARE";
}

const char* convertToString2(canal c)
{

	if (c == 0) return "APEL_TELEFONIC";
	else if (c == 1) return "APLICATIE_MOBILA";
}

struct Rezervare {
	char* numeClient;
	int numarTelefon;
	int id;
	status s;
	canal c;
	unsigned int durata;
};


struct Heap {
	Rezervare** elements;
	int heapSize;
	int index;
};


void initHeap(Heap&, int);
void displayRezervare(Rezervare*);
void ReheapUp(Heap, int, int);
void displayQ(Heap&);

void initHeap(Heap& heap, int size) {
	heap.elements = (Rezervare**)malloc(sizeof(Rezervare*)*size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(Rezervare*)*size);
}

void displayRezervare(Rezervare* r) {
	printf("Nume client:%s\nNumar telefon:%d\nId:%d\nStatus:%s\nCanal:%s\nDurata:%d\n\n",r->numeClient, r->numarTelefon, r->id, convertToString(r->s), convertToString2(r->c), r->durata);
}

void Enqueue(Heap& heap, Rezervare* c) {
	if (heap.index < heap.heapSize) {
		Rezervare* nou = (Rezervare*)malloc(sizeof(Rezervare));
		nou->numeClient = (char*)malloc(strlen(c->numeClient) + 1);
		strcpy(nou->numeClient, c->numeClient);
		nou->numarTelefon = c->numarTelefon;
		nou->id = c->id;
		nou->s = c->s;
		nou->c = c->c;
		nou->durata = c->durata;
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}

void ReheapUp(Heap heap, int first, int last)
{
	int parinte;
	Rezervare* temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->durata <
			heap.elements[last]->durata)
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
		displayRezervare(heap.elements[i]);
	}
}

void raport(Heap& heap) {
	int* arr = (int*)malloc(sizeof(int)*heap.heapSize);
	int j = 0;
	for (int i = 0; i < heap.heapSize; i++) {
		if (heap.elements[i]->s == 1) {
			arr[j] = heap.elements[i]->durata;
			j++;
		}
	}
	int nr = j;
	for (int i = 0; i < nr; i++) {
		for (int j = i + 1; j < nr; j++) {
			if (arr[i] < arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	FILE *fptr;
	fptr = fopen("raport.txt", "w");
	char sep[] = ", ";
	char sep2[] = "\n";
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	else {
		for (int j = 0; j < nr; j++) {
			for (int i = 0; i < heap.heapSize; i++) {
				if (arr[j] == heap.elements[i]->durata&& heap.elements[i]->s==1) {
					fprintf(fptr, "%s", heap.elements[i]->numeClient);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", heap.elements[i]->numarTelefon);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", heap.elements[i]->id);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%s", convertToString(heap.elements[i]->s));
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%s", convertToString2(heap.elements[i]->c));
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", heap.elements[i]->durata);
					fprintf(fptr, "%s", sep2);
				}
			}
		}
		fclose(fptr);
		printf("\nRaportul a fost creat");
	}
}

void swap(Rezervare* a, Rezervare* b)
{
	Rezervare* temp = (Rezervare*)malloc(sizeof(Rezervare));
	temp->numeClient = (char*)malloc(strlen(a->numeClient) + 1);
	strcpy(temp->numeClient, a->numeClient);
	temp->numarTelefon = a->numarTelefon;
	temp->id = a->id;
	temp->s = a->s;
	temp->c = a->c;
	temp->durata = a->durata;

	a->numeClient = (char*)malloc(strlen(b->numeClient) + 1);
	strcpy(a->numeClient, b->numeClient);
	a->numarTelefon = b->numarTelefon;
	a->id =b->id;
	a->s = b->s;
	a->c = b->c;
	a->durata = b->durata;

	b->numeClient = (char*)malloc(strlen(temp->numeClient) + 1);
	strcpy(b->numeClient, temp->numeClient);
	b->numarTelefon = temp->numarTelefon;
	b->id = temp->id;
	b->s = temp->s;
	b->c = temp->c;
	b->durata = temp->durata;

	free(temp);
	//temp = a;
	//a = b;
	//b = temp;
}

struct Node
{
	Rezervare* r;
	Node* pNext;
	Node* pPrev;
};
struct Queue
{
	Node* head = NULL;
	Node* tail = NULL;
};

Node * createNode(Rezervare* r)
{
	Node* node = NULL;
	node = (Node*)malloc(sizeof(Node));
	node->r = r;
	node->pNext = node->pPrev = NULL;
	return node;
}
void push(Queue& q, Rezervare* r)
{
	Node *tmp, *qu;
	tmp = (Node *)malloc(sizeof(Node));
	tmp = createNode(r);
	/*Queue is empty or item to be added has priority more than first item*/
	if (q.head == NULL)
	{
		tmp->pNext = q.head;
		q.head = tmp;
	}
	else
	{
		qu = q.head;
		while (qu->pNext != NULL)
			qu = qu->pNext;
		tmp->pNext = qu->pNext;
		qu->pNext = tmp;
	}
}


void extragereRezervari(Heap& heap, Queue& q) {
	char** chars = (char**)malloc(sizeof(char*)*heap.heapSize);
	int j = 0;
	for (int i = 0; i < heap.heapSize; i++)
	{
		if (heap.elements[i]->s == convertToStatus("IN_ASTEPTARE")) {
			heap.elements[i]->s = convertToStatus("CONFIRMATA");
			push(q, heap.elements[i]);
			chars[j] = heap.elements[i]->numeClient;
			j++;
			
		}
	}
	for (int k = 0; k < j; k++) {
		for (int i = 0; i < heap.heapSize; i++)
		{
			if (strcmp(heap.elements[i]->numeClient,chars[k])==0) {
				swap(heap.elements[i], heap.elements[heap.heapSize - 1]);
				heap.heapSize -= 1;
			}
			for (int j = 0; j < heap.heapSize; j++)
			{
				if (strcmp(heap.elements[j]->numeClient, chars[k]) == 0) {
					swap(heap.elements[j], heap.elements[heap.heapSize - 1]);
					heap.heapSize -= 1;
				}
			}
		}
	}

	for (int i = 0; i < heap.heapSize; i++)
	{
		ReheapUp(heap, 0, i);
	}
}

void mutareElementeInAltaStructura(Heap& heap,Heap& h, const char* client) {
	for (int i = 0; i < heap.heapSize; i++)
	{
		if (strcmp(heap.elements[i]->numeClient, client) == 0) {
			swap(heap.elements[i], heap.elements[heap.heapSize - 1]);
			heap.heapSize -= 1;
		}
	}
	for (int i = 0; i < heap.heapSize; i++)
	{
		ReheapUp(heap, 0, i);
	}
	initHeap(h, heap.heapSize);
	for (int i = 0; i < heap.heapSize; i++)
	{
		Enqueue(h, heap.elements[i]);	
	}
}


void display(Queue& q)
{
	if (q.head == NULL)
		printf("\nStack is Empty!!!\n");
	else {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			displayRezervare(temp->r);
			temp = temp->pNext;
		}
		displayRezervare(temp->r);
	}
}

void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		displayRezervare(temp->r);
		temp = temp->pNext;
	}
}
void creareRaport(Queue& q) {
	FILE *fptr;
	fptr = fopen("raportul.txt", "w");
	char sep[] = ", ";
	char sep2[] = "\n";
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	else {
		if (q.head == NULL)
			printf("\nStack is Empty!!!\n");
		else {
			Node *temp = q.head;
			while (temp->pNext != NULL) {
				if (temp->r->s == 0) {
					fprintf(fptr, "%s", temp->r->numeClient);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", temp->r->numarTelefon);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", temp->r->id);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%s", convertToString(temp->r->s));
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%s", convertToString2(temp->r->c));
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", temp->r->durata);
					fprintf(fptr, "%s", sep2);
				}
				temp = temp->pNext;
			}
			if (temp->r->s == 0) {
				fprintf(fptr, "%s", temp->r->numeClient);
				fprintf(fptr, "%s", sep);
				fprintf(fptr, "%d", temp->r->numarTelefon);
				fprintf(fptr, "%s", sep);
				fprintf(fptr, "%d", temp->r->id);
				fprintf(fptr, "%s", sep);
				fprintf(fptr, "%s", convertToString(temp->r->s));
				fprintf(fptr, "%s", sep);
				fprintf(fptr, "%s", convertToString2(temp->r->c));
				fprintf(fptr, "%s", sep);
				fprintf(fptr, "%d", temp->r->durata);
				fprintf(fptr, "%s", sep2);
			}
			}
		fclose(fptr);
		printf("\nRaportul a fost creat");
		}
}

void main() {
	Heap heap;
	Rezervare* r = (Rezervare*)malloc(sizeof(Rezervare));
	initHeap(heap, 8);
	FILE* f = fopen("rezervari.txt", "r");
	char* buffer = (char*)malloc(DIM_BUFFER);
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			r->numeClient = (char*)malloc(strlen(token) + 1);
			strcpy(r->numeClient, token);
			token = strtok(NULL, sep);
			r->numarTelefon = atoi(token);
			token = strtok(NULL, sep);
			r->id = atoi(token);
			token = strtok(NULL, sep);
			r->s = convertToStatus(token);
			token = strtok(NULL, sep);
			r->c = convertToCanal(token);
			token = strtok(NULL, sep);
			r->durata = atoi(token);
			Enqueue(heap, r);
		}
	}
	/*displayQ(heap);*/
    
	//ex3
	/*raport(heap);
	printf("\n\n\n");*/

	//ex4
	/*Queue queue;
	extragereRezervari(heap, queue);
	displayQ(heap);
	printf("\n\n\n");
	display(queue);*/

	/*printf("\n\n\n");

	//ex5
	Heap h;
    mutareElementeInAltaStructura(heap,h, "Harton David");
	displayQ(h);*/

	//ex6
	/*creareRaport(queue);*/

}



