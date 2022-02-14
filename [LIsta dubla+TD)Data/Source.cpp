#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct Numar {
	int data;
};

struct Nod {
	Numar* info;
	Nod* next;
	Nod* prev;
};

void afisareData(Numar* p) {
	printf("Data:%d\n", p->data);
		
}

void adaugareNodInLista(Nod** cap, Numar* p) {
	if (*cap == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = p;
		nou->next = nou->prev = nou;
		(*cap) = nou;
	}
	else {
		Nod* last = (*cap)->prev;
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = p;
		nou->next = (*cap);
		(*cap)->prev = nou;
		nou->prev = last;
		last->next = nou;
	}
}

void push(Nod** head_ref, Numar* p)
{
	Nod* new_node = (Nod*)malloc(sizeof(Nod));
	new_node->info = p;

	new_node->next = (*head_ref);
	new_node->prev = NULL;

	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;

	(*head_ref) = new_node;
}

void parcurgereListaDubla(Nod* node) {
	Nod* last;
	while (node != NULL) {
		afisareData(node->info);
		last = node;
		node = node->next;
	}
}

struct HashTable
{
	Nod** slots;
	int size;
};

void initHashTable(HashTable* ht, int size)
{
	ht->slots = (Nod**)malloc(sizeof(Nod*) * size);
	ht->size = size;
	memset(ht->slots, NULL, sizeof(Nod*) * size);
}

int pozitieHTable(Numar* p, int size,int a,int b,int c) {
	int result = (a*pow(p->data, 2)) + (b*(p->data)) + c;
	printf("%d\n\n", result % size);
	return result % size;
}

void inserareHTable(HashTable* h, Numar* p,int a,int b,int c) {
	int k;
	k = pozitieHTable(p, h->size,a,b,c);
	Nod*newNode = (Nod*)malloc(sizeof(Nod));
	newNode->info = p;
	newNode->next = NULL;
	if (h->slots[k]) {
		Nod*temp = h->slots[k];
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	else {
		h->slots[k] = newNode;
	}
}

HashTable* inserareInHT(Nod* node, HashTable* h,int dim,int a, int b, int c) {
	Nod *last;
	initHashTable(h, dim);
	while (node != NULL)
	{
		inserareHTable(h, node->info,a,b,c);
		last = node;
		node = node->next;
	}
	return h;
}

void displayH(HashTable* h) {
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Nod*temp = h->slots[i];
				while (temp)
				{
					afisareData(temp->info);
					temp = temp->next;
				}
			}
		}
	}
}
int cautare(HashTable* h,int data) {
	int sw = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Nod*temp = h->slots[i];
				while (temp)
				{
					if (data == temp->info->data) {
						sw = 1;
					}
					temp = temp->next;
				}
			}
		}
	}
	if (sw) {
		return 1;
	}
	else {
		return 0;
	}
}
void stergereListaDubla(Nod* node) {

	Nod* temp = (Nod*)malloc(sizeof(Nod));
	while (node != NULL) {
		temp = node;
		node = node->next;
		free(temp);
	}
	printf("Lista dubla inlantuita a fost stearsa.\n");
}
void stergereHashTable(HashTable** h) {
	Nod* tmp;
	for (int i = 0; i < (*h)->size; i++)
	{
		if ((*h)->slots[i]) {
			Nod*temp = (*h)->slots[i];
			while (temp)
			{
				tmp = temp;
				temp = temp->next;
				free(tmp->info);
				free(tmp);
			}
		}
	}
	*h = NULL;
	printf("Tabela de dispersie a fost stearsa.\n");
}

void main() {
	Numar* p = NULL;
	Nod* cap = NULL;
	int m, a, b,c,data;

	printf("Dimensiunea tabelei de dispersie:");
	scanf("%d", &m);
	printf("a=");
	scanf("%d", &a);
	printf("b=");
	scanf("%d", &b);
	printf("c=");
	scanf("%d", &c);
	for (int i = 0; i < m; i++) {
		p = (Numar*)malloc(sizeof(Numar));
		scanf("%d", &data);
		p->data = data;
		push(&cap, p);
	}
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	inserareInHT(cap,h,m,a,b,c);
	displayH(h);
	int n;
	printf("Tasteaza numarul pe care vrei sa il cauti in tabela de dispersie:");
	scanf("%d", &n);
	int element=cautare(h, n);
	if (element) {
		printf("Numarul %d a fost gasit!\n", n);
	}
	else {
		printf("Numarul %d nu a fost gasit!\n", n);
	}
	stergereListaDubla(cap);
	stergereHashTable(&h);
}