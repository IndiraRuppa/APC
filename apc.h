#ifndef APC_H
#define APC_H

#include<stdio.h>         //input and output/error
#include<string.h>        //string manipulation functions
#include<stdlib.h>       //Dynamic memory allocation functions
#include<ctype.h>        //character classification functions for conveting digit

#define SUCCESS 1
#define FAILURE 0

typedef struct node
{
 unsigned char data;       //Stores a single numeric digit (0 to 9)
 struct node *prev;    //Pointer to the previous node
 struct node *next;    //Pointer to the next node
}Dlist;  


int  string_to_list(char *str,Dlist **head,Dlist **tail);
int insert_at_first(Dlist **head,Dlist **tail,unsigned char data);
int insert_at_last(Dlist **head,Dlist **tail,unsigned char data);
int compare_list(Dlist *head,Dlist *tail);
void print_list(Dlist *head);
void free_list(Dlist **head);


int Add(Dlist *head1,Dlist *tail,Dlist *head2, Dlist *tail2,Dlist **res_head,Dlist **res_tail);
int Sub(Dlist *head1,Dlist *tail,Dlist *head2, Dlist *tail2,Dlist **res_head,Dlist **res_tail);
int Mul(Dlist *head1,Dlist *tail,Dlist *head2, Dlist *tail2,Dlist **res_head,Dlist **res_tail);
int Div(Dlist *head1,Dlist *tail,Dlist *head2, Dlist *tail2,Dlist **res_head,Dlist **res_tail);

#endif