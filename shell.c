#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define BUFFER_LEN 1024

int main()
{
	char line[BUFFER_LEN];	//get command line
	char *argv[100];	//user command
	char *path = "/bin/";	//set path at bin
	char progpath[20];	//full file path
	int argc;		//arg count

	while (1) {

		printf("My shell>> ");	//print shell prompt

		if (!fgets(line, BUFFER_LEN, stdin)) {	//get command and put it in line
		//	size_t length = strlen(line);
		//	if (line[length - 1] == '\n')
		//	line[length - 1] = '\0';
			exit(0);	//if user hits CTRL+D break
		}
		else {
                  line[strcspn(line, "\n")] = '\0';
                }

		
		if (strcmp(line, "exit") == 0) {	//check if command is exit
			exit(0);
			break;
		}

		char *token;	//split command into separate strings
		token = strtok(line, " ");
		int i = 0;
		while (token != NULL) {
			argv[i] = token;
			//printf("token =%s ",token);
			token = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;	//set last value to NULL for execvp

		argc = i;	//get arg count
		for (i = 0; i < argc; i++) {
			printf("%s\n", argv[i]);	//print command/args
		}
		strcpy(progpath, path);	//copy /bin/ to file path
		strcat(progpath, argv[0]);	//add program to path

		for (i = 0; i < strlen(progpath); i++) {	//delete newline
			if (progpath[i] == '\n') {
				progpath[i] = '\0';
			}
		}
		int pid = fork();	//fork child

		if (pid == 0) {	//Child
			execvp(progpath, argv);
			fprintf(stderr, "Child process could not do execvp\n");

		} else {	//Parent
			wait(NULL);
			printf("Child exited\n");
		}

	}
}
