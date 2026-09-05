#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int Sub(Dlist *head1,Dlist *tail1,Dlist *head2,Dlist *tail2,Dlist **res_head,Dlist **res_tail)
{
    // Determine which number is larger
    int cmp=compare_list(head1,head2);
    int is_negative=0;
    Dlist *temp1=NULL;
    Dlist *temp2=NULL;
    if(cmp>=0)
    {
        // Oper1 >= Oper2: result is positive
        temp1= tail1;
        temp2=tail2;
        is_negative=0;
    }
    else
    {
        // Oper1 >= Oper2: result is positive,esult is negative
        temp1=tail2;
        temp2=tail1;
         is_negative=1;
    }
    int borrow=0;
    // Digit-by-digit subtraction from tail to head
    while(temp1!=NULL )
    {
        int val1,val2;
       val1= temp1->data- borrow;
        if(temp2!=NULL)
        {
          val2=temp2->data;
        }
        borrow=0;
        if(val1 < val2)
        {
            val1 += 10;
            borrow=1;// Borrow from higher digit of temp1
        }
        int diff =val1 -val2;
        if(insert_at_first(res_head,res_tail,(unsigned char)diff)==0)
        {
            return FAILURE;
        }
        temp1=temp1->prev;
        if(temp2!=NULL)
        {
            temp2=temp2->prev;
        }
    }
        while(*res_head && (*res_head)->data ==0 && (*res_head)->next !=NULL)
        {
            Dlist *del=*res_head;
            *res_head=(*res_head)->next;
            (*res_head)->prev=NULL;
            free(del);
        }
    return is_negative;
}