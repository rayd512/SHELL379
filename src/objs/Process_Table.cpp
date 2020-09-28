#include "Process_Table.h"

using namespace std;

void Process_Table::update() {
	FILE *all_ps;
	char ps[80];

	all_ps = popen("ps -eo pid,etime,state", "r");

	if (all_ps == NULL) {
		perror("popen");
	}

	// vector<Pair<pid_t, bool>> ps_tracker;

	// for (int i = 0; i < int(processes.size()); i++) {
	// 	ps_tracker.push_back(Pair<pid_t, bool> ps(processes[i].pid, false));
	// }

	for(int i = 0; i < int(processes.size()); i++) {
		processes[i].isInPS = false;
	}

	while(fgets(ps, sizeof(ps), all_ps) != NULL) {
		for(int i = 0; i < int(processes.size()); i++) {
			char pid_arr[21];
			sprintf(pid_arr, "%ld", (long)processes[i].pid);
			if (strstr(ps, pid_arr)) {
				vector<string> ps_info = split_input((string)ps);
				if (ps_info[2][0] == 'Z') {
					processes.erase(processes.begin() + i);
				} else {
					processes[i].set_status(ps_info[2][0]);
					processes[i].set_time(convert_time(ps_info[1]));
				}
				processes[i].isInPS = true;
			}
		}
	}

	for(int i = 0; i < int(processes.size()); i++) {
		if(processes[i].isInPS == false) {
			processes.erase(processes.begin() + i);
		}
	}


	pclose(all_ps);

}

int Process_Table::size() {
	return processes.size();
}

void Process_Table::add(Process child) {
	processes.push_back(child);
}

int Process_Table::convert_time(string time) {
	string minute = time.substr(0,2);
	string seconds = time.substr(3,2);
	return stoi(minute) * 60 + stoi(seconds);
}