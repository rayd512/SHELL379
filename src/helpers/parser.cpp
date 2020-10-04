#include "parser.h"

using namespace std;

// Keywords for user implemented functions, not to be "exec'd"
const vector<string> keywords = {"exit", "jobs", "kill", "resume", "suspend",
								"wait", "sleep"};

void call_wait(int signum);
void preprocess_input(vector<string> &command, bool &isBackgroundProcess,
					  vector<pair<string, string> > &files);

/** Processes command issued by user
 *
 * Parses the command inputted by user and calls the relevant functions to
 * properly execute it.
 *
 * @param usage a struct to hold the user and cpu time 
 * @param process_table contains the vector holding all processes spawn by the 
 *   					shell
 */
void process_input(string command, struct rusage &usage,
				   Process_Table &process_table) {

	vector<pair<string, string> > files;
	pid_t cpid;
	int status;
	bool isShell379Command = false;
	bool isBackgroundProcess = false;
	bool isSleep = false;
	vector<string> split_command;

	// Splits users input by space and returns a vector
	split_command = split_input(command);

	// Checks for the "&", "<", and ">" symbols in the commands
	preprocess_input(split_command, isBackgroundProcess, files);

	// Loop through command and check for keywords that use a user
	// implemented function. If there is a match, using the case statement
	// call the corresponding function. Special case if the command is sleep
	for (int i = 0; i < int(keywords.size()); i++) {
		if (split_command[0] == keywords[i]) {
			switch(i) {
				case 0:
					exit_shell379(usage);
					break;
				case 1:
					display_jobs(usage, process_table);
					break;
				case 2:
					signal_job(process_table, split_command, SIGKILL);
					break;
				case 3:
					signal_job(process_table, split_command, SIGCONT);
					break;
				case 4:
					signal_job(process_table, split_command, SIGSTOP);
					break;
				case 5:
					wait_job(process_table, split_command);
					break;
				case 6:
					isSleep = true;
					break;
			}
			if(!isSleep) {
				isShell379Command = true;
			}
		}
	}

	// If command is not a user implemented function, fork and execvp the command
	if (!isShell379Command) {
		cpid = fork();
		if (cpid < 0) {
			perror("Fork Failed");
			_exit(EXIT_FAILURE);
		}
		else if (cpid == 0) {
			if(!isSleep) {
				vector<char*> argv(split_command.size() + 1);

				// Handles input and and output redirection
				if (files.size() != 0 && files.size() <= 2) {
					for(int i = 0; i < int(files.size()); i++) {
						// Take input from a file
						if(files[i].first == "<") {
							int in = open(&files[i].second[0], O_RDONLY);
							if(in == -1) {
								perror("Error ");
								_exit(EXIT_FAILURE);
							}
							dup2(in, STDIN_FILENO);
							close(in);
						} else { 
							// export STDOUT to a file
							int out = open(&files[i].second[0],
										O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
							if(out == -1) {
								perror("Error ");
								_exit(EXIT_FAILURE);
							}
							dup2(out, STDOUT_FILENO);
							close(out);
						}
					}
				}

				// Convert vector of strings unto a format execvp will accept
				for (int i = 0; i < int(split_command.size()); i++) {
					argv[i] = &split_command[i][0];
				}

				execvp(argv[0], argv.data());
				_exit(EXIT_FAILURE);
			} else { 
				// special case for when the command is sleep, (user implemented)
				sleep(stoi(split_command[1]));
				_exit(EXIT_SUCCESS);
			}

		} else {
			if (!isBackgroundProcess) {
				signal(SIGCHLD, SIG_DFL);
				// Wait for child process if not run in background
				waitpid(cpid, &status, WUNTRACED);

				cout << endl;
			} else {
				// Add process to process table if run in background
				// Signal to recieve signals from children and avoid zombies
				signal(SIGCHLD, SIG_IGN);
				Process child_process = Process(cpid, command);
				process_table.add(child_process);

			}
		}
	}
}


/** Preprocesses the input 
 *
 * Identifies any special arguments and records relevant information of them
 *
 * @param command the command issued by the user
 * @param isBackgroundProcess boolean variable, true if process is issued to 
 *                            run in the background
 * @param files an empty vector, that will hold the file names of any input or
 *				output
 */
void preprocess_input(vector<string> &command, bool &isBackgroundProcess,
					  vector<pair<string, string> > &files) {

	if(command.back() == "&") {
		command.pop_back();
		isBackgroundProcess = true;
	}

	// Check for inputs and outputs. If found, remove from command vector,
	// and add to the files vector
	for(int i = 0; i < int(command.size()); i++ ) {
		if(command[i].find("<") != string::npos) {
			pair<string,string> input;
			input.first = "<";
			input.second = command[i].substr(1,command[i].size() - 1);
			files.push_back(input);
			command.erase(command.begin() + i);
		}

		if(command[i].find(">") != string::npos) {
			pair<string,string> output;
			output.first = ">";
			output.second = command[i].substr(1,command[i].size() - 1);
			files.push_back(output);
			command.erase(command.begin() + i);
		}
	}
}