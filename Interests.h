#ifndef INTERESTS_H
#define INTERESTS_H
#include <iostream>
#include <map>
#include <vector>
#include <string>

class Interests{
	public:
		Interests();
		Interests(std::string s);
		void show();
		void format();
	private:
		std::map<std::string, std::map<int,std::string>> interests;
};

std::pair<int, std::string> parse_pair(std::string info);
std::map<int,std::string> parse_nodes(std::string s);

//void parse_interests(std::string s, std::map<std::string,std::map<int,std::string>> &interests);
//void parse_interests(std::string s);

#endif
