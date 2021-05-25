#include "stdio.h"
#include "stdlib.h"
#include<string.h>
#include<iostream>
using namespace std;
#define DIM_BUFFER 300

enum Modalitate {
	APEL_TELEFONIC,
	APLICATIE_MOBILA
};

struct Rezervare {
	char* denumireRestaurant;
	char* numeClient;
	int durataRezervarii;
	Modalitate m;
};

Modalitate convertToModalitate(const string& str)
{
	if (str == "APEL_TELEFONIC") return APEL_TELEFONIC;
	else if (str == "APLICATIE_MOBILA") return APLICATIE_MOBILA;
}

const char* convertToString(Modalitate m)
{
	
	if (m == 0) return "APEL_TELEFONIC";
	else if (m == 1) return "APLICATIE_MOBILA";
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
//Rezervare* createRezervare(Rezervare* r)
//{
//	Rezervare* retValue = NULL;
//	//1.space allocation for var
//	retValue = (Rezervare*)malloc(sizeof(Rezervare));
//	//2.initializing var attributes
//	retValue->denumireRestaurant = (char*)malloc(strlen(r->denumireRestaurant) + 1);
//	strcpy(retValue->denumireRestaurant, r->denumireRestaurant);
//	retValue->numeClient = (char*)malloc(strlen(r->numeClient) + 1);
//	strcpy(retValue->numeClient, r->numeClient);
//	retValue->durataRezervarii=r->durataRezervarii;
//	retValue->m = r->m;
//	return retValue;
//}
void printRezervare(Rezervare* r)
{
	
	printf("Denumire restaurant:%s\nNume client:%s\nDurata rezervarii:%d\nModalitate:%d\n\n",r->denumireRestaurant,r->numeClient,r->durataRezervarii,r->m);

}
Node * createNode(Rezervare* r)
{
	Node* node = NULL;
	node = (Node*)malloc(sizeof(Node));
	node->r = r;
	node->pNext = node->pPrev = NULL;
	return node;
}
void push(Node** head, Rezervare* r)
{
	Node* node = createNode(r);
	//1.conectati nodul de structura
	node->pNext = *head;
	//2.conectati structura la nod
	if (*head != NULL)
		(*head)->pPrev = node;
	*head = node;
}
Rezervare* pop(Node*& head)
{
	Rezervare* value = NULL;
	if (head != NULL)
	{
		value = head->r;
		Node* tmp = head;
		head = head->pNext;
		if (head != NULL)
			head->pPrev = NULL;
		free(tmp);
	}
	return value;
}

Rezervare* peek(Node* stack)
{
	Rezervare* r = NULL;
	if (stack != NULL)
		r = stack->r;
	return r;
}

Node* newNode(Rezervare* r)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->r = r;
	temp->pNext = NULL;

	return temp;
}

void push2(Queue& q, Rezervare* r,int p)
{
	Node *tmp, *qu;

	tmp = (Node *)malloc(sizeof(Node));
	tmp = newNode(r);
	/*Queue is empty or item to be added has priority more than first item*/
	if (q.head == NULL || p < q.head->r->durataRezervarii)
	{
		tmp->pNext = q.head;
		q.head = tmp;
	}
	else
	{
		qu = q.head;
		while (qu->pNext != NULL && qu->pNext->r->durataRezervarii <= p)
			qu = qu->pNext;
		tmp->pNext = qu->pNext;
		qu->pNext = tmp;
	}
}

void push3(Queue& q,Rezervare* r,int p)
{
	Node *tmp, *qu;
	tmp = (Node *)malloc(sizeof(Node));
	tmp = newNode(r);
	if (q.head == NULL || p < q.head->r->durataRezervarii)
	{
		tmp->pNext = q.head;
		q.head = tmp;
	}
	else
	{
		qu = q.head;
		while (qu->pNext != NULL && qu->pNext->r->durataRezervarii <= p)
			qu = qu->pNext;
		tmp->pNext = qu->pNext;
		qu->pNext = tmp;
	}
}

Rezervare* getQueue(Queue& queue)
{
	Rezervare* value = NULL;
	if (queue.head != NULL)
	{
		value = queue.head->r;
		Node* tmp = queue.head;
		queue.head = queue.head->pNext;
		if (queue.head != NULL)
			queue.head->pPrev = NULL;
		else
			queue.tail = NULL;
		free(tmp);
	}
	return value;
}


void display(Queue& q)
{
	if (q.head == NULL)
		printf("\nStack is Empty!!!\n");
	else {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			printRezervare(temp->r);
			temp = temp->pNext;
		}
		printRezervare(temp->r);
	}
}

Rezervare* peek(Node** head)
{
	return (*head)->r;
}

int isEmpty(Node** head)
{
	return (*head) == NULL;
}
void pop(Node** head)
{
	Node* temp = *head;
	(*head) = (*head)->pNext;
	free(temp);
}

//void display(Node*q) {
//	while (!isEmpty(&q))
//	{
//		printRezervare(peek(&q));
//		pop(&q);
//	}
//}
int nrRezervari(Queue& q)
{
	int nr = 0;
	Node *ptr;
	ptr = q.head;
	if (q.head == NULL)
		printf("Queue is empty\n");
	else
	{
		while (ptr != NULL)
		{
			printRezervare(ptr->r);
			nr++;
			ptr = ptr->pNext;
		}
	}
	return nr;
}

int volum(Queue& q) {
	return sizeof(Queue)*1;
}
Node* add(Node* head, Rezervare* data) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->r = data;
	nou->pNext = head;
	return nou;
}

Node* determinareRezervari(Queue& q) {
	Node*ptr;
	Node* node = NULL;
	ptr = q.head;
	if (q.head == NULL)
		printf("Queue is empty\n");
	else
	{
		while (ptr != NULL)
		{
			if(ptr->r->durataRezervarii>3)
			node = add(node, ptr->r);
			ptr = ptr->pNext;
		}
	}
	return node;
}

void generareRaport(Queue& q,const char* client) {
	Node*ptr;
	Node* node = NULL;
	ptr = q.head;
	if (q.head == NULL)
		printf("Queue is empty\n");
	else
	{
		while (ptr != NULL)
		{
			if (strcmp(ptr->r->numeClient, client) == 0) {
				FILE *fptr;
				fptr = fopen("raport.txt", "w");
				char sep[] = ", ";
				/*char sep2[] = "\n";*/
				if (fptr == NULL)
				{
					printf("Error!");
					exit(1);
				}
				else {
					fprintf(fptr, "%s", ptr->r->denumireRestaurant);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%s", ptr->r->numeClient);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%d", ptr->r->durataRezervarii);
					fprintf(fptr, "%s", sep);
					fprintf(fptr, "%s", convertToString(ptr->r->m));
					fprintf(fptr, "%s", sep);
				/*	fprintf(fptr, "%s", sep2);*/
				}
				fclose(fptr);
			}
			ptr = ptr->pNext;
		}
	}
}

//void display2(Queue& q)
//{
//	Node *temp;
//	temp = q.head;
//	if (q.head == NULL) {
//		printf("\n Queue is Empty!!!\n");
//		return;
//	}
//	while (temp->pNext != NULL)
//	{
//		printRezervare(temp->r);
//		temp = temp->pNext;
//	}
//	/*printRezervare(temp->r);*/
//}

void swap(Rezervare* a, Rezervare* b)
{
	Rezervare* temp = (Rezervare*)malloc(sizeof(Rezervare));
	temp->denumireRestaurant = (char*)malloc(strlen(a->denumireRestaurant) + 1);
	strcpy(temp->denumireRestaurant, a->denumireRestaurant);
	temp->numeClient = (char*)malloc(strlen(a->numeClient) + 1);
	strcpy(temp->numeClient, a->numeClient);
	temp->durataRezervarii = a->durataRezervarii;
	temp->m = a->m;

	a->denumireRestaurant = (char*)malloc(strlen(b->denumireRestaurant) + 1);
	strcpy(a->denumireRestaurant, b->denumireRestaurant);
	a->numeClient = (char*)malloc(strlen(b->numeClient) + 1);
	strcpy(a->numeClient, b->numeClient);
	a->durataRezervarii = b->durataRezervarii;
	a->m = b->m;


	b->denumireRestaurant = (char*)malloc(strlen(temp->denumireRestaurant) + 1);
	strcpy(b->denumireRestaurant, temp->denumireRestaurant);
	b->numeClient = (char*)malloc(strlen(temp->numeClient) + 1);
	strcpy(b->numeClient, temp->numeClient);
	b->durataRezervarii = temp->durataRezervarii;
	b->m = temp->m;

	free(temp);
	//temp = a;
	//a = b;
	//b = temp;
}



Rezervare* extract(Queue& q, const char* client) {
	
	Node*ptr;
	Node*ptr2;
	Node *temp;
	Node*head;
	Rezervare* re=NULL;
	Rezervare* rez = NULL;
	ptr = q.head;
	if (q.head == NULL)
		printf("Queue is empty\n");
	else
	{
		while (ptr != NULL)
		{
			if (strcmp(ptr->r->numeClient, client) == 0) {
				swap(q.head->r, ptr->r);
			}
			ptr = ptr->pNext;
		}
		Node *temp = q.head;
		re = q.head->r;
		q.head = q.head->pNext;
		free(temp);
	}
	ptr2 = q.head;
	Queue que;
	while (ptr2 != NULL)
	{
		rez = (Rezervare*)malloc(sizeof(Rezervare));
		rez->denumireRestaurant = (char*)malloc(strlen(ptr2->r->denumireRestaurant) + 1);
		strcpy(rez->denumireRestaurant, ptr2->r->denumireRestaurant);
		rez->numeClient = (char*)malloc(strlen(ptr2->r->numeClient) + 1);
		strcpy(rez->numeClient, ptr2->r->numeClient);
		rez->durataRezervarii = ptr2->r->durataRezervarii;
		rez->m = ptr2->r->m;
		push3(que, rez,rez->durataRezervarii);
		ptr2 = ptr2->pNext;
	}
	q = que;
	return re;
}



void printList(Node* n)
{
	Node* temp = n;
	while (temp != NULL) {
		printRezervare(temp->r);
		temp = temp->pNext;
	}
}

void main() {
	Rezervare* r = NULL;
	Node* stack = NULL;
	Node* list = NULL;
	Queue queue;
	FILE* f = fopen("rezervari.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			r=(Rezervare*)malloc(sizeof(Rezervare));
			token = strtok(buffer, sep);
			r->denumireRestaurant = (char*)malloc(strlen(token) + 1);
			strcpy(r->denumireRestaurant, token);
			token = strtok(NULL, sep);
			r->numeClient = (char*)malloc(strlen(token) + 1);
			strcpy(r->numeClient, token);
			token = strtok(NULL, sep);
			r->durataRezervarii = atoi(token);
			token = strtok(NULL, sep);
			r->m = convertToModalitate(token);
			/*put(queue, r);*/
			push(&stack, r);
			push2(queue, r, r->durataRezervarii);
		}
		fclose(f);
	}
	/*displayStack(stack);*/
	/*display(queue);*/

	//ex4
	/*printf("%d", volum(queue));*/

	//ex5
	/*list=determinareRezervari(queue);
	printList(list);*/

	//ex6
	/*generareRaport(queue, "Harton David");*/

	//ex7
	/*r = extract(queue, "Harton David");
	printRezervare(r);
	printf("\n\n\n");
	display(queue);*/
	/*push3(queue, queue.head->r);*/
}
