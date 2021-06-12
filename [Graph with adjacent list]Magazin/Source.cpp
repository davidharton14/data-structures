#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE_BUFFER 300
#define N 6
struct Magazin {
	int id;
	char* denumire;
	char* localitate;
	float suprafata;
	int nrAngajati;
};

void displayMagazin(Magazin m) {
	printf("Id:%d\nDenumire:%s\nLocalitate:%s\nSuprafata:%.2f\nNr angajati:%d\n\n", m.id, m.denumire, m.localitate, m.suprafata, m.nrAngajati);
}
// Adjascency List representation in C

struct node {
	Magazin m;
	struct node* next;
};
struct node* createNode(int);

struct Graph {
	int numVertices;
	struct node** adjLists;
};

// Create a node
struct node* createNode(int v, Magazin m) {
	struct node* newNode =(struct node*) malloc(sizeof(struct node));
	newNode->m.id = v;
	newNode->m = m;
	newNode->next = NULL;
	return newNode;
}

// Create a graph
struct Graph* createAGraph(int vertices) {
	struct Graph* graph =(struct Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;

	graph->adjLists =(struct node**)malloc(vertices * sizeof(struct node*));

	int i;
	for (i = 0; i < vertices; i++)
		graph->adjLists[i] = NULL;

	return graph;
}

// Add edge
void addEdge(struct Graph* graph,Magazin m, int s, int d) {
	// Add edge from s to d
	struct node* newNode = createNode(d,m);
	newNode->next = graph->adjLists[s];
	graph->adjLists[s] = newNode;

	// Add edge from d to s
	newNode = createNode(s,m);
	newNode->next = graph->adjLists[d];
	graph->adjLists[d] = newNode;
}

// Print the graph
void printGraph(struct Graph* graph) {
	int v;
	int sw = 0;
	for (v = 0; v < graph->numVertices; v++) {
		if (graph->adjLists[v]) {
			struct node* temp = graph->adjLists[v];
			sw = 0;
			node* tmp = temp;
			while (tmp) {
				if (v != tmp->m.id) {
					sw = 1;
				}
				tmp = tmp->next;
			}
			if (sw == 1) {
				printf("\n Vertex %d\n ", v);
				/*displayMagazin(graph->adjLists[v]->m);*/
				printf("\n\n ");
				printf("Nodurile sunt:\n ");
				while (temp) {
					if (v != temp->m.id) {
						/*printf("%d", temp->m.id);*/
						printf("\n");
						displayMagazin(temp->m);
					}
					temp = temp->next;
				}
			}
			printf("\n");
		}
	}
}
float suprafataTotala(struct Graph* graph) {
	float suprafata = 0;
	int sw = 0;
	for (int v = 0; v < graph->numVertices; v++) {
		if (graph->adjLists[v]) {
			struct node* temp = graph->adjLists[v];
			sw = 0;
			node* tmp = temp;
			while (tmp) {
				if (v != tmp->m.id) {
					sw = 1;
				}
				tmp = tmp->next;
			}
			if (sw == 1) {
				while (temp) {
					if (v != temp->m.id) 
					suprafata += temp->m.suprafata;
					temp = temp->next;
				}
			}
		}
	}
	return suprafata;
}

int nr(struct Graph* graph) {
	int nr = 0;
	int sw = 0;
	for (int v = 0; v < graph->numVertices; v++) {
		if (graph->adjLists[v]) {
			struct node* temp = graph->adjLists[v];
			sw = 0;
			node* tmp = temp;
			while (tmp) {
				if (v != tmp->m.id) {
					sw = 1;
				}
				tmp = tmp->next;
			}
			if (sw == 1) {
				while (temp) {
					if (v != temp->m.id) {
						nr++;
					}
					temp = temp->next;
				}
			}
		}
	}
	return nr;
}

float* vectorDeChirii(struct Graph* graph) {
	int j = 0;
	int sw = 0;
	float* vector = (float*)malloc(sizeof(float)*nr(graph));
	for (int v = 0; v < graph->numVertices; v++) {
		if (graph->adjLists[v]) {
			struct node* temp = graph->adjLists[v];
			sw = 0;
			node* tmp = temp;
			while (tmp) {
				if (v != tmp->m.id) {
					sw = 1;
				}
				tmp = tmp->next;
			}
			if (sw == 1) {
				while (temp) {
					if (v != temp->m.id) {
						vector[j] = temp->m.suprafata * 9;
						j++;
					}
					temp = temp->next;
				}
			}
		}
	}
	return vector;
}

void stergereMagazin(struct Graph* graph,int id) {
	int sw = 0;
	for (int v = 0; v < graph->numVertices; v++) {
		if (graph->adjLists[v]) {
			struct node* temp = graph->adjLists[v];
			if (temp->m.id == id) {
				sw = 0;
				node* tmp = temp;
				while (tmp) {
					if (v != tmp->m.id) {
						sw = 1;
					}
					tmp = tmp->next;
				}
				if (sw == 1) {
					printf("\n Vertex %d\n ", v);
					printf("\n\n");
					while (temp) {
						if (v != temp->m.id) {
							//printf("%d", temp->m.id);*/
							printf("\n");
							displayMagazin(temp->m);
						}
						temp = temp->next;
					}
					temp = NULL;
				    graph->adjLists[v] = NULL;
				}
				printf("\n");
			}
		}
	}
}

void modificareAngajati(struct Graph* graph, int id,int nr) {
	int sw = 0;
	for (int v = 0; v < graph->numVertices; v++) {
		if (graph->adjLists[v]) {	
			struct node* temp = graph->adjLists[v];
				sw = 0;
				if (temp->m.id == id) {
					temp->m.nrAngajati = nr;
					graph->adjLists[v]->m.nrAngajati = nr;
					node* tmp = temp;
					while (tmp) {
						if (v != tmp->m.id) {
							sw = 1;
						}
						tmp = tmp->next;
					}
					if (sw == 1) {
						/*printf("\n Vertex %d\n ", v);*/
						displayMagazin(graph->adjLists[v]->m);
						printf("\n\n");
						while (temp) {
							if (v != temp->m.id) {
								//printf("%d", temp->m.id);*/
								printf("\n");
								displayMagazin(temp->m);
							}
							temp = temp->next;
						}
					}
					printf("\n");
				}
		}
	}
}

int main() {
	struct Graph* graph = createAGraph(50);
	Magazin m;
	int k = 0;
	FILE* f = fopen("magazine.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	if (f)
	{
		char* token, separators[] = ",\n";
		while (fgets(buffer, SIZE_BUFFER, f))
		{
			token = strtok(buffer, separators);
			m.id = atoi(token);
			token = strtok(NULL, separators);
			m.denumire = (char*)malloc(strlen(token) + 1);
			strcpy(m.denumire, token);
			token = strtok(NULL, separators);
			m.localitate = (char*)malloc(strlen(token) + 1);
			strcpy(m.localitate, token);
			token = strtok(NULL, separators);
			m.suprafata = atof(token);
			token = strtok(NULL, separators);
			m.nrAngajati = atoi(token);
			if(23!=m.id)
			addEdge(graph,m, 23, m.id);
			else 
			addEdge(graph, m, 15, m.id);
			/*addEdge(graph, m, 15, 23);
			addEdge(graph,m,23, 15);
			addEdge(graph, m, 23, 30);
			addEdge(graph, m, 23, 42);*/

		}
		fclose(f);
	}
	printGraph(graph);
	printf("\n\n\n");
	//ex3
	/*printf("Suprafata totala a magazinelor este:%.2f", suprafataTotala(graph));*/

	//ex4
	/*float* vector = (float*)malloc(sizeof(float)*nr(graph));
	vector = vectorDeChirii(graph);
	printf("Vectorul de chirii este:");
	for (int i = 0; i < nr(graph); i++) {
		printf("%.2f ", vector[i]);
	}*/

	//ex5
	/*stergereMagazin(graph, 23);*/
	/*printGraph(graph);*/

	//ex6
	modificareAngajati(graph, 23, 100);
	/*printGraph(graph);*/
	
}
