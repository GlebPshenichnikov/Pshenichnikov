#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>

#define SIZE 10

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("ОШИБКА нет файлов");
        return 1;
    }
    int x;
    char *name1 = argv[1], *name2 = argv[2];
    int len1 = 0, len2 = 0;

    int f1, f2;
    if ((f1 = open(name1, O_RDONLY)) == -1)
    {
        printf("cp: %s: No such file or directory\n", name1);
        free(name1);
        free(name2);
        return 0;
    }
    f2 = open(name2, O_WRONLY | O_CREAT | O_TRUNC);

    char buf[SIZE];
    int n;
    while ((n =read(f1, buf, SIZE * sizeof(char))) > 0)
        write(f2, buf, n);

    //изменение прав доступа
    struct stat statv1;
    lstat(name1, &statv1);

    fchmod(f2, statv1.st_mode);


    close(f1);
    close(f2);
}

/*
    O_CREAT создает файл, если он не существует
    O_TRUNC стирает данные  файла, устанавливая размер файла равным нулю
    O_WRONLY открывает файл для записи.
*/