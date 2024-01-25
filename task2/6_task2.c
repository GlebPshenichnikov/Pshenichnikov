#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *link;
typedef int elemtype;

typedef struct node{
    elemtype  elem;
    link right;
    link left;
}node;

typedef link tree;

void dl(tree tr)
{
    if (tr != NULL)
    {
        dl(tr->right);
        dl(tr->left);
        free(tr);
    }
}

void ptr(tree tr)
{
    if (tr != NULL)
    {
        printf("%d\n", tr->elem);
        ptr(tr->left);
        ptr(tr->right);
        
    }
}

void pls(tree tr, int a){
    if (a > tr->elem){
        if (tr->right == NULL){
            tr->right = (tree) malloc( sizeof(node));
            tr->right->left = NULL;
            tr->right->right = NULL;
            tr->right->elem = a;
        }
        else pls(tr->right, a);
    }
    else
        if (a < tr->elem){
            if (tr->left == NULL){
                tr->left = (tree) malloc( sizeof(node));
                tr->left->left = NULL;
                tr->left->right = NULL;
                tr->left->elem = a;
            }
            else  pls(tr->left, a);
        }
}


void prov(tree tr, int a){
    if (tr->elem < a)
        if (tr->right == NULL)
            printf ("%d no \n", a);
        else
             prov(tr->right, a);
    else
        if (tr->elem > a )
            if ( tr->left == NULL)
                printf ("%d no \n", a);
            else
                 prov(tr->left, a);
        else
            printf ("%d yes \n", a);
}

void obch(tree tr)
{
    tree p = tr->right;
    if (p->left == NULL)
    {
        tr->elem = p->elem;
        tr->right = p->right;
        free(p);
        return;
    }
    while (p->left->left != NULL)
        p = p->left;
    tr->elem = p->left->elem;
    p->left = p->left->right;
    free(p->left);
}

tree kor(tree tr)
{
    tree p = tr;
    if (tr->right == NULL && tr->left == NULL)
    {
        free(p);
        return NULL;
    }
    if (tr->right == NULL)
    {
        tr = tr->left;
        free(p);
        return tr;
    }
    if (tr->left == NULL)
    {
        tr = tr->right;
        free(p);
        return tr;
    }
    obch(tr);
    return tr;
}


void bok(tree q, tree p)
{
    if (q->right == p) q->right = p;
    else q->left = p;
    free(p);
}




tree mins(tree tr, int a)
{
    tree p = tr, q = tr;
    //если удаляемое эл-т в корне
    if (tr->elem == a) return kor(tr);
    
    if (p->elem < a) p = p->right;
    else p = p->left;

    while (p->elem != a)
    {
        if (q->right == p) q = q->right;
        else q = q->left;
        
        if (p->elem < a) p = p->right;
        else p = p->left;
    }
    //удаляемый эл-т лист
    if (p->right == NULL && p->left == NULL)
    {
        if (q->right == p) q->right = NULL;
        else q->left = NULL;
        free(p);
        return tr;
    }

    //у удаляемого элемента нет одного поддерева
    tree s;
    if (p->right == NULL || p->left == NULL)
    {
        if (p->right == NULL) s = p->left;
        else s = p->right;
        if (q->right == p) q->right = s;
        else q->left = s;
        free(p);
        return tr;
    }
    
    //у эл-та есть оба поддерева
    obch(p);
    return tr;
}

int prov2(tree tr, int a)
{
    if (tr == NULL) return 0;
    else
        if (tr->elem == a) return 1;
        else return prov2(tr->left, a) | prov2(tr->right, a);
}


int main(){
    tree tr = NULL;
    char c[255];
    int x, i;
    while (scanf("%s", c) != EOF){
        i = 1;
        x = 0;
        while (c[i] != '\0')
        {
            x = x * 10 + c[i] - '0';
            i++;
        }

        switch(c[0])
        {
            case '+':
                if (tr == NULL){
                    tr = (tree) malloc(sizeof(node));
                    tr->right = NULL;
                    tr->left = NULL;
                    tr->elem = x;
                }
                else pls(tr, x);
                break;
            case '?':
                if (tr == NULL) printf ("%d no \n", x);
                else prov(tr,x);
                break;
            default:
                if (prov2(tr,x) == 1) tr = mins(tr,x);
                else printf("Элемента %d не было в дереве\n", x);
        }
        //ptr(tr);
    }
    dl(tr);
    tr = NULL;
}
