#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LINESIZE 300

struct Factura {
	int nr;
	char* client;
	char* furnizor;
	char* data;
	int nrZileRamase;
	float plata;
};

struct Heap {
	Factura** elements;
	int heapSize;
	int index;
};

void initHeap(Heap&, int);
void displayFactura(Factura*);
void ReheapUp(Heap, int, int);
void displayQ(Heap&);

//Factura* createFactura(int nr, char* client, char* furnizor, char* data, int nrZileRamase, float plata) {
//	Factura* f = (Factura*)malloc(sizeof(Factura));
//	f->nr = nr;
//	f->client = (char*)malloc(strlen(client) + 1);
//	strcpy(f->client, client);
//	f->furnizor = (char*)malloc(strlen(furnizor) + 1);
//	strcpy(f->furnizor, furnizor);
//	f->data = (char*)malloc(strlen(data) + 1);
//	strcpy(f->data, data);
//	f->nrZileRamase = nrZileRamase;
//	f->plata = plata;
//	return f;
//}

Factura* createFactura(Factura* fa) {
	Factura* f = (Factura*)malloc(sizeof(Factura));
	f->nr = fa->nr;
	f->client = (char*)malloc(strlen(fa->client) + 1);
	strcpy(f->client, fa->client);
	f->furnizor = (char*)malloc(strlen(fa->furnizor) + 1);
	strcpy(f->furnizor, fa->furnizor);
	f->data = (char*)malloc(strlen(fa->data) + 1);
	strcpy(f->data, fa->data);
	f->nrZileRamase = fa->nrZileRamase;
	f->plata = fa->plata;
	return f;
}


void displayFactura(Factura* f) {
	printf("Nr:%d\nClient:%s\nFurnizor:%s\nData:%s\nNr zile ramase:%d\nPlata:%.2f\n\n", f->nr, f->client, f->furnizor, f->data,f->nrZileRamase, f->plata);
}

void initHeap(Heap& heap, int size) {
	heap.elements = (Factura**)malloc(sizeof(Factura*)*size);
	heap.heapSize = size;
	heap.index = 0;
	memset(heap.elements, NULL, sizeof(Factura*)*size);
}

void Enqueue(Heap& heap, Factura* f) {
	if (heap.index < heap.heapSize) {
		Factura* nou = (Factura*)malloc(sizeof(Factura));
		nou = createFactura(f);
		heap.elements[heap.index] = nou;
		ReheapUp(heap, 0, heap.index);
		heap.index++;
		return;
	}
}

void ReheapUp(Heap heap, int first, int last)
{
	int parinte;
	Factura* temp = NULL;
	if (first < last)
	{
		parinte = (last - 1) / 2;
		if (heap.elements[parinte]->nrZileRamase <
			heap.elements[last]->nrZileRamase)
		{
			temp = heap.elements[parinte];
			heap.elements[parinte] = heap.elements[last];
			heap.elements[last] = temp;
			ReheapUp(heap, first, parinte);
		}
	}
}

void swap(Factura* a, Factura* b)
{
	Factura* temp = (Factura*)malloc(sizeof(Factura));
	temp->nr = a->nr;
	temp->client = (char*)malloc(strlen(a->client) + 1);
	strcpy(temp->client, a->client);
	temp->furnizor = (char*)malloc(strlen(a->furnizor) + 1);
	strcpy(temp->furnizor, a->furnizor);
	temp->data = (char*)malloc(strlen(a->data) + 1);
	strcpy(temp->data, a->data);
	temp->nrZileRamase = a->nrZileRamase;
	temp->plata = a->plata;

	a->client = (char*)malloc(strlen(b->client) + 1);
	strcpy(a->client, b->client);
	a->furnizor = (char*)malloc(strlen(b->furnizor) + 1);
	strcpy(a->furnizor, b->furnizor);
	a->data = (char*)malloc(strlen(b->data) + 1);
	strcpy(a->data, b->data);
	a->nrZileRamase = b->nrZileRamase;
	a->plata = b->plata;

	b->client = (char*)malloc(strlen(temp->client) + 1);
	strcpy(b->client, temp->client);
	b->furnizor = (char*)malloc(strlen(temp->furnizor) + 1);
	strcpy(b->furnizor, temp->furnizor);
	b->data = (char*)malloc(strlen(temp->data) + 1);
	strcpy(b->data, temp->data);
	b->nrZileRamase = temp->nrZileRamase;
	b->plata = temp->plata;

	free(temp);
	//temp = a;
	//a = b;
	//b = temp;
}

void displayQ(Heap& heap) {
	for (int i = 0; i < heap.heapSize; i++) {
		printf("Index:%d\n", i);
		displayFactura(heap.elements[i]);
	}
}


void stergereFacturi(Heap& heap, int nr) {
	for (int i = 0; i < heap.heapSize; i++) {
		if (heap.elements[i]->nrZileRamase < nr) {
			swap(heap.elements[i], heap.elements[heap.heapSize - 1]);
			heap.heapSize -= 1;
		}
		for (int j = 0; j < heap.heapSize; j++) {
			if (heap.elements[j]->nrZileRamase < nr) {
				swap(heap.elements[j], heap.elements[heap.heapSize - 1]);
				heap.heapSize -= 1;
			}
		}
	}
	for (int i = 0; i < heap.heapSize; i++)
	{
		ReheapUp(heap, 0, i);
	}
}

struct NodArb {
	Factura* info;
	NodArb* left;
	NodArb* right;
};

NodArb* inserareArb(NodArb* rad, Factura* p) {
	if (rad) {
		if (p->nr < rad->info->nr) {
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

NodArb* insertElementsToArb(Heap& heap, const char* client) {
	NodArb* nod = NULL;
	for (int i = 0; i < heap.heapSize; i++) {
		if(strcmp(heap.elements[i]->client,client)==0)
		nod = inserareArb(nod, heap.elements[i]);
	}
	return nod;
}
void afisareArb(NodArb* rad) {
	if (rad) {
		displayFactura(rad->info);
		afisareArb(rad->right);
		afisareArb(rad->left);
	}
}

struct Node {
	Factura* data;
	Node* next;
};

void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		displayFactura(temp->data);
		temp = temp->next;
	}
}

Node* add(Node* head, Factura* data) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->data = data;
	nou->next = head;
	return nou;
}

bool addToList(NodArb*root, Node** s, int target)
{
	if (root == NULL)
		return false;

	if (root->info->nr == target) {
		*s = add(*s, root->info);
		return true;
	}
	if (addToList(root->left, s, target) ||
		addToList(root->right, s, target))
	{
		*s = add(*s, root->info);
		return true;
	}
	return false;
}

void deleteHeap(Heap& heap) {
	for (int i = 0; i < heap.heapSize; i++) {
		free(heap.elements[i]->client);
		free(heap.elements[i]->furnizor);
		free(heap.elements[i]->data);
		free(heap.elements[i]);
		heap.heapSize -= 1;
	}
	printf("Heap structure is empty.");
}

void _deleteTree(NodArb* node)
{
	if (node->left)
	{
		_deleteTree(node->left);
		free(node->left);
	}
	if (node->right)
	{
		_deleteTree(node->right);
		free(node->right);
	}
}

void deleteTree(NodArb** node_ref)
{
	if (*node_ref)
	{
		_deleteTree(*node_ref);
		free(*node_ref);
	}
}

void deleteList(Node** head_ref)
{

	Node* current = *head_ref;
	Node* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void main() {
	Factura* f = NULL;
	Heap heap;
	initHeap(heap, 8);
	FILE*file = fopen("facturi.txt", "r");
	if (file) {
		char* token, buffer[LINESIZE], sep[] = ",";
		while (fgets(buffer, sizeof(buffer), file)) {
			f = (Factura*)malloc(sizeof(Factura));
			token = strtok(buffer, sep);
			f->nr = atoi(token);
			token = strtok(NULL, sep);
			f->client = (char*)malloc(strlen(token) + 1);
			strcpy(f->client, token);
			token = strtok(NULL, sep);
			f->furnizor = (char*)malloc(strlen(token) + 1);
			strcpy(f->furnizor, token);
			token = strtok(NULL, sep);
			f->data = (char*)malloc(strlen(token) + 1);
			strcpy(f->data, token);
			token = strtok(NULL, sep);
			f->nrZileRamase = atof(token);
			token = strtok(NULL, sep);
			f->plata = atof(token);
			Enqueue(heap, f);
		}
		fclose(file);
	}

	//ex2
	/*displayQ(heap);
	printf("\n\n\n");
	stergereFacturi(heap,10);
	displayQ(heap);*/

	//ex3
	/*NodArb* rad=insertElementsToArb(heap, "Harton Maria");*/
	/*afisareArb(rad);*/
	
	//ex4
	/*NodArb* rad = insertElementsToArb(heap, "Harton Maria");
	Node* list = NULL;
	addToList(rad, &list,3);
	printList(list);*/

	//ex5
	/*deleteHeap(heap);
	displayQ(heap);*/

	/*NodArb* rad = insertElementsToArb(heap, "Harton Maria");
	deleteTree(&rad);*/

	/*NodArb* rad = insertElementsToArb(heap, "Harton Maria");
	Node* list = NULL;
	addToList(rad, &list,3);
	deleteList(&list);
	printList(list);*/

}


