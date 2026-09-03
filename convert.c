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
