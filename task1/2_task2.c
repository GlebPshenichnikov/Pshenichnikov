#include <stdio.h>


int main(void){
	unsigned char uc = -1;
	char c = -1;
	int i = uc, k = c;
	if (i == k)
	{	
		printf("Способ представления unsigned\n");
	}
	else
		printf("Способ представления signed\n");

	return 0;
}
