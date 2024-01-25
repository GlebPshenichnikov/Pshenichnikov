#define SIZE 16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int c; /*текущий символ */
extern char **lst; /* список слов (в виде массива)*/
extern char *buf; /* буфер для накопления текущего слова*/
extern int sizebuf; /* размер буфера текущего слова*/
extern int sizelist; /* размер списка слов*/
extern int curbuf; /* индекс текущего символа в буфере*/
extern int curlist; /* индекс текущего слова в списке*/
void nullbuf() //удаление буфера
{
    //free(buf);
    buf = NULL;
    sizebuf = 0;
    curbuf = 0;
}

void addsym() //добавление символа в буфер
{
if (curbuf > sizebuf - 1)
        buf = realloc(buf, sizebuf += SIZE);/* увеличиваем буфер при необходимости */
    buf[curbuf++] = c;
}

void addword()//добавление буфера в список
{
if (curbuf > sizebuf - 1)
        buf = realloc(buf, sizebuf += 1); /* для записи ’\0’ увеличиваем буфер при необходимости  */
    buf[curbuf++] = '\0';
    /*выравниваем используемую память точно по размеру слова*/
    buf = realloc(buf,sizebuf = curbuf);
if (curlist > sizelist - 1)
    lst = realloc(lst, (sizelist += SIZE) * sizeof(*lst)); /* увеличиваем массив под список при необходимости */
    lst[curlist++] = buf;
}

