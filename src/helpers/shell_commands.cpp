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


void display_jobs(struct rusage& usage) {

	getrusage(RUSAGE_CHILDREN, &usage);

	cout << endl;
	cout << "Running Processes:" << endl;
	cout << "Processes =     " << endl;
	cout << "Completed Processes: " << endl;
	cout << "User time =     " << usage.ru_utime.tv_sec << " seconds" << endl;
	cout << "Sys  time =     " << usage.ru_stime.tv_sec << " seconds" << endl;
	cout << endl;
	
	_exit(0);
}
