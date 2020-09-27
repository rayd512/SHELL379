#pragma once

#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/resource.h>
#include <process.h>
#include <vector>

void exit_shell379(struct rusage& usage);

void display_jobs(struct rusage& usage, std::vector<Process> process_table);