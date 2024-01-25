#include <stdio.h>

double x,a,ans,a0,i,n;

int main(){
	scanf("%lf %lf %lf", &n, &x, &ans);
	n += 1;
	i = ans / n;
    double pr = ans;
	while (scanf("%lf", &a) != EOF)
	{	
		n -= 1;
		i *= x;
		i += a/n;
        ans *= x;
        pr *= x;
        pr += ans;
        pr += a;
        ans += a;
        a0 = a;

	}
    
    a = 0;
    for (n = n; n > 1; n--)
    {
        i *= x;
        i += a/n;
        ans *= x;
        pr *= x;
        pr += ans;
        pr += a;
        ans += a;
        a0 = a;
    }

	printf("Многочлен %.10g \n", ans);
    printf("Производая %.10g \n", (pr-ans)/x);
	printf("Интеграл %.10g \n", i * x);
}

