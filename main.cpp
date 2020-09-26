#include <iostream>
#include "validity.h"
#include "parser.h"

using namespace std;

int main(void) {
	string command;
	while (true) {
		cout << "SHELL379: ";
		getline(cin, command);
		if(is_valid_input(command)) {
			process_input(command);
		} else {
			cout << "Not a valid command" << endl;
		}
	}

}