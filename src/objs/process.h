#pragma once

#include <unistd.h>
#include <string>

class Process {

	public:
		pid_t pid;

	private:
		char status;
		int time;
		std::string command;

	Process(pid_t id);

};