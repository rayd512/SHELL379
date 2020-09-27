#include "process.h"

Process::Process(int process_number, pid_t id, std::string command) {
	this->pid = id;
	this->number = process_number;
	this->command = command;
	Process::check_status();
}


int Process::get_time() {
	return this->time;
}

char Process::get_status() {
	return this->status;
}

std::string Process::get_command() {
	return this->command;
}

void Process::check_status() {
	int status;
	pid_t return_pid = waitpid(this->pid, &status, WNOHANG);

	if (return_pid == -1) {
		this->status = 'E';
	} else if (return_pid == 0) {
		this->status = 'R';
	} else {
		this->status = 'D';
	}
}