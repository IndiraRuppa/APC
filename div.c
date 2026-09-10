#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int Div(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    // Check for Division by Zero
    if (head2 == NULL || (head2->data == 0 && head2->next == NULL))
    {
        printf("Error: Division by zero!\n");
        return FAILURE;
    }

    Dlist *temp_head = NULL, *temp_tail = NULL;
    Dlist *curr = head1;

    // Traverse through dividend list head1 digit by digit
    while (curr != NULL)
    {
        // 1. store current digit to temp list
        if (insert_at_last(&temp_head, &temp_tail, curr->data) == FAILURE)
        {
            free_list(&temp_head);
            return FAILURE;
        }

        // 2. Remove leading zeros 
        while (temp_head != NULL && temp_head->data == 0 && temp_head->next != NULL)
        {
            Dlist *del = temp_head;
            temp_head = temp_head->next;
            temp_head->prev = NULL;
            free(del);
        }

        // Properly update temp_tail 
        if (temp_head == NULL)
        {
            temp_tail = NULL;
        }
        else
        {
            temp_tail = temp_head;
            while (temp_tail->next != NULL)
            {
                temp_tail = temp_tail->next;
            }
        }

        int count = 0;

        // 3. Repeated subtraction 
        while (temp_head != NULL && compare_list(temp_head, head2) >= 0)
        {
            Dlist *rem_head = NULL, *rem_tail = NULL;

            // subtraction: temp_head - head2
            if (Sub(temp_head, temp_tail, head2, tail2, &rem_head, &rem_tail) == FAILURE)
            {
                free_list(&temp_head);
                return FAILURE;
            }

            // Free previous temp_head and swap with rem_head
            free_list(&temp_head);
            temp_head = rem_head;
            temp_tail = rem_tail;

            count++;
        }

        // 4. Append subtraction count digit to result 
        if (*res_head != NULL || count > 0)
        {
            if (insert_at_last(res_head, res_tail, (unsigned char)count) == FAILURE)
            {
                free_list(&temp_head);
                return FAILURE;
            }
        }

        curr = curr->next;
    }

    free_list(&temp_head);

    // 5. If result list is empty
    if (*res_head == NULL)
    {
        if (insert_at_last(res_head, res_tail, 0) == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}
