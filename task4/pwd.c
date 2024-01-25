#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *buf;
    int n;
    n = 2;
    buf = (char*) malloc (n * sizeof(char));
    int i;
    while (1 == 1)
    {
        for (i = 0; i < n; i++) buf[i] = '\0';
        if (getcwd(buf, n) == NULL)
        {
            n++;
            buf = realloc(buf, n * sizeof(char));
        }
        else
            break;
    } 
    printf("%s", buf);
    printf("\n");
    free(buf);
}