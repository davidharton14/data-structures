#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stack>
using namespace std;
#define DIM_BUFFER 300

struct Evaluation {
	int evaluationId;
	int noCredits;
	char* examName;
	int studentId;
	double grade;
};

struct Nod {
	Evaluation* info;
	Nod* next;
	Nod* prev;
};

struct NodArb {
	Evaluation* info;
	NodArb* left;
	NodArb* right;
};

void afisareEvaluation(Evaluation* e) {
	printf("Evaluation id:%d\nNo credits:%d\nExam name:%s\nStudent id:%d\nGrade:%lf\n\n",e->evaluationId,e->noCredits,e->examName,e->studentId,e->grade);
}

bool isEmpty(Nod* cap) {
	return cap == NULL;
}

//adaugare in lista simpla circulara
void insertFirst(Nod** cap, Evaluation* e) {

	Nod*link = (Nod*)malloc(sizeof(Nod));
	link->info = e;
	if (isEmpty(*cap)) {
		*cap = link;
		(*cap)->next = *cap;
	}
	else {
		link->next = *cap;
		(*cap) = link;
	}
}

//afisare lista simpla circulara
void printList(Nod* cap) {

	Nod*ptr = cap;
	if (cap != NULL) {
		while (ptr->next != ptr) {
			afisareEvaluation(ptr->info);
			ptr = ptr->next;
		}
		afisareEvaluation(ptr->info);
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

int number(Nod* cap) {
	int nr = 0;
	Nod*ptr = cap;
	if (cap != NULL) {
		while (ptr->next != ptr) {
			nr++;
			ptr = ptr->next;
		}
		nr++;
	}
	return nr;
}

int nrExam(Nod* cap) {
	int nr = 0;
	char** charsArr = (char**)malloc(sizeof(char*)*number(cap));
	int j = 0;
	Nod*ptr = cap;
	if (cap != NULL) {
		while (ptr->next != ptr) {
			if (cautareString(charsArr, j, ptr->info->examName) == 0) {
				charsArr[j] = ptr->info->examName;
				j++;
				nr++;
			}
			ptr = ptr->next;
		}
		if (cautareString(charsArr, j, ptr->info->examName) == 0) {
			charsArr[j] = ptr->info->examName;
			j++;
			nr++;
		}
	}
	return nr;
}

int* numarTotalStudenti(Nod* cap) {
	int* arr = (int*)malloc(sizeof(int)*nrExam(cap));
	char** charsArr = (char**)malloc(sizeof(char*)*nrExam(cap));
	int j = 0;
	int k = 0;
	Nod*ptr = cap;
	if (cap != NULL) {
		while (ptr->next != ptr) {
			if (cautareString(charsArr, j, ptr->info->examName) == 0) {
				charsArr[j] = ptr->info->examName;
				j++;
			}
			ptr = ptr->next;
		}
		if (cautareString(charsArr, j, ptr->info->examName) == 0) {
			charsArr[j] = ptr->info->examName;
			j++;
		}
	}
	int l = 0;
	for (int i = 0; i < j; i++) {
		l = 0;
		Nod*ptr = cap;
		if (cap != NULL) {
			while (ptr->next != ptr) {
				if (strcmp(ptr->info->examName, charsArr[i]) == 0) {
					l++;
				}
				ptr = ptr->next;
			}
			if (strcmp(ptr->info->examName, charsArr[i]) == 0) {
				l++;
			}
		}
		arr[k] = l;
		printf("%s\n", charsArr[i]);
		k++;	
	}
	return arr;
}


NodArb* inserareArb(NodArb* rad, Evaluation* e) {
	if (rad) {
		if (e->evaluationId < rad->info->evaluationId) {
			rad->left = inserareArb(rad->left, e);
		}
		else
			rad->right = inserareArb(rad->right, e);
		return rad;
	}
	else {
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->info = e;
		nou->left = NULL;
		nou->right = NULL;
	}
}

NodArb* insertToTree(Nod* cap) {
	NodArb* rad = NULL;
	Nod*ptr = cap;
	if (cap != NULL) {
		while (ptr->next != ptr) {
			rad = inserareArb(rad, ptr->info);
			ptr = ptr->next;
		}
		rad = inserareArb(rad, ptr->info);
	}
	return rad;
}

void afisareArb(NodArb* rad) {
	if (rad) {
		afisareArb(rad->left);
		afisareEvaluation(rad->info);
		afisareArb(rad->right);
	}
}

Evaluation* createEvaluation(Evaluation* e)
{
	Evaluation* retValue = NULL;
	retValue = (Evaluation*)malloc(sizeof(Evaluation));
	retValue->evaluationId = e->evaluationId;
	retValue->examName = (char*)malloc(strlen(e->examName));
	strcpy(retValue->examName, e->examName);
	retValue->grade = e->grade;
	retValue->noCredits = e->noCredits;
	retValue->studentId = e->studentId;
	return retValue;
}

Evaluation** printChildrens(Nod* cap,NodArb* root, int* a, int* i) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	Evaluation** ev = (Evaluation**)malloc(sizeof(Evaluation*)*number(cap));
	int j = 0;
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->left;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (a[*i] == curr->info->evaluationId) {
				if (curr->left) {
					ev[j] = curr->left->info;
					j++;
				}
				if (curr->right) {
					ev[j]=curr->right->info;
					j++;
				}
				return ev;
			}
			curr = curr->right;
		}
	}
}

int nrChildrens(Nod* cap, NodArb* root, int* a, int* i) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	int j = 0;
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->left;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (a[*i] == curr->info->evaluationId) {
				if (curr->left) {
					j++;
				}
				if (curr->right) {
					j++;
				}
				return j;
			}
			curr = curr->right;
		}
	}
}
void printEvaluation(Evaluation** n,int k)
{
	for (int i = 0; i < k; i++) {
		afisareEvaluation(n[i]);
	}
}

void deleteNode(Nod** head, int id) {
	if (head == NULL)
		return;
	Nod*curr = *head, *prev;
	while (curr->info->studentId != id)
	{
		if (curr->next == *head)
		{
			break;
		}

		prev = curr;
		curr = curr->next;
	}
	if (curr->next == *head)
	{
		return;
	}
	if (curr == *head)
	{
		prev = *head;
		while (prev->next != *head)
			prev = prev->next;
		*head = curr->next;
		prev->next = *head;
		free(curr);
		deleteNode(head, id);

	}
	else if (curr->next == *head && curr == *head)
	{
		prev->next = *head;
		free(curr);
		deleteNode(head, id);
	}
	else
	{
		prev->next = curr->next;
		free(curr);
		deleteNode(head, id);

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
	}
}

void deleteLSC(Nod** head_ref) {
	if (*head_ref != NULL) {

		Nod*temp, *current;
		current = (*head_ref)->next;

		while (current != *head_ref) {
			temp = current->next;
			free(current);
			current = temp;
		}

		free(head_ref);
		head_ref = NULL;
	}
	printf("All nodes are deleted successfully.\n");
	
}

void main() {
	Evaluation* e=NULL;
	Nod* cap = NULL;
	FILE* f = fopen("examene.txt", "r");
	int* arr = (int*)malloc(sizeof(int) * 15);
	int k = 0;
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			e = (Evaluation*)malloc(sizeof(Evaluation));
			token = strtok(buffer, sep);
			e->evaluationId = atoi(token);
			token = strtok(NULL, sep);
			e->noCredits = atoi(token);
			token = strtok(NULL, sep);
			e->examName = (char*)malloc(strlen(token) + 1);
			strcpy(e->examName, token);
			token = strtok(NULL, sep);
			e->studentId = atoi(token);
			token = strtok(NULL, sep);
			e->grade = strtod(token, NULL);
			arr[k] = e->evaluationId;
			k++;
			insertFirst(&cap, e);
		}
		fclose(f);
	}
	//ex1
	printList(cap);
	//ex2
	int* array = (int*)malloc(sizeof(int)*nrExam(cap));
	array = numarTotalStudenti(cap);
	for (int i = 0; i < nrExam(cap); i++) {
		printf("%d ", array[i]);
	}
    //ex4
	printf("\n\n");
	NodArb* arb = NULL;
	arb = insertToTree(cap);
	afisareArb(arb);
	//ex5
	Evaluation** ev= NULL;
	printf("%d", number(cap));
	for (int i = 0; i < number(cap); i++) {
		ev = (Evaluation**)malloc(sizeof(Evaluation*)*number(cap));
		printf("Nodul:%d\n", arr[i]);
		ev = printChildrens(cap,arb, arr, &i);
		int nr = nrChildrens(cap, arb, arr, &i);
		if (nr!=0) {
			printf("\nLista de descendenti:\n\n");
			printEvaluation(ev,nr);
			printf("\n\n");
		}
		else {
			printf("NULL\n\n");
		}
	}
	//ex3
	//printf("\n\n");
	//deleteNode(cap, 62);
	//printList(cap);
	//ex6
	/*deleteLSC(&cap);*/
	deleteTree(&arb);
	free(array);
	free(arr);
}

