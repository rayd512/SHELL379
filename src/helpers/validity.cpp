#include "validity.h"

using namespace std;

const int LINE_LENGTH = 100;
const int MAX_ARGS = 7;
const int MAX_LENGTH = 20;

/** Checks if an input is valid
 *
 * Given the constraints, the function checks if the constraints are met 
 * with the input
 *
 * @param command the input from the user
 * @return true if input is valid
 */
bool is_valid_input(string command) {

	if (command.length() > LINE_LENGTH) {
		return false;
	}

	vector<string> split_command = split_input(command);

	if(split_command.size() > MAX_ARGS) {
		return false;
	}


	for (int i = 0; i < int(split_command.size()); i++) {
		if(split_command[i].length() > MAX_LENGTH) {
			return false;
		}
	}

	return true;

}