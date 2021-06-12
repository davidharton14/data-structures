#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM 100
#define SIZE_BUFFER 300


struct ContBancar
{
	char* nume_client;
	float sold;
	char* valuta_cont;
	int id_Client;
	int pin_Card;
	long cod_Card;
	int nivel_card;
	float soldTotal;
};

struct Node
{
	ContBancar* info;
	Node* pNext;
	Node* pPrev;
};
struct HashTable
{
	Node** slots;
	int size;
};

Node* createNode(ContBancar* c)
{
	Node* nou = NULL;
	nou = (Node*)malloc(sizeof(Node));
	nou->info = c;
	nou->pNext = NULL;
	nou->pPrev = NULL;
	return nou;
}

void displayContBancar(ContBancar * c) {
	printf("Numele:%s\nSoldul:%.2f\nValuta%s\nId Client:%d\nPinul de card:%d\nCod Card:%d\nNivel Card:%d\n\n",
		c->nume_client,c->sold,c->valuta_cont,c->id_Client,c->pin_Card,c->cod_Card,c->nivel_card);
}

void initHashTable(HashTable* ht, int size)
{
	ht->slots = (Node**)malloc(sizeof(Node*) * size);
	ht->size = size;
	memset(ht->slots, NULL, sizeof(Node*) * size);
}

int pozitieHTable(ContBancar* c, int size) {
	
	return strlen(c->nume_client) % size;
}

void inserareHTable(HashTable* h, ContBancar* c) {
	int k;
	k = pozitieHTable(c, h->size);
	Node*newNode = (Node*)malloc(sizeof(Node));
	newNode->info = c;
	newNode->pNext = NULL;
	if (h->slots[k]) {
		Node*temp = h->slots[k];
		while (temp->pNext)
		{
			temp = temp->pNext;
		}
		temp->pNext = newNode;
	}
	else {
		h->slots[k] = newNode;
	}
}

void displayH(HashTable* h) {
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					displayContBancar(temp->info);
					temp = temp->pNext;
				}
			}
		}
	}
}

ContBancar* createContBancar(ContBancar* c) {
	ContBancar* nou = (ContBancar*)malloc(sizeof(ContBancar));
	nou->nume_client = (char*)malloc(strlen(c->nume_client) + 1);
	strcpy(nou->nume_client, c->nume_client);
	nou->sold = c->sold;
	nou->valuta_cont = (char*)malloc(strlen(c->valuta_cont) + 1);
	strcpy(nou->valuta_cont, c->valuta_cont);
	nou->id_Client = c->id_Client;
	nou->pin_Card = c->pin_Card;
	nou->cod_Card = c->cod_Card;
	nou->nivel_card = c->nivel_card;
	return nou;
}

ContBancar* createContBancarr(char* nume,float soldTotal) {
	ContBancar* nou = (ContBancar*)malloc(sizeof(ContBancar));
	nou->nume_client = (char*)malloc(strlen(nume) + 1);
	strcpy(nou->nume_client, nume);
	nou->soldTotal = soldTotal;
	return nou;
}

int nrConturiBancare(HashTable* h, const char* valuta) {
	int nr = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (strcmp(temp->info->valuta_cont, valuta) == 0) {
						nr++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return nr;
}

ContBancar** determinareConturiBancare(HashTable* h,const char* valuta) {
	ContBancar** vector = (ContBancar**)malloc(sizeof(ContBancar)*nrConturiBancare(h,valuta));
	int j = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (strcmp(temp->info->valuta_cont, valuta) == 0) {
						vector[j] = createContBancar(temp->info);
						j++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return vector;
	free(vector);
}

int cautare(int k, char** s, const char* string) {
	int sw = 0;
	for (int i = 0; i < k; i++) {
		if (strcmp(s[i], string) == 0) {
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

int nrClienti(HashTable* h) {
	char** arr = (char**)malloc(sizeof(char*)*h->size);
	int j = 0;
	int nr = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (cautare(j, arr, temp->info->nume_client) == 0) {
						arr[j] = temp->info->nume_client;
						j++;
						nr++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	return nr;
	free(arr);
}

ContBancar** determinareSolduriBancare(HashTable* h) {
	ContBancar** vector = (ContBancar**)malloc(sizeof(ContBancar)*nrClienti(h));
	int l = 0;
	char** arr = (char**)malloc(sizeof(char*)*nrClienti(h));
	int j = 0;
	if (h) {
		for (int i = 0; i < h->size; i++)
		{
			if (h->slots[i]) {
				Node*temp = h->slots[i];
				while (temp)
				{
					if (cautare(j, arr, temp->info->nume_client) == 0) {
						arr[j] = temp->info->nume_client;
						j++;
					}
					temp = temp->pNext;
				}
			}
		}
	}
	int nr = j;
	for (int k = 0; k < nr; k++) {
		float value = 0;
		if (h) {
			for (int i = 0; i < h->size; i++)
			{
				if (h->slots[i]) {
					Node*temp = h->slots[i];
					while (temp)
					{
						if (strcmp(arr[k],temp->info->nume_client)==0) {
							value += temp->info->sold;	
						}
						temp = temp->pNext;
					}
				}
			}
		}
		vector[l] = createContBancarr(arr[k], value);
		l++;
	}
	return vector;
	free(vector);
	free(arr);
}

void deleteHashTable(HashTable** h) {
	Node* tmp;

	for (int i = 0; i < (*h)->size; i++)
	{
		if ((*h)->slots[i]) {
			Node*temp = (*h)->slots[i];
			while (temp)
			{
				tmp = temp;
				temp = temp->pNext;
				free(tmp->info);
				free(tmp);
			}
		}
	}
	*h = NULL;
}



void main() {
	FILE* pFile = fopen("fisier.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	ContBancar* c = NULL;
	initHashTable(h, DIM);
	if (pFile)
	{
		char* token, separators[] = ",\n";
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			c = (ContBancar*)malloc(sizeof(ContBancar));
			token = strtok(buffer, separators);
			c->nume_client = (char*)malloc(strlen(token) + 1);
			strcpy(c->nume_client, token);
			token = strtok(NULL, separators);
			c->sold = atof(token);
			token = strtok(NULL, separators);
			c->valuta_cont = (char*)malloc(strlen(token) + 1);
			strcpy(c->valuta_cont, token);
			token = strtok(NULL, separators);
			c->id_Client = atoi(token);
			token = strtok(NULL, separators);
			c->pin_Card = atoi(token);
			token = strtok(NULL, separators);
			c->cod_Card = atoi(token);
			token = strtok(NULL, separators);
			c->nivel_card = atoi(token);
			inserareHTable(h,c);
		}
		displayH(h);
	}
	
	printf("\n\n\n");
	ContBancar** vector = (ContBancar**)malloc(sizeof(ContBancar)*nrConturiBancare(h,"lei"));
	vector = determinareConturiBancare(h, "lei");
	for (int i = 0; i < nrConturiBancare(h, "lei"); i++) {
		displayContBancar(vector[i]);
	}
	printf("\n\n\n");
	ContBancar** vec = (ContBancar**)malloc(sizeof(ContBancar)*nrClienti(h));
	vec = determinareSolduriBancare(h);
	for (int i = 0; i < nrClienti(h); i++) {
		printf("Nume client:%s\n", vec[i]->nume_client);
		printf("Sold total:%.2f\n\n", vec[i]->soldTotal);
	}

	deleteHashTable(&h);
	free(vector);
	free(vec);
}

