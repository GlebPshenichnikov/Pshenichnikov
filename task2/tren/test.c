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
    //printf("%d \n", 99);
    if (a > tr->elem){
        if (tr->right == NULL){
            tr->right = (tree) malloc( sizeof(node));
            tr->right->elem = a;
            tr->right->left = NULL;
            tr->right->right = NULL;
        }
        else  pls(tr->right, a);
    }
    else
        if (a < tr->elem){
            if (tr->left == NULL){
                tr->left = (tree) malloc( sizeof(node));
                tr->left->elem = a;
                tr->left->left = NULL;
                tr->left->right = NULL;
            }
            else  pls(tr->left, a);
        }
}


void prov(tree tr, int a){
    if (tr->elem < a)
        if ( tr->right == NULL)
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


tree rn(tree tr){
    if (tr->right == NULL){
        //найти минимальное в правом поддереве
        if (tr->right->left != NULL)
        {
            tr = tr->right;
            while (tr->left->left != NULL)
                tr = tr -> left;
        }
    }
    else{
            //найти максимальное в левом поддереве
            if (tr->left->right != NULL)
            {
                tr = tr->left;
                while (tr->right->right != NULL)
                    tr = tr -> right;
            }
        }
    return tr;
}

link seat(tree p, int a)
{
    link q;
   // printf("%d", 99);
    if (p->right != NULL && p->left != NULL)
    {
        if (a > p->elem)
            q = seat(p->right, a);
        if (a < p->elem)
            q = seat(p->left, a);
        if (a == p->elem)
            q = p;
    }
    
    
    if (p->left == NULL && p->right != NULL )
    {
        if (p->right->elem != a)
            q = seat(p->right, a);
        else
            q = p;
    }
    
    if (p->right == NULL && p->left != NULL)
    {
        if (p->left->elem != a)
            q = seat(p->right, a);
        else
            q = p;
    }
    return q;

}

void mins(tree tr, int a){
    link p, q, g, s;
    p = tr;
    q = tr;
    if (p->elem != a){
       // printf("%d", 4);
        /*
        while (p->right->elem != a && p->left->elem != a)
            if (a > p->elem)
                p = p->right;
            else
                p = p->left;
         */
        p = seat(tr, a);
        printf("%d", p->elem);
        if (p->right->elem == a){
            if (p->right->right == NULL && p->right->left == NULL){
                //если нет обоих потомков
                q = p->right;
                free(q);
                p->right = NULL;
            }
            else
            {
                g = rn(p->right);
                if (g->right->right == NULL)
                {
                    p->right->elem = g->right->elem;
                    s = g->right;
                    g->right = g->right->left;
                    free(s);
                }
                else
                {
                    p->right->elem = g->left->elem;
                    s = g->left;
                    g->left = g->left->right;
                    free(s);
                }
            }
        }
        else
        {
            if (p->left->right == NULL && p->left->left == NULL){
                //если нет обоих потомков
                q = p->left;
                free(q);
                p->left = NULL;
            }
            else
            {
                g = rn(p->left);
                if (g->right->right == NULL)
                {
                    p->left->elem = g->right->elem;
                    s = g->right;
                    g->right = g->right->left;
                    free(s);
                }
                else
                {
                    p->left->elem = g->left->elem;
                    s = g->left;
                    g->left = g->left->right;
                    free(s);
                }
            }
        }
        
    }
    else
        //удалить корень
        if (tr->right == NULL && tr->left == NULL){
            free(tr);
            tr = NULL;
        }
        else
            if (tr->right != NULL)
            {
                q = tr;
                tr->right->left = tr->left;
                free(q);
            }
            else
            {
                q = tr;
                tr->left->right = tr->right;
                free(q);
            }
}


int main(){
    tree tr = NULL;
    char c[255];
    int x, i;
    while (scanf("%s", c) != EOF){
       // printf("%c\n", zn);
        i = 1;
        x = 0;
        while (c[i] != '\0')
        {
            x = x * 10 + c[i] - '0';
            i++;
        }
      //  printf("%c\n", c[0]);
        switch(c[0])
        {
            case '+':
                if (tr == NULL){
                    // printf("%d\n", 66);
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
                //printf("%d\n", 88);
                break;
            default:
                if (tr != NULL)
                    mins(tr,x);
        }
       // ptr(tr);
    }
}










/*
int maximum(tree t)
{
    if (t->rigth == NULL && t->left == NULL)
    {
        return maximum
    }
    else
    {
        if (t->elem > maximum(t->right) && t->elem > maximum(t->left))   return t->elem
        else
            if (maximum(t->right) > t->elem && maximum(t->right)  > maximum(t->left)) return maximum(t->right)
            else
                return maximum(t->left))
    }
}
*/


/*
int count(tree t, int a)
{
    if (t == NULL) return 0;
    else if(t->elem == a)
        return count(t->right, a) + count(t->left, a) + 1
}
*/

/*
int sum(tree t, int a)
{
    if (t == NULL) return 0;
    else return sum(t->right, a) + sum(t->left, a) + a
}
*/

/*
int vh(tree t, int a)
{
    if (t == NULL) return 0;
    else
        if (t->elem = a) return 1;
        else return (vh(t->ight, a) | vh(t->left, a));
}

a | b-  or
a & b- and
a ^ b - xor
a = a << 3
a = a >> 4
~a

Yfnfif
Ukt,
*/

/*
void prt(tree tr)
{
    if (tr != NULL)
        if (tr->right != NULL && tr->left != NULL)
        {
            printf("%d\n", tr->elem);
            prt(tr->right);
            prt(tr->left);
        }
}


int sr(tree t, tree g)
{
    if (t == NULL)
    {
        if (g == NULL) return 1;
        else return 0
    }
    else
        if (g == NULL) return 0;
        else
            if (g->elem == t->elem)
                return sr(t->right, g->right) & sr(t->left, g->left);
            else return 0;
        
}

*/
