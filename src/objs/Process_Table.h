#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <process.h>
#include <cstring>
#include <string>
#include <string_funcs.h>

/**
 * An implementation of a Process Table for a shell
 *
 * Holds a vector of class process and contains methods
 * of maintaining the processes
 *
 */

class Process_Table {

	public:
		std::vector<Process> processes;
		void update();
		int size();
		void add(Process child);

	private:
		int convert_time(std::string time);

};