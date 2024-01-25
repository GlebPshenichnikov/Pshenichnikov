#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>

#include <time.h>

struct dirent *readdir(DIR *dir);
struct dirent *drnt;

char *kot; //имя каталога, из которого вызвалась функция ls
char *hod;
int lenhod;

//определение текущего каталога
char* name() 
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
    return buf;
}

//создание списка из файлов/каталогов
char **ls(int *k, DIR *dr)
{
    int n = 0;
    char **lst;//список из файлов/каталогов текущего каталога
    lst = NULL;
    int ind = 0;
    while((drnt = readdir(dr)))
    {
        if(strcmp(drnt->d_name, ".") != 0 &&
        strcmp(drnt->d_name, "..") != 0 && 
        strcmp(drnt->d_name, ".DS_Store") != 0)
        {
            lst = realloc(lst, (++n) * sizeof(*lst));
            lst[ind++] = drnt->d_name;
        }
    }
    lst = realloc(lst, (++n) * sizeof(*lst));
    lst[ind] = NULL;

    *k = n;
    // сортировка списка
    if (lst == NULL) return NULL;
    int ans;
    char *tmp;
    for (int i = n - 2; i >= 0; i--)
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
    return lst;
}

//вывод списка
void prt(char **lst, int n)
{
    int i;
    if (lst == NULL) return;
    for (i = 0; i < n - 1; i++)
        printf("%s   ",lst[i]);
}


//определние типа файла
void display_file_type ( int st_mode ) 
{                                   
    switch ( st_mode & S_IFMT )
    {
        case S_IFDIR:  putchar ( 'd' ); return;
        case S_IFCHR:  putchar ( 'c' ); return;
        case S_IFBLK:  putchar ( 'b' ); return;
        case S_IFREG:  putchar ( '-' ); return;
        case S_IFLNK:  putchar ( 'l' ); return;
        case S_IFSOCK: putchar ( 's' ); return;
    }
} 

//определние прав доступа
void display_permission ( int st_mode )
{
  static const char xtbl[10] = "rwxrwxrwx";
  char     amode[10];
  int      i, j;
 
  for ( i = 0, j = ( 1 << 8 ); i < 9; i++, j >>= 1 )
    amode[i] = ( st_mode&j ) ? xtbl[i]: '-';
  if ( st_mode & S_ISUID )   amode[2]= 's';
  if ( st_mode & S_ISGID )   amode[5]= 's';
  if ( st_mode & S_ISVTX )   amode[8]= 't';
  amode[9]='\0';
  printf ( "%s ",amode );
}


//случай флага -l / -g/
void lsl(char** lst, int n, int x)
{
    struct stat statv;
    struct passwd *pw_d; //для имени пользователя
    struct group *gr; //для имени группы
    char  *mv[12];
    mv[0] = "янв";
    mv[1] = "фкв";
    mv[2] = "мар";
    mv[3] = "апр";
    mv[4] = "май";
    mv[5] = "июнь";
    mv[6] = "июль";
    mv[7] = "авг";
    mv[8] = "сен";
    mv[9] = "окт";
    mv[10] = "ноя";
    mv[11] = "дек";
    struct tm *t; //для времени
    for (int i = 0; i < n - 1; i++)
    {
        lstat(lst[i], &statv);
        //тип и права
        display_file_type (statv.st_mode);
        display_permission (statv.st_mode);
        printf(" ");

        //кол-во жестких ссылок
        printf("%d", statv.st_nlink);
        printf(" ");

        //имя владельца
        if (x == 'l')
        {
            pw_d = getpwuid ( statv.st_uid );
            printf("%s", pw_d->pw_name);
            printf("  ");
        }
        else if (x == 'p')
        {
            printf("%d  ", statv.st_uid);
        }

        //имя группы
        gr = getgrgid ( statv.st_gid );
        printf("%s", gr->gr_name);
        printf(" ");

        //размер
        printf("%7lld", statv.st_size);
        printf(" ");

        //дата
        t = gmtime(&statv.st_mtime);
        if (t -> tm_mday < 10) printf("0");
        printf("%d", t -> tm_mday); //день
        printf(" ");
        printf("%s", mv[t -> tm_mon]);//месяц
        printf(" ");

        if (t -> tm_hour < 10) printf("0");
        printf("%d", t -> tm_hour); //час
        printf(":");
        if (t -> tm_min < 10) printf("0");
        printf("%d", t -> tm_min); //минуты
        printf(" ");

        //печать имени файла
        printf("%s", lst[i]);
        printf("\n");
    }
}



void rl(DIR *dr)
{
    DIR *kr;
    printf("./%s:\n", hod);
    char **lst;//список из файлов/каталогов текущего каталога
    int n;
    char *med;//промежуточный каталог
    lst = NULL;

    int *k;
    k = (int*) malloc (sizeof(int));
    lst = ls(k, dr);
    n = *k;
    free(k);
    //prt(lst,n);
    lsl(lst,n,'l');

    printf("\n\n");

    int i;
    med = name(); //промежуточный каталог
    for (i = 0; i < n - 1; i++)
    {
        if (chdir(lst[i]) == 0)
        {
            char *temphod;
            temphod = (char*) malloc ((lenhod) * sizeof(char));
            strcpy(temphod, hod);
            int templen = lenhod;

            hod[lenhod-1] = '/';
            lenhod = lenhod + 1 + strlen(lst[i]);
            hod = realloc(hod, lenhod * sizeof(char));
            strcat(hod, lst[i]);
            char *po = name();

            kr = opendir(po);
            rl(kr);
            closedir(kr);

            free(po);
            free(hod);

            chdir(med);

            hod = (char*) malloc ((templen) * sizeof(char));
            lenhod = templen;
            strcpy(hod, temphod);
            free(temphod);
        }
    }
    free(lst);
    lst = NULL;
    free(med);
}


void lg(DIR *dr)
{
    DIR *kr;
    printf("./%s:\n", hod);
    char **lst;//список из файлов/каталогов текущего каталога
    int n;
    char *med;//промежуточный каталог
    lst = NULL;

    int *k;
    k = (int*) malloc (sizeof(int));
    lst = ls(k, dr);
    n = *k;
    free(k);
    //prt(lst,n);
    lsl(lst,n,'g');

    printf("\n\n");

    int i;
    med = name(); //промежуточный каталог
    for (i = 0; i < n - 1; i++)
    {
        if (chdir(lst[i]) == 0)
        {
            char *temphod;
            temphod = (char*) malloc ((lenhod) * sizeof(char));
            strcpy(temphod, hod);
            int templen = lenhod;

            hod[lenhod-1] = '/';
            lenhod = lenhod + 1 + strlen(lst[i]);
            hod = realloc(hod, lenhod * sizeof(char));
            strcat(hod, lst[i]);
            char *po = name();

            kr = opendir(po);
            lg(kr);
            closedir(kr);

            free(po);
            free(hod);

            chdir(med);

            hod = (char*) malloc ((templen) * sizeof(char));
            lenhod = templen;
            strcpy(hod, temphod);
            free(temphod);
        }
    }
    free(lst);
    lst = NULL;
    free(med);
}
// случай флага -R
void lsr(DIR *dr)
{
    DIR *kr;
    printf("./%s:\n", hod);
    char **lst;//список из файлов/каталогов текущего каталога
    int n;
    char *med;//промежуточный каталог
    lst = NULL;

    int *k;
    k = (int*) malloc (sizeof(int));
    lst = ls(k, dr);
    n = *k;
    free(k);
    prt(lst,n);
    printf("\n\n");

    int i;
    med = name(); //промежуточный каталог
    for (i = 0; i < n - 1; i++)
    {
        if (chdir(lst[i]) == 0)
        {
            char *temphod;
            temphod = (char*) malloc ((lenhod) * sizeof(char));
            strcpy(temphod, hod);
            int templen = lenhod;

            hod[lenhod-1] = '/';
            lenhod = lenhod + 1 + strlen(lst[i]);
            hod = realloc(hod, lenhod * sizeof(char));
            strcat(hod, lst[i]);
            char *po = name();

            kr = opendir(po);
            lsr(kr);
            closedir(kr);

            free(po);
            free(hod);

            chdir(med);

            hod = (char*) malloc ((templen) * sizeof(char));
            lenhod = templen;
            strcpy(hod, temphod);
            free(temphod);
        }
    }
    free(lst);
    lst = NULL;
    free(med);
}



int main(int argc, char** argv)
{
    //определение текущего каталога
    char* kot = name();


    //основная часть
    DIR *dr, *pr;
    char **lst; //список из файлов/каталогов текущего каталога
    int n; // кол-во файлов в каталоге
    int x;
    dr = opendir(kot);
    if (argc == 1) x = '\n';
    if (argc == 2) 
    {
        x = argv[1][1];
        if (x != 'l' && x != 'R' && x != 'g' && x != 'p')
        {
            x = '\n';
        }
    }
    if (argc == 3)
    {
        if (argv[1][1] == 'l' || argv[2][1] == 'l') x = 'x';
        if (argv[1][1] == 'g' || argv[2][1] == 'g') x = 'y';
        if (argv[1][1] == 'g' && argv[2][1] == 'l') x = 'g';
        if (argv[1][1] == 'l' && argv[2][1] == 'g') x = 'g';
    }

    if (argc == 4) x = 'y';



    if (x == '\n')
    {
        int *k;
        k = (int*) malloc (sizeof(int));
        lst = ls(k, dr);
        n = *k;
        free(k);
        prt(lst,n);
        printf("\n");
    }
    else
    {
        if (x == 'R')
        {
            int *k;
            k = (int*) malloc (sizeof(int));
            lst = ls(k, dr);
            n = *k;
            free(k);
            prt(lst,n);

            printf("\n\n");
            int i;
            for (i = 0; i < n - 1; i++)
            {
                if (chdir(lst[i]) == 0)
                {

                    lenhod = strlen(lst[i]) + 1;
                    hod = (char*) malloc ((lenhod) * sizeof(char));
                    strcpy(hod, lst[i]);

                    char *po;
                    po = name();

                    pr = opendir(po);
                    lsr(pr);
                    closedir(pr);

                    free(po);
                    free(hod);

                    chdir(kot);
                }
            }  
        }
        else if (x == 'l' || x == 'g' || x == 'p')
        {
            int *k;
            k = (int*) malloc (sizeof(int));
            lst = ls(k, dr);
            n = *k;
            free(k);
            
            lsl(lst,n, x);
        }
        else if (x == 'x')
        {
            int *k;
            k = (int*) malloc (sizeof(int));
            lst = ls(k, dr);
            n = *k;
            free(k);
            //prt(lst,n);
            lsl(lst,n,'l');

            printf("\n\n");
            int i;
            for (i = 0; i < n - 1; i++)
            {
                if (chdir(lst[i]) == 0)
                {

                    lenhod = strlen(lst[i]) + 1;
                    hod = (char*) malloc ((lenhod) * sizeof(char));
                    strcpy(hod, lst[i]);

                    char *po;
                    po = name();

                    pr = opendir(po);
                    rl(pr);
                    closedir(pr);

                    free(po);
                    free(hod);

                    chdir(kot);
                }
            }  
        }
        else if (x == 'y')
        {
            int *k;
            k = (int*) malloc (sizeof(int));
            lst = ls(k, dr);
            n = *k;
            free(k);
            //prt(lst,n);
            lsl(lst,n,'g');

            printf("\n\n");
            int i;
            for (i = 0; i < n - 1; i++)
            {
                if (chdir(lst[i]) == 0)
                {

                    lenhod = strlen(lst[i]) + 1;
                    hod = (char*) malloc ((lenhod) * sizeof(char));
                    strcpy(hod, lst[i]);

                    char *po;
                    po = name();

                    pr = opendir(po);
                    lg(pr);
                    closedir(pr);

                    free(po);
                    free(hod);

                    chdir(kot);
                }
            }  
        }

    }
    free(kot);
    closedir(dr);     
    free(lst);
}

/*
struct stat 
{
   dev_t    st_dev;     // идентификатор файловой системы
   ino_t    st_ino;     // номер индексного дескриптора файла
   u_short  st_mode;    // содержит тип файла и флаги доступа
   short    st_nlink;   // значение счетчика жестких связей
   uid_t    st_uid;     // идентификатор владельца файла
   gid_t    st_gid;     // идентификатор группы
   dev_t    st_rdev;    // содержит старший и младший номера устройства
   off_t    st_size;    // размер файла в байтах
   time_t   st_atime;   // время последнего доступа
   time_t   st_mtime;   // время последней модификации
   time_t   st_ctime;   // время последнего изменения индексного дескриптора
};
 

struct group {
    char    *gr_name;        //название группы 
    char    *gr_passwd;      //пароль группы 
    gid_t   gr_gid;          // идентификатор группы 
    char    **gr_mem;        // члены группы 
};

struct passwd
{
    char *pw_name;    // имя пользователя
    char *pw_passwd;  // пароль
    int   pw_uid;     // идентификатор пользователя
    int   pw_gid;     // идентификатор группы
    char *pw_dir;     // домашний каталог пользователя
    char *pw_shell;   // shell запускаемый после регистрации (по умолчанию "/bin/sh")
};

#define S_IFMT    0170000 // позволяет “вырезать” тип файла
#define S_IFDIR   0040000 // каталог
#define S_IFCHR   0020000 // байт-ориентированный
#define S_IFBLK   0060000 // блок-ориентированный
#define S_IFREG   0100000 // обычный
#define S_IFLNK   0120000 // символическая ссылка
#define S_IFSOCK  0140000 // сокет
#define S_ISUID   0004000 // установка идентификатора пользователя при выполнении (изменяется eUID процесса)
#define S_ISGID   0002000 // установка идентификатора группы при выполнении (изменяется eGID процесса)
#define S_ISVTX   0001000 // для обычного файла - сохранить текст программы (машинный код) в ОП после завершения процесса;

struct tm {
    int tm_sec; //сек
    int tm_min; //мин
    int tm_hour; //час
    int tm_mday; //день
    int tm_mon; //месяц
    int tm_year; //год
    int tm_wday; //день недели
    int tm_yday; //день года 0-365
    int tm_isdst; //летнее время
};
*/