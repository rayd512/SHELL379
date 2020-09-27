#include "shell_commands.h"

using namespace std;

void exit_shell379(struct rusage& usage) {
	
	while(wait(NULL) > 0);

	getrusage(RUSAGE_CHILDREN, &usage);

	cout << endl;
	cout << "Resources used: " << endl;
	cout << "User time =     " << usage.ru_utime.tv_sec << " seconds" << endl;
	cout << "Sys  time =     " << usage.ru_stime.tv_sec << " seconds" << endl;	
	
	// kill(getppid(), SIGINT);
	
	_exit(0);
}


void display_jobs(struct rusage& usage, Process_Table &process_table) {
	int running_processes;


	process_table.update();
	running_processes = process_table.size();
	getrusage(RUSAGE_CHILDREN, &usage);

	cout << endl;
	cout << "Running Processes:" << endl;
	if (running_processes != 0) {
		cout << " #     PID S SEC COMMAND" << endl;
		for (int i = 0; i < running_processes; i++) {
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
	
}


void signal_job(Process_Table &process_table, vector<string> split_command, int signal) {
	process_table.update();
	vector<Process> ps_vec = process_table.processes;

	for (int i = 0; i < int(ps_vec.size()); i++) {
		if(stoi(split_command[1]) == (int)ps_vec[i].pid) {
			kill(ps_vec[i].pid, signal);
		}
	}
}
