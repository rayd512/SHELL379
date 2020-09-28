#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <process.h>
#include <cstring>
#include <string>
#include <string_funcs.h>
// #include <utility>

class Process_Table {

	public:
		std::vector<Process> processes;
		void update();
		int size();
		void add(Process child);
		void print_processes();

	private:
		int convert_time(std::string time);

};