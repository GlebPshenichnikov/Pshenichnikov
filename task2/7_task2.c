#include <stdio.h>
#include <setjmp.h>

jmp_buf begin;     /* начало диалога */
char curlex;   /* текущая лексема */

void getlex(void); /* выделение очередной лексемы */

int expr(void); /* распознание выражения и вычисление его значения */

int add(void); /* распознание слагаемого и вычисление его значения */

int mult(void); /* распознание множителя и вычисление его значения */

void error(); /* сообщение об ошибке в выражении и передача управления в начало функции main (точка begin) */
int st(void);


int main()
 {
     int result;
     setjmp(begin);
     printf("==>");
     getlex();
     result=expr();
     if (curlex != '\n') 
     {
         if (curlex == ')') printf("Нет открывающей скобки");
         error();
     }
     printf("\n%d\n",result);
     return 0;
}

void getlex()
{
    while ( (curlex=getchar()) == ' ');
}

void error(void)
{
    printf("\nОШИБКА!\n");
    while((getchar())!='\n');
    longjmp(begin,0);
}

int expr()
{
    int e=add();
    char c;    
    while (curlex == '+' || curlex == '-')
    {
        c = curlex;
        getlex();
        if (c == '-') e-=add();
        else e+=add();
    }
    return e;
}

int add()
{
    int a=st();
    char c;
    while (curlex == '*' || curlex == '/')
    {
        c = curlex;
        getlex();
        if (c == '*') a*=mult();
        else 
        {
            int w =  mult();
            if (w != 0) a/=w;
            else error();
        }
    }
    return a;
}

int st()
{
    int a=mult();
    int i,v,x = a;
    while (curlex == '^')
    {
        getlex();
        v = st();
        a = 1;
        if (v < 0) error();
        for (i = 1; i <= v; i++)
            a*=x;
    }
    return a;
}

int mult()
{
    int m;
    switch(curlex){
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
            m = curlex-'0';
            break;
        case '(':
            getlex();
            m=expr();
            if (curlex == ')') break;
      /* иначе ошибка - нет закрывающей скобки */
        default :
            printf("Нет закрвающей скобки");
            error();
  }
  getlex();
  return m;
}



