#include "Process_Table.h"

using namespace std;

void Process_Table::update() {
	for(int i = 0; i < int(processes.size()); i++) {
		processes[i].check_status();
		if(processes[i].get_status() == 'D' || processes[i].get_status() == 'E') {
			processes.erase(processes.begin() + i);
			// cout << "Erased" << endl;
		}
	}

}

int Process_Table::size() {
	return processes.size();
}

void Process_Table::add(Process child) {
	processes.push_back(child);
}
