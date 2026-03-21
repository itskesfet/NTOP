#pragma once
#include <string>
#include <vector>
#include <sstream>

inline std::vector<std::string> split(std::string const &input){
	using namespace std;
	vector<string> packs;
	string token;
	istringstream input_stream(input);
	
	while(input_stream >> token){
		packs.push_back(token);
	}
	return packs;
}


inline std::string htostr(const std::string& str){
	auto pos = str.find(':');
	if(pos == std::string::npos) return"";

	std::string ipHex = str.substr(0,pos);
	std::string portHex = str.substr(pos+1);

	unsigned int ip = std::stoul(ipHex,nullptr,16);

    	unsigned char b1 = ip & 0xFF;
    	unsigned char b2 = (ip >> 8) & 0xFF;
    	unsigned char b3 = (ip >> 16) & 0xFF;
    	unsigned char b4 = (ip >> 24) & 0xFF;

    	std::ostringstream out;
    	out << (int)b1 << "."
    	    << (int)b2 << "."
    	    << (int)b3 << "."
    	    << (int)b4;

	unsigned int port = std::stoul(portHex, nullptr, 16);

	out << ":" << port;
    	return out.str();


}

