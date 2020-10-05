# SHELL379

## Description  
A mini shell which has overly restrictive syntax. The goal of this project was to
explore how shell's work. 

## How to use  
This shell will contain most basic commands. A description is show below:  

```
exit - End the execution of shell379. Wait until all processes initiated by the
shell are complete. Print out the total user and system time for all
processes run by the shell.

jobs - Display the status of all running processes spawned by shell379. See
the print format below in the example.

kill <int> - Kill process <int>.

resume <int> - Resume the execution of process <int>. This undoes a suspend.

sleep <int> - Sleep for <int> seconds.

suspend <int> - Suspend execution of process <int>. A resume will reawaken it.

wait <pid> - Wait until process <int> has completed execution.

<cmd> <arg>* Spawn a process to execute command <cmd> with 0 or more arguments
<arg>.

There are three special arguments that a command may have:

& - If used, this must be the last argument and indicates that the command is
to be executed in the background.

<fname - This argument is the “<” character followed by a string of characters, a file
name to be used for program input.

>fname - This argument is the “>” character followed by a string of characters, a file
name to be used for program output.
```