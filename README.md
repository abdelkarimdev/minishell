# Minishell

The goal of this project is to recreate the core behavior of a shell such as `bash`, while learning about **processes, file descriptors, pipes, redirections, signals, environment variables, and command execution**.

---

## 📚 Table of Contents

* [About](#about)
* [Objectives](#objectives)
* [Features](#features)
* [Shell Workflow](#shell-workflow)
* [Command Execution](#command-execution)
* [Built-in Commands](#built-in-commands)
* [Pipes](#pipes)
* [Redirections](#redirections)
* [Environment Variables](#environment-variables)
* [Signals](#signals)
* [Exit Status](#exit-status)
* [Parsing](#parsing)
* [Compilation](#compilation)
* [Usage](#usage)
* [Project Structure](#project-structure)
* [Important Concepts](#important-concepts)
* [42 Project](#42-project)
* [Author](#author)

---

## About

**Minishell** is a small Unix shell written in C.

The project reproduces some of the fundamental features of a real shell:

```text
$ echo "Hello World"
Hello World

$ pwd
/home/user

$ ls | grep .c

$ cat < input.txt > output.txt

$ echo $USER
username
```

The project requires understanding how a shell reads commands, interprets them, creates processes, connects processes together, and manages their execution.

---

## Objectives

The main objectives of Minishell are to understand:

* Processes
* `fork()`
* `execve()`
* `wait()` / `waitpid()`
* Pipes
* File descriptors
* Input/output redirection
* Signals
* Environment variables
* Command parsing
* Quoting
* Exit status
* Process synchronization
* Memory management

The project is essentially about understanding what happens behind a command such as:

```bash
ls -la | grep ".c"
```

instead of simply calling an existing shell.

---

## Features

### Command execution

Execute programs using the system environment:

```bash
ls
pwd
cat
grep
echo
```

Arguments are supported:

```bash
ls -la
cat file.txt
grep hello file.txt
```

---

### Built-in commands

Minishell implements the required shell built-ins:

| Command  | Description                               |
| -------- | ----------------------------------------- |
| `echo`   | Prints text                               |
| `cd`     | Changes the current directory             |
| `pwd`    | Prints the current working directory      |
| `export` | Creates or modifies environment variables |
| `unset`  | Removes environment variables             |
| `env`    | Displays environment variables            |
| `exit`   | Exits the shell                           |

Examples:

```bash
echo Hello
```

```bash
cd ..
```

```bash
pwd
```

```bash
export NAME=Karim
```

```bash
unset NAME
```

```bash
env
```

```bash
exit
```

---

## Shell Workflow

The general workflow of Minishell can be represented as:

```text
          User Input
              |
              ↓
           Readline
              |
              ↓
            Lexer
              |
              ↓
            Parser
              |
              ↓
      Command Representation
              |
              ↓
       Redirections / Pipes
              |
              ↓
          Execution
              |
              ↓
       Wait / Exit Status
              |
              ↓
        Display Prompt
```

The shell continuously repeats this process until the user exits.

---

## Command Execution

External commands are generally executed using:

```c
fork()
```

followed by:

```c
execve()
```

The parent process waits for the child using:

```c
waitpid()
```

Conceptually:

```text
              Minishell
                  |
                fork()
              /       \
             /         \
        Parent          Child
          |               |
       waitpid()        execve()
                          |
                          ↓
                       Program
```

For example:

```bash
ls -la
```

Minishell creates a child process and the child executes `ls`.

---

## Built-in Commands

Built-ins are handled differently from external programs.

For example:

```bash
cd ..
```

must change the directory of the **shell process itself**.

If `cd` were executed only inside a child process, the directory change would disappear when the child exits.

Therefore, commands such as:

```text
cd
export
unset
exit
```

require special handling.

---

## Pipes

Pipes allow the output of one command to become the input of another command.

Example:

```bash
ls | grep ".c"
```

Conceptually:

```text
        ls
         |
       stdout
         |
         ↓
      [ PIPE ]
         |
       stdin
         |
         ↓
       grep
```

The pipe is created using:

```c
pipe()
```

The processes then use:

```c
dup2()
```

to connect their standard input/output to the appropriate pipe ends.

For example:

```text
Command 1
stdout ───────→ pipe ───────→ stdin
                              Command 2
```

Multiple pipes can be chained:

```bash
cat file.txt | grep hello | wc -l
```

```text
cat
 |
 ↓
grep
 |
 ↓
wc
```

---

## Redirections

Minishell supports the standard shell redirections.

### Input redirection

```bash
cat < input.txt
```

The command reads from `input.txt` instead of standard input.

---

### Output redirection

```bash
echo hello > output.txt
```

The output is written to `output.txt`.

---

### Append

```bash
echo hello >> output.txt
```

The output is appended to the file instead of replacing its contents.

---

### Here-document

```bash
cat << EOF
Hello
World
EOF
```

The shell reads input until it encounters the specified delimiter.

Conceptually:

```text
User input
    |
    ↓
Here-document
    |
    ↓
Temporary input
    |
    ↓
Command stdin
```

---

## Environment Variables

Minishell maintains an environment containing variables such as:

```bash
USER
HOME
PATH
PWD
OLDPWD
```

Variables can be accessed using `$`:

```bash
echo $USER
```

or:

```bash
echo $HOME
```

The shell expands the variable before executing the command.

For example:

```text
Input:

echo $USER

        ↓

Expansion

        ↓

echo abdelkarim

        ↓

Execution
```

---

## PATH Resolution

When executing an external command such as:

```bash
ls
```

the shell needs to find the executable.

It uses the `PATH` environment variable.

For example:

```text
PATH=/usr/local/bin:/usr/bin:/bin
```

The shell searches these directories:

```text
/usr/local/bin/ls
/usr/bin/ls
/bin/ls
```

until it finds an executable.

---

## Signals

Minishell handles signals such as:

```text
SIGINT
SIGQUIT
```

For example, pressing:

```text
Ctrl + C
```

generates `SIGINT`.

The shell must handle signals differently depending on whether it is:

* Waiting for user input
* Executing a command
* Waiting for a child process

The goal is to reproduce shell-like behavior.

Examples:

```text
Ctrl + C
```

interrupts the current command/input.

```text
Ctrl + \
```

has different behavior depending on the execution context.

---

## Exit Status

Every command returns an exit status.

The special variable:

```bash
$?
```

contains the exit status of the last executed command.

Example:

```bash
true
echo $?
```

Output:

```text
0
```

Another example:

```bash
false
echo $?
```

Output:

```text
1
```

Minishell therefore needs to correctly manage the status returned by:

* Built-ins
* External commands
* Child processes
* Signals

---

## Parsing

One of the most important parts of Minishell is parsing.

The shell must understand different components of a command.

For example:

```bash
echo "hello world" | grep hello > output.txt
```

contains:

```text
Command:
echo

Argument:
"hello world"

Pipe:
|

Command:
grep

Argument:
hello

Redirection:
>

File:
output.txt
```

The parser converts the raw user input into a structure that the execution phase can understand.

---

## Quotes

Minishell handles:

### Single quotes

```bash
echo '$USER'
```

The content inside single quotes is treated literally.

---

### Double quotes

```bash
echo "$USER"
```

Variable expansion can occur inside double quotes.

Conceptually:

```text
'$USER'
   ↓
$USER

"$USER"
   ↓
actual USER value
```

Quotes therefore affect how the shell interprets the command.

---

## File Descriptors

Unix processes use file descriptors to communicate with the outside world.

The standard descriptors are:

```text
0 → stdin
1 → stdout
2 → stderr
```

For example:

```bash
cat < input.txt
```

changes the command's standard input:

```text
input.txt
    |
    ↓
 fd 0 (stdin)
    |
    ↓
   cat
```

And:

```bash
echo hello > output.txt
```

changes standard output:

```text
echo
 |
 fd 1
 |
 ↓
output.txt
```

Important system calls/functions used for this include:

```c
open()
close()
dup()
dup2()
pipe()
```

---

## Memory Management

Because Minishell continuously allocates and frees memory while parsing and executing commands, correct memory management is important.

The project requires careful handling of:

* Token arrays
* Command structures
* Environment variables
* Strings
* Paths
* Pipes
* File descriptors

Every dynamically allocated resource should have a clear owner and cleanup path.

---

## Compilation

Clone the repository and compile:

```bash
make
```

The project should be compiled with strict flags:

```text
-Wall -Wextra -Werror
```

---

## Usage

Start Minishell:

```bash
./minishell
```

You should see a shell prompt similar to:

```text
minishell$
```

You can then execute commands:

```bash
minishell$ pwd
/home/user

minishell$ echo Hello
Hello

minishell$ ls | grep .c

minishell$ exit
```

---

## Makefile

Common Makefile targets:

```bash
make
```

Compile the project.

```bash
make clean
```

Remove object files.

```bash
make fclean
```

Remove object files and the executable.

```bash
make re
```

Clean and rebuild the project.

---

## Important Concepts

### `fork()`

Creates a new process.

```text
Parent
  |
fork()
 / \
↓   ↓
P   C
```

---

### `execve()`

Replaces the current process image with another program.

```text
Child process
     |
   execve()
     |
     ↓
   ls / grep / cat / ...
```

---

### `waitpid()`

Allows the parent to wait for a child process.

---

### `pipe()`

Creates a communication channel between processes.

```text
Process A
   |
 stdout
   |
 pipe
   |
 stdin
   |
Process B
```

---

### `dup2()`

Redirects a file descriptor.

It is one of the key tools used for:

* Pipes
* Input redirection
* Output redirection

---

### `open()`

Opens or creates files for redirections.

---

### Signals

Signals provide a mechanism for processes to receive asynchronous events.

Minishell must handle them correctly to behave like a real shell.

---

## What I Learned

Through Minishell, I learned how a Unix shell works internally instead of treating the terminal as a black box.

The project helped me understand the relationship between:

```text
User Input
    ↓
Parsing
    ↓
Expansion
    ↓
Redirections
    ↓
Pipes
    ↓
Processes
    ↓
execve()
    ↓
Program Execution
    ↓
Exit Status
```

The most important lesson is that a shell is essentially a **process manager and command interpreter**.

---

## Author

**Abd El Karim**

42 / 1337 Coding School

Morocco
