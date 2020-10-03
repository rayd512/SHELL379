#include <iostream>
#include "validity.h"
#include "parser.h"
#include "Process_Table.h"

using namespace std;


// Simple main function that will print "Shell 379: " and take in inputs.
// Inputs are passed to functions to ensure validity and to parse.
int main(void) {
	
	string command;
	// Struct to be used to keep track of system and user time of all processes
	struct rusage usage;
	// Instantiate process table here to be used for whole program. See Process_table.h
	// for more information
	Process_Table process_table;

	// Infinite loop to take input and process it
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