#ifndef SHELL_H
#define SHELL_H

// Starts the shell loop: reads input, echoes, executes commands
void shell_loop();

// Executes a parsed command string
void execute_command(const char *cmd);

#endif
