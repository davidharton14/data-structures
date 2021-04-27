#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE_HT 100
#define SIZE_BUFFER 300
struct Cinemagia {
	char* idCinema;
	char* nume;
	int nrLocuri;
	float buget;
	int nrSpectatori;
	float* preturiBilete;
	char* titluFilm;
	char* gen;

};

struct Node {
	Cinemagia* info;
	Node* next;
};
struct HashTable {
	Node** elements;
	int sizeHash;
	static void initHashTable(HashTable*, int);
	int hashCode(const char*,int);
	void insertHT(HashTable*, Cinemagia*,int);
	void displayHT(HashTable*,int);
};

Cinemagia* createCinemagia(char* idCinema, char* nume, char* titluFilm, int nrLocuri, int nrSpectatori,float* preturiBilete,float buget,char* gen) {
	Cinemagia* nou = (Cinemagia*)malloc(sizeof(Cinemagia));
	nou->idCinema = (char*)malloc(strlen(idCinema) + 1);
	strcpy(nou->idCinema, idCinema);
	nou->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(nou->nume, nume);
	nou->nrLocuri = nrLocuri;
	nou->nrSpectatori = nrSpectatori;
	nou->preturiBilete = (float*)malloc(sizeof(float)*nrSpectatori);
	for (int i = 0; i < nou->nrSpectatori; i++) {
		nou->preturiBilete[i] = preturiBilete[i];
	}
	nou->titluFilm = (char*)malloc(strlen(titluFilm) + 1);
	strcpy(nou->titluFilm, titluFilm);
	nou->buget = buget;
	nou->gen = (char*)malloc(strlen(gen) + 1);
	strcpy(nou->gen, gen);
	return nou;
}

void displayCinemagia(Cinemagia* c) {
	printf("Id cinema:%s\nNnume:%s\nTitlu film:%s\nNr locuri:%d\nNr spectatori:%d\nBuget:%.2fGenul:%s\n", c->idCinema, c->nume, c->titluFilm, c->nrLocuri, c->nrSpectatori, c->buget,c->gen);
	printf("Preturi bilete:\n");
	for (int i = 0; i < c->nrSpectatori; i++) {
		printf("%.2f, ", c->preturiBilete[i]);
	}
	printf("\n\n");
}

Node* createNode(Node* head,Cinemagia* c) {
	Node* retValue = NULL;
	retValue = (Node*)malloc(sizeof(Node));
	retValue->info = c;
	retValue->next = head;
	/*newNode->info->idCinema = (char*)malloc(strlen(c->idCinema) + 1);
	strcpy(newNode->info->idCinema, c->idCinema);
	newNode->info->nume = (char*)malloc(strlen(c->nume) + 1);
	strcpy(newNode->info->nume, c->nume);
	newNode->info->titluFilm = (char*)malloc(strlen(c->titluFilm) + 1);
	strcpy(newNode->info->titluFilm, c->titluFilm);
	newNode->info->nrLocuri = c->nrLocuri;
	newNode->info->nrSpectatori = c->nrSpectatori;
	newNode->info->buget = c->buget;
	newNode->next = head;*/
	return retValue;
}


void displayList(Node* head) {
	Node* temp = head;
	while (temp != NULL) {
		displayCinemagia(temp->info);
		temp = temp->next;
	}
}

void HashTable::initHashTable(HashTable* ht, int sizeHT) {
	ht->elements = (Node**)malloc(sizeof(Node*)*sizeHT);
	ht->sizeHash = sizeHT;
	for (int i = 0; i < ht->sizeHash; i++) {
		ht->elements[i] = 0;
	}
}

int HashTable::hashCode(const char* id,int size) {
	int s = 0;
	for (int i = 0; i < strlen(id); i++) {
		s += id[i];
	}
	return s%size;
}
void HashTable::insertHT(HashTable* ht,Cinemagia* c,int size) {
	int i;
	int sw = 0;
	i = hashCode(c->idCinema, size);
	ht->elements[i] = createNode(ht->elements[i], c);
			
}

void HashTable::displayHT(HashTable* ht,int size) {
	for (int i = 0; i < size; i++) {
		if (ht->elements[i]) {
			displayList(ht->elements[i]);
		}
	}
}

int cautareString(char** sir,int j,char* string) {
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
void nrTotalFilme(HashTable* ht) {
	char** charsArr = (char**)malloc(sizeof(char*)*ht->sizeHash);
	int j = 0,k=0;
	for (int i = 0; i < ht->sizeHash; i++) {
		if (ht->elements[i]) {
				if (cautareString(charsArr, j, ht->elements[i]->info->nume) == 0) {
					charsArr[j] = (char*)malloc(sizeof(char));
					charsArr[j] = ht->elements[i]->info->nume;
					j++;
					k++;
				}
		}
	}
	int l = 0;
	for (int i = 0; i < k; i++) {
		l = 0;
		for (int j = 0; j < ht->sizeHash; j++) {
			if (ht->elements[j]) {
				if (strcmp(charsArr[i],ht->elements[j]->info->nume)==0)
					l++;
			}
		  }
		printf("Cinema:%s - Nr filme:%d\n", charsArr[i],l);
	}
}

void displayTitle(HashTable* ht) {
	float incasari = 0;
	float pierdere;
	float profit;
	for (int i = 0; i < ht->sizeHash; i++) {
		if (ht->elements[i]) {
			incasari = 0;
			for (int j = 0; j < ht->elements[i]->info->nrSpectatori; j++) {
				incasari += ht->elements[i]->info->preturiBilete[j];
			}
			if (incasari < ht->elements[i]->info->buget) {
				pierdere = ht->elements[i]->info->buget - incasari;
				printf("Nume film:%s - %.2f lei pierdere\n", ht->elements[i]->info->titluFilm,pierdere);
			}
			else {
				profit = incasari-ht->elements[i]->info->buget;
				printf("Nume film:%s - %.2f lei profit\n", ht->elements[i]->info->titluFilm, profit);
			}
			
		}
	}
}

float incasariTotale(HashTable* ht,const char* id) {
	float incasari = 0;
	for (int i = 0; i < ht->sizeHash; i++) {
		if (ht->elements[i]) {
			if (strcmp(ht->elements[i]->info->idCinema, id) == 0) {
				for (int j = 0; j < ht->elements[i]->info->nrSpectatori; j++) {
					incasari += ht->elements[i]->info->preturiBilete[j];
				}
			}
		}
	}
	return incasari;
}

void determinareGen(HashTable* ht) {
	float incasari = 0;
	int j = 0, k;
	char** genuri = (char**)malloc(sizeof(char*)*ht->sizeHash);
	float* incasariTotaleDupaGen = (float*)malloc(sizeof(float)*ht->sizeHash);
	for (int i = 0; i < ht->sizeHash; i++) {
		if (ht->elements[i]) {
			if (cautareString(genuri, j, ht->elements[i]->info->gen) == 0) {
				genuri[j] = ht->elements[i]->info->gen;
				/*printf("%s\n", genuri[j]);*/
				j++;
				
			}
		}
	}
	k = j;
	for (int j = 0; j < k; j++) {
		incasari = 0;
		for (int i = 0; i < ht->sizeHash; i++) {
			if (ht->elements[i]) {
				if (strcmp(ht->elements[i]->info->gen, genuri[j]) == 0) {
					for (int l = 0; l < ht->elements[i]->info->nrSpectatori; l++) {
						incasari += ht->elements[i]->info->preturiBilete[l];
					}
				}
			}
		}
		incasariTotaleDupaGen[j] = incasari;
	}
	float max = 0;
	char gen[30];
	for (int i = 0; i < k; i++) {
		printf("Gen film:%s - incasari:%.2f LEI\n\n",genuri[i],incasariTotaleDupaGen[i]);
	}
	for (int i = 0; i < k; i++) {
		if (incasariTotaleDupaGen[i] > max) {
			max = incasariTotaleDupaGen[i];
			strcpy(gen, genuri[i]);
		}
	}
	printf("Genul de film cu incasarile cele mai mari a fost genul %s.\n", gen);
	printf("Incasarile au fost de %.2f LEI", max);

}
void main() {

	HashTable ht;
	HashTable::initHashTable(&ht, SIZE_HT);
	Cinemagia* c=(Cinemagia*)malloc(sizeof(Cinemagia));
	char* buffer = (char*)malloc(SIZE_BUFFER);
	FILE* f = fopen("cinemagia.txt", "r");
	if (f) {
		char sep[] = ",";
		char* token;
		char idCinema[10];
		char nume[30];
		int nrLocuri;
		float buget;
		int nrSpectatori;
		char titluFilm[50];
		char gen[30];
		while (fgets(buffer, SIZE_BUFFER, f)) {
			token = strtok(buffer, sep);
			/*c->idCinema = (char*)malloc(strlen(token) + 1);*/
			strcpy(idCinema, token);
			token= strtok(NULL, sep);
		/*	c->nume = (char*)malloc(strlen(token) + 1);*/
			strcpy(nume, token);
			token = strtok(NULL, sep);
		/*	c->titluFilm= (char*)malloc(strlen(token) + 1);*/
			strcpy(titluFilm, token);
			token = strtok(NULL, sep);
			nrLocuri = atoi(token);
			token = strtok(NULL, sep);
			nrSpectatori = atoi(token);
			float* preturi = (float*)malloc(sizeof(float)*nrSpectatori);
			token = strtok(NULL, sep);
			buget = atof(token);
			for (int i = 0; i < nrSpectatori; i++) {
				token = strtok(NULL, sep);
				preturi[i] = atof(token);
			}
			token = strtok(NULL, sep);
			strcpy(gen, token);
			c= createCinemagia(idCinema,nume,titluFilm,nrLocuri,nrSpectatori,preturi,buget,gen);
			ht.insertHT(&ht, c,SIZE_HT);
		}
		/*ht.displayHT(&ht,SIZE_HT);*/ //ex2 ex4
	}
	/*nrTotalFilme(&ht);*/ //ex3
	/*printf("Incasarile totale sunt:%.2f", incasariTotale(&ht,"29"));*/ //ex5
	/*displayTitle(&ht);*/ //ex6
	/*determinareGen(&ht);*/ //ex7


}

