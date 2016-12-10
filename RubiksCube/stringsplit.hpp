// String splitter

#ifndef __STR_SPLITTER_H__
#define __STR_SPLITTER_H__

#include <string>
#include <sstream>
#include <cstring>
#include <vector>

void split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
void split(char delim, std::vector<std::string>& elems);
std::vector<std::string> split(const std::string &s, char delim[]);
	
#endif
