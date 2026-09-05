#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int Mul(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    // Handle multiplication by zero
    if ((head1->data == 0 && head1->next == NULL) || (head2->data == 0 && head2->next == NULL))
    {
        return insert_at_first(res_head, res_tail, 0);
    }

    Dlist *temp2 = tail2; 
    Dlist *R_res_head = NULL, *R_res_tail = NULL;
    int zero = 0;

    while (temp2 != NULL) // Loop till tail2 reaches NULL
    {
        Dlist *r1_head = NULL, *r1_tail = NULL; 
        int carry = 0;

        // Step: Insert positional 'n' zeros to R1
        for (int i = 0; i < zero; i++)
        {
            if (insert_at_first(&r1_head, &r1_tail, 0) == FAILURE)
            {
                free_list(&r1_head);
                free_list(&R_res_head);
                return FAILURE;
            }
        }

        // Loop till tail1 reaches NULL
        Dlist *temp1 = tail1;
        while (temp1 != NULL)
        {
            // Multiply tail1->data * tail2->data + carry
            int prod = (temp1->data * temp2->data) + carry;
            unsigned char digit = prod % 10;
            carry = prod / 10;

            // Store the last digit in R1 (inserting at first to keep order)
            if (insert_at_first(&r1_head, &r1_tail, digit) == FAILURE)
            {
                free_list(&r1_head);
                free_list(&R_res_head);
                return FAILURE;
            }

            // Update temp1 to prev
            temp1 = temp1->prev;
        }

        // If carry remains, prepend it to R1
        if (carry > 0)
        {
            if (insert_at_first(&r1_head, &r1_tail, (unsigned char)carry) == FAILURE)
            {
                free_list(&r1_head);
                free_list(&R_res_head);
                return FAILURE;
            }
        }

        // Add R1 to running sum R -> store in R2
        if (R_res_head == NULL)
        {
            // First iteration: directly set running_res to R1
            R_res_head = r1_head;
            R_res_tail = r1_tail;
        }
        else
        {
            Dlist *r2_head = NULL, *r2_tail = NULL;

            // Perform Add(R_res, r1) -> r2
            if (Add(R_res_head, R_res_tail, r1_head, r1_tail, &r2_head, &r2_tail) == FAILURE)
            {
                free_list(&r1_head);
                free_list(&R_res_head);
                return FAILURE;
            }

            // Free old intermediate lists R and R1
            free_list(&R_res_head);
            free_list(&r1_head);

            // Swap R2 -> R
            R_res_head = r2_head;
            R_res_tail = r2_tail;
        }

        // Update temp2 to prev and increment zeros
        temp2 = temp2->prev;
        zero++;
    }

    // Assign final result pointers
    *res_head = R_res_head;
    *res_tail = R_res_tail;

    return SUCCESS;
}