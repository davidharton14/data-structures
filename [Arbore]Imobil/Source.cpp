#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300

struct Imobil {
	unsigned int idImobil;
	char* numeStrada;
	unsigned int nrStrazii;
	int nrApartamente;
	int* numarLocatari;
	float valoareTotala;
};

struct NodArb {
	Imobil im;
	NodArb* st;
	NodArb* dr;
};

void displayImobil(Imobil im) {
	printf("Id imobil:%d\nNume strada:%s\nNr strazii:%d\nNr apartamente:%d\n",im.idImobil,im.numeStrada,im.nrStrazii,im.nrApartamente);
	printf("Nr locatari:\n");
	for (int i = 0; i < im.nrApartamente; i++) {
		printf("%d ",im.numarLocatari[i]);
	}
	printf("\nValoare totala:%.2f\n\n",im.valoareTotala);
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


NodArb* inserareArb(NodArb* rad, Imobil im, int&e) {
	if (rad) {
		if (im.idImobil< rad->im.idImobil) {
			rad->st = inserareArb(rad->st, im, e);
		}
		else {
			rad->dr = inserareArb(rad->dr, im, e);
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
		nou->im = im;
		nou->st = NULL;
		nou->dr = NULL;
		rad = nou;
	}
	
}

void displayArb(NodArb* rad) {
	if (rad) {
		displayImobil(rad->im);
		displayArb(rad->st);
		displayArb(rad->dr);
	}
}

NodArb* displayLeafNodes(NodArb* radacina) {
	if (radacina == NULL)
		return NULL;
	if (radacina->dr == NULL && radacina->st == NULL) {
		displayArb(radacina);
		free(radacina);
		return NULL;
	}
	radacina->st = displayLeafNodes(radacina->st);
	radacina->dr = displayLeafNodes(radacina->dr);
	return radacina;
}
int nr = 0;
void nrImobile(NodArb* rad,const char* nume) {
	if (rad) {
		if (strcmp(rad->im.numeStrada, nume) == 0) {
			nr++;
		}
		nrImobile(rad->st, nume);
		nrImobile(rad->dr, nume);
	}
}
float suma=0;
float plata;
float valoarePlata(NodArb* rad, int id) {
	
	if (rad) {
		if (rad->im.idImobil == id) {
			for (int i = 0; i < rad->im.nrApartamente; i++) {
				suma += rad->im.numarLocatari[i];
			}
			plata = rad->im.valoareTotala / suma;
		}
		valoarePlata(rad->st, id);
		valoarePlata(rad->dr, id);
		return plata;
		
	}
}
float sum = 0;
float value;
float* valori = (float*)malloc(sizeof(float)*20);
float* valoareAp(NodArb* rad,int nr, int id) {
	
	if (rad) {
		if (rad->im.idImobil == id) {
			for (int i = 0; i < nr; i++) {
					valori[i] = rad->im.valoareTotala / rad->im.numarLocatari[i];
			}
		}
		valoareAp(rad->st,nr, id);
		valoareAp(rad->dr,nr, id);
		return valori;
	}
	
}
void main() {
	Imobil im;
	NodArb* rad = NULL;
	FILE* f = fopen("imobil.txt", "r");
	char buffer[DIM_BUFFER];
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			im.idImobil = atoi(token);
			token = strtok(NULL, sep);
			im.numeStrada = (char*)malloc(strlen(token) + 1);
			strcpy(im.numeStrada, token);
			token = strtok(NULL, sep);
			im.nrStrazii = atoi(token);
			token = strtok(NULL, sep);
			im.nrApartamente = atoi(token);
			im.numarLocatari = (int*)malloc(sizeof(int)*im.nrApartamente);
			for (int i = 0; i < im.nrApartamente; i++) {
				token = strtok(NULL, sep);
				im.numarLocatari[i] = atoi(token);
			}
			token = strtok(NULL, sep);
			im.valoareTotala = atof(token);
			int e = 0;
			rad = inserareArb(rad, im, e);//ex2
			if (e) {
				free(im.numeStrada);
				free(im.numarLocatari);
			}
		}
	}
	/*displayArb(rad);*/ //ex3
	/*printf("\nNodurile frunza sunt:\n\n");
	displayLeafNodes(rad);*/
	/*nrImobile(rad, "Strada Macului"); //ex4
	printf("%d", nr);*/
	//plata=valoarePlata(rad, 10); //ex5
	//printf("%.2f", plata);
	/*valori = valoareAp(rad, 20, 10); //ex6
	for (int i = 0; i < 20; i++) {
		printf("%.2f\n", valori[i]);
	}*/
}
