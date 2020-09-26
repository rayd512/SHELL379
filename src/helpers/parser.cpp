#include "parser.h"

using namespace std;

const vector<string> keywords = {"exit", "jobs", "kill", "resume", "sleep", "suspend", "wait"};


void process_input(string command) {
	vector<string> split_command = split_input(command);
	// for(int i = 0; i < split_command.size(); i++)
	// 	cout << split_command[i] << endl;
	struct rusage usage;
	vector<Process> process_table;
	pid_t cpid = fork();

	if (cpid < 0) {
		perror("Fork Failed");
		_exit(EXIT_FAILURE);
	}
	else if (cpid == 0) {
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

		const char **argv = convert_string_vec_to_char(split_command);

		// for (int i = 0; i < int(split_command.size()); i++) {
		// 	cout << argv[i] << endl;
		// }

		execvp(argv[0], (char **) argv);
		cout << "Exec Failed" << endl;
		_exit(EXIT_FAILURE);

	} else {
		wait(NULL);
		cout << endl;
	}

	// switch(split_command[0]) {
	// 	case keywords[0]: 
	// 		exit_shell379();
	// 		break
	// }
}
