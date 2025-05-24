#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include "parser.h"

//I defined a Node structure to create a linked list for feature 5
typedef struct Node {
    char *name;          
    char *value;         
    struct Node *next; 
} Node;

Node *var_list = NULL; //We will use this as the head of the list

int read_line(int infile, char *buffer, int maxlen)
{
    int readlen = 0;

    // TODO: Read a single line from file; retains final '\n'
    char c;

    // Read character by character until newline or EOF
    while (readlen < maxlen - 1) {  // Leave space for the null terminator
        int result = read(infile, &c, 1);  // Read one character at a time

        if (result == 0) {  // End of file (EOF)
            break;
        } else if (result < 0) {  // Error reading file
            return -1;
        }

        // Store the character in the buffer
        buffer[readlen++] = c;

        // Stop if we hit a newline character
        if (c == '\n') {
            break;
        }
    }

    buffer[readlen] = '\0';  // Null-terminate the string
    
    return readlen;
}


int normalize_executable(char **command) {
    // Convert command to absolute path if needed (e.g., "ls" -> "/bin/ls")
    // Returns TRUE if command was found, FALSE otherwise
    if (command[0][0] == '/' || strstr(command[0], "/")) {
        if(access(command[0], X_OK) ){
            return 1;
        }else{
            return 0;
        }
    }

    char* path = getenv("PATH");
    char path_copy[1024];
    strncpy(path_copy, path, sizeof(path_copy));
    char* dir = strtok(path_copy, ":");
    while (dir) {
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, command[0]);
        if (access(fullpath, X_OK) == 0) {
            command[0] = strdup(fullpath);  // Update command to full path
            return 1;
        }
        dir = strtok(NULL, ":");
    }
    return 0;
}

void update_variable(char* name, char* value) {
    Node *current = var_list;
    // We first check if the variable already exists
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }

    // If the variable does not exist
    Node *new_node = malloc(sizeof(Node));
    new_node->name = strdup(name);
    new_node->value = strdup(value);
    new_node->next = var_list;
    var_list = new_node;
}

char* lookup_variable(char* name) {

    Node *current = var_list;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value; // Return the value if found
        }
        current = current->next;
    }
    return NULL; // Not found
}


void handle_pipe(char **first_command, char **second_command, char *output_file) {
    int pipe_fd[2];

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // First command: execute the command before the pipe
    if (fork() == 0) {
        close(pipe_fd[0]);  // Close the read end of the pipe in the first child
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to the pipe
        close(pipe_fd[1]);  // Close the write end after dup2

        // Execute the first command (e.g., echo)
        normalize_executable(first_command);
        execv(first_command[0], first_command);
        perror("execv failed");  // If execv returns, it must have failed
        exit(EXIT_FAILURE);
    }

    // Second command: execute the command after the pipe
    if (fork() == 0) {
        close(pipe_fd[1]);  // Close the write end of the pipe in the second child
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect stdin to the pipe
        close(pipe_fd[0]);  // Close the read end after dup2

        if (output_file != NULL) {
            // Handle redirection to a file
            int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                perror("open failed for redirection");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);  // Redirect stdout to the file
            close(fd);
        }

        // Execute the second command (e.g., rev)
        normalize_executable(second_command);
        execv(second_command[0], second_command);
        perror("execv failed");
        exit(EXIT_FAILURE);
    }

    // Close both ends of the pipe in the parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    wait(NULL);
    wait(NULL);
}

int main(int argc, char *argv[])
{
    

    if(argc != 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return -1;
    }

    int infile = open(argv[1], O_RDONLY);
    if(infile < 0) {
        perror("Error opening input file");
        return -2;
    }

    char buffer[1024];
    int readlen;

    // Read file line by line
    while( 1 ) {
        // Load the next line
        readlen = read_line(infile, buffer, 1024);
        if(readlen < 0) {
            perror("Error reading input file");
            return -3;
        }

        if(readlen == 0) {
            break;
        }

        // Tokenize the line
        int numtokens = 0;
        token_t** tokens = tokenize(buffer, readlen, &numtokens);
        assert(numtokens > 0);

        char *args[numtokens];
        int redirect_index = -1;
        int pipe_index = -1;
        int end = 0;
        char *output_file = NULL;

        for(int i = 0; i < numtokens; i++){
            if (tokens[i]->type == TOKEN_REDIR) {
                redirect_index = i;
                output_file = strdup(tokens[redirect_index + 1]->value);
            } else if (tokens[i]->type == TOKEN_PIPE) {
                pipe_index = i;
            } else {
                args[end] = malloc(strlen(tokens[i] -> value) + 1);   
                strcpy(args[end], tokens[i] -> value);  
                end++;
            }                                                    
        }
        args[end] = NULL;


        if (pipe_index != -1) {
            char *first_command[pipe_index + 1];
            for (int i = 0; i < pipe_index; i++) {
                first_command[i] = strdup(tokens[i]->value);
            }
            first_command[pipe_index] = NULL;

            char *second_command[numtokens - pipe_index];
            int second_end = 0;
            for (int i = pipe_index + 1; i < numtokens; i++) {
                if (tokens[i]->type == TOKEN_REDIR) break; 
                second_command[second_end] = strdup(tokens[i]->value);
                second_end++;
            }
            second_command[second_end] = NULL;

            // Handle the pipe and the redirection
            handle_pipe(first_command, second_command, output_file);
        }else{
            if (fork() != 0) {
                wait(NULL); 
            }
            else {
                if (fork() == 0) {
                    if (redirect_index != -1) {
                        
                        int fd = open(tokens[redirect_index + 1]->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);   // Open the file for redirection (output)
                        if (fd == -1) {
                            perror("open failed");
                            exit(1);
                        }

                        dup2(fd, STDOUT_FILENO);// Redirect stdout to the file
                        close(fd);  // Close the file descriptor after redirection

                        // Modify the args to exclude the redirection token and file name
                        args[redirect_index] = NULL; 
                    }

                    // Execute the single command (without pipe)
                    normalize_executable(args);
                    execv(args[0], args);
                    perror("execv failed");  // If execv returns, it must have failed
                    exit(EXIT_FAILURE);
                } else {
                    wait(NULL);  // Parent process waits for the child to finish
                }
            }
        }

        for (int i = 0; i < numtokens; i++) {
            if (tokens[i]->type == TOKEN_ASSIGN) {
                // This means the previous token is the variable name
                char *var_name = tokens[i - 1]->value;
                char *var_value = tokens[i + 1]->value;
                update_variable(var_name, var_value); // Store in the variable list
            } else if (tokens[i]->type == TOKEN_VAR) { 
                char *var_name = tokens[i]->value + 1; // Skip the $ 
                char* var_value = lookup_variable(var_name);
                if (var_value != NULL) {
                    // Replace the token with the variable value
                    tokens[i]->value = strdup(var_value);
                }
            }
        }
	

        // Free tokens vector
        for (int ii = 0; ii < numtokens; ii++) {
            free(tokens[ii]->value);
            free(tokens[ii]);
        }
        free(tokens);

        for (int i = 0; i < end; i++) {
                free(args[i]);
            }

        if (output_file != NULL) {
            free(output_file);
        }
    }

    close(infile);
    
    // Remember to deallocate anything left which was allocated dynamically
    // (i.e., using malloc, realloc, strdup, etc.)

    // We do this here
    Node *current = var_list;
    while (current) {
        Node *next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }

    return 0;
}


