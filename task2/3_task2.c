#include <stdio.h>

long rec(long h){
	int x;
	if (h == 0 || h == 1) return h;
	else return rec(h-1) + rec(h-2);
}


long iter(long h){
	int a = 0, b = 1, c;
	for (long i = 0; i < h; ++i)
	{
		c = b;
		b += a;
		a = c;
	}
	return a;
}


int main(){
	long i;
	while (scanf("%ld", &i) != EOF)
	{
		printf("%ld-ое число: \n", i);
		printf("Итеративно %ld \n", iter(i));
		printf("Рекурсивно %ld \n", rec(i));
	}
}
