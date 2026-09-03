#include "apc.h"

void print_list(Dlist *head)
{
    if(head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    Dlist *temp = head;
    while(temp !=NULL)
    {
         printf("%d",temp->data);
         temp=temp->next; 
    }
}

void free_list(Dlist **head)
{
    Dlist *temp=NULL;
    while(*head!=NULL)
    {
        temp=*head;
        *head=(*head)->next;
        free(temp);
    }
    *head=NULL;
}

int main(int argc,char *argv[])
{
    //Validate input arguments
    if(validate_args(argc,argv)==0)
    {
        return FAILURE;
    }
    Dlist *head1=NULL,*tail1=NULL;
    Dlist *head2=NULL,*tail2=NULL;
    Dlist *res_head=NULL,*res_tail=NULL;

    //Convert operand strings to lists
    if(string_to_list(argv[1],&head1,&tail1))
    {
        return FAILURE;
    }

       if(string_to_list(argv[3],&head2,&tail2))
    {
        return FAILURE;
    }

    char operator = argv[2][0];
    
    //Perform operation directly on inputs
    if(operator =='+')
    {
        Add(head1, tail1, head2, tail2, &res_head, &res_tail);
    }
    else if (operator == '-')
    {
        sub(head1, tail1, head2, tail2, &res_head, &res_tail);
    }
     // Step 4: Display Output
    printf("Result=");
    print_list(res_head);

    // Step 5: Free all memory lists
    free_list(&head1);
    free_list(&head2);
    free_list(&res_head);

    return  SUCCESS;
}