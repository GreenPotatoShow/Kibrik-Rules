#define _CRT_SECURE_NO_WARNINGS

#include "JSONCreator.h"
#include "macros.h"

#include <vector>
#include <fstream>
#include <codecvt>
#include <string>

JSONCreator::JSONCreator(std::vector<Chain> chains, std::wstring text, std::string fileName) {

	fileName = JSON_DIRECTORY + fileName.substr(0, fileName.find("."))+".json";
	std::ofstream file(fileName);
	uint* end_pos=new uint;
	json j;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	j["text"] = myconv.to_bytes(text);


	std::vector< std::vector<std::vector<uint>>> entities(chains.size());
	std::vector<std::vector<uint>> jsonChain;
	for (uint i = 0; i < chains.size();i++) {
		entities[i] = std::vector<std::vector<uint>>(chains[i].getWords().size());
		for (uint j = 0; j < chains[i].getWords().size(); j++) {
			entities[i][j] = std::vector<uint>(2);
			entities[i][j][0] = chains[i].getWords()[j]->getWordShell()->GetTextPos(end_pos);
			entities[i][j][1] = *end_pos;
		}
	}

	j["entities"] = entities;

	std::vector<std::vector<int>> includes = std::vector<std::vector<int>>(entities.size());
	
	j["includes"] = includes;

    std::string s = j.dump();
	file << s;
	file.close();
}
