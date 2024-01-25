#include <stdio.h>

double x,a,ans;

int main(){
	scanf("%lf %lf", &x, &ans);
	while (scanf("%lf", &a) != EOF)
	{
		ans *= x;
		ans += a;
	}
	printf("%.10g \n", ans);
}

