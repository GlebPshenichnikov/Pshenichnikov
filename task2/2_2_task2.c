#include <stdio.h>

double x,a,ans,pr,a0;

int main(){
	scanf("%lf %lf", &x, &ans);
	pr = ans;
	while (scanf("%lf", &a) != EOF)
	{
		ans *= x;
		pr *= x;
		pr += ans;
		pr += a;
		ans += a;
		a0 = a;
	}
	printf("Многочлен %.10g \n", ans);
	printf("Производая %.10g \n", (pr-ans)/x);
}

