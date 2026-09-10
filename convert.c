#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "apc.h"

int insert_at_last(Dlist **head, Dlist **tail, unsigned char data)
{
    Dlist *new_node = malloc(sizeof(Dlist));
    if (new_node == NULL)
    {
        return FAILURE;
    }

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = *tail;

    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        (*tail)->next = new_node;
        *tail = new_node;
    }

    return SUCCESS;
}

int insert_at_first(Dlist **head, Dlist **tail, unsigned char data)
{
    Dlist *new_node = malloc(sizeof(Dlist));
    if (new_node == NULL)
    {
        return FAILURE;
    }

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = *head;

    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        (*head)->prev = new_node;
        *head = new_node;
    }

    return SUCCESS;
}

int string_to_list(char *str, Dlist **head, Dlist **tail)
{
    if (str == NULL || *str == '\0')
    {
        return FAILURE;
    }

    int i = 0;
    if (str[i] == '+' || str[i] == '-')
    {
        i++;
    }

    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            free_list(head);
            return FAILURE;
        }

        unsigned char digit = str[i] - '0';
        if (insert_at_last(head, tail, digit) == FAILURE)
        {
            free_list(head);
            return FAILURE;
        }

        i++;
    }

    return SUCCESS;
}

int compare_list(Dlist *head1, Dlist *head2)
{
    // Skip leading zero nodes before comparing magnitude
    while (head1 != NULL && head1->data == 0 && head1->next != NULL)
    {
        head1 = head1->next;
    }
    while (head2 != NULL && head2->data == 0 && head2->next != NULL)
    {
        head2 = head2->next;
    }

    int len1 = 0, len2 = 0;
    for (Dlist *t = head1; t != NULL; t = t->next)
    {
        len1++;
    }
    for (Dlist *t = head2; t != NULL; t = t->next)
    {
        len2++;
    }

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data) return 1;
        if (head1->data < head2->data) return -1;
        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}

void print_list(Dlist *head)
{
    if (head == NULL)
    {
        printf("0");
        return;
    }

    Dlist *temp = head;
    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
}

void free_list(Dlist **head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    Dlist *temp = NULL;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}