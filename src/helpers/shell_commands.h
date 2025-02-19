#pragma once

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <process.h>
#include <vector>
#include <iomanip>
#include <Process_Table.h>

void exit_shell379(struct rusage& usage, Process_Table &process_table);

void display_jobs(struct rusage& usage, Process_Table &process_table);

void signal_job(Process_Table &process_table, std::vector<std::string> split_command, int signal);

void wait_job(Process_Table &process_table, std::vector<std::string> split_command);
