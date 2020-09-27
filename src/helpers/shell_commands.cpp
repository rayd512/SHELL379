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


void display_jobs(struct rusage& usage, vector<Process> process_table) {
	int running_processes = process_table.size();
	getrusage(RUSAGE_CHILDREN, &usage);

	cout << endl;
	cout << "Running Processes:" << endl;
	if (running_processes != 0) {
		cout << " #     PID S SEC COMMAND" << endl;
		for (int i = 0; i < int(process_table.size()); i++) {
			process_table[i].check_status();
			cout << " " << i << ":   " << process_table[i].pid << " "
				<< process_table[i].get_status() << " " << process_table[i].get_time()
				<< "   " << process_table[i].get_command() << endl;
		}
	}
	cout << "Processes =     " << running_processes << endl;
	cout << "Completed Processes: " << endl;
	cout << "User time =     " << usage.ru_utime.tv_sec << " seconds" << endl;
	cout << "Sys  time =     " << usage.ru_stime.tv_sec << " seconds" << endl;
	cout << endl;
	
	// _exit(0);
}
