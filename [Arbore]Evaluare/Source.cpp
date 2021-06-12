#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
#include <stack>
using namespace std;
#define DIM_BUFFER 300

struct Evaluare {
	unsigned int marca;
	char* numeAngajat;
	char* departament;
	unsigned int notaEvaluare;
	char* dataEvaluare;
};

struct NodArb {
	Evaluare e;
	NodArb* st;
	NodArb* dr;
};

void displayEvaluare(Evaluare e) {
	printf("Marca:%d\nNume angajat:%s\nDepartament:%s\nNota evaluare:%d\nData evaluare:%s\n\n", e.marca, e.numeAngajat, e.departament, e.notaEvaluare,e.dataEvaluare);
	
}

int inaltimeArbore(NodArb* rad) {
	if (rad) {
		int inaltimeST = inaltimeArbore(rad->st);
		int inaltimeDR = inaltimeArbore(rad->dr);
		return 1 + (inaltimeST > inaltimeDR ? inaltimeST : inaltimeDR);
	}
	else {
		return 0;
	}
}

int calculareGradEchilibru(NodArb* rad) {
	if (rad) {
		int inaltimeST = inaltimeArbore(rad->st);
		int inaltimeDR = inaltimeArbore(rad->dr);
		return inaltimeST - inaltimeDR;
	}
	else {
		return 0;
	}
}

NodArb* rotireLaStanga(NodArb* root) {
	if (root) {
		NodArb* aux = root->dr;
		root->dr = aux->st;
		aux->st = root;
		return aux;
	}
	else {
		return root;
	}
}
NodArb* rotireLaDreapta(NodArb* root) {
	if (root) {
		NodArb* aux = root->st;
		root->dr = aux->dr;
		aux->dr = root;
		return aux;
	}
	else {
		return root;
	}
}


NodArb* inserareArb(NodArb* rad, Evaluare e, int&error) {
	if (rad) {
		if (e.marca < rad->e.marca) {
			rad->st = inserareArb(rad->st, e, error);
		}
		else {
			rad->dr = inserareArb(rad->dr, e, error);
		}
		if (calculareGradEchilibru(rad) == 2) {
			if (calculareGradEchilibru(rad->st) != 1) {
				rad->st = rotireLaStanga(rad->st);
			}
			rad = rotireLaDreapta(rad);
		}
		if (calculareGradEchilibru(rad) == -2) {
			if (calculareGradEchilibru(rad->dr) != -1) {
				rad->dr = rotireLaDreapta(rad->dr);
			}
			rad = rotireLaStanga(rad);
		}
		return rad;
	}
	else {
		/*if (rad->im.idImobil == im.idImobil) e = 1;*/
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->e = e;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}

}

void displayArb(NodArb* rad) {
	if (rad) {
		displayEvaluare(rad->e);
		displayArb(rad->st);
		displayArb(rad->dr);
	}
}
int sw = 0;
void cautareAngajat(NodArb* rad, int id) {
	if (rad) {
		if (rad->e.marca == id) {
			printf("Evaluarea angajatului nu a fost gasita.\n");
			displayEvaluare(rad->e);

			sw = 1;
		}
		cautareAngajat(rad->st,id);
		cautareAngajat(rad->dr, id);
	}
	if (sw == 0) {
		printf("Evaluarea angajatului nu a fost gasita");
		sw = 1;
	}
}
NodArb* minValueNode(struct NodArb* node) {
	NodArb* current = node;
	while (current && current->st != NULL)
		current = current->st;
	return current;
}
NodArb* deleteNode(NodArb* root, int key) {
	if (root == NULL) return root;
	if (key < root->e.marca)
		root->st = deleteNode(root->st, key);
	else if (key > root->e.marca)
		root->dr = deleteNode(root->dr, key);
	else {
		if (root->st == NULL) {
			NodArb* temp = root->dr;
			free(root);
			return temp;
		}
		else if (root->dr == NULL) {
			NodArb* temp = root->st;
			free(root);
			return temp;
		}
		NodArb* temp = minValueNode(root->dr);
		root->e.marca = temp->e.marca;
		root->dr = deleteNode(root->dr, temp->e.marca);
	}
	return root;
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
int nrEvaluari(NodArb* root,const char* dep) {
	int nr=0;
	stack<NodArb*> stack;
	NodArb* curr = root;
	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			if (strcmp(curr->e.departament, dep) == 0) {
				nr++;
			}
			stack.pop();
			curr = curr->dr;
		}
	}
	return nr;
}

void salvareEvaluari(NodArb* root,const char* dep) {
	char** charsArr = (char**)malloc(sizeof(char*)*nrEvaluari(root,dep));
	int j = 0,k;
	stack<NodArb*> stack;
	NodArb* curr = root;

	while (!stack.empty() || curr != nullptr)
	{
		if (curr != nullptr)
		{
			stack.push(curr);
			curr = curr->st;
		}
		else {
			curr = stack.top();
			stack.pop();
			if (cautareString(charsArr, j, curr->e.departament) == 0) {
				if (strcmp(curr->e.departament, dep) == 0) {
					charsArr[j] = curr->e.departament;
					j++;
				}
			}
			curr = curr->dr;
		}
	}
	FILE *fptr;

	
	fptr = fopen("asd.txt", "w");
	char sep[] = ", ";
	char sep2[] = "\n";
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	else {
		for (int i = 0; i < j; i++) {
			/*k = 0;*/
			NodArb* curr = root;
			while (!stack.empty() || curr != nullptr)
			{
				if (curr != nullptr)
				{
					stack.push(curr);
					curr = curr->st;
				}
				else {
					curr = stack.top();
					stack.pop();
					if (strcmp(charsArr[i], curr->e.departament) == 0) {
						/*k++;*/
						fprintf(fptr, "%d", curr->e.marca);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%s", curr->e.numeAngajat);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%s", curr->e.departament);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%d", curr->e.notaEvaluare);
						fprintf(fptr, "%s", sep);
						fprintf(fptr, "%s", curr->e.dataEvaluare);
						fprintf(fptr, "%s", sep2);
						displayEvaluare(curr->e);
					}
					curr = curr->dr;
				}
			}
			/*printf("Departament:%s - Nr evaluari:%d\n", charsArr[i], k);*/
		}
	}
	fclose(fptr);
}



void main() {
	Evaluare e;
	NodArb* rad = NULL;
	FILE* f = fopen("evaluare.txt", "r");
	char buffer[DIM_BUFFER];
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			e.marca = atoi(token);
			token = strtok(NULL, sep);
			e.numeAngajat = (char*)malloc(strlen(token) + 1);
			strcpy(e.numeAngajat, token);
			token = strtok(NULL, sep);
			e.departament = (char*)malloc(strlen(token) + 1);
			strcpy(e.departament, token);
			token = strtok(NULL, sep);
			e.notaEvaluare = atoi(token);
			token = strtok(NULL, sep);
			e.dataEvaluare = (char*)malloc(strlen(token) + 1);
			strcpy(e.dataEvaluare, token);
			int error = 0;
			rad = inserareArb(rad, e, error);//ex2
			if (error) {
				free(e.numeAngajat);
				free(e.departament);
				free(e.dataEvaluare);
			}
		}
		fclose(f);
	}
	/*displayArb(rad);*/
	/*cautareAngajat(rad, 1);*/
	/*rad = deleteNode(rad, 1);*///ex4
	/*printf("\n");
	rad = deleteNode(rad, 1);
	displayArb(rad);
	cautareAngajat(rad, 1);*/
	//printf("%d", nrEvaluari(rad));
	
	salvareEvaluari(rad, "IT");
}




