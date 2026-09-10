#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int Add(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    Dlist *t1 = tail1;
    Dlist *t2 = tail2;
    int carry = 0;

    // Process until both lists and carry are completely exhausted
    while (t1 != NULL || t2 != NULL || carry != 0)
    {
        int d1 = (t1 != NULL) ? (int)t1->data : 0;
        int d2 = (t2 != NULL) ? (int)t2->data : 0;

        int sum = d1 + d2 + carry;
        int digit = sum % 10;
        carry = sum / 10;

        // Insert new digit at the head (MSB side)
        if (insert_at_first(res_head, res_tail, (unsigned char)digit) == FAILURE)
        {
            free_list(res_head);
            return FAILURE;
        }

        if (t1 != NULL) t1 = t1->prev;
        if (t2 != NULL) t2 = t2->prev;
    }

    return SUCCESS;
}