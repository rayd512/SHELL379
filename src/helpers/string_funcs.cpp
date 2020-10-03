#include "string_funcs.h"

using namespace std;

/** Splits a vector by space
 *
 * Takes in a string, splits it by space and return it in a vector
 * @param command a string to be split
 * @return a vector of strings split from orginal string
 */
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


