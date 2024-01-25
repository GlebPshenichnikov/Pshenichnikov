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




int main(){
    tree tr = NULL;
    char c[255];
    int x, i;
    while (scanf("%s", c) != EOF){
       //printf("%c\n", zn);
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
                if (tr == NULL) printf ("NO \n");
                else prov(tr,x);
                //printf("%d\n", 88);
                break;
            default:
                printf("%d\n", 5);
        }
    }
}

