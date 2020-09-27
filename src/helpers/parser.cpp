#include "parser.h"

using namespace std;

const vector<string> keywords = {"exit", "jobs", "kill", "resume", "suspend", "wait"};

void preprocess_input(vector<string> &command, bool &isBackgroundProcess);

void process_input(string command, struct rusage &usage, vector<Process> &process_table) {
	vector<string> split_command = split_input(command);
	pid_t cpid;
	bool isShell379Command = false;
	bool isBackgroundProcess = false;
	preprocess_input(split_command, isBackgroundProcess);

	for (int i = 0; i < int(keywords.size()); i++) {
		if (split_command[0] == keywords[i]) {
			switch(i) {
				case 0:
					exit_shell379(usage);
					break;
				case 1:
					display_jobs(usage, process_table);
					break;
			}
			isShell379Command = true;
		}
	}

	if (!isShell379Command) {
		cpid = fork();
		if (cpid < 0) {
			perror("Fork Failed");
			_exit(EXIT_FAILURE);
		}
		else if (cpid == 0) {
			vector<char *> argv(split_command.size() + 1);

			for (int i = 0; i < int(split_command.size()); i++) {
				argv[i] = &split_command[i][0];
			}

			execvp(argv[0], argv.data());
			cout << "Exec Failed" << endl;
			_exit(EXIT_FAILURE);

		} else {
			if (!isBackgroundProcess) {
				wait(NULL);
				cout << endl;
			} else {
				Process child_process = Process(process_table.size(), cpid, command);
				process_table.push_back(child_process);
			}
		}
	}
}

void preprocess_input(vector<string> &command, bool &isBackgroundProcess) {
	if(command.back() == "&") {
		command.pop_back();
		isBackgroundProcess = true;
	}
}