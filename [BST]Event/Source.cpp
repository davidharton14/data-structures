#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stack>
using namespace std;
#define DIM_BUFFER 300

struct Event {
	int idEvent;
	float ticketPrice;
	char* clientName;
	char eventDate[10];
	char* eventName;
	int durata;
	float totalCost;
};

struct NodArb {
	Event* e;
	NodArb* st;
	NodArb* dr;
};
struct nodLista {
	Event* info;
	nodLista* next;
};
Event* createEvent(Event* e) {
	Event* nou=(Event*)malloc(sizeof(Event));
	nou->idEvent = e->idEvent;
	nou->ticketPrice = e->ticketPrice;
	nou->clientName = (char*)malloc(strlen(e->clientName) + 1);
	strcpy(nou->clientName, e->clientName);
	strcpy(nou->eventDate, e->eventDate);
	nou->eventName = (char*)malloc(strlen(e->eventName) + 1);
	strcpy(nou->eventName, e->eventName);
	nou->durata = e->durata;
	return nou;
}

void displayEvent(Event* e) {
	printf("Id event:%d\nTicket price:%.2f\nClient name:%s\nEvent date:%s\nEvent name:%s\nDurata:%d\n\n",
		e->idEvent, e->ticketPrice, e->clientName, e->eventDate, e->eventName, e->durata);
}


NodArb* inserareArb(NodArb* rad, Event* e) {
	if (rad) {
		if (e->idEvent < rad->e->idEvent) {
			rad->st = inserareArb(rad->st, e);
		}
		else {
			rad->dr = inserareArb(rad->dr, e);
		}
		return rad;
	}
	else
	{

		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->e = e;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}

}

void displayArb(NodArb* rad) {
	if (rad) {
		displayEvent(rad->e);
		displayArb(rad->st);
		displayArb(rad->dr);
	}
}

int nrEvents(NodArb* root, const char* eventDate) {
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
			if (strcmp(curr->e->eventDate,eventDate)==0) {
				nr++;
			}
			curr = curr->dr;
		}
	}
	return nr;
}

Event** determinareEvents(NodArb* root, const char* eventDate) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	Event** vector = (Event**)malloc(sizeof(Event*)*nrEvents(root, eventDate));
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
			if (strcmp(curr->e->eventDate, eventDate) == 0) {
				vector[j] = createEvent(curr->e);
				j++;
			}
			curr = curr->dr;
		}
	}
	return vector;
}

int cautare(int k, char** sir, const char*string) {
	int sw = 0;
	for (int i = 0; i < k; i++) {
		if (strcmp(sir[i],string)==0) {
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

int nrTotalEvents(NodArb* root) {
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
	char** sir = (char**)malloc(sizeof(char*)*nrTotalEvents(root));
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
			if (cautare(j, sir, curr->e->clientName) == 0) {
				sir[j] = curr->e->clientName;
				j++;
			}
			curr = curr->dr;
		}
	}
	return j;
}

Event* createEventt(char* clientName, float sum) {
	Event* nou = (Event*)malloc(sizeof(Event));
	nou->clientName = (char*)malloc(strlen(clientName) + 1);
	strcpy(nou->clientName, clientName);
	nou->totalCost = sum;
	return nou;
}

Event** salvareEvents(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	char** sir = (char**)malloc(sizeof(char*)*nrClienti(root));
	Event** vector = (Event**)malloc(sizeof(Event*)*nrClienti(root));
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
			if (cautare(j, sir, curr->e->clientName) == 0) {
				sir[j] = curr->e->clientName;
				j++;
			}
			curr = curr->dr;
		}
	}
	for (int i = 0; i < j; i++) {
		NodArb* t = root;
		float sum = 0;
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
				if (strcmp(sir[i],t->e->clientName)==0)
					sum += t->e->ticketPrice;
				t = t->dr;
			}
		}
		vector[k] = createEventt(sir[i], sum);
		k++;
	}
	return vector;
}

void displayTree(NodArb* root) {
	if (root) {
		displayTree(root->st);
		displayEvent(root->e);
		displayTree(root->dr);
	}
}
void setChild(NodArb* node, bool toLeft, NodArb* child) {
	if (toLeft) {
		node->st = child;
	}
	else {
		node->dr = child;
	}
}

NodArb* splitTree(NodArb* root, int k) {
	NodArb* root2 = NULL;
	NodArb* parent1 = NULL;
	NodArb* parent2 = NULL;
	bool toLeft = root != NULL && k <= root->e->durata;

	while (root != NULL) {
		while (root != NULL && (k <= root->e->durata) == toLeft) {
			parent1 = root;
			root = toLeft ? root->st : root->dr;
		}
		setChild(parent1, toLeft, NULL); 
		toLeft = !toLeft; 
		if (root2 == NULL) {
			root2 = root; 
		}
		else if (parent2 != NULL) {
			setChild(parent2, toLeft, root); 
		}
		parent2 = parent1;
		parent1 = NULL;
	}
	return root2;
}

void _deleteTree(NodArb* node)
{
	if (node->st)
	{
		_deleteTree(node->st);
		free(node->st);
	}
	if (node->dr)
	{
		_deleteTree(node->dr);
		free(node->dr);
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


void main() {
	Event* e=NULL;
	NodArb* rad = NULL;
	FILE* f = fopen("file.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			e = (Event*)malloc(sizeof(Event));
			token = strtok(buffer, sep);
			e->idEvent = atoi(token);
			token = strtok(NULL, sep);
			e->ticketPrice = atof(token);
			token = strtok(NULL, sep);
			e->clientName = (char*)malloc(strlen(token) + 1);
			strcpy(e->clientName, token);
			token = strtok(NULL, sep);
			strcpy(e->eventDate, token);
			token = strtok(NULL, sep);
			e->eventName = (char*)malloc(strlen(token) + 1);
			strcpy(e->eventName, token);
			token = strtok(NULL, sep);
			e->durata = atoi(token);
			rad = inserareArb(rad, e);
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu a fost deschis");
	}
	//ex1
	displayArb(rad);
	//ex2
	printf("\n\n");
	Event** vector = (Event**)malloc(sizeof(Event*)*nrEvents(rad, "25.06.2025"));
	vector = determinareEvents(rad, "25.06.2025");
	for (int i = 0; i < nrEvents(rad, "25.06.2025"); i++) {
		displayEvent(vector[i]);
	}
	//ex3
	printf("\n\n");
	Event** vec = (Event**)malloc(sizeof(Event*)*nrClienti(rad));
	vec = salvareEvents(rad);
	printf("The size of array is:%d\n\n", nrClienti(rad));
	for (int i = 0; i < nrClienti(rad); i++) {
		printf("Client name:%s\nTotal cost:%.2f\n\n", vec[i]->clientName, vec[i]->totalCost);
	}
	//ex4
	printf("\n\n");
	NodArb* node = NULL;
	node = splitTree(rad, 100);
	printf("The first complementary BST is:\n\n");
	displayArb(rad);
	printf("The second complementary BST is:\n\n");
	displayArb(node);
	//ex5
	deleteTree(&rad);
	printf("The first complementary BST has been deleted\n");
	deleteTree(&node);
	printf("The second complementary BST has been deleted\n");
	free(vector);
	printf("The first array has been deleted");
	printf("\n");
	free(vec);
	printf("The second array has been deleted");

}