#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300
#define DIM 100

struct Programare {
	char* cod;
	int zi;
	int luna;
	int an;
	int ora;
	char* nume_solicitant;
	int varsta_solicitant;
	char* localitate;
	char* nume_functionar;
	int numar;
};

struct Nod {
	Programare* info;
	Nod* next;
	Nod* prev;
};

void afisareProgramare(Programare* p) {
	printf("Cod:%s\nZi:%d\nLuna:%d\nAn:%d\nOra:%d\nNume solicitant:%s\nVarsta solicitant:%d\nLocalitate:%s\nNume functionar:%s\n\n",
		p->cod, p->zi, p->luna, p->an, p->ora,p->nume_solicitant, p->varsta_solicitant,p->localitate,p->nume_functionar);
}

void adaugareNodInLista(Nod** cap, Programare* p) {
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

void push(Nod** head_ref, Programare* p)
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
		afisareProgramare(node->info);
		last = node;
		node = node->next;
	}
}

int nrProgramari(Nod* node, int luna) {
	Nod *last;
	int nr = 0;
	while (node != NULL)
	{
		if (node->info->luna==luna) {
			nr++;
		}
		last = node;
		node = node->next;
	}
	return nr;
}

Programare** determinareProgramari(Nod* node, int luna) {
	Nod *last;
	Programare** vector = (Programare**)malloc(sizeof(Programare*)*nrProgramari(node, luna));
	int j = 0;
	while (node != NULL)
	{
		if (node->info->luna == luna) {
			vector[j] = node->info;
			j++;
		}
		last = node;
		node = node->next;
	}
	return vector;
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

int pozitieHTable(Programare* p, int size) {

	return p->luna % size;
}

void inserareHTable(HashTable* h, Programare* p) {
	int k;
	k = pozitieHTable(p, h->size);
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

HashTable* inserareInHT(Nod* node, HashTable* h) {
	Nod *last;
	initHashTable(h, DIM);
	while (node != NULL)
	{
		inserareHTable(h, node->info);
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
					afisareProgramare(temp->info);
					temp = temp->next;
				}
			}
		}
	}
}

int cautare(int k, int* s, int luna) {
	int sw = 0;
	for (int i = 0; i < k; i++) {
		if (s[i]==luna) {
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

int number(Nod* node) {
	Nod *last;
	int nr = 0;
	while (node != NULL)
	{
		if (node->info->an == 2021) {
			nr++;
		}
		last = node;
		node = node->next;
	}
	return nr;
}


int nrLuni(Nod* node) {
	int* arr = (int*)malloc(sizeof(int)*number(node));
	int j = 0;
	int nr = 0;
	Nod *last;
	while (node != NULL)
	{
		if (node->info->an == 2021) {
			if (cautare(j, arr, node->info->luna) == 0) {
				arr[j] = node->info->luna;
				j++;
				nr++;
			}
		}
		last = node;
		node = node->next;
	}
	return nr;
}
Programare* createProgramare(int luna,int numar) {
	Programare* nou = (Programare*)malloc(sizeof(Programare));
	nou->luna = luna;
	nou->numar = numar;
	return nou;
}

Programare** nrMaximLunar(Nod* node) {
	int* arr = (int*)malloc(sizeof(int)*nrLuni(node));
	int j = 0;
	Programare** vector = (Programare**)malloc(sizeof(Programare*));
	int k = 0;
	Nod *temp = node;
	Nod *last;
	while (temp != NULL)
	{
		if (temp->info->an == 2021) {
			if (cautare(j, arr, temp->info->luna) == 0) {
				arr[j] = temp->info->luna;
				j++;
			}
		}
		last = temp;
		temp = temp->next;
	}
	int maxim;
	int m = 0;
	int l = 0;
	for (int i = 0; i < j; i++) {
		Nod *temp = node;
		Nod *last;
		maxim = 0;
		int nr = 0;
		while (temp != NULL)
		{
			if (temp->info->an == 2021) {
				if (arr[i] == temp->info->luna) {
					nr++;
				}
			}
			last = temp;
			temp = temp->next;
		}
		if (nr > maxim) {
			maxim = nr;	
		}
		if (maxim > m) {
			m = maxim;
			l = arr[i];
		}
	}
	vector[k] = createProgramare(l, m);
	k++;
	return vector;
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
	Programare* p = NULL;
	Nod* cap = NULL;
	FILE* f = fopen("file.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			p = (Programare*)malloc(sizeof(Programare));
			token = strtok(buffer, sep);
			p->cod = (char*)malloc(strlen(token) + 1);
			strcpy(p->cod, token);
			token = strtok(NULL, sep);
			p->zi = atoi(token);
			token = strtok(NULL, sep);
			p->luna = atoi(token);
			token = strtok(NULL, sep);
			p->an = atoi(token);
			token = strtok(NULL, sep);
			p->ora = atoi(token);
			token = strtok(NULL, sep);
			p->nume_solicitant = (char*)malloc(strlen(token) + 1);
			strcpy(p->nume_solicitant, token);
			token = strtok(NULL, sep);
			p->varsta_solicitant = atoi(token);
			token = strtok(NULL, sep);
			p->localitate = (char*)malloc(strlen(token) + 1);
			strcpy(p->localitate, token);
			token = strtok(NULL, sep);
			p->nume_functionar = (char*)malloc(strlen(token) + 1);
			strcpy(p->nume_functionar, token);
			push(&cap, p);
		}
		fclose(f);
	}
	//ex1
	parcurgereListaDubla(cap);
	//ex2
	printf("---------\n");
	Programare** vector = (Programare**)malloc(sizeof(Programare*)*nrProgramari(cap, 4));
	vector = determinareProgramari(cap, 4);
	for (int i = 0; i < nrProgramari(cap, 4); i++) {
		afisareProgramare(vector[i]);
	}
	//ex3
	printf("---------\n");
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	inserareInHT(cap,h);
	displayH(h);
	//ex4
	printf("---------\n");
	Programare** vec = (Programare**)malloc(sizeof(Programare*));
	vec = nrMaximLunar(cap);
	printf("Luna:%d\nNumarul maxim lunar:%d\n\n", vec[0]->luna,vec[0]->numar);
	//ex5
	printf("---------\n");
	free(vector);
	vector = NULL;
	printf("Primul vector a fost sters.\n");
	free(vec);
	vec = NULL;
	printf("Al doilea vector a fost sters.\n");
	stergereListaDubla(cap);
	stergereHashTable(&h);
}