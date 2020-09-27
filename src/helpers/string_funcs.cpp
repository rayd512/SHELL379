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


