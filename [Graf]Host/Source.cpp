#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define DIM_BUFFER 300

struct Host {
	int id;
	char* nume;
	int capacitate;
	int nrSiteuri;
	int nrCasuteMail;
};

struct nodListaPrincipala;
struct nodListaSecundara {
	nodListaSecundara* next;
	nodListaPrincipala* info;
	int distanta;
};

struct nodListaPrincipala {
	nodListaSecundara*vecini;
	Host* info;
	nodListaPrincipala*next;
};

nodListaPrincipala*inserareListaPrincipala(nodListaPrincipala* cap, Host* d) {
	nodListaPrincipala* nou = (nodListaPrincipala*)malloc(sizeof(nodListaPrincipala));
	nou->info = d;
	nou->vecini = NULL;
	nou->next = NULL;
	if (cap) {
		nodListaPrincipala* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}


nodListaSecundara* inserareListaSecundara(nodListaSecundara*cap, nodListaPrincipala* info, int distanta) {
	nodListaSecundara* nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
	nou->info = info;
	nou->distanta = distanta;
	nou->next = NULL;
	if (cap) {
		nodListaSecundara*p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

nodListaPrincipala* cautareDupaID(nodListaPrincipala* cap, int id) {
	while (cap && cap->info->id != id) {
		cap = cap->next;
	}
	return cap;
}
void inserareArcInGraf(nodListaPrincipala* graf, int idStart, int idStop, int distanta) {
	if (graf) {
		nodListaPrincipala*nodStart = cautareDupaID(graf, idStart);
		nodListaPrincipala*nodStop = cautareDupaID(graf, idStop);
		if (nodStart && nodStop) {
			nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop, distanta);
			/*nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart,distanta);*/
		}
	}
}

void afisareListaSecundara(nodListaSecundara* cap) {
	while (cap) {
		printf("Id:%d\nNume:%s\nCapacitate:%d\nNr siteuri:%d\nNr casute mail:%d\n\n",
			cap->info->info->id, cap->info->info->nume, cap->info->info->capacitate, cap->info->info->nrSiteuri, cap->info->info->nrCasuteMail);
		printf("Distanta:%d\n", cap->distanta);
		cap = cap->next;
	}
}

void afisareListaPrincipala(nodListaPrincipala*cap) {
	while (cap) {
		if (cap->vecini) {
			printf("NODUL:\n\nId:%d\nNume:%s\nCapacitate:%d\nNr siteuri:%d\nNr casute mail:%d\n\n",
				cap->info->id, cap->info->nume, cap->info->capacitate, cap->info->nrSiteuri, cap->info->nrCasuteMail);
			
			printf("\n");
			printf("AU URMATORII VECINI:\n");
			afisareListaSecundara(cap->vecini);
		}
		cap = cap->next;
	}
}

struct nodStiva {
	int id;
	nodStiva*next;
};

nodStiva* push(nodStiva* cap, int id) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->next = cap;
	nou->id = id;
	return nou;
}

int pop(nodStiva*&cap) {
	if (cap) {
		int id = cap->id;
		nodStiva* temp = cap;
		cap = cap->next;
		free(temp);
		return id;
	}
	else {
		return -1;
	}
}

int calculareNumarNoduri(nodListaPrincipala* graf) {
	int contor = 0;
	while (graf) {
		contor++;
		graf = graf->next;
	}

	return contor;
}

void parcurgereAdancime(nodListaPrincipala*graf, int idNodStart) {
	if (graf) {
		nodStiva* stiva = NULL;
		int nrNoduri = calculareNumarNoduri(graf);
		int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
		for (int i = 0; i < nrNoduri; i++) {
			vizitate[i] = 0;
		}
		stiva = push(stiva, idNodStart);
		vizitate[idNodStart] = 1;

		while (stiva) {
			int idNodCurent = pop(stiva);
			nodListaPrincipala* nodCurent = cautareDupaID(graf, idNodCurent);
			if (nodCurent) {
				printf("NODURILE:\nId:%d\nNume:%s\nCapacitate:%d\nNr siteuri:%d\nNr casute mail:%d\n\n",
					nodCurent->info->id, nodCurent->info->nume, nodCurent->info->capacitate, nodCurent->info->nrSiteuri,nodCurent->info->nrSiteuri);
				nodListaSecundara* p = nodCurent->vecini;
				while (p) {
					if (vizitate[p->info->info->id] == 0) {
						stiva = push(stiva, p->info->info->id);
						vizitate[p->info->info->id] = 1;
					}
					p = p->next;
				}
			}
		}
	}
}

int number(nodListaPrincipala*cap, int value) {
	int nr = 0;
	nodListaPrincipala*temp = cap;
	while (temp) {
		if (temp->vecini) {
			if (temp->vecini->distanta > value) {
				nr += 2;
			}
		}
		temp = temp->next;
	}
	return nr;
}

int* determinareArce(nodListaPrincipala*cap, int pondere) {
	int* vector = (int*)malloc(sizeof(int)*number(cap, pondere));
	int j = 0;
	while (cap) {
		if (cap->vecini) {
			if (cap->vecini->distanta > pondere) {
				vector[j] = cap->info->id;
				j++;
				vector[j] = cap->vecini->info->info->id;
				j++;
			}
		}
		cap = cap->next;
	}
	return vector;
}

int nrHosturiPeUnCriteriu(nodListaPrincipala*cap, int value) {
	nodListaPrincipala*temp = cap;
	int nr = 0;
	while (temp) {
		if (temp->info->nrSiteuri == value) {
			nr++;
		}
		temp = temp->next;
	}
	return nr;
}

Host** determinareHosturiPeUnCriteriu(nodListaPrincipala*cap, int value) {
	Host** vector = (Host**)malloc(sizeof(Host*)*nrHosturiPeUnCriteriu(cap, value));
	int j = 0;
	nodListaPrincipala*temp = cap;
	while (temp) {
		if (temp->info->nrSiteuri == value) {
			vector[j] = temp->info;
			j++;
		}
		temp = temp->next;
	}
	return vector;
}

void dezalocareLs(nodListaSecundara *cap) {
	nodListaSecundara *temp = cap;
	while (temp) {
		nodListaSecundara *temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocareLp(nodListaPrincipala* cap) {
	nodListaPrincipala *temp = cap;
	while (temp) {
		nodListaPrincipala *temp2 = temp->next;
		if (temp->vecini != NULL)
			dezalocareLs(temp->vecini);
		free(temp);
		temp = temp2;
	}
}


void main()
{
	nodListaPrincipala* graf = NULL;
	Host* h = NULL;
	FILE* file = fopen("hosts.txt", "r");
	if (file) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		int nr = 0;
		int nrArce;
		while (fgets(buffer, DIM_BUFFER, file)) {
			if (nr == 0) {
				token = strtok(buffer, sep);
				nrArce = atoi(token);
				for (int i = 0; i < nrArce; i++) {
					token = strtok(NULL, sep);
					token = strtok(NULL, sep);
					token = strtok(NULL, sep);
				}
			}
			else {
				h = (Host*)malloc(sizeof(Host));
				token = strtok(buffer, sep);
				h->id = atoi(token);
				token = strtok(NULL, sep);
				h->nume = (char*)malloc(strlen(token) + 1);
				strcpy(h->nume, token);
				token = strtok(NULL, sep);
				h->capacitate = atoi(token);
				token = strtok(NULL, sep);
				h->nrSiteuri = atoi(token);
				token = strtok(NULL, sep);
				h->nrCasuteMail = atoi(token);
				graf = inserareListaPrincipala(graf, h);
			}
			nr++;
		}
		fclose(file);
	}
	int nrArce;
	FILE*f = fopen("hosts.txt", "r");
	if (f) {
		char buffer[DIM_BUFFER];
		char* token, sep[] = ",";
		int nr = 0;
		while (fgets(buffer, DIM_BUFFER, f)) {
			if (nr == 0) {
				token = strtok(buffer, sep);
				nrArce = atoi(token);
				for (int i = 0; i < nrArce; i++) {
					token = strtok(NULL, sep);
					int idStart = atoi(token);
					token = strtok(NULL, sep);
					int idStop = atoi(token);
					token = strtok(NULL, sep);
					int distanta = atoi(token);
					inserareArcInGraf(graf, idStart, idStop, distanta);
				}
			}
			nr++;
		}
		fclose(f);
	}

	//ex1
	afisareListaPrincipala(graf);
	//ex2
	printf("\n\n");
	int* vector = (int*)malloc(sizeof(int)*number(graf, 110));
	vector = determinareArce(graf, 110);
	for (int i = 0; i < number(graf, 110); i++) {
		printf("%d ", vector[i]);
	}
	//ex3
	printf("\n");
	Host** vec = (Host**)malloc(sizeof(Host*)*nrHosturiPeUnCriteriu(graf, 5));
	vec = determinareHosturiPeUnCriteriu(graf, 5);
	for (int i = 0; i < nrHosturiPeUnCriteriu(graf, 5); i++) {
		printf("Id:%d\nNume:%s\nCapacitate:%d\nNr siteuri:%d\nNr casute mail:%d\n\n",
			vec[i]->id, vec[i]->nume, vec[i]->capacitate, vec[i]->nrSiteuri, vec[i]->nrCasuteMail);
	}
	//ex5
	for (int i = 0; i < nrArce; i++) {
		free(vec[i]->nume);
	}
	free(vec);
	vec = NULL;
	dezalocareLp(graf);

}