#pragma once

#include <vector>
#include <iostream>
#include <process.h>


class Process_Table {

	public:
		std::vector<Process> processes;
		friend class Process;
		void update();
		int size();
		void add(Process child);

};