#include "shell_commands.h"

using namespace std;

/** Exits the program
 *
 * Waits for any processes spawned by the shell that are still running and then 
 * displays the total user and cpu time of the whole program
 *
 * @param usage a struct used to calculate rusage
 */
void exit_shell379(struct rusage& usage) {
	
	// Wait for processes to terminate
	while(wait(NULL) > 0);

	// Get usage time and display to STDOUT
	getrusage(RUSAGE_CHILDREN, &usage);

	cout << endl;
	cout << "Resources used: " << endl;
	cout << "User time =     " << usage.ru_utime.tv_sec << " seconds" << endl;
	cout << "Sys  time =     " << usage.ru_stime.tv_sec << " seconds" << endl;	
	
	_exit(EXIT_SUCCESS);
}

/** Displays jobs
 *
 * Displays all processes spawned by the shell that have not been terminated.
 *
 * @param usage a struct used to calculate rusage
 * @param process_table holds all current processes
 */
void display_jobs(struct rusage& usage, Process_Table &process_table) {
	int running_processes;

	// Get and update information
	process_table.update();
	running_processes = process_table.size();
	getrusage(RUSAGE_CHILDREN, &usage);

	// Display information
	cout << endl;
	cout << "Running Processes:" << endl;
	if (running_processes != 0) {
		cout << " #     PID S SEC COMMAND" << endl;
		for (int i = 0; i < running_processes; i++) {
			cout << " " << i << ":" << setw(6) 
				<< process_table.processes[i].pid << " "
				<< process_table.processes[i].get_status() << " " 
				<< process_table.processes[i].get_time() << "   " 
				<< process_table.processes[i].get_command() << endl;
		}
	}
	cout << "Processes =     " << process_table.size() << endl;
	cout << "Completed Processes: " << endl;
	cout << "User time =     " << usage.ru_utime.tv_sec << " seconds" << endl;
	cout << "Sys  time =     " << usage.ru_stime.tv_sec << " seconds" << endl;
	cout << endl;
	
}


/** Sends a job a specified signal
 *
 * Issues a process a singal, i.e. kill, suspend, resume
 *
 * @param process_table holds all current processes
 * @param split_command a vector a strings holding the command issued 
 *						by user split by spaces
 * @param signal The signal to send the process
 */
void signal_job(Process_Table &process_table, vector<string> split_command,
				int signal) {

	process_table.update();
	vector<Process> ps_vec = process_table.processes;
	bool hasMatch = false;

	// Loop through PID's and find a matching one. Then send the signal 
	// requested
	for (int i = 0; i < int(ps_vec.size()); i++) {
		if(stoi(split_command[1]) == (int)ps_vec[i].pid) {
			if(kill(ps_vec[i].pid, signal) != 0) {
				cout << "Operation Unsuccesfull" << endl;
			}
			hasMatch = true;
		}
	}

	if(!hasMatch) {
		cout << "Could not find PID: " + split_command[1] << endl;
	}
}

/** Waits for a sepcified job to finish executing
 *
 * Will lock up the terminal until a specified process has finished executing
 *
 * @param process_table holds all current processes
 * @param split_command a vector a strings holding the command issued 
 *						by user split by spaces
 */
void wait_job(Process_Table &process_table, vector<string> split_command) {
	
	process_table.update();
	int state;
	vector<Process> ps_vec = process_table.processes;
	bool hasMatch = false;

	// Loop through PID's to check if PID exists. Wait for it if it does.
	for (int i = 0; i < int(ps_vec.size()); i++) {
		if(stoi(split_command[1]) == (int)ps_vec[i].pid) {
			waitpid(ps_vec[i].pid, &state, WUNTRACED);
			hasMatch = true;
		}
	}

	if(!hasMatch) {
		cout << "Could not find PID: " + split_command[1] << endl;
	}
}
