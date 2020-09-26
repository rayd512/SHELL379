#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "string_funcs.h"
#include "shell_commands.h"
#include "process.h"

void process_input(std::string command);