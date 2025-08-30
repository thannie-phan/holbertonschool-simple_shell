## Simple Shell
![360_F_1295184842_Wpxn9uH9Tc0kwYDW2GbDtDBq55OGYZvT](https://github.com/user-attachments/assets/d45ea5a3-59fa-4f27-b910-00ba007d40e4)


*A simplified UNIX command interpreter in C*

>*Our simple shell project is similar to the bash shell in that it takes user input, finds the command in the path and executes the command.*


### Overview

By building our own Simple Shell, we were able to pull apart the inner workings of the bash shell and see what happens when a command is executed. 

We have built our shell from scratch using the foundation knowledge we have learned of the C language. This project gave us the chance to explore how the shell operates, how it searches the environment, what unexpected behaviour might happen in the background, and what is needed to create a smooth user experience within the shell.


### Highlights / Features

Our shell runs in an infinite loop, continuously taking in user input and processing it step by step as the behaviour of a real shell. It supports built-in commands such as exit, which allows the user the terminate the program while saving the exit status of the previous commands, and it supports env, which displays the current environment. For all other input, the shell searches the path and executes the command in a child process, managing both parent and child exit statuses. We have also handled memory allocation and deallocation and every stage to prevent leaks. By including these features, our shell can operate in both interactive and non-interactive modes, executing commands, handling errors and running efficiently.


### Flowchart
The flowchart below shows the behaviour of the main function. There are three main helper functions that are called from main and are not simply copycat functions (like _printenv):
- char *read_input(void)
- char **split_string(char *str)
- int *execute_command(char **args, int *exit_status)
![SIMPLE SHELL GROUP PROJECT](https://github.com/user-attachments/assets/7efb8033-68b6-4274-9432-a5e23bfb834d)


### Installation

*You are welcome to use our simple shell, please install as below.*

```py
$ git clone https://github.com/thannie-phan/holbertonschool-simple_shell.git
$ cd holbertonschool-simple_shell
$ ./hsh
#cisfun$
```


### Usage

```bash
interactive mode and non-interactive mode:
```

https://github.com/user-attachments/assets/517dce74-f97d-4756-a159-c7a8ed67ecac




### Authors

Thannie Phan - https://github.com/thannie-phan

Madison Fleming - https://github.com/madisonfleming

Sheeny Soulsby - https://github.com/sheeny84
