## Simple Shell
![360_F_1295184842_Wpxn9uH9Tc0kwYDW2GbDtDBq55OGYZvT](https://github.com/user-attachments/assets/d45ea5a3-59fa-4f27-b910-00ba007d40e4)


*A simplified UNIX command interpreter in C*

>*Our simple shell project is similar to the bash shell in that it takes user input, finds the command in the path and executes the command.*


### Highlights / Features

- Display a promt and wait for the user to type a command
- Handles commands with arguments
- Handles the PATH
- Builtin commands exit and env
- Handles invlaid input and errors in execution
- Memory management.


### Overview

You never truely know something until you tear it apart.

By building our own Simple Shell, we were able to pull apart the inner workings of the bash shell and see what happens when a command is executed. 

We have built our shell from scratch using the foundation knowledge we have learned of the C language. This project gave us the chance to explore how the shell operates, how it searches the environment, what unexpected behaviour might happen in the background, and what is needed to create a smooth user experience within the shell.


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
interactive mode:
```
<img width="720" height="379" alt="interactive" src="https://github.com/user-attachments/assets/a454be4c-10b6-4c09-a8bc-3114813cca8c" />

```bash
non-interactive mode:
```
<img width="720" height="288" alt="non-interactive" src="https://github.com/user-attachments/assets/25c3328a-fb66-4e2c-9072-c18d9abb67f5" />


### Authors

Thannie Phan - https://github.com/thannie-phan

Madison Fleming - https://github.com/madisonfleming

Sheeny Soulsby - https://github.com/sheeny84
