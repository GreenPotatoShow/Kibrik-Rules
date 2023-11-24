#include "TextLoader.h"
#include "macros.h"
#include "LinearDistance.h"
#include "ParagraphDistance.h"

#include "KNKernel.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

bool isEntity(std::string word) {
	return true;
}

TextLoader::TextLoader(std::string fileName) {
	setlocale(LC_ALL, "Russian");
	//std::vector<std::string
	uint* len=new uint;
	std::string textStr, line;
	bool isVerb = false;
	std::ifstream file;
	file.open(INPUT_DIRECTORY+fileName);
	while (!file.eof()) {
		getline(file, line);
		textStr += line;
	}
	this->text = textStr;
	char * text = const_cast<char*>(textStr.c_str());;
	this->manager= GenerateAPIManager();
	this->manager->Create();
	this->engine = manager->GetEngine();
	this->engine->Run(text, 0, len);


	//ParagraphDistance paragraphDistance(textStr);
	//std::cout << paragraphDistance.getValue();

	file.close();
}

TextLoader::~TextLoader() {
	this->manager->Release();
}

int TextLoader::linearDistance(int first, int second) {
	uint lastPosId = 0;
	std::string word, text;
	int value = 0;
	uint* end_pos = new uint;;
	text = this->text;
	IKNResultList* resultList;
	resultList = this->engine->GetResultList();
	resultList->InitWordsList();
	const char* infinitive = "ÈÍÔÈÍÈÒÈÂ";
	IKNWordShell* wordShell;
	wordShell = resultList->GetNextWordShell();
	lastPosId = wordShell->GetPosId();
	IKNWord* iknWord;
	IKNParsedText* parsedText;
	parsedText = this->engine->GetParsedText();
	const IKNAtom* atom;
	atom = parsedText->Get(2);
	std::cout << atom->GetData();
	while (text.find(" ") == 0) { text=text.substr(1); }
	while (wordShell != NULL) {
		word = text.substr(0, text.find(" "));
		text = text.substr(text.find(" ") + 1);
		iknWord = wordShell->GetWord();
		auto partSpeech = iknWord->GetPartSpeech();
		if ((wordShell->GetTextPos(end_pos) >= first) && (wordShell->GetTextPos(end_pos) < second)) {
			if ((*partSpeech == 'Ã') || (*partSpeech == *infinitive)) {
				value += 1;
			}
		}
		if (wordShell->GetTextPos(end_pos) >= second) {
			break;
		}
		lastPosId = wordShell->GetTextPos(end_pos);
		wordShell = resultList->GetNextWordShell();
		while (wordShell->GetTextPos(end_pos) == lastPosId) {
			lastPosId = wordShell->GetTextPos(end_pos);
			wordShell = resultList->GetNextWordShell();
			if (!wordShell) { break; }
		}
	}
	std::cout << value;
	return value;
}