#include "Interests.h"

Interests::Interests(){
	std::map<int,std::string> sports;
	std::map<int,std::string> science;
	std::map<int,std::string> music;
	interests.insert(std::pair<std::string,std::map<int,std::string>>("sports",sports));
	interests.insert(std::pair<std::string,std::map<int,std::string>>("science",science));
	interests.insert(std::pair<std::string,std::map<int,std::string>>("music",music));
	
}

void Interests::show(){
	for (auto itr1 = interests.begin(); itr1 != interests.end(); ++itr1){
		std::cout << itr1->first << std::endl;
		for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); ++itr2){
			std::cout << itr2->first << " : " << itr2->second << std::endl;
		} 
	} 
}

void Interests::format(){
	std::string formatted;
	for (auto itr1 = interests.begin(); itr1 != interests.end(); ++itr1){
		formatted.append("|");
		for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); ++itr2){
			int first = itr2->first;
			formatted.append(std::to_string(first));
			formatted.append("+");
			formatted.append(itr2->second);
			formatted.append(",");
		} 
		formatted.pop_back();
	} 
	formatted.erase(0,1);
	std::cout << formatted << std::endl;
}


std::pair<int, std::string> parse_pair(std::string info){
	int delimeter = info.find("+");
	int guid = std::stoi(info.substr(0,delimeter));
	std::string address = info.substr(delimeter+1);
	std::pair<int, std::string> node_pair(guid,address);
	return node_pair;
}

std::map<int,std::string> parse_nodes(std::string s){
	
	std::map<int,std::string> hobby;
	char c = ',';
	std::string::size_type i = 0;
	std::string::size_type j = s.find(c);
	while(j!=std::string::npos){
		hobby.insert(parse_pair(s.substr(i,j-1)));
		i = ++j;
		j = s.find(c,j);
		if (j == std::string::npos){
			//std::cout<<s.substr(i,s.length());
			hobby.insert(parse_pair(s.substr(i,s.length())));
		}
	}
	return hobby;
} 

//void parse_interests(std::map<std::string,std::map<int,std::string>>&interests, std::string s){
Interests::Interests(std::string s){
	int first = s.find("|");
	int second = s.find("|",first+1);

	std::string sports = s.substr(0,first);
	std::string science = s.substr(first+1,second-first-1);
	std::string music = s.substr(second+1,s.size()-1-second);
	
	std::cout << sports << std::endl;
	std::cout << science << std::endl;
	std::cout << music << std::endl;

	std::map<int,std::string> sports_map = parse_nodes(sports);
	std::map<int,std::string> science_map = parse_nodes(science);
	std::map<int,std::string> music_map = parse_nodes(music);
	
	interests.insert(std::pair<std::string,std::map<int,std::string>>("sports",sports_map));
	interests.insert(std::pair<std::string,std::map<int,std::string>>("science",science_map));
	interests.insert(std::pair<std::string,std::map<int,std::string>>("music",music_map));
	
}
	

