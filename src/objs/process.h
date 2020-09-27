#pragma once

#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>

class Process {

	public:
		int number;
		pid_t pid;
		Process(int process_number, pid_t id, std::string command);
		int get_time();
		char get_status();
		std::string get_command();
		void check_status();

	private:
		char status;
		int time = 0;
		std::string command;

	
};