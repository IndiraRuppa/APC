#ifndef VALIDATION_H
#define VALIDATION_H
#include "apc.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int validate_args(int argc, char *argv[])
{
    // Check argument count
    if(argc <4)
    {
        printf("Eroor: argument count is invalid\n");
        return   FAILURE;
    }

    // Validate Operator
    if(strlen(argv[2]!=1) || strchr("+-x/",argv[2][0]==NULL))
    {
        printf("Invalid operators:Allow only +,-,x,/ \n");
        return FAILURE;
    }

    // Validate Operand 1
    for(int i=0;argv[1][i]!="\0";i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
           printf("Error: Non-numeric character are not allowed\n");
           return FAILURE; 
        }
    }

    // Validate Operand 2
    for(int i=0;argv[3][i]!='\0';i++)
    {
        if (argv[3][i] < '0' || argv[3][i] > '9')
        {
           printf("Error: Non-numeric character are not allowed\n");
           return FAILURE; 
        }
    }
  return SUCCESS;
}
#endif