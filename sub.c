#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int sub(Dlist *head1,Dlist *tail1,Dlist *head2,Dlist *tail2,Dlist **res_head,Dlist **res_tail)
{
    int cmp=compare(head1,head2);
    Dlist *temp1=NULL;
    Dlist *temp2=NULL;
    if(cmp>=0)
    {
        temp1= tail1;
        temp2=tail2;
    }
    else
    {
        temp1=tail2;
        temp2=tail1;

    }
}