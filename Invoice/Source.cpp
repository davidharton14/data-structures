#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM 100
#define LINESIZE 300

struct Invoice {
	int nr;
	char* customer;
	char* provider;
	char* data;
	float payment;
};

Invoice* createInvoice(int nr, char* customer, char* provider, char* data, float payment) {
	Invoice* i = (Invoice*)malloc(sizeof(Invoice));
	i->nr = nr;
	i->customer = (char*)malloc(strlen(customer) + 1);
	strcpy(i->customer, customer);
	i->provider = (char*)malloc(strlen(provider) + 1);
	strcpy(i->provider, provider);
	i->data = (char*)malloc(strlen(data) + 1);
	strcpy(i->data, data);
	i->payment = payment;
	return i;
}
void displayInvoice(Invoice i) {
	printf("Nr:%d\nCustomer:%s\nProvider:%s\nData:%s\nPayment:%.2f\n\n", i.nr, i.customer, i.provider, i.data, i.payment);
}


struct HashTable {
	unsigned int size;
	Invoice** array;
};

HashTable init(int size)
{
	HashTable ht;
	ht.size = size;
	ht.array = (Invoice**)malloc(sizeof(Invoice*)*ht.size);
	for (int i = 0; i < ht.size; i++) {
		ht.array[i] = NULL;
	}
	return ht;
}

int hashFunction(HashTable ht,Invoice* i) {
	return i->nr % ht.size;
}


int nr = 0;
int j = 0;
int* numbers = (int*)malloc(sizeof(int)*5);
int number = 0;
void inserareInvoice(HashTable h, Invoice *i) {
	if (h.size > 0) {
		int pozitie = hashFunction(h, i);
		if (h.array[pozitie] != NULL) {
			//coliziune
			nr++;
			numbers[j] = h.array[pozitie]->nr;
			/*printf("%d\n", numbers[j]);*/
			j++;
			number = h.array[pozitie]->nr;
			int index = (pozitie + 1) % h.size;
			while (h.array[index] != NULL && index != pozitie) {
				index = (index + 1) % h.size;
			}
			if (index == pozitie) {
				/*return -1;*/
			}
			else {
				h.array[index] = i;
				/*return index;*/
			}

		}
		else {
			h.array[pozitie] = i;
			/*return pozitie;*/
		}
	}
	else {
		/*return -2;*/
	}
}

void afisareTabela(HashTable h) {
	for (int i = 0; i < h.size; i++) {
		if (h.array[i]) {
			displayInvoice(*h.array[i]);
		}
	}
}
void deleteElements(HashTable h,const char* nume) {
	for (int i = 0; i < h.size; i++) {
		if (h.array[i]) {
			if (strcmp(h.array[i]->provider, nume) == 0) {
				h.array[i] = NULL;
			}
		}
	}
}

struct Node {
	Invoice info;
	Node* next;
};

Node* pushStack(Node* head, Invoice i) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou = (Node*)malloc(sizeof(Node));
	nou->info = i;
	nou->next = head;
	return nou;
}
Node* parcurgereStack(HashTable h, const char* nume) {
	Node* stack = NULL;
	for (int i = 0; i < h.size; i++) {
		if (h.array[i]) {
			if (strcmp(h.array[i]->provider,nume)==0) {
				stack = pushStack(stack, *h.array[i]);
			}
		}
	}
	return stack;
}

void displayStack(HashTable h, const char* nume) {
	Node* temp = parcurgereStack(h, nume);
	while (temp) {
		displayInvoice(temp->info);
		temp = temp->next;
	}
	/*free(temp);*/
}
void deleteH(HashTable h) {
	for (int i = 0; i < h.size; i++) {
		if (h.array[i]) {
			free(h.array[i]->customer);
			free(h.array[i]->provider);
			free(h.array[i]->data);
			free(h.array[i]);
		}
	}
}
void deleteStack(HashTable h, const char* nume) {
	Node* temp = parcurgereStack(h, nume);
	while (temp) {
		free(temp->info.customer);
		free(temp->info.provider);
		free(temp->info.data);
		temp = temp->next;
	}
	free(temp);
}
void main() {
	Invoice* i = NULL;
	FILE*f = fopen("invoices.txt", "r");
	HashTable h=init(8);
	if (f) {
		char* token, buffer[LINESIZE], sep[] = ",";
		while (fgets(buffer, sizeof(buffer), f)) {
			i=(Invoice*)malloc(sizeof(Invoice));
			token = strtok(buffer, sep);
			i->nr = atoi(token);
			token = strtok(NULL, sep);
			i->customer = (char*)malloc(strlen(token) + 1);
			strcpy(i->customer, token);
			token = strtok(NULL, sep);
			i->provider = (char*)malloc(strlen(token) + 1);
			strcpy(i->provider, token);
			token = strtok(NULL, sep);
			i->data = (char*)malloc(strlen(token) + 1);
			strcpy(i->data, token);
			token = strtok(NULL, sep);
			i->payment = atof(token);
			inserareInvoice(h,i);
		}
		fclose(f);
	}
	/*afisareTabela(h);*/
	/*if (nr >= 2) {
		for (int i = 0; i < j; i++) {
			printf("%d - %d\n",i, numbers[i]);
		}
	}
	else {
		free(numbers);
		printf("0 - %d\n", number);
	}*/
	/*printf("\nElements were been deleted\n");
	deleteElements(h, "UPC");
	afisareTabela(h);*/
	/*deleteH(h);*/
	/*deleteStack(h, "UPC");*/
	/*displayStack(h, "UPC");*/
	afisareTabela(h);

}
