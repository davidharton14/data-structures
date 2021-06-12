#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300

struct Factura {
	int nr;
	char* client;
	char* furnizor;
	char* data;
	int nrZileRamase;
	float plata;
};


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
	printf("Nr:%d\nClient:%s\nFurnizor:%s\nData:%s\nNr zile ramase:%d\nPlata:%.2f\n\n", f->nr, f->client, f->furnizor, f->data, f->nrZileRamase, f->plata);
}

struct Node
{
	Factura* r;
	Node* pNext;
	Node* pPrev;
};
struct Queue
{
	Node* head = NULL;
	Node* tail = NULL;
};

Node* newNode(Factura* r)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->r = r;
	temp->pNext = NULL;

	return temp;
}


void push2(Queue& q, Factura* r, int p)
{
	Node *tmp, *qu;
	tmp = (Node *)malloc(sizeof(Node));
	tmp = newNode(r);
	/*Queue is empty or item to be added has priority more than first item*/
	if (q.head == NULL || p < q.head->r->nr)
	{
		tmp->pNext = q.head;
		q.head = tmp;
	}
	else
	{
		qu = q.head;
		while (qu->pNext != NULL && qu->pNext->r->nr <= p)
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
			displayFactura(temp->r);
			temp = temp->pNext;
		}
		displayFactura(temp->r);
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



void stergereFacturi(Queue& q, const char* client) {

	Node*ptr;
	Node*ptr2;
	Node*ptr3= q.head;
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
				if (strcmp(ptr->r->client, client) == 0) {
					swap(q.head->r, ptr->r);
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
	Factura* f = NULL;
	while (ptr2 != NULL)
	{
		/*f = (Factura*)malloc(sizeof(Factura));
		f->nr = ptr2->r->nr;
		f->client = (char*)malloc(strlen(ptr2->r->client) + 1);
		strcpy(f->client, ptr2->r->client);
		f->furnizor = (char*)malloc(strlen(ptr2->r->furnizor) + 1);
		strcpy(f->furnizor, ptr2->r->furnizor);
		f->data = (char*)malloc(strlen(ptr2->r->data) + 1);
		strcpy(f->data, ptr2->r->data);
		f->nrZileRamase = ptr2->r->nrZileRamase;
		f->plata = ptr2->r->plata;*/
		push2(que, ptr2->r, ptr2->r->nr);
		ptr2 = ptr2->pNext;
	}
	q = que;
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

NodArb* insertElementsToArb(Queue& q, const char* client) {
	NodArb* nod = NULL;
	if (q.head == NULL)
		printf("\nQueue is empty!!!\n");
	else {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (strcmp(temp->r->client, client) == 0)
				nod = inserareArb(nod, temp->r);
			temp = temp->pNext;
		}
	}
	return nod;
}
void afisareArb(NodArb* rad) {
	if (rad) {
		displayFactura(rad->info);
		afisareArb(rad->right);
		afisareArb(rad->left);
	}
	else {
		printf("Binary tree is empty.");
	}
}

struct Node2 {
	Factura* data;
	Node2* next;
};

void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		displayFactura(temp->r);
		temp = temp->pNext;
	}
}

Node* add(Node* head, Factura* data) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->r = data;
	nou->pNext = head;
	return nou;
}


void printList(Node2* n)
{
	Node2* temp = n;
	while (temp != NULL) {
		displayFactura(temp->data);
		temp = temp->next;
	}
}

Node2* add2(Node2* head, Factura* data) {
	Node2* nou = (Node2*)malloc(sizeof(Node2));
	nou->data = data;
	nou->next = head;
	return nou;
}

bool addToList(NodArb*root, Node2** s, int target)
{
	if (root == NULL)
		return false;

	if (root->info->nr == target) {
		*s = add2(*s, root->info);
		return true;
	}
	if (addToList(root->left, s, target) ||
		addToList(root->right, s, target))
	{
		*s = add2(*s, root->info);
		return true;
	}
	return false;
}

void deleteList(Node** head_ref)
{

	Node* current = *head_ref;
	Node* next = NULL;

	while (current != NULL)
	{
		next = current->pNext;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void deleteList2(Node2** head_ref)
{

	Node2* current = *head_ref;
	Node2* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
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
		*node_ref = NULL;
	}
}

void main() {
	Factura* f = NULL;
	Node* stack = NULL;
	/*Node* list = NULL;*/
	Queue queue;
	FILE* file = fopen("facturi.txt", "r");
	if (file) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, file)) {
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
			push2(queue, f, f->nr);
		}
		fclose(file);
	}
	/*display(queue);*/
	//ex2
	//stergereFacturi(queue, "Harton Maria");
	/*printf("\n\n\n");*/

	//ex3
	/*NodArb* rad=insertElementsToArb(queue, "Harton Maria");
	afisareArb(rad);*/

	//ex5
	/*Node2* list2 = NULL;
	NodArb* rad = insertElementsToArb(queue, "Harton Maria");
	deleteTree(&rad);
	afisareArb(rad);*/
	/*addToList(rad, &list2, 6);
	deleteList2(&list2);*/
	//deleteQ(queue);
	//display(queue);
}

