#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t3_2.h"
#include "t3_3.h"


#define N 5
int c; /*текущий символ */
char **lst; /* список слов (в виде массива)*/
char *buf; /* буфер для накопления текущего слова*/
int sizebuf; /* размер буфера текущего слова*/
int sizelist; /* размер списка слов*/
int curbuf; /* индекс текущего символа в буфере*/
int curlist; /* индекс текущего слова в списке*/
int lg;


char str[N];

int curstr; /* индекс текущего слова в str*/


int main() {
    typedef enum {Start, Word, Greater, Greater2, Newline, Stop} vertex;
    vertex V = Start;
    
    curstr = N;
    
    c = getsym();
    null_list();
    while(1 == 1)
    {
        switch(V)
        {
            case Start:
                if(c == ' '|| c == '\t') c = getsym();
                else if (c == EOF)
                {
                    termlist();
                    if (lst != NULL) printf("\nКол-во слов: %d\n", sizelist - 1);
                    printlist();
                    
                    sort();
                    if (lst != NULL) printf("\nОтсортированный список: %d\n", sizelist - 1);
                    printlist();
                    printf("\n");
                    
                    clearlist();
                    V=Stop;
                }
                else if (c == '\n')
                {
                    termlist();
                    if (lst != NULL) printf("\nКол-во слов: %d\n", sizelist - 1);
                    printlist();
                    
                    sort();
                    if (lst != NULL) printf("\nОтсортированный список: \n");
                    printlist();
                    printf("\n");
                    
                    V = Newline;
                    curstr = N;
                    c = getsym();
                }
                else
                {
                    nullbuf();
                    addsym();
                    V = (c == '>' || c == '|' || c == '&')? Greater: Word;
                    c = getsym();
                }
                break;
                
            case Word:
                if (symset(c))
                {
                    addsym();
                    c = getsym();
                }
                else
                {
                    V = Start;
                    addword();
                }
                break;
                
            case Greater:
                if (c == '>' || c == '|' || c == '&')
                {
                    addsym();
                    c = getsym();
                    V = Greater2;
                }
                else
                {
                    V = Start;
                    addword();
                }
                break;
                
            case Greater2:
                V = Start;
                addword();
                break;
                
            case Newline:
                clearlist();
                V = Start;
                break;
                
            case Stop:
                exit(0);
                break;
        }
    }
}
    
