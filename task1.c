#include "shell.h"

/* Check the code 
 * main - Checks the correctness of the code 
 * write - writes to an open file
 * while - repeats a statement until a specified expression becomes false
 *
 * Return: Always 0.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];

    while (1)
    {
        write(STDOUT_FILENO, "cisfun> ", 8);

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            if (feof(stdin))
            {
                write(STDOUT_FILENO, "\n", 1);
                break; /*End of file (Ctrl+D) was encountered */
            }
        }

        command[strcspn(command, "\n")] = '\0'; /*Remove trailing newline character*/

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            continue;
        }
        else if (pid == 0)
        {
            /*Child Process*/
            execlp(command, command, NULL);
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            /*Parent Proces*/
            wait(NULL);
        }
    }

    return 0;
}
