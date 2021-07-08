#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define DIM_HT 200
#define DIM_BUFFER 200

struct Evaluation {
	char* examName;
	char* studentName;
	int semester;
	float finalGrade;
	int noCredits;
	char* teacherName;
};

struct Node
{
	Evaluation* info;
	Node* next,*prev;
};

struct HashTable
{
	Node** elements;
	int dim;
};

Evaluation* createEvaluation(Evaluation* e) {
	Evaluation* newNode = (Evaluation*)malloc(sizeof(Evaluation));
	newNode->examName = (char*)malloc(strlen(e->examName) + 1);
	strcpy(newNode->examName, e->examName);
	newNode->studentName = (char*)malloc(strlen(e->studentName) + 1);
	strcpy(newNode->studentName, e->studentName);
	newNode->semester = e->semester;
	newNode->finalGrade = e->finalGrade;
	newNode->noCredits = e->noCredits;
	newNode->teacherName = (char*)malloc(strlen(e->teacherName) + 1);
	strcpy(newNode->teacherName, e->teacherName);
	return newNode;
}


int pHT(int dim, Evaluation* e) {

	int s = 0;
	for (int i = 0; i < strlen(e->examName); i++) {
		s += e->examName[i];
	}
	return s % dim;
}

void initializeHT(int dim, HashTable* ht)
{
	ht->elements = (Node**)malloc(sizeof(Node*) * dim);
	ht->dim = dim;
	for (int i = 0; i < dim; i++) {
		ht->elements[i] = NULL;
	}
}

void displayHT(HashTable* h) {
	if (h) {
		for (int i = 0; i < h->dim; i++)
		{
			if (h->elements[i]) {
				Node*temp = h->elements[i];
				while (temp)
				{
					printf("Examen name:%s\nStudent name:%s\nSemester:%d\nFinal grade:%.2f\nNo credits:%d\nTeacher name:%s\n\n",
						temp->info->examName, temp->info->studentName, temp->info->semester, 
						temp->info->finalGrade, temp->info->noCredits, temp->info->teacherName);
					temp = temp->next;
				}
			}
		}
	}
}


void insertToHT(Evaluation* e, HashTable* h) {
	int k;
	k = pHT(h->dim,e);
	Node*newNode = (Node*)malloc(sizeof(Node));
	newNode->info = e;
	newNode->next = NULL;
	if (h->elements[k]) {
		Node*temp = h->elements[k];
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	else {
		h->elements[k] = newNode;
	}
}

int noEvaluations(int noCredits, HashTable* h) {
	int number = 0;
	if (h) {
		for (int i = 0; i < h->dim; i++)
		{
			if (h->elements[i]) {
				Node*temp = h->elements[i];
				while (temp)
				{
					if (temp->info->noCredits==noCredits) {
						number++;
					}
					temp = temp->next;
				}
			}
		}
	}
	return number;
}

int numberEvaluationForSem1(HashTable* h) {
	int number = 0;
	if (h) {
		for (int i = 0; i < h->dim; i++)
		{
			if (h->elements[i]) {
				Node*temp = h->elements[i];
				while (temp)
				{
					if (temp->info->semester == 1) {
						number++;
					}
					temp = temp->next;
				}
			}
		}
	}
	return number;
}

int numberEvaluationForSem2(HashTable* h) {
	int number = 0;
	if (h) {
		for (int i = 0; i < h->dim; i++)
		{
			if (h->elements[i]) {
				Node*temp = h->elements[i];
				while (temp)
				{
					if (temp->info->semester == 2) {
						number++;
					}
					temp = temp->next;
				}
			}
		}
	}
	return number;
}

Evaluation** evaluationsGroupedBySem1(HashTable* h) {
	Evaluation** arr = (Evaluation**)malloc(sizeof(Evaluation*)*numberEvaluationForSem1(h));
	int j = 0;
	if (h) {
		for (int i = 0; i < h->dim; i++)
		{
			if (h->elements[i]) {
				Node*temp = h->elements[i];
				while (temp)
				{
					if (temp->info->semester == 1) {
						arr[j] = createEvaluation(temp->info);
						j++;
					}
					temp = temp->next;
				}
			}
		}
	}
	return arr;
}

Evaluation** evaluationsGroupedBySem2(HashTable* h) {
	Evaluation** arr = (Evaluation**)malloc(sizeof(Evaluation*)*numberEvaluationForSem2(h));
	int j = 0;
	if (h) {
		for (int i = 0; i < h->dim; i++)
		{
			if (h->elements[i]) {
				Node*temp = h->elements[i];
				while (temp)
				{
					if (temp->info->semester == 2) {
						arr[j] = createEvaluation(temp->info);
						j++;
					}
					temp = temp->next;
				}
			}
		}
	}
	return arr;
}

Evaluation** retrievingAllEvaluations(int noCredits, HashTable* h) {
	Evaluation** arr = (Evaluation**)malloc(sizeof(Evaluation*)*noEvaluations(noCredits,h));
	int index = 0;
	if (h!=NULL) {
		for (int i = 0; i < h->dim; i++)
		{
			if (h->elements[i]) {
				Node*temp = h->elements[i];
				while (temp!=NULL)
				{
					if(temp->info->noCredits == noCredits) {
						arr[index] = createEvaluation(temp->info);
						index++;
					}
					temp = temp->next;
				}
			}
		}
	}
	return arr;
}

void deleteHT(HashTable** h) {
	Node* tmp;
	for (int i = 0; i < (*h)->dim; i++)
	{
		if ((*h)->elements[i]) {
			Node*temp = (*h)->elements[i];
			while (temp)
			{
				tmp = temp;
				temp = temp->next;
				free(tmp->info);
				free(tmp);
			}
		}
	}
	printf("The hastable table structure was deleted.\n");
}

int cautareString(int* sir, int j, int nr) {
	int sw = 0;
	for (int i = 0; i < j; i++) {
		if (sir[i] == nr) {
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
	

void main() {
	FILE* file = fopen("file.txt", "r");
	HashTable* h = (HashTable*)malloc(sizeof(HashTable));
	Evaluation* e = NULL;
	initializeHT(DIM_HT,h);
	char buffer[DIM_BUFFER];
	if (file)
	{
		char sep[] = ",";
		char* token;
		while (fgets(buffer, DIM_BUFFER, file))
		{
			e = (Evaluation*)malloc(sizeof(Evaluation));
			token = strtok(buffer, sep);
			e->examName = (char*)malloc(strlen(token) + 1);
			strcpy(e->examName, token);
			token = strtok(NULL, sep);
			e->studentName = (char*)malloc(strlen(token) + 1);
			strcpy(e->studentName, token);
			token = strtok(NULL, sep);
			e->semester = atoi(token);
			token = strtok(NULL, sep);
			e->finalGrade = atof(token);
			token = strtok(NULL, sep);
			e->noCredits = atoi(token);
			token = strtok(NULL, sep);
			e->teacherName = (char*)malloc(strlen(token) + 1);
			strcpy(e->teacherName, token);
			insertToHT(e,h);
		}
	}
	printf("----------\n");
	displayHT(h);
	printf("----------\n");
	Evaluation** arr = (Evaluation**)malloc(sizeof(Evaluation)*noEvaluations(3,h));
	arr = retrievingAllEvaluations(3,h);
	for (int i = 0; i < noEvaluations(3, h); i++) {
		printf("Examen name:%s\nStudent name:%s\nSemester:%d\nFinal grade:%.2f\nNo credits:%d\nTeacher name:%s\n\n",
			arr[i]->examName, arr[i]->studentName, arr[i]->semester, arr[i]->finalGrade, 
			arr[i]->noCredits, arr[i]->teacherName);
	}

	
	printf("----------\n");
	printf("The evaluations for semester 1:\n");
	Evaluation** array1 = (Evaluation**)malloc(sizeof(Evaluation*)*numberEvaluationForSem1(h));
	array1 = evaluationsGroupedBySem1(h);
	for (int i = 0; i < numberEvaluationForSem1(h); i++) {
		printf("Examen name:%s\nStudent name:%s\nSemester:%d\nFinal grade:%.2f\nNo credits:%d\nTeacher name:%s\n\n",
			array1[i]->examName, array1[i]->studentName, array1[i]->semester, array1[i]->finalGrade,
			array1[i]->noCredits, array1[i]->teacherName);
	}
	printf("The evaluations for semester 2:\n");
	Evaluation** array2 = (Evaluation**)malloc(sizeof(Evaluation*)*numberEvaluationForSem2(h));
	array2 = evaluationsGroupedBySem2(h);
	for (int i = 0; i < numberEvaluationForSem2(h); i++) {
		printf("Examen name:%s\nStudent name:%s\nSemester:%d\nFinal grade:%.2f\nNo credits:%d\nTeacher name:%s\n\n",
			array2[i]->examName, array2[i]->studentName, array2[i]->semester, array2[i]->finalGrade,
			array2[i]->noCredits, array2[i]->teacherName);
	}
	deleteHT(&h);
	free(arr);
	printf("First array deleted.\n");
	free(array1);
	printf("Second array deleted.\n");
	free(array2);
	printf("Thrid array deleted.\n");
}



