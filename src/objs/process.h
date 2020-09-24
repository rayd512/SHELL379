#pragma once

#include <string>

class Process {

	public:
		int process_id;

	private:
		char status;
		int time;
		std::string command;

	Process(int id);

};