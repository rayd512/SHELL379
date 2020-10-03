#include "Process_Table.h"

using namespace std;

/** Updates the process table
 *
 *
 * Updates the process table by calling "ps -o pid,time,state" and parsing the
 * STDOUT. This is then compared with internal memory and then updated according
 * to the STDOUT
 */
void Process_Table::update() {
	
	FILE *all_ps;
	char ps[80];

	// Call popen to get output of ps
	all_ps = popen("ps -o pid,time,state", "r");

	// Errror check
	if (all_ps == NULL) {
		perror("Failed to Popen");
	}


	// For each process in the table, set boolean variable "isInPS" to fale
	for(int i = 0; i < int(processes.size()); i++) {
		processes[i].isInPS = false;
	}

	// Loop through STDOUT of ps and check for relevant PID's. Find the 
	// matching PID in internal table and update the information. If the PID is
	// found, then "isInPS" for the process is set to true

	while(fgets(ps, sizeof(ps), all_ps) != NULL) {
		for(int i = 0; i < int(processes.size()); i++) {
			char pid_arr[21];
			sprintf(pid_arr, "%ld", (long)processes[i].pid);

			// Check for matching PID and update info
			if (strstr(ps, pid_arr)) {
				vector<string> ps_info = split_input((string)ps);
				processes[i].set_status(ps_info[2][0]);
				processes[i].set_time(convert_time(ps_info[1]));
				processes[i].isInPS = true;
			}
		}
	}

	// If there was no match to a PID in the ps call, remove it from the internal
	// table. This is when "isInPS" was not set to true in the while loop above
	for(int i = 0; i < int(processes.size()); i++) {
		if(processes[i].isInPS == false) {
			processes.erase(processes.begin() + i);
		}
	}

	pclose(all_ps);

}


/** Call to return the size of the table.
 *
 * Returns the size of the vector holding the processes
 */
int Process_Table::size() {
	return processes.size();
}

/** Call to add a process to the table
 *
 * Calls push_back on the process vector to add the process
 *
 * @param process a process to add to the table
 */
void Process_Table::add(Process child) {
	processes.push_back(child);
}

/** Converts time
 *
 * Converts the time return by "ps -o time" and returns it as seconds of 
 * type int
 *
 * @param time the time to be converted 
 *
 * @return an int representation of the time in seconds
 */
int Process_Table::convert_time(string time) {
	string hour = time.substr(0,2);
	string minute = time.substr(3,2);
	string seconds = time.substr(6,2);
	return stoi(hour) * 36000 + stoi(minute) * 60 + stoi(seconds);
}