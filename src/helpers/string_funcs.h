#pragma once

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split_input(std::string command);

const char ** convert_string_vec_to_char(std::vector<std::string> command);