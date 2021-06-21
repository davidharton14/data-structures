#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300
struct Depozit {
	int cod;
	char* id;
	int capacitate;
	float coordonateGPS;
	int nrMateriale;
	char** categoriiMateriale;
	int procentVolum;
};

struct nodListaPrincipala;
struct nodListaSecundara {
	nodListaSecundara* next;
	nodListaPrincipala* info;
	int distanta;
};

struct nodListaPrincipala {
	nodListaSecundara*vecini;
	Depozit* info;
	nodListaPrincipala*next;
};

nodListaPrincipala*inserareListaPrincipala(nodListaPrincipala* cap, Depozit* d) {
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


nodListaSecundara* inserareListaSecundara(nodListaSecundara*cap, nodListaPrincipala* info,int distanta) {
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
	while (cap && cap->info->cod != id) {
		cap = cap->next;
	}
	return cap;
}
void inserareArcInGraf(nodListaPrincipala* graf, int idStart, int idStop,int distanta) {
	if (graf) {
		nodListaPrincipala*nodStart = cautareDupaID(graf, idStart);
		nodListaPrincipala*nodStop = cautareDupaID(graf, idStop);
		if (nodStart && nodStop) {
			nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop,distanta);
			/*nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart,distanta);*/
		}
	}
}

void afisareListaSecundara(nodListaSecundara* cap) {
	while (cap) {
		printf("Cod:%d\nId:%s\nCapacitate:%d\nCoordonate GPS:%.2f\nProcent volum:%d\nNr materiale:%d\n",
			cap->info->info->cod, cap->info->info->id, cap->info->info->capacitate, cap->info->info->coordonateGPS, cap->info->info->procentVolum, cap->info->info->nrMateriale);
		printf("Categorii materiale:\n\n");
		for (int i = 0; i < cap->info->info->nrMateriale; i++) {
			printf("%s\n", cap->info->info->categoriiMateriale[i]);
		}
		printf("\n");
		printf("Distanta:%d\n", cap->distanta);
		cap = cap->next;
	}
}

void afisareListaPrincipala(nodListaPrincipala*cap) {
	while (cap) {
		if (cap->vecini) {
		printf("NODUL:\n\nCod:%d\nId:%s\nCapacitate:%d\nCoordonate GPS:%.2f\nProcent volum:%d\nNr materiale:%d\n",
			cap->info->cod, cap->info->id, cap->info->capacitate, cap->info->coordonateGPS, cap->info->procentVolum, cap->info->nrMateriale);
		printf("Categorii materiale:\n\n");
		for (int i = 0; i < cap->info->nrMateriale; i++) {
			printf("%s\n", cap->info->categoriiMateriale[i]);
		}
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
				printf("NODURILE:\nCod:%d\nId:%s\nCapacitate:%d\nCoordonate GPS:%.2f\nProcent volum:%d\nNr materiale:%d\n",
					nodCurent->info->cod, nodCurent->info->id, nodCurent->info->capacitate, nodCurent->info->coordonateGPS, nodCurent->info->procentVolum, nodCurent->info->nrMateriale);
				printf("Categorii materiale:\n\n");
				for (int i = 0; i < nodCurent->info->nrMateriale; i++) {
					printf("%s\n", nodCurent->info->categoriiMateriale[i]);
				}
				printf("\n");
				nodListaSecundara* p = nodCurent->vecini;
				while (p) {
					if (vizitate[p->info->info->cod] == 0) {
						stiva = push(stiva, p->info->info->cod);
						vizitate[p->info->info->cod] = 1;
					}
					p = p->next;
				}
			}
		}
	}
}

int nr(nodListaPrincipala*graf) {
	nodListaPrincipala*temp = graf;
	int nr = 0;
	while (temp) {
		if (temp->info->procentVolum >= 60) {
			nr++;
			}
		temp = temp->next;
	}
	return nr;
}
int* determinareDepozite(nodListaPrincipala*graf) {
	int nrNoduri = calculareNumarNoduri(graf);
	int* iduri = (int*)malloc(sizeof(int)*nr(graf));
	int j = 0;
	nodListaPrincipala*temp = graf;
	int nr = 0;
	while (temp) {
		if (temp->info->procentVolum >= 60) {
			iduri[j] = temp->info->cod;
			j++;
		}
		temp = temp->next;
	}
	return iduri;
}

int nrMateriale(nodListaPrincipala*graf) {
	nodListaPrincipala*temp = graf;
	int nr = 0;
	while (temp) {
		for (int i = 0; i < temp->info->nrMateriale; i++) {
			nr++;
		}
		temp = temp->next;
	}
	return nr;
}
char** determinareMateriale(nodListaPrincipala*graf) {
	char** charsArr = (char**)malloc(sizeof(char*)*nrMateriale(graf));
	int j = 0;
	nodListaPrincipala*temp = graf;
	int nr = 0;
	while (temp) {
		for (int i = 0; i < temp->info->nrMateriale; i++) {
			charsArr[j] = temp->info->categoriiMateriale[i];
			j++;
		}
		temp = temp->next;
	}
	return charsArr;
}

int number(nodListaPrincipala*cap,int value) {
	int nr = 0;
	nodListaPrincipala*temp = cap;
	while (temp) {
		if (temp->vecini) {
			if (temp->vecini->distanta > value) {
				nr+=2;
			}
		}
		temp = temp->next;
	}
	return nr;
}

int nrDepozitePeUnCriteriu(nodListaPrincipala*cap, int value) {
	nodListaPrincipala*temp = cap;
	int nr = 0;
	while (temp) {
		if (temp->info->capacitate == value) {
			nr++;
		}
		temp = temp->next;
	}
	return nr;
}

Depozit** determinareDepozitePeUnCriteriu(nodListaPrincipala*cap, int value) {
	Depozit** vector = (Depozit**)malloc(sizeof(Depozit*)*nrDepozitePeUnCriteriu(cap, value));
	int j = 0;
	nodListaPrincipala*temp = cap;
	while (temp) {
		if (temp->info->capacitate == value) {
			vector[j] = temp->info;
			j++;
		}
		temp = temp->next;
	}
	return vector;
}

int* determinareArce(nodListaPrincipala*cap, int pondere) {
	int* vector = (int*)malloc(sizeof(int)*number(cap,pondere));
	int j = 0;
	while (cap) {
		if (cap->vecini) {
			if (cap->vecini->distanta > pondere) {
				vector[j] = cap->info->cod;
				j++;
				vector[j] = cap->vecini->info->info->cod;
				j++;
			}
		}
		cap = cap->next;
	}
	return vector;
}


void main() {
	nodListaPrincipala* graf = NULL;
	Depozit* d=NULL;
	FILE* f = fopen("fisier.txt", "r");
	char buffer[DIM_BUFFER];
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			d = (Depozit*)malloc(sizeof(Depozit));
			token = strtok(buffer, sep);
			d->cod = atoi(token);
			token = strtok(NULL, sep);
			d->id = (char*)malloc(strlen(token) + 1);
			strcpy(d->id, token);
			token = strtok(NULL, sep);
			d->capacitate = atoi(token);
			token = strtok(NULL, sep);
			d->coordonateGPS = atof(token);
			token = strtok(NULL, sep);
			d->procentVolum = atoi(token);
			token = strtok(NULL, sep);
			d->nrMateriale = atoi(token);
			d->categoriiMateriale = (char**)malloc(sizeof(token)*d->nrMateriale);
			for (int i = 0; i < d->nrMateriale; i++) {
				token = strtok(NULL, sep);
				d->categoriiMateriale[i] = token;
			}
			graf = inserareListaPrincipala(graf, d);
		}
		fclose(f);
	}
	int nrArce = 0;
	printf("Numarul de arce:");
	scanf("%d", &nrArce);
	for (int i = 0; i < nrArce; i++) {
		int idStart = 0;
		printf("Id-ul nodului de start:");
		scanf("%d", &idStart);
		int idStop = 0;
		printf("Id-ul nodului de stop:");
		scanf("%d", &idStop);
		printf("Distanta arcului este:");
		int distanta;
		scanf("%d", &distanta);
		inserareArcInGraf(graf, idStart, idStop, distanta);
	}
	afisareListaPrincipala(graf);

	printf("\n\n");
	int* sir = (int*)malloc(sizeof(int)*nr(graf));
	char** charsArr = (char**)malloc(sizeof(char*)*nrMateriale(graf));
	charsArr = determinareMateriale(graf);
	sir=determinareDepozite(graf);
	for (int i = 0; i < nr(graf); i++) {
		printf("%d ", sir[i]);
	}
	printf("\n\n");
	printf("-----------\n");
	printf("Lista tuturor materialelor din depozit:\n");
	for (int i = 0; i < nrMateriale(graf); i++) {
		printf("%s\n\n", charsArr[i]);
	}

	printf("\n\n");
	int* vector = (int*)malloc(sizeof(int)*number(graf, 110));
	vector = determinareArce(graf, 110);
	for (int i = 0; i < number(graf, 110); i++) {
		printf("%d ", vector[i]);
	}
	printf("\n\n");
	Depozit** vec = (Depozit**)malloc(sizeof(Depozit*)*nrDepozitePeUnCriteriu(graf, 300));
	vec = determinareDepozitePeUnCriteriu(graf, 300);
	for (int i = 0; i < nrDepozitePeUnCriteriu(graf, 300); i++) {
		printf("Cod:%d\nId:%s\nCapacitate:%d\nCoordonate GPS:%.2f\nProcent volum:%d\nNr materiale:%d\n",
			vec[i]->cod, vec[i]->id, vec[i]->capacitate, vec[i]->coordonateGPS, vec[i]->procentVolum, vec[i]->nrMateriale);
		printf("Categorii materiale:\n\n");
		for (int j = 0; j < vec[i]->nrMateriale; j++) {
			printf("%s\n", vec[i]->categoriiMateriale[j]);
		}
		printf("\n");
	}
}