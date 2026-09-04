#include<stdio.h>
#include<stdlib.h>
#include "apc.h"

int Add(Dlist *head1,Dlist *tail1,Dlist *head2,Dlist *tail2,Dlist **res_head,Dlist **res_tail)
{
    Dlist *temp1=tail1;
    Dlist *temp2=tail2;
    int carry =0;
    while(temp1 !=NULL || temp2!=NULL)
    {
        // Process both lists from tail to head
        int val1= (temp1!=NULL)?temp1->data:0;
        int val2=(temp2!=NULL)?temp2->data:0;

        int sum=val1+val2+carry;
        unsigned char digit= sum%10;
        carry=sum/10;
        // Insert the digit at the front of the result list
        if(insert_at_first(res_head,res_tail,digit)==0)
        {
            return FAILURE;   //memory is not allocated
        }
        // Move pointers toward the head
        if(temp1!=NULL) 
        temp1=temp1->prev;
        if(temp2!=NULL)
        temp2=temp2->prev;
    }
    if(carry > 0)
    {
        if(insert_at_first(res_head,res_tail,(unsigned char)carry)==0)
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}