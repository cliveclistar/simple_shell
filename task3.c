#include "shell.h"

/*main - Checks the correctness of the code 
 *
 * Return: Always 0.
 */
// Function to handle the PATH
char *get_path(char *command)
{
    // TODO: Implement the logic to retrieve the PATH for the given command
    // and return the appropriate path
    
    return NULL; // Placeholder return value
}

// Main shell function
int main(void)
{
    char *command;
    char *path;
    
    // Loop to continuously read commands
    while (1)
    {
        printf("$ "); // Display a prompt
        
        // Read the command from the user
        ssize_t bufsize = 0;
        getline(&command, &bufsize, stdin);
        
        // Removing the newline character at the end of the command
        command[strcspn(command, "\n")] = 0;
        
        // Check if the command exists in the PATH
        path = get_path(command);
        if (path == NULL)
        {
            printf("Command not found\n");
            continue; // Skip to the next iteration of the loop
        }
        
        // Create a child process
        pid_t pid = fork();
        
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0) // Child process
        {
            // Execute the command
            if (execve(path, NULL, NULL) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
        else // Parent process
        {
            int status;
            wait(&status); // Wait for the child process to finish
            
            // TODO: Handle the exit status of the child process if needed
            
            // Free allocated memory
            free(path);
        }
    }
    
    return 0;
}
