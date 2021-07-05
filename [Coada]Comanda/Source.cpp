#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300

enum MetodaDePlata {
	CASH,
	CARD
};

const char* convertToString(MetodaDePlata m)
{
	if (m == 0) return "CASH";
	else if (m == 1) return "CARD";
}
MetodaDePlata convertToMetodaDePlata(const char* string)
{
	if (strcmp(string,"CASH")==0) return CASH;
	else if (strcmp(string,"CARD")==0) return CARD;
}
struct Comanda {
	int timp_livrare;
	int cod_client;
	int id_comanda;
	char* nume_client;
	float suma_plata;
	char* numar_telefon;
	float total_plata;
	MetodaDePlata m;
};

void displayComanda(Comanda* c) {
	printf("Timp livrare:%d\nCod client:%d\nId comanda:%d\nNume client:%s\nSuma plata:%.2f\nNumar de telefon:%s\nMetoda de plata:%s\n\n",
		c->timp_livrare, c->cod_client, c->id_comanda, c->nume_client, c->suma_plata, c->numar_telefon,convertToString(c->m));
}

struct Node
{
	Comanda* c;
	Node* pNext;
	Node* pPrev;
};
struct Queue
{
	Node* head = NULL;
	Node* tail = NULL;
};


Node* newNode(Comanda* c)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->c = c;
	temp->pNext = NULL;

	return temp;
}


void push(Queue& q, Comanda* c, int p)
{
	Node *tmp, *qu;
	tmp = (Node *)malloc(sizeof(Node));
	tmp = newNode(c);
	if (q.head == NULL || p < q.head->c->id_comanda)
	{
		tmp->pNext = q.head;
		q.head = tmp;
	}
	else
	{
		qu = q.head;
		while (qu->pNext != NULL && qu->pNext->c->id_comanda <= p)
			qu = qu->pNext;
		tmp->pNext = qu->pNext;
		qu->pNext = tmp;
	}
}

void display(Queue& q)
{
	if (q.head == NULL)
		printf("\nQueue is empty!!!\n");
	else {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			displayComanda(temp->c);
			temp = temp->pNext;
		}
		displayComanda(temp->c);
	}
}

void swap(Comanda* a, Comanda* b)
{
	Comanda* temp = (Comanda*)malloc(sizeof(Comanda));
	temp->timp_livrare = a->timp_livrare;
	temp->cod_client = a->cod_client;
	temp->id_comanda = a->id_comanda;
	temp->nume_client = (char*)malloc(strlen(a->nume_client) + 1);
	strcpy(temp->nume_client, a->nume_client);
	temp->suma_plata = a->suma_plata;
	temp->numar_telefon = (char*)malloc(strlen(a->numar_telefon) + 1);
	strcpy(temp->numar_telefon, a->numar_telefon);
	temp->m = a->m;

	a->timp_livrare = b->timp_livrare;
	a->cod_client = b->cod_client;
	a->id_comanda = b->id_comanda;
	a->nume_client = (char*)malloc(strlen(b->nume_client) + 1);
	strcpy(a->nume_client, b->nume_client);
	a->suma_plata = b->suma_plata;
	a->numar_telefon = (char*)malloc(strlen(b->numar_telefon) + 1);
	strcpy(a->numar_telefon, b->numar_telefon);
	a->m = b->m;

	b->timp_livrare = temp->timp_livrare;
	b->cod_client = temp->cod_client;
	b->id_comanda = temp->id_comanda;
	b->nume_client = (char*)malloc(strlen(temp->nume_client) + 1);
	strcpy(b->nume_client, temp->nume_client);
	b->suma_plata = temp->suma_plata;
	b->numar_telefon = (char*)malloc(strlen(temp->numar_telefon) + 1);
	strcpy(b->numar_telefon, temp->numar_telefon);
	b->m = temp->m;

	free(temp);
	//temp = a;
	//a = b;
	//b = temp;
}

void stergereComenzi(Queue& q, int timp) {

	Node*ptr;
	Node*ptr2;
	Node*ptr3 = q.head;
	Node*temp;
	Node*head;
	int sw = 0;
	ptr = q.head;
	if (q.head == NULL)
		printf("Queue is empty\n");
	else
	{
		while (ptr != NULL)
		{
			sw = 0;
			if (ptr->c->timp_livrare > timp) {
				swap(q.head->c, ptr->c);
				sw = 1;
			}
			ptr = ptr->pNext;
			if (sw == 1) {
				Node *temp = q.head;
				q.head = q.head->pNext;
				free(temp);
			}
		}
	}
	ptr2 = q.head;
	Queue que;
	Comanda* c = NULL;
	while (ptr2 != NULL)
	{
		push(que, ptr2->c, ptr2->c->id_comanda);
		ptr2 = ptr2->pNext;
	}
	q = que;
}

int nrComenziTotale(Queue& q) {
	int nr = 0;
	if (q.head) {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			nr++;
			temp = temp->pNext;
		}
		nr++;
	}
	return nr;
}

int nrComenzi(Queue& q,int timp) {
	int nr = 0;
	if (q.head) {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (temp->c->timp_livrare > timp) {
				nr++;
			}
			temp = temp->pNext;
		}
		if(temp->c->timp_livrare>timp)
		nr++;
	}
	return nr;
}

Comanda** determinareComenzi(Queue& q, int timp) {
	Comanda** vector = (Comanda**)malloc(sizeof(Comanda*)*nrComenzi(q, timp));
	int j = 0;
	if (q.head){
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (temp->c->timp_livrare > timp) {
				vector[j] = temp->c;
				j++;
			}
			temp = temp->pNext;
		}
		if (temp->c->timp_livrare > timp) {
			vector[j] = temp->c;
			j++;
		}
	}
	return vector;
}

struct Heap {
	Comanda** elements;
	int heapSize;
	int index;
};

void initHeap(Heap& heap, int size) {
	heap.elements = (Comanda**)malloc(sizeof(Comanda*)*size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(Comanda*)*size);
}

void ReheapUp(Heap heap, int first, int last)
{
	int parinte;
	Comanda* temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->id_comanda <
			heap.elements[last]->id_comanda)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			ReheapUp(heap, first, parinte);
		}
	}
}

void Enqueue(Heap& heap, Comanda* c) {
	if (heap.index < heap.heapSize) {
		Comanda* nou = (Comanda*)malloc(sizeof(Comanda));
		nou->timp_livrare = c->timp_livrare;
		nou->cod_client = c->cod_client;
		nou->id_comanda = c->id_comanda;
		nou->nume_client = (char*)malloc(strlen(c->nume_client) + 1);
		strcpy(nou->nume_client, c->nume_client);
		nou->suma_plata = c->suma_plata;
		nou->numar_telefon = (char*)malloc(strlen(c->numar_telefon) + 1);
		strcpy(nou->numar_telefon, c->numar_telefon);
		nou->m = c->m;
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}


void displayQ(Heap& heap) {
	for (int i = 0; i < heap.heapSize; i++) {
		printf("Index:%d\n", i);
		displayComanda(heap.elements[i]);
	}
}

int nr(Queue& q,int timp) {
	int nr = 0;
	if (q.head) {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (temp->c->timp_livrare==timp) {
				nr++;
			}
			temp = temp->pNext;
		}
		nr++;
	}
	return nr;
}
Heap copiere(Queue& q,int timp) {
	Heap heap;
	initHeap(heap, nr(q, timp));
	if (q.head){
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (temp->c->timp_livrare == timp) {
				Enqueue(heap, temp->c);
			}
			temp = temp->pNext;
		}
		if (temp->c->timp_livrare == timp) {
			Enqueue(heap, temp->c);
		}
	}
	return heap;
}

Comanda* createComanda(Comanda* c) {
	Comanda* nou = (Comanda*)malloc(sizeof(Comanda));
	nou->timp_livrare = c->timp_livrare;
	nou->cod_client = c->cod_client;
	nou->id_comanda = c->id_comanda;
	nou->nume_client = (char*)malloc(strlen(c->nume_client) + 1);
	strcpy(nou->nume_client, c->nume_client);
	nou->suma_plata = c->suma_plata;
	nou->numar_telefon = (char*)malloc(strlen(c->numar_telefon) + 1);
	strcpy(nou->numar_telefon, c->numar_telefon);
	nou->m = c->m;
	return nou;
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

int cautare(int k, int* sir, int value) {
	int sw = 0;
	for (int i = 0; i < k; i++) {
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

int nrClienti(Queue& q) {
	int* sir = (int*)malloc(sizeof(int)*nrComenziTotale(q));
	int j = 0;
	if (q.head) {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (cautare(j, sir, temp->c->cod_client) == 0) {
				sir[j] = temp->c->cod_client;
				j++;
			}
			temp = temp->pNext;
		}
		if (cautare(j, sir, temp->c->cod_client) == 0) {
			sir[j] = temp->c->cod_client;
			j++;
		}
	}
	return j;
}

Comanda* creareComandaCuDouaAtribute(int cod, float suma) {
	Comanda* nou = (Comanda*)malloc(sizeof(Comanda));
	nou->cod_client = cod;
	nou->total_plata = suma;
	return nou;
}

Comanda** salvareComenzi(Queue& q) {
	int* sir = (int*)malloc(sizeof(int)*nrClienti(q));
	Comanda** vector = (Comanda**)malloc(sizeof(Comanda*)*nrClienti(q));
	int j = 0;
	int k = 0;
	if (q.head) {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (cautare(j, sir, temp->c->cod_client) == 0) {
				sir[j] = temp->c->cod_client;
				j++;
			}
			temp = temp->pNext;
		}
		if (cautare(j, sir, temp->c->cod_client) == 0) {
			sir[j] = temp->c->cod_client;
			j++;
		}
	}
	for (int i = 0; i < j; i++) {
		float sum = 0;
		if (q.head) {
			Node *temp = q.head;
			while (temp->pNext != NULL) {
				if (sir[i] == temp->c->cod_client)
					sum += temp->c->suma_plata;
				temp = temp->pNext;
			}
			if (cautare(j, sir, temp->c->cod_client) == 0) {
				sir[j] = temp->c->cod_client;
				j++;
			}
		}
		vector[k] = creareComandaCuDouaAtribute(sir[i], sum);
		k++;
	}
	return vector;
}

void deleteQ(Queue& q) {

	Node*ptr;
	Node*temp;
	int sw = 0;
	ptr = q.head;
	if (q.head == NULL)
		printf("Queue is empty\n");
	else
	{
		while (ptr != NULL)
		{
			ptr = ptr->pNext;
			Node *temp = q.head;
			q.head = q.head->pNext;
			free(temp);
		}
	}
	printf("Coada implementata prin lista simpla inlantuita a fost stearsa.\n");
}

void main() {
	Comanda* c = NULL;
	Node* stack = NULL;
	/*Node* list = NULL;*/
	Queue queue;
	FILE* file = fopen("file.txt", "r");
	if (file) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, file)) {
			c = (Comanda*)malloc(sizeof(Comanda));
			token = strtok(buffer, sep);
			c->timp_livrare = atoi(token);
			token = strtok(NULL, sep);
			c->cod_client = atoi(token);
			token = strtok(NULL, sep);
			c->id_comanda = atoi(token);
			token = strtok(NULL, sep);
			c->nume_client = (char*)malloc(strlen(token) + 1);
			strcpy(c->nume_client, token);
			token = strtok(NULL, sep);
			c->suma_plata = atof(token);
			token = strtok(NULL, sep);
			c->numar_telefon = (char*)malloc(strlen(token) + 1);
			strcpy(c->numar_telefon, token);
			token = strtok(NULL, sep);
			c->m = convertToMetodaDePlata(token);
			push(queue, c, c->id_comanda);
		}
		fclose(file);
	}
	
	display(queue);
	printf("----------\n");
	Comanda** vector = (Comanda**)malloc(sizeof(Comanda*)*nrComenzi(queue, 1));
	vector = determinareComenzi(queue, 1);
	for (int i = 0; i < nrComenzi(queue, 1); i++) {
		displayComanda(vector[i]);
	}
	printf("-----------\n");
	Heap h;
	h = copiere(queue, 1);
	displayQ(h);
	printf("----------------\n");
	Comanda*p = NULL;
	p = extragereComanda(h, 1);
	displayQ(h);
	printf("\nComanda extrasa din structura este:\n\n");
	displayComanda(p);
	printf("------------\n");
	Comanda** vec = (Comanda**)malloc(sizeof(Comanda*)*nrClienti(queue));
	vec = salvareComenzi(queue);
	for (int i = 0; i < nrClienti(queue); i++) {
		printf("Cod client:%d\nTotal plata:%.2f\n\n", vec[i]->cod_client,vec[i]->total_plata);
	}
	stergereComenzi(queue, 2);
	printf("-----------\n");
	display(queue);
	for (int i = 0; i < nrComenzi(queue, 1); i++) {
		free(vector[i]->nume_client);
		free(vector[i]->numar_telefon);
	}
	free(vector);
	vector = NULL;
	printf("Primul vector implementat a fost sters.\n");
	free(vec);
	vec = NULL;
	printf("Al doilea vector implementat a fost sters.\n");
	deleteQ(queue);
}


