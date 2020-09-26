#include "parser.h"

using namespace std;

const vector<string> keywords = {"exit", "jobs", "kill", "resume", "sleep", "suspend", "wait"};


void process_input(string command) {
	vector<string> split_command = split_input(command);
	struct rusage usage;

	if (fork() == 0) {
		for (int i = 0; i < int(keywords.size()); i++) {
			if (split_command[0] == keywords[i]) {
				switch(i) {
					case 0:
						exit_shell379(usage);
						break;
					case 1:
						display_jobs(usage);
						break;
				}
			}
		}

	char *argv[] = {"sleep", "3", NULL};
	execvp(argv[0], argv);
	cout << "Here" << endl;
	} else {
		wait(NULL);
	}

	// switch(split_command[0]) {
	// 	case keywords[0]: 
	// 		exit_shell379();
	// 		break
	// }
}
