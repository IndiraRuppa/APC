#include "apc.h"
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Step 1: Validate input arguments
    if (validate_args(argc, argv) == FAILURE)
    {
        return FAILURE;
    }

    // Step 2: Determine signs of input operands
    int sign1 = (argv[1][0] == '-') ? -1 : 1;
    int sign2 = (argv[3][0] == '-') ? -1 : 1;
    
    // Key encoding: 11 = (+,+), -11 = (-,-), 9 = (+,-), -9 = (-,+)
    int sign_combination = (sign1 * 10) + sign2; 

    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *res_head = NULL, *res_tail = NULL;

    // Step 3: Convert operand strings to doubly linked lists
    if (string_to_list(argv[1], &head1, &tail1) == FAILURE)
    {
        printf("Error: Failed to convert operand 1.\n");
        return FAILURE;
    }

    if (string_to_list(argv[3], &head2, &tail2) == FAILURE)
    {
        printf("Error: Failed to convert operand 2.\n");
        free_list(&head1);
        return FAILURE;
    }

    char operator = argv[2][0];
    int is_negative = 0;

    // Step 4: Perform arithmetic operation based on sign logic
    switch (operator)
    {
        case '+':
            switch (sign_combination)
            {
                case 11: // (+A) + (+B) = A + B
                    if (Add(head1, tail1, head2, tail2, &res_head, &res_tail) == FAILURE)
                    {
                        printf("Error during Addition.\n");
                        free_list(&head1); free_list(&head2);
                        return FAILURE;
                    }
                    break;

                case -11: // (-A) + (-B) = -(A + B)
                    if (Add(head1, tail1, head2, tail2, &res_head, &res_tail) == FAILURE)
                    {
                        printf("Error during Addition.\n");
                        free_list(&head1); free_list(&head2);
                        return FAILURE;
                    }
                    is_negative = 1;
                    break;

                case 9: // (+A) + (-B) = A - B
                case -9: // (-A) + (+B) = B - A = -(A - B) -> Sub handles comparison internally
                    is_negative = Sub(head1, tail1, head2, tail2, &res_head, &res_tail);
                    if (sign_combination == -9)
                    {
                        // Reverse result sign for (-A) + (+B)
                        is_negative = !is_negative;
                    }
                    break;
            }
            break;

        case '-':
            switch (sign_combination)
            {
                case 11:  // (+A) - (+B) = A - B
                case -11: // (-A) - (-B) = -A + B = -(A - B)
                    is_negative = Sub(head1, tail1, head2, tail2, &res_head, &res_tail);
                    if (sign_combination == -11)
                    {
                        // Flip sign for (-A) - (-B)
                        is_negative = !is_negative;
                    }
                    break;

                case 9: // (+A) - (-B) = A + B
                    if (Add(head1, tail1, head2, tail2, &res_head, &res_tail) == FAILURE)
                    {
                        printf("Error during Subtraction.\n");
                        free_list(&head1); free_list(&head2);
                        return FAILURE;
                    }
                    break;

                case -9: // (-A) - (+B) = -(A + B)
                    if (Add(head1, tail1, head2, tail2, &res_head, &res_tail) == FAILURE)
                    {
                        printf("Error during Subtraction.\n");
                        free_list(&head1); free_list(&head2);
                        return FAILURE;
                    }
                    is_negative = 1;
                    break;
            }
            break;

        case 'x':
            if (Mul(head1, tail1, head2, tail2, &res_head, &res_tail) == FAILURE)
            {
                printf("Error during Multiplication.\n");
                free_list(&head1); free_list(&head2);
                return FAILURE;
            }
            if (sign1 != sign2 && res_head != NULL && res_head->data != 0)
            {
                is_negative = 1;
            }
            break;

        case '/':
            if (Div(head1, tail1, head2, tail2, &res_head, &res_tail) == FAILURE)
            {
                printf("Error during Division.\n");
                free_list(&head1); free_list(&head2);
                return FAILURE;
            }
            if (sign1 != sign2 && res_head != NULL && res_head->data != 0)
            {
                is_negative = 1;
            }
            break;

        default:
            printf("Error: Invalid operator '%c'. Supported operators: +, -, x, /\n", operator);
            free_list(&head1);
            free_list(&head2);
            return FAILURE;
    }

    // Step 5: Display Result
    printf("Result=");
    if (is_negative == 1 && res_head != NULL && res_head->data != 0)
    {
        printf("-");
    }
    print_list(res_head);
    printf("\n");

    // Step 6: Free memory allocations
    free_list(&head1);
    free_list(&head2);
    free_list(&res_head);

    return SUCCESS;
}