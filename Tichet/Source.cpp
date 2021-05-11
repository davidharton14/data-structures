#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
#define DIM 100
#define LINESIZE 300
enum Stare {
	NEW,
	OPEN,
	PROGRESS,
	FIXED,
	CLOSED
};

Stare convertToStare(const string& str)
{
	if (str == "NEW") return NEW;
	else if (str == "OPEN") return OPEN;
	else if (str == "PROGRESS") return PROGRESS;
	else if (str == "FIXED") return FIXED;
	else if (str == "CLOSED") return CLOSED;
}

struct Tichet {
	char* cod;
	char* descriere;
	char* numeEmitent;
	char* dataDescriere;
	Stare s;
};

struct Nod {
	Tichet t;
	Nod* next;
};

void displayTichet(Tichet t) {
	printf("Cod tichet:%s\nDescriere:%s\nNume:%s\nData:%s\nStare:%d\n\n", t.cod, t.descriere,t.numeEmitent,t.dataDescriere,t.s);
	
}

int pozitieHTable(Tichet t, int size) {
	int s = 0;
	for (int i = 0; i < strlen(t.numeEmitent); i++) {
		s += t.numeEmitent[i];
	}
	return s % size;
}

Nod* adaugareNod(Nod* cap, Tichet t) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->t.cod = (char*)malloc(strlen(t.cod) + 1);
	strcpy(nou->t.cod, t.cod);
	nou->t.descriere = (char*)malloc(strlen(t.descriere) + 1);
	strcpy(nou->t.descriere, t.descriere);
	nou->t.numeEmitent = (char*)malloc(strlen(t.numeEmitent) + 1);
	strcpy(nou->t.numeEmitent, t.numeEmitent);
	nou->t.dataDescriere = (char*)malloc(strlen(t.dataDescriere) + 1);
	strcpy(nou->t.dataDescriere, t.dataDescriere);
	nou->t.s = t.s;
	nou->next = cap;
	return nou;
}

Nod* hTable[DIM];

void init()
{
	for (int i = 0; i < DIM; i++)
		hTable[i] = NULL;
}
void inserareHTable(Tichet t, int hSize) {
	int k;
	k = pozitieHTable(t, hSize);
	Nod*newNode = (Nod*)malloc(sizeof(Nod));
	newNode->t = t;
	newNode->next = NULL;
	if (hTable[k]) {
		Nod*temp = hTable[k];
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	else {
		hTable[k] = newNode;
	}
}

void displayLista(Nod* cap) {
	Nod* temp = cap;
	while (temp) {
		displayTichet(temp->t);
		temp = temp->next;
	}
}

void displayH(int size) {
	for (int i = 0; i < size; i++)
	{
		if (hTable[i]) {
			struct Nod*temp = hTable[i];
			while (temp)
			{
				displayTichet(temp->t);
				temp = temp->next;
			}
		}
	}
}

int nrTichete(int dim,const char* nume) {
	int nr = 0;
	for (int i = 0; i < dim; i++)
	{
		if (hTable[i]) {
			struct Nod*temp = hTable[i];
			while (temp)
			{
				if(strcmp(temp->t.numeEmitent,nume)==0)
					if (temp->t.s == 1) {
						nr++;
					}
				temp = temp->next;
			}
		}
	}
	return nr;
}

void determinareTichete(int dim, const char* nume, const char* data) {
	for (int i = 0; i < dim; i++)
	{
		if (hTable[i]) {
			struct Nod*temp = hTable[i];
			while (temp)
			{
				if (strcmp(temp->t.numeEmitent, nume) == 0)
					if (strcmp(temp->t.dataDescriere,data)==0) {
						if(temp->t.s==1)
						displayTichet(temp->t);
					}
				temp = temp->next;
			}
		}
	}
}
void schimbareStareTichet(int dim) {
	for (int i = 0; i < dim; i++)
	{
		if (hTable[i]) {
			struct Nod*temp = hTable[i];
			while (temp)
			{
				if (temp->t.s == 3)
					temp->t.s = convertToStare("OPEN");
				temp = temp->next;
			}
		}
	}
}
void main() {
	int key, value, n;
	Tichet t;
	FILE*f = fopen("tichets.txt", "r");
	/*Nod** hTable = (Nod**)malloc(sizeof(Nod*)*DIM);*/
	init();
	if (f) {
		char* token, buffer[LINESIZE], sep[] = ",";
		while (fgets(buffer, sizeof(buffer), f)) {
			token = strtok(buffer, sep);
			t.cod = (char*)malloc(strlen(token) + 1);
			strcpy(t.cod, token);
			token = strtok(NULL, sep);
			t.descriere = (char*)malloc(strlen(token) + 1);
			strcpy(t.descriere, token);
			token = strtok(NULL, sep);
			t.numeEmitent = (char*)malloc(strlen(token) + 1);
			strcpy(t.numeEmitent, token);
			token = strtok(NULL, sep);
			t.dataDescriere = (char*)malloc(strlen(token) + 1);
			strcpy(t.dataDescriere, token);
			token = strtok(NULL, sep);
			t.s = convertToStare(token);
			inserareHTable(t,DIM);
		}
		fclose(f);
	}
	/*displayH(DIM);*/
	/*printf("Numarul de tichete deschise de angajatul Lumperdean Radu este:%d", nrTichete(DIM,"Lumperdean Radu"));*/
	/*determinareTichete(DIM, "Lumperdean Radu", "02/06/2018");*/
	/*schimbareStareTichet(DIM);*/
	displayH(DIM);
	/*determinareTichete(DIM, "Harton Claudiu", "09/07/2021");*/

}