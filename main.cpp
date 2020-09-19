#include <iostream>
#include "validity.h"

using namespace std;

int main(void) {
	string command;
	while (true) {
		cout << "SHELL379: ";
		cin >> command;
		if(is_valid_input(command)) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}

}