#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
#include<math.h>
#include<ctype.h>
using namespace std;
float calculateLnx(double n)
{

	float num, mul, cal, sum = 0;
	num = (n - 1) / (n + 1);

	// terminating value of the loop
	// can be increased to improve the precision
	for (int i = 1; i <= 1000; i++) {
		mul = (2 * i) - 1;
		cal = pow(num, mul);
		cal = cal / mul;
		sum = sum + cal;
	}
	sum = 2 * sum;
	return sum;
}
void main() {
	double x, y;
	int a, b, c, sw = 0;
	char car1, car2;
	printf("car1 si car2");
	scanf("%c%c", &car1, &car2);
	printf("x=");
	scanf("%lf", &x);
	//printf("y=");
	//scanf("%ld", &y);
	printf("a=");
	scanf("%d", &a);
	printf("b=");
	scanf("%d", &b);
	printf("c=");
	scanf("%d", &c);
	printf("\n");
	int suma = 0;
	int produs = 1;
	int r = 0;
	for (int i = 1; i <= a; i++) {
		suma += i;
	}
	for (int i = 1; i <= a; i++) {
		produs *= i;
	}
	printf("SUMA PRIMELOR A NUMERE ESTE %d\n", suma);
	printf("PRODUSUL PRIMELOR A NUMERE ESTE %d", produs);
	printf("\n");
	if (isalpha(car1)) {
		sw = 1;
	}
	if (sw) {
		car1 = car1 - 32;
		printf("CARACTERUL CAR1 ESTE LITERA!\n");
		printf("%c", car1);
	}
	printf("\n");
	int n, sw1 = 0, sw2 = 0, sw3 = 0;
	printf("n=");
	scanf("%d", &n);
	if (a < n) {
		sw1 = 1;
	}
	if (b < n) {
		sw2 = 1;
	}
	if (c < n) {
		sw3 = 1;
	}
	int aux_a = 0, aux_b = 0, aux_c = 0;
	if (sw1&&sw2&&sw3) {
		while(a<n&&b<n&&c<n) {
			aux_a = a; aux_b = b; aux_c = c;
			r = aux_a % aux_b;
			while (r != 0)
			{
				aux_a = aux_b;
				aux_b = r;
				r = aux_a % aux_b;
			}
			r = aux_b % aux_c;
			while (r != 0)
			{
				aux_b = aux_c;
				aux_c = r;
				r = aux_b % aux_c;
			}
			if(aux_c!=1)
			printf("CMMDC DINTRE %d,%d si %d este %d\n",a,b,c,aux_c);
			a++; b++; c++;     
		}
	}
	printf("\n");
	if (sw2&&sw3) {
		while (b < n&&c < n) {
			aux_b = b;
			aux_c = c;
			while (aux_b != aux_c)
			{
				if (aux_b > aux_c)
					aux_b = aux_b - aux_c;
				else
					aux_c = aux_c - aux_b;
			}
			if(aux_c!=1)
				printf("CMMDC DINTRE %d si %d este %d\n", b, c, aux_c);
			b++; c++;
		}
	}
	printf("\n");
	printf("TASTEAZA CARACTERE\n");
	char caracter;
	int ca = 2;
	while (ca<=127) {
		scanf("%c", &caracter);
		ca = caracter;
		if(ca!=10)
		printf("Caracterul %c are codul ASCII %d\n",caracter, ca);
	}
}
