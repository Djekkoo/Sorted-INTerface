#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sortedcontainer.h"
#include "test.h"

// DO NOT change this value. It does not fix your problems
#define INPUT_INCREMENT 10

#define STR(X) STR2(X)
#define STR2(X) #X

/**
 * @brief Prints the prompt to @c f
 * @param f The FILE to print the prompt to.
 */
void print_prompt(FILE *f)
{
    fprintf(f, "\n> ");
    fflush(f);
}

/**
 * @brief Basic parser to read data from @c command
 * @param command The command string to read the data from
 * @return A new data object
 *
 * TO FIX:
 *   There are two serious problems in this function that are related
 *      - 0 or 1 arugments can be given
 *      - Name can be empty or infinite
 */
data *read_data(char const *command)
{
    int age;
    char name[NAME_LENGTH];
    // Check parameter length
    char scanf_format[12]; 
    sprintf(scanf_format, "%%*s %%i %%%is", NAME_LENGTH);
    if (sscanf(command, scanf_format, &age, name) != 2) // cppcheck-error: NAME_LENGTH = 20, length of name(excluding \0) = 19
    {
        fprintf(stdout, "Not enough arguments");
        return NULL;
    }
    else
    {
        // Check if argument is not '\0'.
        // if (name[0] == '\0')
        // {
        //     fprintf(stdout, "Name cannot be empty");
        //     return NULL;
        // }

        for (int i = 0; i < NAME_LENGTH; i++) {
            if(name[i] == '\0') {
                 if (age < 0) {
                    fprintf(stdout, "Age cannot smaller than 0.");
                    return NULL;
                }
                return data_new(age, name);
            }
        }
        fprintf(stdout, "Name too long");
        return NULL;
    }
   
}

/**
 * @brief Handles @c command
 * @param printFile FILE to print messages to
 * @param sc The sortedcontainer to query or modify
 * @param command The command to handle
 * @return 1 iff the problem should quit, otherwise 0
 *
 * TO FIX:
 *   There are three problems in this function, two of which are related
 *       - fprintf(printFile, command) => fprintf(printFile, "%s", command)
 *       - free data after call to sortercontainer_erase
 *       - free data after call to sortedcontainer_contains
 * todo ownership should not be claimed by contains/erase. Free memory afterwards       
 */
int handle_command(FILE *printFile, sortedcontainer *sc, char *command)
{
    switch (*command)
    {
    case 'i':
    {
        data *rd = read_data(command);
        if (rd != NULL)
        {
            sortedcontainer_insert(sc, rd);
        }
        break;
    }

    case 'e':
    {
        data *rd = read_data(command);
        if (rd != NULL)
        {
            sortedcontainer_erase(sc, rd);
            data_delete(rd);
        }
        break;
    }

    case 'c':
    {
        data *rd = read_data(command);
        if (rd != NULL)
        {
            if (sortedcontainer_contains(sc, rd))
            {
                fprintf(printFile, "y\n");
            }
            else
            {
                fprintf(printFile, "n\n");
            }
            data_delete(rd);
        }

        break;
    }
    case 'p':
        sortedcontainer_print(sc, printFile);
        break;
    case 'x':
        return 1;
        break;
    case 't':
        test(printFile);
        break;
    default:
    {
        fprintf(printFile, "No such command: ");
        fprintf(printFile, "%s", command);
        fprintf(printFile, "\n");
        break;
    }
    }
    return 0;
}

/**
 * @brief Reads a command from the FILE @c in
 * @param in FILE to read a command from
 * @return The read command
 *
 * TO FIX:
 *   There are two separate problems in this function. Fix these problems
 *   by only changing TWO lines in total.
 *      -   "inputAt += incr - 1;" => "inputAt = &input[inputMaxLength-incr-1];"
 *      -   Changed opening bracket of the do-while loop into "{ if (input == NULL) return NULL; "
 */
char *read_command(FILE *in)
{
    int inputMaxLength = 0;
    char *input = NULL;
    char *inputAt = NULL;

    int incr = INPUT_INCREMENT;

    inputMaxLength = incr;
    input = (char *)malloc(sizeof(char) * incr);
    inputAt = input;
    do
    {   if (input == NULL) return NULL; // allocation error, either at malloc or realloc. 
        inputAt[incr - 1] = 'e'; // check if this gets overwritten @ inputAt[incr-1] != '\0'. If not, all input is read.
        if (fgets(inputAt, incr, in) == NULL) {
            free(input);
            return NULL;
        }
        if (inputAt[incr - 1] != '\0' || inputAt[incr - 2] == '\n')
        {
            break;
        }
        inputMaxLength += INPUT_INCREMENT;
        input = realloc(input, sizeof(char) * inputMaxLength);
        inputAt = &input[inputMaxLength-INPUT_INCREMENT-1];
        incr = INPUT_INCREMENT + 1;
    } while (1);
    if (strlen(input) == 0) {
        free(input);
        return NULL;
    }
    input[strlen(input) - 1] = 0; // remove newline before \0 from result.
    return input;
}

/**
 * @brief The main SINT loop
 * @param argc Argument count
 * @param argv Arguments
 * @return 0
 *
 * TO FIX:
 *   One issue needs to be fixed here.
 *      -   free the memory allocated for the read_command result buffer.
 */
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    sortedcontainer *sc = sortedcontainer_new();

    while (1)
    {
        print_prompt(stdout);

        char *command = read_command(stdin);
        if (command == NULL)
        {
            break;
        }

        if (handle_command(stdout, sc, command))
        {
            free(command);
            break;
        }
        free(command);        
    }

    sortedcontainer_delete(sc);

    fprintf(stdout, "\nBye.\n");

    return 0;
}
