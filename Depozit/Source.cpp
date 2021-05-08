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
};

struct nodListaPrincipala {
	nodListaSecundara*vecini;
	Depozit info;
	nodListaPrincipala*next;
};

nodListaPrincipala*inserareListaPrincipala(nodListaPrincipala* cap, Depozit d) {
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


nodListaSecundara* inserareListaSecundara(nodListaSecundara*cap, nodListaPrincipala* info) {
	nodListaSecundara* nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
	nou->info = info;
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
	while (cap && cap->info.cod != id) {
		cap = cap->next;
	}
	return cap;
}
void inserareArcInGraf(nodListaPrincipala* graf, int idStart, int idStop) {
	if (graf) {
		nodListaPrincipala*nodStart = cautareDupaID(graf, idStart);
		nodListaPrincipala*nodStop = cautareDupaID(graf, idStop);
		if (nodStart && nodStop) {
			nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
			nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
		}
	}
}

void afisareListaSecundara(nodListaSecundara* cap) {
	while (cap) {
		printf("Cod:%d\nId:%s\nCapacitate:%d\nCoordonate GPS:%.2f\nProcent volum:%d\nNr materiale:%d\n",
			cap->info->info.cod,cap->info->info.id,cap->info->info.capacitate,cap->info->info.coordonateGPS,cap->info->info.procentVolum,cap->info->info.nrMateriale);
		printf("Categorii materiale:\n\n");
		for (int i = 0; i < cap->info->info.nrMateriale; i++) {
			printf("%s\n", cap->info->info.categoriiMateriale[i]);
		}
		printf("\n");
		cap = cap->next;
	}
}

void afisareListaPrincipala(nodListaPrincipala*cap) {
	while (cap) {
		printf("NODURILE:\n\nCod:%d\nId:%s\nCapacitate:%d\nCoordonate GPS:%.2f\nProcent volum:%d\nNr materiale:%d\n",
			cap->info.cod, cap->info.id,cap->info.capacitate, cap->info.coordonateGPS,cap->info.procentVolum, cap->info.nrMateriale);
		printf("Categorii materiale:\n\n");
		for (int i = 0; i < cap->info.nrMateriale; i++) {
			printf("%s\n", cap->info.categoriiMateriale[i]);
		}
		printf("\n");
		printf("AU URMATORII VECINI:\n");
		afisareListaSecundara(cap->vecini);
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
		//1. ne luam o stiva si un vector de vizitate cu toate nodurile nevizitate
		//2. inseram nodul de start in stiva si il vizitam
		//3. extragem din stiva un nod - nod curent
		//4. afisam/procesare nodul curent
		//5. inseram in stiva nodurile adiacente nevizitate ale nodului curent si le marcam ca vizitate
		//6. revenim la pasul 3

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
					nodCurent->info.cod, nodCurent->info.id, nodCurent->info.capacitate, nodCurent->info.coordonateGPS,nodCurent->info.procentVolum, nodCurent->info.nrMateriale);
				printf("Categorii materiale:\n\n");
				for (int i = 0; i < nodCurent->info.nrMateriale; i++) {
					printf("%s\n", nodCurent->info.categoriiMateriale[i]);
				}
				printf("\n");

				nodListaSecundara* p = nodCurent->vecini;
				while (p) {
					if (vizitate[p->info->info.cod] == 0) {
						stiva = push(stiva, p->info->info.cod);
						vizitate[p->info->info.cod] = 1;
					}
					p = p->next;
				}
			}
		}
	}
}

int nr(nodListaPrincipala*graf, int idNodStart) {
	int nrNoduri = calculareNumarNoduri(graf);
	int nr = 0;
	if (graf) {
		nodStiva* stiva = NULL;
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
				if (nodCurent->info.procentVolum >= 60) {
					nr++;
				}
				
				nodListaSecundara* p = nodCurent->vecini;
				while (p) {
					if (vizitate[p->info->info.cod] == 0) {
						stiva = push(stiva, p->info->info.cod);
						vizitate[p->info->info.cod] = 1;
					}
					p = p->next;
				}
			}
		}
	}
	return nr;
}
int* determinareDepozite(nodListaPrincipala*graf, int idNodStart) {
	int nrNoduri = calculareNumarNoduri(graf);
	int* iduri = (int*)malloc(sizeof(int)*nr(graf, idNodStart));
	int j = 0;
	if (graf) {
		nodStiva* stiva = NULL;
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
				if (nodCurent->info.procentVolum >= 60) {
					iduri[j] = nodCurent->info.procentVolum;
					j++;
				}

				nodListaSecundara* p = nodCurent->vecini;
				while (p) {
					if (vizitate[p->info->info.cod] == 0) {
						stiva = push(stiva, p->info->info.cod);
						vizitate[p->info->info.cod] = 1;
					}
					p = p->next;
				}
			}
		}
	}
	return iduri;
}

int nrMateriale(nodListaPrincipala*graf, int idNodStart) {
	int nrNoduri = calculareNumarNoduri(graf);
	int nr = 0;
	if (graf) {
		nodStiva* stiva = NULL;
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
				for (int i = 0; i < nodCurent->info.nrMateriale; i++) {
					nr++;
				}
				nodListaSecundara* p = nodCurent->vecini;
				while (p) {
					if (vizitate[p->info->info.cod] == 0) {
						stiva = push(stiva, p->info->info.cod);
						vizitate[p->info->info.cod] = 1;
					}
					p = p->next;
				}
			}
		}
	}
	return nr;
}
char** determinareMateriale(nodListaPrincipala*graf, int idNodStart) {
	int nrNoduri = calculareNumarNoduri(graf);
	char** charsArr = (char**)malloc(sizeof(char*)*nrMateriale(graf, idNodStart));
	int j = 0;
	if (graf) {
		nodStiva* stiva = NULL;
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
				for (int i = 0; i < nodCurent->info.nrMateriale; i++) {
					charsArr[j] = nodCurent->info.categoriiMateriale[i];
					j++;
				}

				nodListaSecundara* p = nodCurent->vecini;
				while (p) {
					if (vizitate[p->info->info.cod] == 0) {
						stiva = push(stiva, p->info->info.cod);
						vizitate[p->info->info.cod] = 1;
					}
					p = p->next;
				}
			}
		}
	}
	return charsArr;
}

void main() {
	nodListaPrincipala* graf = NULL;
	Depozit d;
	FILE* f = fopen("depozite.txt", "r");
	char buffer[DIM_BUFFER];
	if (f) {
		char* token, sep[] = ",";
		while (fgets(buffer, DIM_BUFFER, f)) {
			token = strtok(buffer, sep);
			d.cod = atoi(token);
			token = strtok(NULL, sep);
			d.id= (char*)malloc(strlen(token) + 1);
			strcpy(d.id, token);
			token = strtok(NULL, sep);
			d.capacitate = atoi(token);
			token = strtok(NULL, sep);
			d.coordonateGPS = atof(token);
			token = strtok(NULL, sep);
			d.procentVolum = atoi(token);
			token = strtok(NULL, sep);
			d.nrMateriale = atoi(token);
			d.categoriiMateriale = (char**)malloc(sizeof(token)*d.nrMateriale);
			for (int i = 0; i < d.nrMateriale; i++) {
				token = strtok(NULL, sep);
				d.categoriiMateriale[i] = token;
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
		inserareArcInGraf(graf, idStart, idStop);
	}
	/*afisareListaPrincipala(graf);*/
	//parcurgereAdancime(graf, 5);
	/*printf("-----------\n");*/
	int* sir = (int*)malloc(sizeof(int)*nr(graf,5));
	char** charsArr = (char**)malloc(sizeof(char*)*nrMateriale(graf, 5));
	charsArr = determinareMateriale(graf, 5);
	/*printf("\n\n\n%d", nr(graf, 5));*/
	/*sir=determinareDepozite(graf, 5);
	for (int i = 0; i < nr(graf, 5); i++) {
		printf("%d ", sir[i]);
	}*/
	/*printf("Nr materiale:%d", nrMateriale(graf, 5));*/
	printf("Lista tuturor materialelor din depozit:\n");
	for (int i = 0; i < nrMateriale(graf, 5); i++) {
		printf("%s\n\n", charsArr[i]);
	}
}