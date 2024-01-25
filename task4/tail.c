#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>


int file;
int stop = 1; //идентификатор отсановки при занесении слов в список
char **lst = NULL; //список строк файла
int lenlst = 0; //кол-во строк в файле

//ПОЛУЧЕНИЕ СТРОКИ
char* getbuf()
{
    char *buf = NULL;
    int n = 0;
    int ind = 0;
    char x[1];
    while ((stop = read(file, x, sizeof(char))) > 0)
    {   
        if  (*x == '\n')
        {
            buf = realloc(buf, ++n * sizeof(char));
            buf[ind++] = '\0'; 
            break;
        }
        buf = realloc(buf, ++n * sizeof(char)); 
        buf[ind++] = *x;
    }

    if (stop == 0)
    {
        if (ind != 0)
        {
            buf = realloc(buf, ++n * sizeof(char));
            buf[ind] = '\0'; 
        }
        else return NULL;
    }

    return buf;
}

//ПОЛУЧЕНИЕ СПИСКА ИЗ СТРОК
void getlst()
{
    int indlst = 0;
    while (stop)
    {
        lst = realloc(lst, ++lenlst * sizeof(*lst));
        lst[indlst++] = getbuf();
    }
    if (lst[lenlst - 1] != NULL)
    {
        lst = realloc(lst, ++lenlst * sizeof(*lst));
        lst[indlst] = NULL;
    }
}


//печать списка
void printlist_1(int w) //печать списка
{
    if (lst == NULL) return;
    int i;
    int k = lenlst - w - 1;
    if (k < 0) k = 0;
    for (i = k; i < lenlst - 2; i++)
        printf("%s\n",lst[i]);
    if(lst[lenlst - 2][0] == '\0')
        printf("\n");
    else printf("%s", lst[lenlst - 2]);
}


void printlist_2(int k) //печать списка
{
    int i;
    if (lst == NULL) return;
    if (k == 0) k = 1;
    for (i = k - 1; i < lenlst - 2; i++)
        printf("%s\n",lst[i]);
    if (k > lenlst - 1) return;
    if(lst[lenlst - 2][0] == '\0')
        printf("\n");
    else printf("%s", lst[lenlst - 2]);
}

int main(int argc, char** argv)
{
    int x;
    int i;

    //-n == '-'; +n == '+'; без флага == '='
    char *name = NULL;
    int n = 0;
    int ind = 0;
    int f = '=';
    int ans = 10;

    if (argc == 2)
    {
        int q = strlen(argv[1]) + 1;
        name = realloc(name, q * sizeof(char));
        strcpy(name, argv[1]);
    }

    if (argc == 3)
    {   
        f = argv[1][0];
        ans = 0;
        int q = strlen(argv[1]) - 1;
        for (i = 1; i <= q; i++)
            ans = ans * 10 + argv[1][i] - '0';
        
        q = strlen(argv[2]) + 1;
        name = realloc(name, q * sizeof(char));
        strcpy(name, argv[2]); 
    }

    if ((file = open(name, O_RDONLY)) == -1)
    {
        printf("tail: No such file or directory\n");
        free(name);
        return 0;
    }

    getlst();
    
    switch (f)
    {
        case '=': case '-':
            printlist_1(ans);
            break;
        case '+':
            printlist_2(ans);
            break;
    }


    for (i = 0; i < lenlst - 1; i++)
        free(lst[i]);
    free(lst);

    free(name);
    close(file);
}
