# Building-A-Shell
The OS command interpreter is the program that people interact with in order to launch and control programs. On UNIX systems, the command interpreter is often called shell: a user-level program that gives people a command-line interface to launching, suspending, and killing other programs. sh, ksh, csh, tcsh, bash, ... are all examples of UNIX shells. You use a shell like this every time you log into a Linux machine at a URCS computer lab and bring up a terminal. It might be useful to look at the manual pages of these shells, for example, type "man bash". 

# Requirements in detail: 
Your job is to implement a very primitive shell that knows how to launch new programs in the foreground and the background. It should also recognize a few internal commands. More specifically, it should support the following features. 
    • It should recognize the internal commands: exit, jobs, and cd. exit should use the exit() system call to terminate the       shell. cd uses the chdir() system call to change to a new directory. 
    • If the command line does not indicate any internal commands, it should be in the following form:
     <program name> <arg1> <arg2> .... <argN> 
  
Your shell should invoke the program, passing it the list of arguments in the command line. The shell must wait until the started program completes. 

To allow users to pass arguments you need to parse the input line into words separated by whitespace (spaces and '\t' tab characters). You might try to use strtok_r() for parsing (check the manual page of strtok_r() and Google it for examples of using it). In case you wonder, strtok_r() is a user-level utility, not a system call. This means this function is fulfilled without the help of the operating system kernel. 

The shell runs programs using two core system calls: fork() and execvp(). Read the manual pages to see how to use them. In short, fork() creates an exact copy of the currently running process, and is used by the shell to spawn a new process. The execvp() call is used to overlay the currently running program with a new program, which is how the shell turns a forked process into the program it wants to run. In addition, the shell must wait until the previously started program. This is done with the wait() system call or one of its variants (such as waitpid()). All these system calls can fail due to unforeseen reasons (see their manual pages for details). You should check their return status and report errors if they occur. 

No input the user gives should cause the shell to exit (except when the user types exit or Ctrl+D). This means your shell should handle errors gracefully, no matter where they occur. Even if an error occurs in the middle of a long pipeline, it should be reported accurately and your shell should recover gracefully. You may need to use signal() and kill() systems calls. In addition, your shell should not generate leaking open file descriptors. Hint: you can monitor the current open file descriptors of the shell process through the /proc file system. 

# Pipes: 
Shell needs to support pipes. Pipes allow the stdins and stdouts of a list of programs to be concatenated in a chain. More specifically, the first program's stdout is directed to the stdin of the second program; the second program's stdout is directed to the stdin of the third program; and so on so forth. Multiple piped programs in a command line are separated with the token "|". 
A command line will therefore have the following form:
     <program1> <arglist1> | <program2> <arglist2> | ... | <programN> <arglistN> [&]

Try an example like this: pick a text file with more than 10 lines (assume it is called textfile) and then type
     cat textfile | gzip -c | gunzip -c | tail -n 10 in a regular shell. Pause a bit to think what it really does. Note that multiple processes need to be launched for piped commands and all waited on in a foreground execution. The pipe() and dup2() system calls will be useful.
