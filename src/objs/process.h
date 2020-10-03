#pragma once

#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>


/** An implementation of a process
 *
 * Holds all the relevant information of a process
 */
class Process {

	public:
		pid_t pid;
		bool isInPS = true;
		Process(pid_t id, std::string command);
		int get_time();
		char get_status();
		std::string get_command();
		void set_time(int time);
		void set_status(char status);

	private:
		char status;
		int time = 0;
		std::string command;

	
};