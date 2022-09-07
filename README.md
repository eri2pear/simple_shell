# 0x16. C - Simple Shell

### Authors of This Repository

[Yoseph Seyoum](https://github.com/Yoseph47)

[Patricia A. Rukud'de](https://github.com/eri2pear)

# Simple Shell project 0x16.c - hsh -

This is a simple UNIX command interpreter based on bash and Sh.

## Overview

**hshy** is a sh-compatible command language interpreter that executes commands read from the standard input or from a file.

### Invocation

Usage: **hsh** 
hsh is started with the standard input connected to the terminal. To start, compile all .c located in this repository by using this command: 
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
./hsh
```

**hsh** is allowed to be invoked interactively and non-interactively. If **hsh** is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:
```
$ echo "echo 'alx'" | ./hsh
'alx'
$
```

When **hsh** is invoked with standard input connected to a terminal (determined by isatty(3), the interactive mode is opened. **hsh** Will be using the following prompt `^-^ `.

Example:
```
$./hsh
^-^
```

If a command line argument is invoked, **hsh** will take that first argument as a file from which to read commands.

Example:
```
$ cat text
echo 'alx'
$ ./hsh text
'alx'
$
```

### Environment

Upon invocation, **hsh** receives and copies the environment of the parent process in which it was executed. This environment is an array of *name-value* strings describing variables in the format *NAME=VALUE*. A few key environmental variables are:

#### HOME
The home directory of the current user and the default directory argument for the **cd** builtin command.

```
$ echo "echo $HOME" | ./hsh
/home/vagrant
```

#### PWD
The current working directory as set by the **cd** command.

```
$ echo "echo $PWD" | ./hsh
/home/vagrant/alx/simple_shell
```

#### OLDPWD
The previous working directory as set by the **cd** command.

```
$ echo "echo $OLDPWD" | ./hsh
/home/vagrant/alx/bog-062019-test_suite
```

#### PATH
A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

```
$ echo "echo $PATH" | ./hsh
/home/vagrant/.cargo/bin:/home/vagrant/.local/bin:/home/vagrant/.rbenv/plugins/ruby-build/bin:/home/vagrant/.rbenv/shims:/home/vagrant/.rbenv/bin:/home/vagrant/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/vagrant/.cargo/bin:/home/vagrant/workflow:/home/vagrant/.local/bin
```

### Command Execution

After receiving a command, **hsh** tokenizes it into words using `" "` as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command. **hsh** then proceeds with the following actions:
1. If the first character of the command is neither a slash (`\`) nor dot (`.`), the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
2. If the first character of the command is none of a slash (`\`), dot (`.`), nor builtin, **hsh** searches each element of the **PATH** environmental variable for a directory containing an executable file by that name.
3. If the first character of the command is a slash (`\`) or dot (`.`) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

### Exit Status 

**hsh** returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.
If a command is not found, the return status is 127; if a command is found but is not executable, the return status is 126.
All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

### Signals

While running in interactive mode, **hsh** ignores the keyboard input ctrl+c. Alternatively, an input of End-Of-File ctrl+d will exit the program.

User hits ctrl+d in the foutrh command.
```
$ ./hsh
^-^ ^C
^-^ ^C
^-^ ^C
^-^
```

### Variable Replacement

**hsh** interprets the `$` character for variable replacement.

#### $ENV_VARIABLE
`ENV_VARIABLE` is substituted with its value.

Example:
```
$ echo "echo $PWD" | ./hsh
/home/vagrant/alx/simple_shell
```

#### $?
`?` is substitued with the return value of the last program executed.

Example:
```
$ echo "echo $?" | ./hsh
0
```

#### $$
The second `$` is substitued with the current process ID.

Example:
```
$ echo "echo $$" | ./hsh
3855
```

### Comments

**hsh** ignores all words and characters preceeded by a `#` character on a line.

Example:
```
$ echo "echo 'alx' #this will be ignored!" | ./hsh
'alx'
```

### Operators

**hsh** specially interprets the following operator characters:

#### ; - Command separator
Commands separated by a `;` are executed sequentially.

Example:
```
$ echo "echo 'hello' ; echo 'world'" | ./hsh
'hello'
'world'
```

#### && - AND logical operator
`command1 && command2`: `command2` is executed if, and only if, `command1` returns an exit status of zero.

Example:
```
$ echo "error! && echo 'alx'" | ./hsh
./shellby: 1: error!: not found
$ echo "echo 'my name is' && echo 'alx'" | ./hsh
'my name is'
'alx'
```

#### || - OR logical operator
`command1 || command2`: `command2` is executed if, and only if, `command1` returns a non-zero exit status.

Example:
```
$ echo "error! || echo 'wait for it'" | ./hsh
./hsh: 1: error!: not found
'wait for it'
```

The operators `&&` and `||` have equal precedence, followed by `;`.

### Builtin Commands

#### cd
  * Usage: `cd [DIRECTORY]`
  * Changes the current directory of the process to `DIRECTORY`.
  * If no argument is given, the command is interpreted as `cd $HOME`.
  * If the argument `-` is given, the command is interpreted as `cd $OLDPWD` and the pathname of the new working directory is printed to standad output.
  * If the argument, `--` is given, the command is interpreted as `cd $OLDPWD` but the pathname of the new working directory is not printed.
  * The environment variables `PWD` and `OLDPWD` are updated after a change of directory.

Example:
```
$ ./hsh
^-^ pwd
/home/vagrant/alx/simple_shell
$ cd ../
^-^ pwd
/home/vagrant/alx
^-^ cd -
^-^ pwd
/home/vagrant/alx/simple_shell
```

#### exit
  * Usage: `exit [STATUS]`
  * Exits the shell.
  * The `STATUS` argument is the integer used to exit the shell.
  * If no argument is given, the command is interpreted as `exit 0`.

Example:
```
$ ./hsh
$ exit
```

#### env
  * Usage: `env`
  * Prints the current environment.

Example:
```
$ ./hsh
$ env
NVM_DIR=/home/vagrant/.nvm
...
```

#### setenv
  * Usage: `setenv [VARIABLE] [VALUE]`
  * Initializes a new environment variable, or modifies an existing one.
  * Upon failure, prints a message to `stderr`.

Example:
```
$ ./hsh
$ setenv NAME alx
$ echo $NAME
alx
```

#### unsetenv
  * Usage: `unsetenv [VARIABLE]`
  * Removes an environmental variable.
  * Upon failure, prints a message to `stderr`.

Example:
```
$ ./hsh
$ setenv NAME alx
$ unsetenv NAME
$ echo $NAME

$
```

## Authors & Copyrights

* [Yoseph Seyoum](https://github.com/Yoseph47)
* [Patricia A. Rukud'de](https://github.com/eri2pear)

## More information

**hsh** is a simple shell unix command interpreter that is part of the alx low level programming module at alx School and is intended to emulate the basics **sh** shell. All the information given in this README is based on the **hsh** and **bash** man (1) pages.

## Tasks

###0. Betty would be proud
Write a beautiful code that passes the Betty checks

### 1. Simple shell 0.1
Write a UNIX command line interpreter.

Usage: simple_shell
Your Shell should:

Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
You don’t have to:

use the PATH
implement built-ins
handle special characters : ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments
execve will be the core part of your Shell, don’t forget to pass the environ to it…

### 2. Simple shell 0.2
Simple shell 0.1 +

Handle command lines with arguments

### 3. Simple shell 0.3
Simple shell 0.2 +

Handle the PATH
fork must not be called if the command doesn’t exist

### 4. Simple shell 0.4
Simple shell 0.3 +

Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit

### 5. Simple shell 1.0
Simple shell 0.4 +

Implement the env built-in, that prints the current environment

### 6. Simple shell 0.1.1
Simple shell 0.1 +

Write your own getline function
Use a buffer to read many chars at once and call the least possible the read system call
You will need to use static variables
You are not allowed to use getline
You don’t have to:

be able to move the cursor

### 7. Simple shell 0.2.1
Simple shell 0.2 +

You are not allowed to use strtok

### 8. Simple shell 0.4.1
Simple shell 0.4 +

handle arguments for the built-in exit
Usage: exit status, where status is an integer used to exit the shell

### 9. setenv, unsetenv
Simple shell 1.0 +

Implement the setenv and unsetenv builtin commands

setenv
Initialize a new environment variable, or modify an existing one
Command syntax: setenv VARIABLE VALUE
Should print something on stderr on failure
unsetenv
Remove an environment variable
Command syntax: unsetenv VARIABLE
Should print something on stderr on failure

### 10. cd
Simple shell 1.0 +

Implement the builtin command cd:

Changes the current directory of the process.
Command syntax: cd [DIRECTORY]
If no argument is given to cd the command must be interpreted like cd $HOME
You have to handle the command cd -
You have to update the environment variable PWD when you change directory
man chdir, man getcwd

### 11. ;
Simple shell 1.0 +

Handle the commands separator ;

### 12. && and ||
Simple shell 1.0 +

Handle the && and || shell logical operators

### 13. alias
Simple shell 1.0 +

Implement the alias builtin command
Usage: alias [name[='value'] ...]
alias: Prints a list of all aliases, one per line, in the form name='value'
alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value

### 14. Variables
Simple shell 1.0 +

Handle variables replacement
Handle the $? variable
Handle the $$ variable

### 15. Comments
Simple shell 1.0 +

Handle comments (#)

### 16. File as input
Simple shell 1.0 +

Usage and instruction simple_shell [filename]
Your shell can take a file as a command line argument
The file contains all the commands that your shell should run before exiting
The file should contain one command per line
In this mode, the shell should not print a prompt and should not read from stdin
