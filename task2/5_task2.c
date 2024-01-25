#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node *link;
typedef char elemtype[255];

typedef struct node{
    elemtype elem;
    link next;
}node;

typedef link list;


void print(list p)
{
    while (p != NULL){
        printf("%s ",  p->elem);
        p = p->next;
    }
    printf("\n");
}

list rec(list lst, char a[]){
    if (lst->next != NULL){
        list p;
        list w;
        w = lst;
        while (w->next->next != NULL){
            if (strcmp(a, w->next->elem) == 0){
                p = w->next;
                w->next = w->next->next;
                free(p);
            }
            else w = w->next;
        }
        if (strcmp(a, lst->elem) == 0){
            p = lst;
            lst = lst->next;
            free(p);
        }
    }
    return lst;
}
void del(list l)
{
    list p;
    if (l != NULL)
    {
        p = l;
        l = l->next;
        free(p);
        del(l);
    }
}
    
int main() {
    list lst;
    char a[255];
    list q;
    if (scanf("%s", a) != EOF){
        lst = (link) malloc(sizeof(node));
        q = lst;
        strcpy(q->elem, a);
        lst -> next = (link) malloc(sizeof(node));
        while (scanf("%s", a ) != EOF) {
            strcpy(q -> next -> elem, a);
            q -> next -> next = (link) malloc(sizeof(node));
            q = q -> next;
        }
        free(q -> next);
        q -> next = NULL;
        lst = rec(lst, q->elem);
        print(lst);
        }
    del(lst);
}


