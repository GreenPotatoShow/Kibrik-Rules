#include "TextLoader.h"
#include "macros.h"
#include "LinearDistance.h"
#include "ParagraphDistance.h"

#include "KNKernel.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

TextLoader::TextLoader(std::string fileName) {
	setlocale(LC_ALL, "Russian");
	uint* len=new uint;
	std::string textStr, line, word;
	bool isVerb = false;
	std::ifstream file;
	file.open(INPUT_DIRECTORY+fileName);
	while (!file.eof()) {
		getline(file, line);
		textStr += line;
	}
	char * text = const_cast<char*>(textStr.c_str());;
	IKNManager* manager = GenerateAPIManager();
	IKNEngine* engine;
	manager->Create();
	engine = manager->GetEngine();
	engine->Run(text, 0, len);
	file.seekg(0);
	line = "";
	IKNResultList* resultList;
	resultList = engine->GetResultList();
	LinearDistance linearDistance(resultList);
	std::cout << linearDistance.getValue()<<" ";

	ParagraphDistance paragraphDistance(textStr);
	std::cout << paragraphDistance.getValue();

	file.close();
	manager->Release();
}