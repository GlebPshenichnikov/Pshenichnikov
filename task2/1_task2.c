#include <stdio.h>


double e, x;

double kor(double x){
	double x1 = 1, x2, s;
	do
	{
		x2 = 0.5 * (x1 + x / x1);
		s = x2 - x1;
		if (s < 0) s *= -1;
		x1 = x2;
	}
	while (s >= e);
	return x2;
}

int main(){
	scanf("%lf", &e);
	while (scanf("%lf", &x) != EOF)
	{
		printf("Корень из %.10g = %.10g \n", x, kor(x));

	}
	
}

