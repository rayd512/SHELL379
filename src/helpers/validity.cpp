#include "validity.h"

using namespace std;

const int LINE_LENGTH = 100;
const int MAX_ARGS = 7;
const int MAX_LENGTH = 20;

bool is_valid_input(string command) {

	if (command.length() > LINE_LENGTH) {
		return false;
	}

	vector<string> split_command = split_input(command);

	if(split_command.size() - 1 > MAX_ARGS) {
		return false;
	}


	for (int i = 0; i < int(split_command.size()); i++) {
		if(split_command[i].length() > MAX_LENGTH) {
			return false;
		}
	}

	return true;

}