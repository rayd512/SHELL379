#include "shell_commands.h"

using namespace std;

void exit_shell379(struct rusage& usage) {

	getrusage(RUSAGE_CHILDREN, &usage);

	cout << endl;
	cout << "Resources used: " << endl;
	cout << "User time =     " << usage.ru_utime.tv_sec << " seconds" << endl;
	cout << "Sys  time =     " << usage.ru_stime.tv_sec << " seconds" << endl;	
	kill(getppid(), SIGINT);
	
	_exit(0);
}


void display_jobs(struct rusage& usage, Process_Table process_table) {
	int running_processes = process_table.size();
	getrusage(RUSAGE_CHILDREN, &usage);

	cout << endl;
	cout << "Running Processes:" << endl;
	if (running_processes != 0) {
		cout << " #     PID S SEC COMMAND" << endl;
		for (int i = 0; i < running_processes; i++) {
			process_table.update();
			cout << " " << i << ":   " << process_table.processes[i].pid << " "
				<< process_table.processes[i].get_status() << " " << process_table.processes[i].get_time()
				<< "   " << process_table.processes[i].get_command() << endl;
		}
	}
	cout << "Processes =     " << process_table.size() << endl;
	cout << "Completed Processes: " << endl;
	cout << "User time =     " << usage.ru_utime.tv_sec << " seconds" << endl;
	cout << "Sys  time =     " << usage.ru_stime.tv_sec << " seconds" << endl;
	cout << endl;
	
	// _exit(0);
}
