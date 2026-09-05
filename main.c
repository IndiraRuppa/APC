#include "apc.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc,char *argv[])
{
    //Validate input arguments
    if(argc<4)
    {
        printf("Usage: %s <num1> <operator> <num2>\n", argv[0]);
        return FAILURE;
    }
    Dlist *head1=NULL,*tail1=NULL;
    Dlist *head2=NULL,*tail2=NULL;
    Dlist *res_head=NULL,*res_tail=NULL;

    //Convert operand strings to lists
    if(string_to_list(argv[1],&head1,&tail1)== FAILURE)
    {
        printf("Error: Failed to convert operand 1.\n");
        
        return FAILURE;
    }

       if(string_to_list(argv[3],&head2,&tail2)== FAILURE)
    {
        printf("Error: Failed to convert operand 2.\n");
        free_list(&head1);
        return FAILURE;
    }

    char operator = argv[2][0];
    int is_negative=0;
    //Perform operation directly on inputs
    switch(operator)
    {
        case'+':
        if(Add(head1,tail1,head2,tail2,&res_head,&res_tail)==FAILURE)
        {
            printf("ERROR  during Addition.\n");
            free_list(&head1);
            free_list(&head2);
            return FAILURE;
        }
        break;
        case '-':
        is_negative = Sub(head1, tail1, head2, tail2, &res_head, &res_tail);
        if(is_negative ==  FAILURE && res_head ==NULL)
        {
        printf("Error during subtraction.\n");
        free_list(&head1);
        free_list(&head2);
        return FAILURE;
        }
        break;
        case'x':
        if(Mul(head1,tail1,head2,tail2,&res_head,&res_tail)==FAILURE)
        {
            printf("Error: Memory allocation failed during multiplication.\n");
            free_list(&head1);
            free_list(&head2);
            return FAILURE;
        }
        break;
        case '/':
        if (Div(head1, tail1, head2, tail2, &res_head, &res_tail)==FAILURE)
        {
            
            free_list(&head1);
            free_list(&head2);
            return FAILURE;
        }
        break;
        default :
        printf("Error: Invalid operator '%c'. Supported operators: +, -, *, /\n", operator);
        free_list(&head1);
        free_list(&head2);
        return FAILURE;
    }
     // Step 4: Display Output
    printf("Result=");
    if (is_negative == 1)
    {
        printf("-");
    }
    print_list(res_head);
    printf("\n");
    // Step 5: Free all memory lists
    free_list(&head1);
    free_list(&head2);
    free_list(&res_head);

    return  SUCCESS;
}