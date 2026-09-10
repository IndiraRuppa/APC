#include <stdio.h>
#include <stdlib.h>
#include "apc.h"
#include "validation.h"

int main(int argc, char *argv[])
{
    // Step 1: Validate input arguments
    if (validate_args(argc, argv) == FAILURE)
    {
        return FAILURE;
    }

    char *n1 = argv[1];
    char op = argv[2][0];
    char *n2 = argv[3];

    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *res_head = NULL, *res_tail = NULL;

    // Step 2: Convert operand strings to doubly linked lists
    if (string_to_list(n1, &head1, &tail1) == FAILURE ||
        string_to_list(n2, &head2, &tail2) == FAILURE)
    {
        printf("Error: Failed to convert operands to lists.\n");
        free_list(&head1);
        free_list(&head2);
        return FAILURE;
    }

    int status = SUCCESS;
    int is_negative = 0;

    // Calculate result sign for multiplication/division upfront
    int sign1 = (n1[0] == '-') ? -1 : 1;
    int sign2 = (n2[0] == '-') ? -1 : 1;
    int overall_sign = ((sign1 == -1) ^ (sign2 == -1)) ? -1 : 1;

    // Step 3: Perform arithmetic operations
 switch (op)
    {
        case '+':
            if (sign1 == sign2)
            {
                status = Add(head1, tail1, head2, tail2, &res_head, &res_tail);
                is_negative = (sign1 == -1);
            }
            else
            {
                if (compare_list(head1, head2) >= 0)
                {
                    status = Sub(head1, tail1, head2, tail2, &res_head, &res_tail);
                    is_negative = (sign1 == -1);
                }
                else
                {
                    status = Sub(head2, tail2, head1, tail1, &res_head, &res_tail);
                    is_negative = (sign2 == -1);
                }
            }
            break;

        case '-':
            if (sign1 != sign2)
            {
                status = Add(head1, tail1, head2, tail2, &res_head, &res_tail);
                is_negative = (sign1 == -1);
            }
            else
            {
                if (compare_list(head1, head2) >= 0)
                {
                    status = Sub(head1, tail1, head2, tail2, &res_head, &res_tail);
                    is_negative = (sign1 == -1);
                }
                else
                {
                    status = Sub(head2, tail2, head1, tail1, &res_head, &res_tail);
                    is_negative = (sign1 == 1) ? 1 : 0;
                }
            }
            break;

        case 'x':
            status = Mul(head1, tail1, head2, tail2, &res_head, &res_tail);
            if (overall_sign < 0 && res_head != NULL && res_head->data != 0)
            {
                is_negative = 1;
            }
            break;

        case '/':
            status = Div(head1, tail1, head2, tail2, &res_head, &res_tail);
            if (overall_sign < 0 && !(res_head && res_head->data == 0 && res_head->next == NULL))
            {
                is_negative = 1;
            }
            break;

        default:
            printf("Error: Invalid operator '%c'.\n", op);
            free_list(&head1);
            free_list(&head2);
            return FAILURE;
    }

    // Step 4: Centralized Error Handling
    if (status == FAILURE)
    {
        printf("Error: Operation '%c' failed during execution.\n", op);
        free_list(&head1);
        free_list(&head2);
        return FAILURE;
    }

    // Step 5: Centralized Result Printing
    printf("Result = ");
    if (is_negative && res_head != NULL && !(res_head->data == 0 && res_head->next == NULL))
    {
        printf("-");
    }
    print_list(res_head);
    printf("\n");

    // Step 6: Memory Cleanup
    free_list(&head1);
    free_list(&head2);
    free_list(&res_head);

    return SUCCESS;
}