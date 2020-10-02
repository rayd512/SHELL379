#include "parser.h"

using namespace std;

const vector<string> keywords = {"exit", "jobs", "kill", "resume", "suspend",
								"wait", "sleep"};

void call_wait(int signum);
void preprocess_input(vector<string> &command, bool &isBackgroundProcess,
					  vector<pair<string, string> > &files);

void process_input(string command, struct rusage &usage, Process_Table &process_table) {
	vector<string> split_command = split_input(command);
	vector<pair<string, string> > files;
	pid_t cpid;
	int status;
	bool isShell379Command = false;
	bool isBackgroundProcess = false;
	bool isSleep = false;


	preprocess_input(split_command, isBackgroundProcess, files);

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

	if (!isShell379Command) {
		cpid = fork();
		if (cpid < 0) {
			perror("Fork Failed");
			_exit(EXIT_FAILURE);
		}
		else if (cpid == 0) {
			if(!isSleep) {
				vector<char*> argv(split_command.size() + 1);

				if (files.size() != 0 && files.size() <= 2) {
					for(int i = 0; i < int(files.size()); i++) {
						if(files[i].first == "<") {
							int in = open(&files[i].second[0], O_RDONLY);
							dup2(in, STDIN_FILENO);
							close(in);
						} else {
							int out = open(&files[i].second[0], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
							dup2(out, STDOUT_FILENO);
							close(out);
						}
					}
				}

				for (int i = 0; i < int(split_command.size()); i++) {
					argv[i] = &split_command[i][0];
				}

				execvp(argv[0], argv.data());
				// cout << "Exec Failed" << endl;
				_exit(EXIT_FAILURE);
			} else {
				sleep(stoi(split_command[1]));
				_exit(EXIT_SUCCESS);
			}

		} else {
			if (!isBackgroundProcess) {

				signal(SIGCHLD, SIG_DFL);
				waitpid(cpid, &status, WUNTRACED);

				cout << endl;
			} else {
				signal(SIGCHLD, call_wait);
				Process child_process = Process(process_table.size(), cpid, command);
				process_table.add(child_process);

			}
		}
	}
}

void call_wait(int signum) {
	wait(NULL);
}

void preprocess_input(vector<string> &command, bool &isBackgroundProcess,
					  vector<pair<string, string> > &files) {

	if(command.back() == "&") {
		command.pop_back();
		isBackgroundProcess = true;
	}

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