#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;
#define DIM_BUFFER 300

struct Bicicleta {
	int nrIdentificare;
	int durataUtilizare;
	int idStatieParcare;
	int nrUtilizari;
	char* numeUtilizator;

};

struct NodArb {
	Bicicleta b;
	NodArb* st;
	NodArb* dr;
};

void displayBicicleta(Bicicleta c) {
	printf("Nr identificare:%d\nDurata de utilizare intr-o zi:%d minute\nId statie de parcare:%d\nNr de utilizari pe zi:%d ori\nNumele utilizatorului:%s\n\n", 
		c.nrIdentificare, c.durataUtilizare, c.idStatieParcare,c.nrUtilizari, c.numeUtilizator);
}


NodArb* inserareArb(NodArb* rad, Bicicleta b, int&e) {
	if (rad) {
		if (b.durataUtilizare < rad->b.durataUtilizare) {
			rad->st = inserareArb(rad->st, b, e);
		}
		else {
			rad->dr = inserareArb(rad->dr, b, e);
		}
		return rad;
	}
	else /*if (rad->c.idComanda == c.idComanda) e = 1;*/
	{

		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->b = b;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}

}

void displayArb(NodArb* rad) {
	if (rad) {
		displayArb(rad->st);
		displayBicicleta(rad->b);
		displayArb(rad->dr);
	}
}

int cautareString(int* sir, int j, int value) {
	int sw = 0;
	for (int i = 0; i < j; i++) {
		if (sir[i]==value) {
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

int nrEvaluari(NodArb* root) {
	int nr = 0;
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
				nr++;
			stack.pop();
			curr = curr->dr;
		}
	}
	return nr;
}
int determinareNrDistinctStatiiParcare(NodArb* rad) {
	int* charsArr = (int*)malloc(sizeof(int)*nrEvaluari(rad));
	int j = 0;
	int nr = 0;
	stack<NodArb*> stack;
	NodArb* curr = rad;

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
			if (cautareString(charsArr, j, curr->b.idStatieParcare) == 0) {
					charsArr[j] = curr->b.idStatieParcare;
					j++;
			}
			curr = curr->dr;
		}
	}
	curr = rad;
	int k = 0;
	for (int i = 0; i < j; i++) {
		k = 0;
		curr = rad;
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
				if (charsArr[i] == curr->b.idStatieParcare) {
					k++;
				}
				curr = curr->dr;
			}
		}
		if (k == 1) {
			nr++;
			printf("%d ", charsArr[i]);
		}
	}
	return nr;
	
}
int numarTotalMinute(NodArb* rad) {
	int total=0;
	stack<NodArb*> stack;
	NodArb* curr = rad;
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
			total += curr->b.durataUtilizare;
			curr = curr->dr;
		}
	}
	return total;
}

float valoareaTotalaIncasata(NodArb* rad) {
	float valoare = 0;
	stack<NodArb*> stack;
	NodArb* curr = rad;
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
			if (curr->b.durataUtilizare > 10) {
				valoare += (2 * (curr->b.durataUtilizare - 10));
				printf("\nValoare:%d lei", 2 * (curr->b.durataUtilizare - 10));
			}
			else {
				printf("\nValoare:0 lei");
			}

			curr = curr->dr;
		}
	}
	return valoare;
}
void main() {
	Bicicleta b;
	NodArb* rad = NULL;
	FILE* f = fopen("biciclete.txt", "r");
	char buffer[DIM_BUFFER];
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			b.nrIdentificare = atoi(token);
			token = strtok(NULL, sep);
			b.durataUtilizare = atoi(token);
			token = strtok(NULL, sep);
			b.idStatieParcare = atoi(token);
			token = strtok(NULL, sep);
			b.nrUtilizari = atoi(token);
			token = strtok(NULL, sep);
			b.numeUtilizator = (char*)malloc(strlen(token) + 1);
			strcpy(b.numeUtilizator, token);
			
			int e = 0;
			rad = inserareArb(rad, b, e);
			/*if (e) {
				free(c.numeClient);
			}*/
		}
		fclose(f);
	}
	displayArb(rad);
	//printf("\n\n");
	//printf("Numarul total de minute a tuturor bicicletelor este %d minute", numarTotalMinute(rad));
	/*printf("\nValoarea totala de incasari este:%.2f lei", valoareaTotalaIncasata(rad));*/
	/*printf("Numarul de statii distincte este:%d", determinareNrDistinctStatiiParcare(rad));*/
}




