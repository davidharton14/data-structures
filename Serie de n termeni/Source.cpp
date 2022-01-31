#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
#include<math.h>
#define PI 3.14159265
double find_Solution(double x, int n)
{
	double sum = x, e = 2, o = 1, p = 1;
	double val = 180.0 / PI;
	for (int i = 2; i <= n; i++) {

		// The power to which 'x' is raised
		p += 2;

		sum += (double)(o / e) * (double)(pow(x, p) / p);

		// Numerator value
		o = o * (o + 2);

		// Denominator value
		e = e * (e + 2);
	}
	return atan(sum) * val;
}
void main() {
	int a, b, c;
	double x,y;
	char k1, k2, k3;
	printf("a = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);
	printf("c = ");
	scanf("%d", &c);

	printf("x = ");
	scanf("%lf", &x);
	//printf("y = ");
	//scanf("%.2f", &y);

	//printf("k1 si k2 si k3: ");
	//scanf("%c%c%c", &k1, &k2, &k3);
	//ex1
	double ar=0;
	double p=0;
	if ((a < (b + c)) && (b < (a + c)) && (c < (a + b))) {
		p = (a + b + c) / 2;
		ar = sqrt(p*(p - a)*(p - b)*(p - c));
		printf("\nPerimetru triunghiului este: %lf", p);
		printf("\nAria triunghiului este: %lf", ar);
	}
	//ex2
	printf("\nValoarea aproximativa a lui arctg(x) este: %lf",find_Solution(x, c));
	//ex3
	int i, j, n;

	printf("\nn = ");
	scanf("%d", &n);

	for (i = n; i >=0; i--) {
		int k = 0;
		for (j = n; j > i; j--) {
			printf("%d ", n-k);	
			k++;
		}
		printf("\n");
	}
}