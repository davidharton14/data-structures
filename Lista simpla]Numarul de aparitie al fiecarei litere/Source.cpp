#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIM_BUFFER 300
struct Propozitie {
	char* sir;
	int nrA,nrB,nrC,nrD,nrE,nrF,nrG,nrH,nrI,nrJ,nrK,nrL,nrM,nrN,nrO,nrP,nrQ,
		nrR,nrS,nrT,nrU,nrW,nrX,nrY,nrZ;
};

struct Nod {
	Propozitie* info;
	Nod* next;
};

void afisarePropozitie(Propozitie* p) {
	printf("Propozitia este:%s\n",p->sir);
	if(p->nrA!=0)
		printf("Numarul de litere cu A : %d\n",p->nrA);
	if(p->nrB!=0)
		printf("Numarul de litere cu B : %d\n",p->nrB);
	if (p->nrC!=0)
		printf("Numarul de litere cu C : %d\n", p->nrC);
	if (p->nrD != 0)
		printf("Numarul de litere cu D : %d\n", p->nrD);
	if (p->nrE != 0)
		printf("Numarul de litere cu E : %d\n", p->nrE);
	if (p->nrF != 0)
		printf("Numarul de litere cu F : %d\n", p->nrF);
	if (p->nrG != 0)
		printf("Numarul de litere cu G : %d\n", p->nrG);
	if (p->nrH != 0)
		printf("Numarul de litere cu H : %d\n", p->nrH);
	if (p->nrI != 0)
		printf("Numarul de litere cu I : %d\n", p->nrI);
	if (p->nrJ != 0)
		printf("Numarul de litere cu J : %d\n", p->nrJ);
	if (p->nrK != 0)
		printf("Numarul de litere cu H : %d\n", p->nrK);
	if (p->nrL != 0)
		printf("Numarul de litere cu L : %d\n", p->nrL);
	if (p->nrM != 0)
		printf("Numarul de litere cu M : %d\n", p->nrM);
	if (p->nrN != 0)
		printf("Numarul de litere cu N : %d\n", p->nrN);
	if (p->nrO != 0)
		printf("Numarul de litere cu O : %d\n", p->nrO);
	if (p->nrP != 0)
		printf("Numarul de litere cu P : %d\n", p->nrP);
	if (p->nrQ != 0)
		printf("Numarul de litere cu Q : %d\n", p->nrQ);
	if (p->nrR != 0)
		printf("Numarul de litere cu R : %d\n", p->nrR);
	if (p->nrS != 0)
		printf("Numarul de litere cu S : %d\n", p->nrS);
	if (p->nrT != 0)
		printf("Numarul de litere cu T : %d\n", p->nrT);
	if (p->nrU != 0)
		printf("Numarul de litere cu U : %d\n", p->nrU);
	if (p->nrW != 0)
		printf("Numarul de litere cu W : %d\n", p->nrW);
	if (p->nrX != 0)
		printf("Numarul de litere cu X : %d\n", p->nrX);
	if (p->nrY != 0)
		printf("Numarul de litere cu Y : %d\n", p->nrY);
	if (p->nrZ != 0)
		printf("Numarul de litere cu Z : %d\n", p->nrZ);
}

void push(Nod** head_ref, Propozitie* info)
{
	Nod* new_node = (Nod*)malloc(sizeof(Nod));
	new_node->info = info;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;

}

void parcurgereLista(Nod* cap) {
	Nod* temp = cap;
	while (temp) {
		afisarePropozitie(temp->info);
		temp = temp->next;
	}
}
void main() {
	Propozitie* p = NULL;
	Nod* lista = NULL;
	//char* str=NULL;
	char str[50];
	/*str = (char*)malloc(strlen("asdasdasdasdasdasdasdasdasdasdasd")+1);*/
	printf("Enter a String: ");
	scanf("%[^\n]", str);
	int nrA=0, nrB=0, nrC=0, nrD=0, nrE=0, nrF=0, nrG=0, nrH=0, 
		nrI=0, nrJ=0, nrK=0, nrL=0, nrM=0, nrN=0, nrO=0, nrP=0, nrQ=0,
		nrR=0, nrS=0, nrT=0, nrU=0, nrW=0, nrX=0, nrY=0, nrZ=0;
	p = (Propozitie*)malloc(sizeof(Propozitie));
	p->sir = str;
	for (int i = 0; str[i] != '\0';i++) {
			if (str[i] == 'a' || str[i] == 'A')
				nrA++;
			else if (str[i] == 'b' || str[i] == 'B')
				nrB++;
			else if (str[i] == 'c' || str[i] == 'C')
				nrC++;
			else if (str[i] == 'd' || str[i] == 'D')
				nrD++;
			else if (str[i] == 'e' || str[i] == 'E')
				nrE++;
			else if (str[i] == 'f' || str[i] == 'F')
				nrF++;
			else if (str[i] == 'g' || str[i] == 'G')
				nrG++;
			else if (str[i] == 'h' || str[i] == 'H')
				nrH++;
			else if (str[i] == 'i' || str[i] == 'I')
				nrI++;
			else if (str[i] == 'j' || str[i] == 'J')
				nrJ++;
			else if (str[i] == 'k' || str[i] == 'K')
				nrK++;
			else if (str[i] == 'l' || str[i] == 'L')
				nrL++;
			else if (str[i] == 'm' || str[i] == 'M')
				nrM++;
			else if (str[i] == 'n' || str[i] == 'N')
				nrN++;
			else if (str[i] == 'o' || str[i] == 'O')
				nrO++;
			else if (str[i] == 'p' || str[i] == 'P')
				nrP++;
			else if (str[i] == 'q' || str[i] == 'Q')
				nrQ++;
			else if (str[i] == 'r' || str[i] == 'R')
				nrR++;
			else if (str[i] == 's' || str[i] == 'S')
				nrS++;
			else if (str[i] == 't' || str[i] == 'T')
				nrT++;
			else if (str[i] == 'u' || str[i] == 'U')
				nrU++;
			else if (str[i] == 'w' || str[i] == 'W')
				nrW++;
			else if (str[i] == 'x' || str[i] == 'X')
				nrX++;
			else if (str[i] == 'y' || str[i] == 'Y')
				nrY++;
			else if (str[i] == 'z' || str[i] == 'Z')
				nrZ++;
	}
	p->nrA = nrA;p->nrB = nrB;p->nrC = nrC;p->nrD = nrD;
	p->nrE = nrE;p->nrF = nrF;p->nrG = nrG;p->nrH = nrH;
	p->nrI = nrI;p->nrJ = nrJ;p->nrK = nrK;p->nrL = nrL;
	p->nrM = nrM;p->nrN = nrN;p->nrO = nrO;p->nrP = nrP;
	p->nrQ = nrQ;p->nrR = nrR;p->nrS = nrS;p->nrT = nrT;
	p->nrU = nrU;p->nrW = nrW;p->nrX = nrX;p->nrY = nrY;
	p->nrZ = nrZ;
	push(&lista, p);
	parcurgereLista(lista);	
}

