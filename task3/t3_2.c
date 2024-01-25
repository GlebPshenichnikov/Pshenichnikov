#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 16
#define N 5
extern int c; /*текущий символ */
extern char **lst; /* список слов (в виде массива)*/
extern char *buf; /* буфер для накопления текущего слова*/
extern int sizebuf; /* размер буфера текущего слова*/
extern int sizelist; /* размер списка слов*/
extern int curbuf; /* индекс текущего символа в буфере*/
extern int curlist; /* индекс текущего слова в списке*/
extern int lg;

extern char str[N];

extern int curstr; /* индекс текущего слова в str*/



void sort()
{
    if (lst == NULL) return;
    int ans;
    char *tmp;
    for (int i = sizelist - 2; i >= 0; i--)
    {
        ans = 1; //флаг что были переставлены эл-ты
        for (int j = 0; j < i; j++)
        {
            if (strcmp(lst[j], lst[j + 1]) > 0)
            {
                tmp = lst[j];
                lst[j] = lst[j+1];
                lst[j+1] = tmp;
                ans = 0;
            }
        }
        if (ans) break;
    }
}


void clearlist() //удаление спика
{
    int i;
    sizelist = 0;
    curlist = 0;
    if (lst == NULL) return;
    for (i = 0; lst[i] != NULL; i++)
        free(lst[i]);
    free(lst);
    lst = NULL;
}

void null_list() //обнуление списка
{
    sizelist = 0;
    curlist = 0;
    lst = NULL;
}




void termlist() //завершение списка
{
    if (lst == NULL) return;
    if (curlist > sizelist - 1)
            lst = realloc(lst,(sizelist+1)*sizeof(*lst));
    lst[curlist] = NULL;
    /*выравниваем используемую под список память точно по размеру списка*/
    lst = realloc(lst,(sizelist=curlist+1)*sizeof(*lst));
}



void printlist() //печать списка
{
    int i;
    if (lst == NULL) return;
    for (i = 0; i < sizelist - 1; i++)
        printf("%s\n",lst[i]);
}


int symset(int c) //возвращает 1 если любой сивол кроме специальных
{
    return c!='\n' && c!=' ' && c!='\t' && c!='>' && c!= EOF && c!='|' && c!= '<' && c!=')' && c!='(' && c!= '&';
}


int getsym()
{
   // int si;
    if (curstr >= N - 1)
    {
        for (int i = 0; i < N; i++)
            str[i] = '\0';
        scanf("%3[^\n]", str);
        if ((str[3] = getchar()) == EOF) return EOF;
        curstr = 0;
    }
    if (str[curstr] == '\0') //есди мы встретили его то
    {
        
        curstr = N;
        return '\n';
    }
    return str[curstr++];

}


