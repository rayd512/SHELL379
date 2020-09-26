#pragma once

#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>

void exit_shell379(struct rusage& usage);

void display_jobs(struct rusage& usage);