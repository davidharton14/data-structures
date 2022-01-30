#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
#include<math.h>
#include<iomanip>
#define PI 3.14159265
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
	int a, b, c;
	char car1, car2;
	printf("x=");
	scanf("%.2f", &x);
	//printf("y=");
	//scanf("%ld", &y);
	//printf("a=");
	//scanf("%d", &a);
	//printf("b=");
	//scanf("%d", &b);
	//printf("c=");
	//scanf("%d", &c);
	//printf("car1 ");
	//scanf("%c", &car1);
	//printf("car2 ");
	//scanf("%c", &car2);
	double result = 0;
	if (x < 0) {
		result=(pow(2,x) + calculateLnx(x));
		printf("f(x)=%lf", result);
	}
	else if (x == 0) {
		printf("f(x)=0");
	}
	else if (x > 0) {
		result = (sqrt(3 + pow(x, 2)) + cos(x)) / (2 * x);
		printf("f(x)=%lf", result);
	}
	double val = PI / 180.0;
	printf("\n");
	printf("Valorile functie cosinus sunt:\n");
	for (int i = 0; i <= 100; i++) {
		printf("Valoarea functiei cos(%d) este %lf\n", i,cos(i*val));
		
	}
	printf("\n");
		int i, j;
		printf("TRIUNGHIUL DREPTUNGHIC ESTE\n");
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j <= i; j++)
				printf("+");
			printf("\n");
		}
}