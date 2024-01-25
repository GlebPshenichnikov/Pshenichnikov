#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

int file;
int stop = 1; //идентификатор отсановки при занесении слов в список
char **lst = NULL; //список строк файла
int lenlst = 0; //кол-во строк в файле

//переменные для -f
char **smlst = NULL;
char *smbuf;

//переменные для -n
char **zel = NULL; //массив из целых
char **drob = NULL; //массив из дробных частей
char *bufz; //целая часть
char *bufdr; //дробная часть



//ПОЛУЧЕНИЕ СТРОК

//получение строки файла для "без флага" и -r
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


//получение строки файла для -f
char* getbufsf()
{
    char *buf = NULL;
    int n = 0;
    int ind = 0;
    char x[1];
    smbuf = NULL;
    while ((stop = read(file, x, sizeof(char)) > 0))
    {
        if  (*x == '\n')
        {
            buf = realloc(buf, ++n * sizeof(char));
            buf[ind] = '\0'; 

            smbuf = realloc(smbuf, n * sizeof(int));
            smbuf[ind++] = '\0';
            break;
        }
        buf = realloc(buf, ++n * sizeof(char));
        buf[ind] = *x;

        smbuf = realloc(smbuf, n * sizeof(char));
        smbuf[ind++] = tolower(*x);
    }

    
    if (stop == 0)
    {
        if (ind != 0)
        {
            buf = realloc(buf, ++n * sizeof(char));
            buf[ind] = '\0'; 

            smbuf = realloc(smbuf, n * sizeof(int));
            smbuf[ind] = '\0';
        }
        else return NULL;
    }
    return buf;
}


//получение строки файла для -n
char* getbuf_n()
{
    bufz = NULL;
    bufdr = NULL;
    char *buf = NULL;

    int bind = 0;
    int bn = 0;

    int zn = 0;
    int zind = 0;

    int drn = 0;
    int drind = 0;

    int f = 1; //если 1 - находимся в целой части, если 0 - в дробной 
    char x[1];

    while ((stop = read(file, x, sizeof(char))) > 0 && *x == ' ')
    {
        buf = realloc(buf, ++bn * sizeof(char));
        buf[bind++] = *x;
    }

    if (stop == 0) return NULL;

    if (*x == '\n')
    {
        buf = realloc(buf, ++bn * sizeof(char));
        buf[bind] = '\0';

        zn += 2;
        bufz = realloc(bufz, zn * sizeof(char));
        bufz[zind++] = '\0';
        bufz[zind] = '\0';

        bufdr = realloc(bufdr, ++drn * sizeof(char));
        bufdr[drind] = '\0';
        
        return buf;
    }

    if (*x == '-') 
    {
        buf = realloc(buf, ++bn * sizeof(char));
        buf[bind++] = '-';

        bufz = realloc(bufz, ++zn * sizeof(char));
        bufz[zind++] = '-';
    }
    else if (*x == '.' || *x == ',')
    {
        f = 0;
        bufz = realloc(bufz, ++zn * sizeof(char));
        bufz[zind++] = '+';

        buf = realloc(buf, ++bn * sizeof(char));
        buf[bind++] = *x;
    }
    else
    {
        bufz = realloc(bufz, ++zn * sizeof(char));
        bufz[zind++] = '+';
        lseek(file, -1, SEEK_CUR);
    }

    while ((stop = read(file, x, sizeof(char))) > 0)
    {
        if (*x == '\n')
        {
            buf = realloc(buf, ++bn * sizeof(char));
            buf[bind] = '\0';

            bufz = realloc(bufz, ++zn * sizeof(char));
            bufz[zind] = '\0';

            bufdr = realloc(bufdr, ++drn * sizeof(char));
            bufdr[drind] = '\0';
            break;
        }
        if (*x == '.' || *x == ',') 
        {
            buf = realloc(buf, ++bn * sizeof(char));
            buf[bind++] = *x;
            f = 0;
            continue;
        }
        if (f == 1)
        {
            bufz = realloc(bufz, ++zn * sizeof(char));
            bufz[zind++] = *x;   
        }
        else
        {
            bufdr = realloc(bufdr, ++drn * sizeof(char));
            bufdr[drind++] = *x;  
        }
        buf = realloc(buf, ++bn * sizeof(char));
        buf[bind++] = *x;
    }


    if (stop == 0)
    {
        buf = realloc(buf, ++bn * sizeof(char));
        buf[bind] = '\0';

        bufz = realloc(bufz, ++zn * sizeof(char));
        bufz[zind] = '\0';

        bufdr = realloc(bufdr, ++drn * sizeof(char));
        bufdr[drind] = '\0';
    }
    
    return buf;
}



//ПОЛУЧЕНИЕ СПИСКА ИЗ СТРОК

//получение списка из строк файла для "без флага" и -r
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


//получение списка из строк файла для -f
void getlstf()
{
    int indlst = 0;
    while (stop)
    {
        lst = realloc(lst, ++lenlst * sizeof(*lst));
        lst[indlst] = getbufsf();

        smlst = realloc(smlst, lenlst * sizeof(*smlst));
        smlst[indlst++] = smbuf;

    }

    if (lst[lenlst - 1] != NULL)
    {
        lst = realloc(lst, ++lenlst * sizeof(*lst));
        lst[indlst] = NULL;

        smlst = realloc(smlst, lenlst * sizeof(*smlst));
        smlst[indlst] = NULL;

    } 
}

//получение списка из строк файла для -n
void getlst_n()
{
    int indlst = 0;
    while (stop)
    {
        lst = realloc(lst, ++lenlst * sizeof(*lst));
        lst[indlst] = getbuf_n();

        zel = realloc(zel, lenlst * sizeof(*zel));
        zel[indlst] = bufz;

        drob = realloc(drob, lenlst * sizeof(*drob));
        drob[indlst++] = bufdr;
    }

    if (lst[lenlst - 1] != NULL)
    {
        lst = realloc(lst, ++lenlst * sizeof(*lst));
        lst[indlst] = NULL;

        zel = realloc(zel, lenlst * sizeof(*zel));
        zel[indlst] = NULL;

        drob = realloc(drob, lenlst * sizeof(*drob));
        drob[indlst] = NULL;

    } 
}


//СОРТИРОВКИ

//сортировка для случая без флага
void sort() 
{
    if (lst == NULL) return;
    int ans;
    char *tmp;
    for (int i = lenlst - 2; i >= 0; i--)
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

//сортировка для случая флага -r
void sortr() 
{
    if (lst == NULL) return;
    int ans;
    char *tmp;
    for (int i = lenlst - 2; i >= 0; i--)
    {
        ans = 1; //флаг что были переставлены эл-ты
        for (int j = 0; j < i; j++)
        {
            if (strcmp(lst[j], lst[j + 1]) < 0)
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


//сортировка для случая флага -f
void sortf() 
{
    if (lst == NULL) return;
    int ans;
    char *tmp;
    for (int i = lenlst - 2; i >= 0; i--)
    {
        ans = 1; //флаг что были переставлены эл-ты
        for (int j = 0; j < i; j++)
        {
            if (strcmp(smlst[j], smlst[j + 1]) > 0)
            {
                tmp = lst[j];
                lst[j] = lst[j+1];
                lst[j+1] = tmp;

                tmp = smlst[j];
                smlst[j] = smlst[j+1];
                smlst[j+1] = tmp;

                ans = 0;
            }
        }
        if (ans) break;
    }
}


//сортировка для случая -n

void sw(int j)
{
    char *tmp;
    
    tmp = lst[j];
    lst[j] = lst[j+1];
    lst[j+1] = tmp;

    tmp = zel[j];
    zel[j] = zel[j+1];
    zel[j+1] = tmp;

    tmp = drob[j];
    drob[j] = drob[j+1];
    drob[j+1] = tmp;

}

void sort_n()
{
    if (lst == NULL) return;
    int ans;
    char a1, a2;
    for (int i = lenlst - 2; i >= 0; i--)
    {
        ans = 1; //флаг что были переставлены эл-ты
        for (int j = 0; j < i; j++)
        {
            //знаки чисел
            a1 = zel[j][0];
            a2 = zel[j + 1][0];

            //числа разных знаков или пустая строка
            if (a1 == '+' && (a2 == '-' || a2 == '\0'))
            {
                sw(j);
                ans = 0;
                continue;
            }
            //пустая строка и число с  '-'
            if (a1 == '\0' && a2 == '-')
            {
                sw(j);
                ans = 0;
                continue;
            }
            
            //оба числа имеют знак '+'
            if (a1 == '+' && a2 == '+')
            {
                //целая часть первого большего второго
                if (strlen(zel[j]) > strlen(zel[j + 1]))
                {
                    sw(j);
                    ans = 0;
                    continue;
                }
                //целые части равны по длине
                if (strlen(zel[j]) == strlen(zel[j + 1]))
                {
                    // целая часть первого по значению больше второго
                    if (strcmp(zel[j], zel[j + 1]) > 0)
                    {
                        sw(j);
                        ans = 0;
                        continue;
                    }

                    //целые части равны и по длине и по значению
                    if (strcmp(zel[j], zel[j + 1]) == 0)
                    {
                        //дробная часть первого по значению больше второго
                        if (strcmp(drob[j], drob[j + 1]) > 0)
                        {
                            sw(j);
                            ans = 0;
                            continue;
                        }
                    }
                }
            }

             //оба числа имеют знак '-'
            if (a1 == '-' && a2 == '-')
            {
                //целая часть первого меньше второго
                if (strlen(zel[j]) < strlen(zel[j + 1]))
                {
                    sw(j);
                    ans = 0;
                    continue;
                }
                //целые части равны по длине
                if (strlen(zel[j]) == strlen(zel[j + 1]))
                {
                    // целая часть первого по значению меньше второго
                    if (strcmp(zel[j], zel[j + 1]) < 0)
                    {
                        sw(j);
                        ans = 0;
                        continue;
                    }

                    //целые части равны и по длине и по значению
                    if (strcmp(zel[j], zel[j + 1]) == 0)
                    {
                        //дробная часть первого по значению меньше второго
                        if (strcmp(drob[j], drob[j + 1]) < 0)
                        {
                            sw(j);
                            ans = 0;
                            continue;
                        }
                    }
                }
            }
        }
        if (ans) break;
    }
}


//сортировка для случая +n
void sort_noall(int k)
{
    if (lst == NULL) return;
    int ans;
    char *tmp;
    for (int i = lenlst - 2; i > k; i--)
    {
        ans = 1; //флаг что были переставлены эл-ты
        for (int j = k; j < i; j++)
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


//печать списка
void printlist() //печать списка
{
    int i;
    if (lst == NULL) return;
    for (i = 0; i < lenlst - 1; i++)
        printf("%s\n",lst[i]);
}


int main(int argc, char** argv)
{
    int x;
    int i;
    int ans;



    //-r == r; -f == f; -n == n; +n == m; без флага == '-'
    char *name = NULL;
    int n = 0;
    int ind = 0;
    int f = '-';
    if (argc == 1) return 1;

   if (argc == 2)
   {
        int q = strlen(argv[1]) + 1;
        name = realloc(name, q * sizeof(char));
        strcpy(name, argv[1]);
   }
   if (argc == 3)
   {
        if (argv[1][0] == '+')
        {
            f = 'm';
            ans = 0;
            int q = strlen(argv[1]) - 1;
            for (i = 1; i <= q; i++)
                ans = ans * 10 + argv[1][i] - '0';
        }
        else if(argv[1][0] == '-')
        {
            if (strlen(argv[1]) >= 2)
                f = argv[1][1]; 
        }
        int q = strlen(argv[2]) + 1;
        name = realloc(name, q * sizeof(char));
        strcpy(name, argv[2]); 
   }


    if ((file = open(name, O_RDONLY)) == -1)
    {
        printf("sort: No such file or directory\n");
        free(name);
        return 0;
    }

    //-r == r; -f == f; -n == n; +n == m; без флага == '-'
    switch (f)
    {
        case '-':
            getlst();
            sort();
            break;
        case 'r':
            getlst();
            sortr();
            break;
        case 'f':
            getlstf();
            sortf();
            
            for (i = 0; i < lenlst - 1; i++)
                free(smlst[i]);
            free(smlst);

            break;
        
        case 'n':
            getlst_n();
            sort_n();

            for (i = 0; i < lenlst - 1; i++)
                free(drob[i]);
            free(drob);

            for (i = 0; i < lenlst - 1; i++)
                free(zel[i]);
            free(zel);

            break;
        case 'm':
            getlst();
            sort_noall(ans);
            break;
    }

    printlist();

    for (i = 0; i < lenlst - 1; i++)
        free(lst[i]);
    free(lst);

    free(name);
    close(file);
}