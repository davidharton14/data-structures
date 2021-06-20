#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300

struct Evaluation {
	int evaluationId;
	int noCredits;
	char* examName;
	int studentId;
	double grade;
	float medie;
};

void displayEvaluation(Evaluation* e) {
	printf("Evaluation id:%d\nNo credits:%d\nExam name:%s\nStudent id:%d\nGrade:%.2f\n\n",
		e->evaluationId, e->noCredits, e->examName, e->studentId, e->grade);
}

struct Node
{
	Evaluation* e;
	Node* pNext;
	Node* pPrev;
};
struct Queue
{
	Node* head = NULL;
	Node* tail = NULL;
};

Node* newNode(Evaluation* e)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->e = e;
	temp->pNext = NULL;

	return temp;
}


void push2(Queue& q, Evaluation* e, int p)
{
	Node *tmp, *qu;
	tmp = (Node *)malloc(sizeof(Node));
	tmp = newNode(e);
	if (q.head == NULL || p < q.head->e->evaluationId)
	{
		tmp->pNext = q.head;
		q.head = tmp;
	}
	else
	{
		qu = q.head;
		while (qu->pNext != NULL && qu->pNext->e->evaluationId <= p)
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
			displayEvaluation(temp->e);
			temp = temp->pNext;
		}
		displayEvaluation(temp->e);
	}
}

Evaluation* procesareEvaluare(Queue& q, int id) {
	Evaluation* nou = (Evaluation*)malloc(sizeof(Evaluation));
	if (q.head){
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (temp->e->evaluationId == id)
				nou = temp->e;
			temp = temp->pNext;
		}
	}
	return nou;
}

void schimbarePrioritate(Queue& q, int id) {
	if (q.head) {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (temp->e->evaluationId == id)
				temp->e->evaluationId = 100;
			temp = temp->pNext;
		}
		if (temp->e->evaluationId == id)
			temp->e->evaluationId = 100;
		Node*ptr = q.head;
		Queue que;
		Evaluation* e = NULL;
		while (ptr != NULL)
		{
			push2(que, ptr->e, ptr->e->evaluationId);
			ptr = ptr->pNext;
		}
		q = que;
	}
}

void swap(Evaluation* a, Evaluation* b)
{
	Evaluation* temp = (Evaluation*)malloc(sizeof(Evaluation));
	temp->evaluationId = a->evaluationId;
	temp->noCredits = a->noCredits;
	temp->examName = (char*)malloc(strlen(a->examName) + 1);
	strcpy(temp->examName, a->examName);
	temp->studentId = a->studentId;
	temp->grade = a->grade;
	
	a->evaluationId = b->evaluationId;
	a->noCredits = b->noCredits;
	a->examName = (char*)malloc(strlen(b->examName) + 1);
	strcpy(a->examName, b->examName);
	a->studentId = b->studentId;
	a->grade = b->grade;

	b->evaluationId = temp->evaluationId;
	b->noCredits = temp->noCredits;
	b->examName = (char*)malloc(strlen(temp->examName) + 1);
	strcpy(b->examName, temp->examName);
	b->studentId = temp->studentId;
	b->grade = temp->grade;
	free(temp);
	//temp = a;
	//a = b;
	//b = temp;
}

void stergereEvaluation(Queue& q, int id) {
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
			if (ptr->e->evaluationId==id) {
				swap(q.head->e, ptr->e);
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
	Evaluation* e = NULL;
	while (ptr2 != NULL)
	{
		push2(que, ptr2->e, ptr2->e->evaluationId);
		ptr2 = ptr2->pNext;
	}
	q = que;
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

int nrQ(Queue& q) {
	int nr = 0;
	if (q.head == NULL)
		printf("\nQueue is empty!!!\n");
	else {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			nr++;
			temp = temp->pNext;
		}
		nr++;
	}
	return nr;
}
Evaluation* createEvaluation(char* name, float medie) {
	Evaluation* nou = (Evaluation*)malloc(sizeof(Evaluation));
	nou->examName = (char*)malloc(strlen(name) + 1);
	strcpy(nou->examName, name);
	nou->medie = medie;
	return nou;
}

int nrElemente(Queue& q) {
	char** charsArr = (char**)malloc(sizeof(char*)*nrQ(q));
	int j = 0;
	if (q.head == NULL)
		printf("\nQueue is empty!!!\n");
	else {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (cautareString(charsArr, j, temp->e->examName) == 0) {
				charsArr[j] = temp->e->examName;
				j++;
			}
			temp = temp->pNext;
		}
	}
	free(charsArr);
	return j;
}
Evaluation** vector(Queue& q) {
	char** charsArr = (char**)malloc(sizeof(char*)*nrElemente(q));
	Evaluation** ev = (Evaluation**)malloc(sizeof(Evaluation*)*nrElemente(q));
	int j = 0;
	int k = 0;
	if (q.head == NULL)
		printf("\nQueue is empty!!!\n");
	else {
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (cautareString(charsArr, j, temp->e->examName) == 0) {
				charsArr[j] = temp->e->examName;
				j++;
			}
			temp = temp->pNext;
		}
	}
	for (int i = 0; i < j; i++) {
		int nr = 0;
		float sum = 0;
		Node *temp = q.head;
		while (temp->pNext != NULL) {
			if (strcmp(temp->e->examName,charsArr[i]) == 0) {
				nr++;
				sum += temp->e->grade;
			}
			temp = temp->pNext;
		}
		ev[k] = createEvaluation(charsArr[i], sum / nr);
		k++;
	}
	free(charsArr);
	return ev;
	free(ev);
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

void main() {
	Evaluation* f = NULL;
	Queue queue;
	FILE* file = fopen("evaluari.txt", "r");
	if (file) {
		char* buffer = (char*)malloc(DIM_BUFFER);
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, file)) {
			f = (Evaluation*)malloc(sizeof(Evaluation));
			token = strtok(buffer, sep);
			f->evaluationId = atoi(token);
			token = strtok(NULL, sep);
			f->noCredits = atoi(token);
			token = strtok(NULL, sep);
			f->examName = (char*)malloc(strlen(token) + 1);
			strcpy(f->examName, token);
			token = strtok(NULL, sep);
			f->studentId = atoi(token);
			token = strtok(NULL, sep);
			f->grade = atof(token);
			push2(queue, f, f->evaluationId);
		}
		fclose(file);
	}
	//ex1
	display(queue);
	//ex2
	printf("\n\n");
	Evaluation* ev = NULL;
	ev = procesareEvaluare(queue,74);
	displayEvaluation(ev);
	//ex3
	printf("\n\n");
	printf("before\n");
	display(queue);
	schimbarePrioritate(queue,74);
	printf("after\n");
	display(queue);
	//ex4
	printf("\n\n");
	printf("before\n");
	display(queue);
	stergereEvaluation(queue, 100);
	printf("after\n");
	display(queue);
	//ex5
	printf("\n\n");
	Evaluation** vec = (Evaluation**)malloc(sizeof(Evaluation*)*nrElemente(queue));
	vec = vector(queue);
	for (int i = 0; i < nrElemente(queue); i++) {
		printf("Disciplina:%s\nMedie:%.2f\n\n", vec[i]->examName, vec[i]->medie);
	}
	//ex6
	deleteQ(queue);
	free(vec);
	free(ev);
}

