#include "process.h"

using namespace std;

Process::Process(int process_number, pid_t id, std::string command) {
	this->pid = id;
	this->number = process_number;
	this->command = command;
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

void Process::set_status(char status) {
	this->status = status;
}

void Process::set_time(int time) {
	this->time = time;
}