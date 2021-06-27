#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stack>
using namespace std;
#define DIM_BUFFER 300

struct Spectacol {
	int idSpectacol;
	float pretBilet;
	char* numeClient;
	char dataSustinere[10];
	char* numeSpectacol;
	int durata;
	float costTotal;
};

struct NodArb {
	Spectacol* s;
	NodArb* st;
	NodArb* dr;
};

//functia de afisare a unui spectacol
void afisareSpectacol(Spectacol* s) {
	printf("Id spectacol:%d\nPret bilet:%.2f\nNume client:%s\nData sustinere:%s\nNume spectacol:%s\nDurata:%d\n\n",
		s->idSpectacol, s->pretBilet, s->numeClient, s->dataSustinere, s->numeSpectacol, s->durata);
}
//functia de inserare a unui spectacol intr-o structura de tip arbore
NodArb* inserareArb(NodArb* rad, Spectacol* s) {
	if (rad) {
		if (s->idSpectacol < rad->s->idSpectacol) {
			rad->st = inserareArb(rad->st, s);
		}
		else {
			rad->dr = inserareArb(rad->dr, s);
		}
		return rad;
	}
	else
	{
		NodArb* nou = (NodArb*)malloc(sizeof(NodArb));
		nou->s = s;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}

}
//functia de afisare a nodurilor inserate in structura arbore
void afisareArb(NodArb* rad) {
	if (rad) {
		afisareSpectacol(rad->s);
		afisareArb(rad->st);
		afisareArb(rad->dr);
	}
}
//functia calcularea numarului de spectacole a carei data de sustinere este data de utilizator
int nrSpectacole(NodArb* root, const char* data) {
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
			if (strcmp(curr->s->dataSustinere, data) == 0) {
				nr++;
			}
			curr = curr->dr;
		}
	}
	return nr;
}

//functia de salvare a spectacolelor a carei data de sustinere este data de utilizator
Spectacol** salvareSpectacole(NodArb* root,const char* data) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	Spectacol** vector = (Spectacol**)malloc(sizeof(Spectacol*)*nrSpectacole(root, data));
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
			if (strcmp(curr->s->dataSustinere, data) == 0) {
				vector[j] = curr->s;
				j++;
			}
			curr = curr->dr;
		}
	}
	return vector;
}

//functia care calculeaza numarul total de spectacole
int nrTotalSpectacole(NodArb* root) {
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
//functia care cauta un client in sir 
int cautareString(char** sir,int k, const char*string) {
	int sw = 0;
	for (int i = 0; i < k; i++) {
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

//functia care calculeaza numarul de clienti unici
int numarClienti(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	char** sir = (char**)malloc(sizeof(char*)*nrTotalSpectacole(root));
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
			if (cautareString(sir,j, curr->s->numeClient) == 0) {
				sir[j] = curr->s->numeClient;
				j++;
			}
			curr = curr->dr;
		}
	}
	return j;
}

//fucntia care creaza un spectacol care sa contina doar 2 atribute
Spectacol* createSpectacol(char* numeClient, float sum) {
	Spectacol* nou = (Spectacol*)malloc(sizeof(Spectacol));
	nou->numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy(nou->numeClient, numeClient);
	nou->costTotal = sum;
	return nou;
}
//functia salveaza intr-un vector costul total aferent fiecarui client
Spectacol** costulTotalAferentFiecaruiClient(NodArb* root) {
	stack<NodArb*> stack;
	NodArb* curr = root;
	char** sir = (char**)malloc(sizeof(char*)*numarClienti(root));
	Spectacol** vector = (Spectacol**)malloc(sizeof(Spectacol*)*nrTotalSpectacole(root));
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
			if (cautareString(sir,j, curr->s->numeClient) == 0) {
				sir[j] = curr->s->numeClient;
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
				if (strcmp(sir[i], t->s->numeClient) == 0)
					sum += t->s->pretBilet;
				t = t->dr;
			}
		}
		vector[k] = createSpectacol(sir[i], sum);
		k++;
	}
	return vector;
}

void seteazaCopil(NodArb* node, bool toLeft, NodArb* child) {
	if (toLeft) {
		node->st = child;
	}
	else {
		node->dr = child;
	}
}

NodArb* transformareArb(NodArb* rad, int k) {
	NodArb* radacina = NULL;
	NodArb* parinte1 = NULL;
	NodArb* parinte2 = NULL;
	bool toLeft = rad != NULL && k <= rad->s->idSpectacol;

	while (rad != NULL) {
		while (rad != NULL && (k <= rad->s->idSpectacol) == toLeft) {
			parinte1 = rad;
			rad = toLeft ? rad->st : rad->dr;
		}
		seteazaCopil(parinte1, toLeft, NULL);
		toLeft = !toLeft;
		if (radacina != NULL) {
			radacina = rad;
		}
		else if (parinte2 != NULL) {
			seteazaCopil(parinte2, toLeft, rad);
		}
		parinte2 = parinte1;
		parinte1 = NULL;
	}
	return radacina;
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
	Spectacol* s = NULL;
	NodArb* rad = NULL;
	FILE* f = fopen("file.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			s = (Spectacol*)malloc(sizeof(Spectacol));
			token = strtok(buffer, sep);
			s->idSpectacol = atoi(token);
			token = strtok(NULL, sep);
			s->pretBilet = atof(token);
			token = strtok(NULL, sep);
			s->numeClient= (char*)malloc(strlen(token) + 1);
			strcpy(s->numeClient, token);
			token = strtok(NULL, sep);
			strcpy(s->dataSustinere, token);
			token = strtok(NULL, sep);
			s->numeSpectacol = (char*)malloc(strlen(token) + 1);
			strcpy(s->numeSpectacol, token);
			token = strtok(NULL, sep);
			s->durata = atoi(token);
			rad = inserareArb(rad, s);
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu a fost deschis");
	}
	//1
	//apelarea functiei de afisare a nodurilor din structura de tip arbore
	afisareArb(rad);
	//2
	//apelarea functiei de salvare a spectacolelor a carei data de sustinere este data de utilizator
	printf("Vectorul este:\n");
	Spectacol** vector = (Spectacol**)malloc(sizeof(Spectacol*)*nrSpectacole(rad, "01/03/2021"));
	vector = salvareSpectacole(rad, "01/03/2021");
	for (int i = 0; i < nrSpectacole(rad, "01/03/2021"); i++) {
		afisareSpectacol(vector[i]);
	}
	//3
	//apelarea functiei de salvare intr-un vector a costului total aferent fiecarui client
	printf("Vectorul costului total aferent fiecarui client este:\n");
	Spectacol** vec = (Spectacol**)malloc(sizeof(Spectacol*)*numarClienti(rad));
	vec = costulTotalAferentFiecaruiClient(rad);
	for (int i = 0; i < numarClienti(rad); i++) {
		printf("Nume client:%s\nCost total:%.2f\n\n", vec[i]->numeClient, vec[i]->costTotal);
	}
	//apelarea functiei care calculeaza dimensiunea vectorului
	printf("Dimensiunea vectorului este:%d\n", numarClienti(rad));
	//4
	NodArb* node = NULL;
	node = transformareArb(rad, 29);
	printf("Prima structura complementara este:\n\n");
	afisareArb(rad);
	printf("A doua structura complementara este:\n\n");
	afisareArb(node);
    //5
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
