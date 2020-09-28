#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "string_funcs.h"
#include "shell_commands.h"
#include "process.h"
#include "Process_Table.h"

void process_input(std::string command, struct rusage &usage,
					Process_Table &process_table);

