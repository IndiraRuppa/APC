#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int Mul(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    // Handle multiplication by zero[cite: 5]
    if ((head1->data == 0 && head1->next == NULL) || (head2->data == 0 && head2->next == NULL))
    {
        return insert_at_first(res_head, res_tail, 0);
    }

    Dlist *temp2 = tail2; 
    Dlist *R_res_head = NULL, *R_res_tail = NULL;
    int zero = 0;

    while (temp2 != NULL)
    {
        Dlist *r1_head = NULL, *r1_tail = NULL; 
        int carry = 0;

        // 1. MUST use insert_at_last to append trailing zeros at LSB (tail)[cite: 4, 5]
        for (int i = 0; i < zero; i++)
        {
            if (insert_at_last(&r1_head, &r1_tail, 0) == FAILURE)
            {
                free_list(&r1_head);
                free_list(&R_res_head);
                return FAILURE;
            }
        }

        // 2. Multiply tail1 digits with temp2->data[cite: 5]
        Dlist *temp1 = tail1;
        while (temp1 != NULL)
        {
            int prod = (temp1->data * temp2->data) + carry;
            unsigned char digit = prod % 10;
            carry = prod / 10;

            // Prepend product digits at MSB (head)[cite: 4, 5]
            if (insert_at_first(&r1_head, &r1_tail, digit) == FAILURE)
            {
                free_list(&r1_head);
                free_list(&R_res_head);
                return FAILURE;
            }

            temp1 = temp1->prev;
        }

        // 3. Prepend remaining carry at MSB (head)[cite: 5]
        if (carry > 0)
        {
            if (insert_at_first(&r1_head, &r1_tail, (unsigned char)carry) == FAILURE)
            {
                free_list(&r1_head);
                free_list(&R_res_head);
                return FAILURE;
            }
        }

        // 4. Add partial product to running total[cite: 5]
        if (R_res_head == NULL)
        {
            R_res_head = r1_head;
            R_res_tail = r1_tail;
        }
        else
        {
            Dlist *r2_head = NULL, *r2_tail = NULL;

            if (Add(R_res_head, R_res_tail, r1_head, r1_tail, &r2_head, &r2_tail) == FAILURE)
            {
                free_list(&r1_head);
                free_list(&R_res_head);
                return FAILURE;
            }

            free_list(&R_res_head);
            free_list(&r1_head);

            R_res_head = r2_head;
            R_res_tail = r2_tail;
        }

        temp2 = temp2->prev;
        zero++;
    }

    *res_head = R_res_head;
    *res_tail = R_res_tail;

    return SUCCESS;
}