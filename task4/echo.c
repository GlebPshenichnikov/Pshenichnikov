#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ind, n;
char *buf;
int len;


void viv(int f, int argc, char **argv)
{
    switch(f)
    {
        case '=':
            printf("%s", argv[1]);
            for (int i = 2; i < argc; i++)
            {
                printf(" %s", argv[i]);
            }   
            printf("\n");
            break;
        
        case 'n':
            printf("%s", argv[2]);
            for (int i = 3; i < argc; i++)
            {
                printf(" %s", argv[i]);
            }   
            break;
        
        case 'e':
            for (int i = 2; i < argc; i++)
            {
                int len = strlen(argv[i]);
                char x, y;
                int j;
                for (j = 0; j <= len; j++)
                {
                    x = argv[i][j];
                    if (x == '\\')
                    {
                        if (++j > len) break;
                        y = argv[i][j];
                        if (y == 'n') putchar('\n');
                        else if (y == 'b') putchar('\b');
                        else if (y == 'f') putchar('\f');
                        else if (y == 'r') putchar('\r');
                        else if (y == 't') putchar('\t');
                        else if (y == 'v') putchar('\v');
                        else if (y == 'a') putchar('\a');
                        else putchar('\\');
                    }
                    putchar(argv[i][j]);
                }
                if (i != argc - 1) putchar(' ');
            }   
            printf("\n");
            break;

        case 'E':
            for (int i = 2; i < argc; i++)
            {
                int len = strlen(argv[i]);
                char x, y;
                int j;
                for (j = 0; j <= len; j++)
                {
                    x = argv[i][j];
                    if (x == '\\')
                    {
                        if (++j > len) break;
                        y = argv[i][j];
                        if (y == 'n') printf("\\n");
                        else if (y == 'b') printf("\\b");
                        else if (y == 'f') printf("\\f");
                        else if (y == 'r') printf("\\r");
                        else if (y == 't') printf("\\t");
                        else if (y == 'v') printf("\\v");
                        else if (y == 'a') printf("\\a");
                        else printf("\\");
                        continue;
                    }
                    putchar(argv[i][j]);
                }
                if (i != argc - 1) putchar(' ');
            }   
            printf("\n");
            break;
        case 'm':
            for (int i = 3; i < argc; i++)
            {
                int len = strlen(argv[i]);
                char x, y;
                int j;
                for (j = 0; j <= len; j++)
                {
                    x = argv[i][j];
                    if (x == '\\')
                    {
                        if (++j > len) 
                        {
                            putchar('\\');
                            break;
                        }
                        y = argv[i][j];
                        if (y == 'n') putchar('\n');
                        else if (y == 'b') putchar('\b');
                        else if (y == 'f') putchar('\f');
                        else if (y == 'r') putchar('\r');
                        else if (y == 't') putchar('\t');
                        else if (y == 'v') putchar('\v');
                        else if (y == 'a') putchar('\a');
                        else putchar('\\');
                    }
                    putchar(argv[i][j]);
                }
                if (i != argc - 1) putchar(' ');
            }   
            //printf("\n");
            break;
        case 'y':
            for (int i = 3; i < argc; i++)
            {
                int len = strlen(argv[i]);
                char x, y;
                int j;
                for (j = 0; j <= len; j++)
                {
                    x = argv[i][j];
                    if (x == '\\')
                    {
                        if (++j > len) break;
                        y = argv[i][j];
                        if (y == 'n') printf("\\n");
                        else if (y == 'b') printf("\\b");
                        else if (y == 'f') printf("\\f");
                        else if (y == 'r') printf("\\r");
                        else if (y == 't') printf("\\t");
                        else if (y == 'v') printf("\\v");
                        else if (y == 'a') printf("\\a");
                        else printf("\\");
                        continue;
                    }
                    putchar(argv[i][j]);
                }
                if (i != argc - 1) putchar(' ');
            }   
           // printf("\n");
            break;
        
    }
}

    //'n' -n ; 'e'  -e; 'E' -E; 'm' -e -n; 'y' -E -n 

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("\n");
        return 0;
    }
    char flag = '='; //юез флага

    if (argc == 2)
    {
        if (strcmp(argv[1], "-n") == 0) return 0;

        if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-E") == 0) 
        {
            printf("\n");
            return 0;
        }

        printf("%s\n", argv[1]);
        return 0;
    }

    //'n' -n ; 'e'  -e; 'E' -E; 'm' -e -n; 'y' -E -n 
    if (strcmp(argv[1], "-n") == 0 && strcmp(argv[2], "-e") == 0  ||  strcmp(argv[2], "-n") == 0 && strcmp(argv[1], "-e") == 0)
    {
        viv('m', argc, argv);
        return 0;
    }

    if (strcmp(argv[1], "-n") == 0 && strcmp(argv[2], "-E") == 0  ||  strcmp(argv[2], "-n") == 0 && strcmp(argv[1], "-E") == 0)
    {
        viv('y', argc, argv);
        return 0;
    }

    if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-E") == 0)
    {
        viv(argv[1][1], argc, argv);
        return 0;
    }

    viv('=', argc, argv);
    return 0;



}   