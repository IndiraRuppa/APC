#include <stdio.h>
#include <stdlib.h>
#include "apc.h"
int insert_at_last(Dlist **head,Dlist **tail,unsigned char data) //backward
{
    Dlist *new= malloc(sizeof(Dlist));
    if(new == NULL)
    {
        return 0;
    }
    new->prev=*tail;
    new->data = data;
    new->next=NULL;
    
    if(*head == NULL)
    {
        *head =new;
        *tail = new;
        return 1;
    }
        (*tail)->next=new;
        *tail = new;
         return 1;
    

}
int insert_at_first(Dlist **head,Dlist **tail,unsigned char data)// forward
{
    Dlist *new=malloc(sizeof(Dlist));
    if(new == NULL)
    {
        return 0;
    }
    new->next=*head;
    new->data=data;
    new->prev=NULL;

    if(*head == NULL)
    {
        *head=new;
        *tail = new;
        return 1;
    }
    
      (*head)->prev=new;
        *head=new;
        return 1;
}
int string_to_list(char *str,Dlist **head , Dlist **tail)
{
    int i=0;
    while(str[i]!='\0')
    {
        unsigned char digit=str[i]-'0';
        if(insert_at_last(head,tail,digit)==0)
        {
            return 0;
        }
        i++;
    }
    return 1;
}
int compare_list(Dlist *head1,Dlist *head2)
{
    int len1=0, len2=0;
    // Count length of List 1
    for(Dlist *t=head1;t!=NULL;t=t->next)
    {
        len1++;
    } 
    // Count length of List 2
    for(Dlist *t=head2;t!=NULL;t=t->next)
    {
        len2++;
    }
    // Compare lengths first
    if(len1>len2)
    return 1;
    if(len1<len2)
    return -1;
// Lengths are equal: compare digits
while(head1!=NULL && head2!=NULL)
{
    if(head1->data > head2->data)
    return 1;
    if(head1->data < head2->data)
    return -1;
// Advance pointers to prevent infinite loop
head1 = head1->next;
head2 = head2->next;
}
// Both numbers are equal
return  0;
}
