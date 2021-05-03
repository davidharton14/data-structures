#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300
struct Rezervare {
	unsigned int idRezervare;
	char* denumireHotel;
	unsigned int nrCamereRezervate;
	char* numeClient;
	char* perioadaRezervarii;
	float sumaPlata;
};

struct Nod{
	Rezervare info;
	Nod* next;
	Nod* prev;
};

void afisareRezervare(Rezervare r) {
	printf("Id rezervare:%d\nDenumire hotel:%s\nNr camere rezervate:%d\nNume client:%s\nPerioada rezervarii:%s\nSuma plata:%.2f\n\n",r.idRezervare,r.denumireHotel,r.nrCamereRezervate,r.numeClient,r.perioadaRezervarii,r.sumaPlata);
}

void adaugareNodInLista(Nod** cap, Rezervare r) {
	if (*cap == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = r;
		nou->next = nou->prev = nou;
		(*cap) = nou;
	}
	else {
		Nod* last = (*cap)->prev;
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = r;
		nou->next = (*cap);
		(*cap)->prev = nou;
		nou->prev = last;
		last->next = nou;
	}
}

void parcurgereLista(Nod* cap) {
		
	    Nod* temp = cap;
		while (temp->next != cap) {
			afisareRezervare(temp->info);
			temp = temp->next;
		}
			afisareRezervare(temp->info);
}
float incasari(Nod* cap, const char* data) {
	float i=0;
	Nod* temp = cap;
	while (temp->next != cap) {
		if (strcmp(temp->info.perioadaRezervarii,data)==0) {
			i=temp->info.sumaPlata;
			break;
		}
		temp = temp->next;
	}
	return i;
}

int nrCamere(Nod* cap, const char* nume) {
	Nod* temp = cap;
	while (temp->next != cap) {
		if (strcmp(temp->info.numeClient, nume) == 0) {
			return temp->info.nrCamereRezervate;
			break;
		}
		temp = temp->next;
	}
}

int nrCamereTotal(Nod* cap, const char* hotel) {
	int nr = 0;
	Nod* temp = cap;
	while (temp->next != cap) {
		if (strcmp(temp->info.denumireHotel, hotel) == 0) {
			nr = nr + temp->info.nrCamereRezervate;
		}
		temp = temp->next;
	}
	if (strcmp(temp->info.denumireHotel, hotel) == 0) {
		nr = nr + temp->info.nrCamereRezervate;
	}

	return nr;
}


void main() {
	Rezervare r;
	Nod* cap = NULL;
	FILE* f = fopen("rezervari.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			r.idRezervare = atoi(token);
			token = strtok(NULL, sep);
			r.denumireHotel = (char*)malloc(strlen(token) + 1);
			strcpy(r.denumireHotel, token);
			token = strtok(NULL, sep);
			r.nrCamereRezervate = atoi(token);
			token = strtok(NULL, sep);
			r.numeClient = (char*)malloc(strlen(token) + 1);
			strcpy(r.numeClient, token);
			token = strtok(NULL, sep);
			r.perioadaRezervarii = (char*)malloc(strlen(token) + 1);
			strcpy(r.perioadaRezervarii, token);
			token = strtok(NULL, sep);
			r.sumaPlata = atof(token);
			adaugareNodInLista(&cap, r);//ex2
		}
		fclose(f);
	}
	/*parcurgereLista(cap);*///ex3
	//printf("%.2f",incasari(cap,"01/01/2018-10/01/2018"));//ex4
	//printf("%d",nrCamere(cap,"Harton David"));
	//printf("%d",nrCamereTotal(cap,"Ramada Parc"));//ex5
}
