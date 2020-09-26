#include "string_funcs.h"

using namespace std;

vector<string> split_input(string command) {
	vector<string> words;

	istringstream ss(command); 
  
	do { 
		string word; 
		ss >> word; 
  		words.push_back(word);
		
  
	} while (ss); 

	words.pop_back();
	return words;
}


const char ** convert_string_vec_to_char(vector<string> command) {
	const char **argv = new const char* [command.size()+1];

	for (int i = 0;  i < int(command.size()); i++)
		argv [i] = command[i].c_str();

	argv [command.size()+1] = NULL;

	return argv;
}