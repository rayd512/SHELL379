#include <iostream>
#include "validity.h"
#include "parser.h"
#include "Process_Table.h"

using namespace std;

int main(void) {
	string command;
	struct rusage usage;
	// vector<Process> process_table;
	Process_Table process_table;
	while (true) {
		cout << "SHELL379: ";
		getline(cin, command);
		if(is_valid_input(command)) {
			process_input(command, usage, process_table);
		} else {
			cout << "Not a valid command" << endl;
		}
	}

}