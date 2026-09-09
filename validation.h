#ifndef VALIDATION_H
#define VALIDATION_H
#include "apc.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
// Helper function to check if a string is a valid signed/unsigned integer
static int is_valid_operand(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return 0;
    }

    int i = 0;

    // Skip optional leading sign '+' or '-'
    if (str[i] == '+' || str[i] == '-')
    {
        i++;
    }

    // Must have at least one digit after sign
    if (str[i] == '\0')
    {
        return 0;
    }

    // Verify all remaining characters are purely digits
    while (str[i] != '\0')
    {
        if (!isdigit((unsigned char)str[i]))
        {
            return 0;
        }
        i++;
    }

    return 1;
}

// Helper function to check if an operand is zero (e.g., "0", "00", "-0")
static int is_operand_zero(const char *str)
{
    int i = 0;

    if (str[i] == '+' || str[i] == '-')
    {
        i++;
    }

    while (str[i] != '\0')
    {
        if (str[i] != '0')
        {
            return 0; // Contains non-zero digit
        }
        i++;
    }

    return 1; // Purely zeros
}
int validate_args(int argc, char *argv[])
{
   //  4 arguments are passed: ./a.out <num1> <operator> <num2>
    if (argc != 4)
    {
        printf("Error: Invalid arguments count.\n");
        return FAILURE;
    }

    // Check operator validity: must be a single character and one of +, -, x, /
    if (strlen(argv[2]) != 1 || strchr("+-x/", argv[2][0]) == NULL)
    {
        printf("Error: Invalid operator. Supported operators: +, -, x, /\n");
        return FAILURE;
    }

    return SUCCESS;

    // Validate Operator
// Correct:
if (strlen(argv[2]) != 1 || strchr("+-x/", argv[2][0]) == NULL)
    {
        printf("Invalid operators:Allow only +,-,x,/ \n");
        return FAILURE;
    }

    // Validate Operand 1
   
    if (!is_valid_operand(argv[1]))
    {
        printf("Error: Operand 1 ('%s') is non-numeric or invalid.\n", argv[1]);
        return FAILURE;
    }

    // Validate Operand 2
   if (!is_valid_operand(argv[3]))
    {
        printf("Error: Operand 2 ('%s') is non-numeric or invalid.\n", argv[3]);
        return FAILURE;
    }
    // Prevent division by zero
    if (argv[2][0] == '/' && is_operand_zero(argv[3]))
    {
        printf("Error: Division by zero is not allowed.\n");
        return FAILURE;
    }
  return SUCCESS;
}
#endif