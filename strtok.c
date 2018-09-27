#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  char str[] = "ls -1| echo 'hello world'"; // Input commands separated by ';'

  // Break the commands string into an array
  char *commands[10]; // Array to hold a max of 10 commands
  char *semi = "|";
  char *token = strtok(str, semi);
  int i = 0;
  while (token != NULL) 
  {
    commands[i] = token;
    ++i;
    token = strtok(NULL, semi);
  }
  int numCommands = i; // numCommands is the max number of input commands

  // Run each input command in a child process
  i = 0;
  while (i < numCommands)
  {
    printf("Command: %s\n", commands[i]);

    // Tokenize the command so that it can be run using execvp
    char *args[10] = {}; // Array to hold command args
    args[0] = strtok(commands[i], " ");
    int tokenCounter = 0;
    while (args[tokenCounter] != NULL)
    {
      tokenCounter++;
      args[tokenCounter] = strtok(NULL, " ");
    }

    // Create a child process
    int childpid = fork();

    // If this is child process, run the command
    if (childpid == 0)
    {
      if ((execvp(args[0], args)) < 0)
      {
        printf("Error! Command not recognized.\n");
      }
      exit(0);
    }
    // If this is the parent, wait for the child to finish
    else if (childpid > 0)
    {
      wait(&childpid);
    }
    // If the child process could not be created, print an error and exit
    else
    {
      printf("Error: Could not create a child process.\n");
      exit(1);
    }

    ++i;
  }

  return 0;
}
