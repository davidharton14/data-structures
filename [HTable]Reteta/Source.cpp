#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM 100
#define LINESIZE 300

struct Reteta {
	unsigned int nrReteta;
	unsigned int nrMedicamente;
	char** listaMedicamente;
	char* numeMedic;
	float valoareBruta;
	float procentCompensare;
};

struct Nod {
	Reteta info;
	Nod* next;
};

void displayReteta(Reteta r) {
	printf("Nr reteta:%d\nNr medicamente:%d\n",r.nrReteta,r.nrMedicamente);
	printf("Medicamente: ");
	for (int i = 0; i < r.nrMedicamente; i++) {
		printf("%s, ", r.listaMedicamente[i]);
	}
	printf("\n");
	printf("Nume medic:%s\nValoarea bruta:%.2f\nProcent compensare:%.2f%\n\n",r.numeMedic,r.valoareBruta,r.procentCompensare);
}

struct arrayitem
{
	struct Nod* head;
	struct Nod* tail;
};

struct arrayitem *array;
int size = 0;         
int max = 10;	     

int hashcode(int key)
{
	return (key % max);
}

struct node* get_element(struct node *list, int find_index);
void remove_element(int key);
void rehash();
void init_array();

int find(struct Nod* list, int key)
{
	int retval = 0;
	struct Nod* temp = list;
	while (temp != NULL)
	{
		if (temp->info.nrReteta == key)
		{
			return retval;
		}
		temp = temp->next;
		retval++;
	}
	return -1;

}

struct Nod* get_element(struct Nod* list, int find_index)
{
	int i = 0;
	struct Nod* temp = list;
	while (i != find_index)
	{
		temp = temp->next;
		i++;
	}
	return temp;
}
struct node* get_element(struct node *list, int find_index);

void remove_element(int key)
{
	int index = hashcode(key);
	struct Nod*list = (struct Nod*) array[index].head;

	if (list == NULL)
	{
		printf("This key does not exists\n");

	}
	else
	{
		int find_index = find(list, key);

		if (find_index == -1)
		{
			printf("This key does not exists\n");

		}
		else
		{
			struct Nod*temp = list;
			if (temp->info.nrReteta == key)
			{

				array[index].head = temp->next;
				printf("This key has been removed\n");
				return;
			}

			while (temp->next->info.nrReteta != key)
			{
				temp = temp->next;
			}

			if (array[index].tail == temp->next)
			{
				temp->next = NULL;
				array[index].tail = temp;

			}
			else
			{
				temp->next = temp->next->next;

			}

			printf("This key has been removed\n");

		}

	}

}


void insert(int key, Reteta r)
{
	float n = 0.0;
	int index = hashcode(key);
	struct Nod *list = (struct Nod*) array[index].head;

	struct Nod *item = (struct Nod*) malloc(sizeof(struct Nod));
	item->info.nrReteta = key;
	item->info = r;
	item->next = NULL;

	if (list == NULL)
	{
		array[index].head = item;
		array[index].tail = item;
		size++;

	}
	else
	{

		int find_index = find(list, key);
		if (find_index == -1)
		{
			array[index].tail->next = item;
			array[index].tail = item;
			size++;
		}
		else
		{
			struct Nod* element = get_element(list, find_index);
			element->info = r;
		}

	}
	n = (1.0 * size) / max;
	if (n >= 0.75)
	{
		printf("going to rehash\n");
		rehash();
	}

}
void rehash()
{
	struct arrayitem *temp = array;

	int i = 0, n = max;
	size = 0;
	max = 2 * max;
	array = (struct arrayitem*) malloc(max * sizeof(struct Nod));
	init_array();

	for (i = 0; i < n; i++)
	{
		struct Nod* list = (struct Nod*) temp[i].head;

		if (list == NULL)
		{
			continue;

		}
		else
		{
			while (list != NULL)
			{
				insert(list->info.nrReteta, list->info);
				list = list->next;
			}

		}
	}
	temp = NULL;
}

void display()
{
	
	for (int i = 0; i < max; i++)
	{
		struct Nod*temp = array[i].head;
			while (temp != NULL)
			{
				displayReteta(temp->info);
				temp = temp->next;
			}
	}
}

/* For initializing the Hash Table */
void init_array()
{
	int i = 0;
	for (i = 0; i < max; i++)
	{
		array[i].head = NULL;
		array[i].tail = NULL;
	}
}

/* Returns size of Hash Table */
int size_of_array()
{
	return size;
}

int prezentaMedicament(int nr, const char* medicament) {
	int sw = 0;
	for (int i = 0; i < max; i++)
	{
		struct Nod*temp = array[i].head;
		while (temp != NULL)
		{
			if (temp->info.nrReteta == nr) {
				for (int i = 0; i < temp->info.nrMedicamente; i++) {
					if (strcmp(temp->info.listaMedicamente[i], medicament) == 0) {
						sw = 1;
					}
				}
			}
			temp = temp->next;
		}
	}
	if (sw == 1) {
		return sw;
	}
	else
		return sw;
}

void calculareValoareNeta() {
	float valoareNeta=0;
	for (int i = 0; i < max; i++)
	{
		struct Nod*temp = array[i].head;
		while (temp != NULL)
		{
			displayReteta(temp->info);
			valoareNeta= temp->info.valoareBruta - (temp->info.procentCompensare*temp->info.valoareBruta);
			printf("Valoare neta:%.2f\n\n", valoareNeta);
			temp = temp->next;
		}
	}
}
int cautareString(char** sir, int j, const char* string) {
	int sw = 0;
	for (int i = 0; i < j; i++) {
		if (strcmp(sir[i], string) == 0) {
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
int nrRetete() {
	int nr = 0;
	for (int i = 0; i < max; i++)
	{
		struct Nod*temp = array[i].head;
		while (temp != NULL)
		{
			nr++;
				temp = temp->next;
		}
	}
	return nr;
}

void afisareRetete() {
	char** charsArr = (char**)malloc(sizeof(char*)*nrRetete());
	int j = 0, k;
	for (int i = 0; i < max; i++)
	{
		struct Nod*temp = array[i].head;
		while (temp != NULL)
		{
			if (cautareString(charsArr, j, temp->info.numeMedic) == 0) {
					charsArr[j] = temp->info.numeMedic;
					j++;
			}
			temp = temp->next;
		}
	}
	int nr = 0;
	for (int k = 0; k < j; k++) {
		nr = 0;
		for (int i = 0; i < max; i++)
		{
			struct Nod*temp = array[i].head;
			while (temp != NULL)
			{
				if (strcmp(charsArr[k], temp->info.numeMedic) == 0)
					nr++;
				temp = temp->next;
			}
		}
		printf("Nume medic:%s - numar retete:%d\n", charsArr[k], nr);
	}
	
}

void main() {
	int key, value, n;
	Reteta r;
	FILE*f = fopen("retete.txt", "r");
	array = (struct arrayitem*) malloc(max * sizeof(struct arrayitem*));
	init_array();
	if (f) {
		char* token, buffer[LINESIZE], sep[] = ",";
		while (fgets(buffer, sizeof(buffer), f)) {
			token = strtok(buffer, sep);
			r.nrReteta = atoi(token);
			token = strtok(NULL, sep);
			r.nrMedicamente = atoi(token);
			r.listaMedicamente = (char**)malloc(sizeof(char*)*r.nrMedicamente);
			for (int i = 0; i < r.nrMedicamente; i++) {
				token = strtok(NULL, sep);
				r.listaMedicamente[i] = token;
			}
			token = strtok(NULL, sep);
			r.numeMedic = (char*)malloc(strlen(token) + 1);
			strcpy(r.numeMedic, token);
			token = strtok(NULL, sep);
			r.valoareBruta = atof(token);
			token = strtok(NULL, sep);
			r.procentCompensare = atof(token);
			insert(r.nrReteta, r);
		}
		fclose(f);
	}

	/*remove_element(23);
	display();*/
	/*if (prezentaMedicament(23, "Faringo") == 1) {
		printf("Medicamentul a fost gasit");
	}
	else {
		printf("Medicamentul nu a fost gasit");
	}*/
	/*display();
	printf("\n\n");
	calculareValoareNeta();*/
	/*printf("%d", nrRetete());*/
	/*afisareRetete();*/
}