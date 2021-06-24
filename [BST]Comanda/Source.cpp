#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;
#define DIM_BUFFER 300

struct Comanda {
	int id_comanda;
	int timp_livrare;
	int cod_client;
	char* numeClient;
	int nrProduse;
	int valoareComanda;
	char* data;
	int suma_totala;
};

struct NodArb {
	Comanda* c;
	NodArb* st;
	NodArb* dr;
};
struct nodLista {
	Comanda* info;
	nodLista* next;
};

void displayComanda(Comanda* c) {
	printf("Id comanda:%d\nTimp livrare:%d\nCod client:%d\nNume client:%s\nNr produse:%d\nValoare comanda:%d\nData:%s\n\n",
		c->id_comanda, c->timp_livrare, c->cod_client, c->numeClient, c->nrProduse, c->valoareComanda,c->data);
}


NodArb* inserareArb(NodArb* rad, Comanda* c) {
	if (rad) {
		if (c->id_comanda < rad->c->id_comanda) {
			rad->st = inserareArb(rad->st, c);
		}
		else {
			rad->dr = inserareArb(rad->dr, c);
		}
		return rad;
	}
	else
	{
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->c = c;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}

}

void displayArb(NodArb* rad) {
	if (rad) {
		displayComanda(rad->c);
		displayArb(rad->st);
		displayArb(rad->dr);
	}
}

Comanda* createComanda(Comanda* c) {
	Comanda* nou = (Comanda*)malloc(sizeof(Comanda));
	nou->id_comanda = c->id_comanda;
	nou->timp_livrare = c->timp_livrare;
	nou->cod_client = c->cod_client;
	nou->numeClient = (char*)malloc(strlen(c->numeClient) + 1);
	strcpy(nou->numeClient, c->numeClient);
	nou->nrProduse = c->nrProduse;
	nou->valoareComanda = c->valoareComanda;
	nou->data = (char*)malloc(strlen(c->data) + 1);
	strcpy(nou->data, c->data);
	return nou;
}

int nrComenzi(NodArb* root, int timp) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	int nr = 0;
	int j = 0;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (curr->c->timp_livrare > timp) {
				nr++;
			}
			curr = curr->dr;
		}
	}
	return nr;
}

Comanda** determinareComenzi(NodArb* root, int timp) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	Comanda** vector = (Comanda**)malloc(sizeof(Comanda*)*nrComenzi(root, timp));
	int j = 0;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (curr->c->timp_livrare > timp) {
				vector[j] = createComanda(curr->c);
				j++;
			}
			curr = curr->dr;
		}
	}
	return vector;
}

struct Heap
{
	Comanda**elements;
	int heapSize;
	int index;
};

void initHeap(Heap &, int);
void displayComanda(Comanda*);
void ReheapUp(Heap, int, int);
void displayQ(Heap &);

void initHeap(Heap &heap, int size)
{
	heap.elements = (Comanda**)malloc(sizeof(Comanda*) * size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(Comanda*) * size);
}

void Enqueue(Heap &heap, Comanda* c)
{
	if (heap.index < heap.heapSize)
	{
		Comanda*nou = createComanda(c);
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}

void ReheapUp(Heap heap, int first, int last)
{
	int parinte;
	Comanda*temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->timp_livrare <
			heap.elements[last]->timp_livrare)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			ReheapUp(heap, first, parinte);
		}
	}
}

void displayQ(Heap &heap)
{
	for (int i = 0; i < heap.heapSize; i++)
	{
		printf("Index:%d\n", i);
		displayComanda(heap.elements[i]);
	}
}

Heap copiere(NodArb* root,int timp) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	Heap heap;
	initHeap(heap, nrComenzi(root,timp));
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (curr->c->timp_livrare > timp) {
				Enqueue(heap, curr->c);
			}

			curr = curr->dr;
		}
	}	
	return heap;
}

void swap(Comanda*a, Comanda*b)
{
	Comanda*temp = (Comanda*)malloc(sizeof(Comanda));
	temp->id_comanda = a->id_comanda;
	temp->timp_livrare = a->timp_livrare;
	temp->cod_client = a->cod_client;
	temp->numeClient = (char*)malloc(strlen(a->numeClient) + 1);
	strcpy(temp->numeClient, a->numeClient);
	temp->nrProduse = a->nrProduse;
	temp->valoareComanda = a->valoareComanda;
	temp->data = (char*)malloc(strlen(a->data) + 1);
	strcpy(temp->data, a->data);

	a->id_comanda = b->id_comanda;
	a->timp_livrare = b->timp_livrare;
	a->cod_client = b->cod_client;
	a->numeClient = (char*)malloc(strlen(b->numeClient) + 1);
	strcpy(a->numeClient, b->numeClient);
	a->nrProduse = b->nrProduse;
	a->valoareComanda = b->valoareComanda;
	a->data = (char*)malloc(strlen(b->data) + 1);
	strcpy(a->data, b->data);

	b->id_comanda = temp->id_comanda;
	b->timp_livrare = temp->timp_livrare;
	b->cod_client = temp->cod_client;
	b->numeClient = (char*)malloc(strlen(temp->numeClient) + 1);
	strcpy(b->numeClient, temp->numeClient);
	b->nrProduse = temp->nrProduse;
	b->valoareComanda = temp->valoareComanda;
	b->data = (char*)malloc(strlen(temp->data) + 1);
	strcpy(b->data, temp->data);

	free(temp);
	//temp = a;
	//a = b;
	//b = temp;
}

Comanda*extragereComanda(Heap &heap, int index)
{
	Comanda*nou = (Comanda*)malloc(sizeof(Comanda));
	nou = createComanda(heap.elements[index]);

	swap(heap.elements[index], heap.elements[heap.heapSize - 1]);
	heap.heapSize -= 1;
	for (int i = 0; i < heap.heapSize; i++)
	{
		ReheapUp(heap, 0, i);
	}
	return nou;
	free(nou);
}

Comanda* createComandaa(int cod, int suma) {
	Comanda* nou = (Comanda*)malloc(sizeof(Comanda));
	nou->cod_client = cod;
	nou->suma_totala = suma;
	return nou;
}

int cautare(int k, int* sir, int value) {
	int sw = 0;
	for (int i = 0; i < k; i++) {
		if (sir[i]==value) {
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

int nrComenziTotale(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	int nr = 0;
		while (!stack.empty() || curr != NULL)
		{
			if (curr != NULL)
			{
				stack.push(curr);
				curr = curr->st;
			}
			else {
				curr = stack.top();
				stack.pop();
				nr++;
				curr = curr->dr;
			}
		}
	return nr;
}

int nrClienti(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	int* sir = (int*)malloc(sizeof(int)*nrComenziTotale(root));
	int j = 0;
		while (!stack.empty() || curr != NULL)
		{
			if (curr != NULL)
			{
				stack.push(curr);
				curr = curr->st;
			}
			else {
				curr = stack.top();
				stack.pop();
				if (cautare(j, sir, curr->c->cod_client) == 0) {
					sir[j] = curr->c->cod_client;
					j++;
				}
				curr = curr->dr;
			}
		}
	return j;
}


Comanda** salvareComenzi(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	int* sir = (int*)malloc(sizeof(int)*nrClienti(root));
	Comanda** vector = (Comanda**)malloc(sizeof(Comanda*)*nrClienti(root));
	int j = 0;
	int k = 0;
	while (!stack.empty() || curr != NULL)
	{
		if (curr != NULL)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (cautare(j, sir, curr->c->cod_client) == 0) {
				sir[j] = curr->c->cod_client;
				j++;
			}
			curr = curr->dr;
		}
	}
	for (int i = 0; i < j; i++) {
		NodArb* t = root;
		int sum = 0;
		while (!stack.empty() || t != NULL)
		{
			if (t != NULL)
			{
				stack.push(t);
				t = t->st;
			}
			else {
				t = stack.top();
				stack.pop();
				if (sir[i] == t->c->cod_client)
				sum += t->c->valoareComanda;
				t = t->dr;
			}
		}
		vector[k] = createComandaa(sir[i], sum);
		k++;
	}
	return vector;
}

void main() {
	Comanda* c=NULL;
	NodArb* rad = NULL;
	FILE* f = fopen("comenzi.txt", "r");
	char* buffer = (char*)malloc(DIM_BUFFER);
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			c = (Comanda*)malloc(sizeof(Comanda));
			token = strtok(buffer, sep);
			c->id_comanda = atoi(token);
			token = strtok(NULL, sep);
			c->timp_livrare = atoi(token);
			token = strtok(NULL, sep);
			c->cod_client = atoi(token);
			token = strtok(NULL, sep);
			c->numeClient = (char*)malloc(strlen(token) + 1);
			strcpy(c->numeClient, token);
			token = strtok(NULL, sep);
			c->nrProduse = atoi(token);
			token = strtok(NULL, sep);
			c->valoareComanda = atoi(token);
			token = strtok(NULL, sep);
			c->data = (char*)malloc(strlen(token) + 1);
			strcpy(c->data, token);
			rad = inserareArb(rad, c);
		}
		fclose(f);
	}
	//ex1
	displayArb(rad);
	//ex2
	printf("\n\n");
	Comanda** vector = (Comanda**)malloc(sizeof(Comanda*)*nrComenzi(rad, 10));
	vector = determinareComenzi(rad, 10);
	for (int i = 0; i < nrComenzi(rad, 10); i++) {
		displayComanda(vector[i]);
	}
	//ex3
	printf("\n\n");
	Heap h;
	h = copiere(rad,10);
	displayQ(h);
	printf("\n----------------");
	Comanda*p = NULL;
	p = extragereComanda(h, 1);
	displayQ(h);
	printf("\nComanda extrasa din structura este:\n\n");
	displayComanda(p);
	//ex4
	Comanda** vec = (Comanda**)malloc(sizeof(Comanda*)*nrClienti(rad));
	vec = salvareComenzi(rad);
	for (int i = 0; i < nrClienti(rad); i++) {
		printf("Nr client:%d\nSuma totala:%d\n\n", vec[i]->cod_client, vec[i]->suma_totala);
	}
}