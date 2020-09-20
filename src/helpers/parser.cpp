#include "parser.h"

using namespace std;

const vector<string> keywords = {"exit", "jobs", "kill", "resume", "sleep", "suspend", "wait"};

void process_input(string command) {
	vector<string> split_command = split_input(command);

	for (int i = 0; i < int(keywords.size()); i++) {
		if (split_command[0] == keywords[i]) {
			cout << "yes" << endl;
		}
	}
}