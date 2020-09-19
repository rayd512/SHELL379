#include "validity.h"

using namespace std;

const int LINE_LENGTH = 100;
const int MAX_ARGS = 7;
const int MAX_LENGTH = 20;

bool is_valid_input(string command) {

	if (command.length() > LINE_LENGTH) {
		return false;
	}

	
	return true;

}