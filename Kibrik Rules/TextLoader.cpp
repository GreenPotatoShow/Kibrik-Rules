#include "TextLoader.h"
#include "macros.h"

#include "KNKernel.h"

#include <string>
#include <list>
#include <fstream>
#include <iostream>

bool isEntity(const IKNAtom* atom) {
	return (((atom->GetType() == 4)|| (atom->GetType() == 5)|| (atom->GetType() == 6))&&(atom->GetTextPos()%10==0));
}

//убираем из текста \n \t и прочее
std::string clearText(std::string text) {
	auto position = text.find("\\");
	while (position != std::string::npos) {
		text.erase(position, 2);
		position = text.find("\\");
	}
	return text;
}


TextLoader::TextLoader(std::string fileName) {
	setlocale(LC_ALL, "Russian");
	int position;
	position = 0;
	uint* len=new uint;
	std::string textStr, line, word;
	bool isVerb = false;
	std::ifstream file;
	file.open(INPUT_DIRECTORY+fileName);
	while (!file.eof()) {
		getline(file, line);
		textStr += line;
	}
	this->text = textStr;
	
	std::string clearedTextStr = clearText(textStr);
	char * text = const_cast<char*>(clearedTextStr.c_str());
	this->manager= GenerateAPIManager();
	this->manager->Create();
	this->engine = manager->GetEngine();
	this->engine->Run(text, 0, len);

	//ищем сущности
	std::list<const IKNAtom*> entities;
	this->entities = entities;

	IKNParsedText* parsedText=engine->GetParsedText();
	const IKNAtom* atom;
	uint maxAtoms = parsedText->GetCount();
	for (uint i=0;i< maxAtoms;i++){
		atom = parsedText->Get(i);
		if (isEntity(atom)) {
			this->entities.push_back(atom);
		}
	}

	file.close();
}

TextLoader::~TextLoader() {
	this->manager->Release();
}

const std::list<const IKNAtom*> TextLoader::getEntities() const{
	return this->entities;
};

int TextLoader::linearDistance(int first, int second) const{
	uint lastPosId = 0;
	std::string word, text;
	int value = 0;
	uint* end_pos = new uint;;
	text = this->text;
	IKNResultList* resultList;
	resultList = this->engine->GetResultList();
	resultList->InitWordsList();
	const char* infinitive = "ИНФИНИТИВ";
	IKNWordShell* wordShell;
	wordShell = resultList->GetNextWordShell();
	lastPosId = wordShell->GetPosId();
	IKNWord* iknWord;
	IKNParsedText* parsedText;
	parsedText = this->engine->GetParsedText();
	while (text.find(" ") == 0) { text=text.substr(1); }
	while (wordShell != NULL) {
		word = text.substr(0, text.find(" "));
		text = text.substr(text.find(" ") + 1);
		iknWord = wordShell->GetWord();
		auto partSpeech = iknWord->GetPartSpeech();
		if ((wordShell->GetTextPos(end_pos) >= (uint) first) && (wordShell->GetTextPos(end_pos) < (uint) second)) {
			if ((*partSpeech == 'Г') || (*partSpeech == *infinitive)) {
				value += 1;
			}
		}
		if (wordShell->GetTextPos(end_pos) >= (uint) second) {
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
	return value;
}

int TextLoader::paragraphDistance(int first, int second) const{
	int value = 0;
	std::string cutText = this->text.substr(first, second - first);
	while (cutText.find("\\n") != std::string::npos) {
		cutText = cutText.substr(cutText.find("\\n") + 2);
		value += 1;
	}
	return value;
}

double TextLoader::activationСoeff(int first, int second) const{
	double CA = 0;
	int linD = this->linearDistance(first, second);
	int paraD = this->paragraphDistance(first, second);

	switch (linD)
	{
	case 0: break;
	case 1: break;
	case 2: CA -= 0.1; break;
	case 3: CA -= 0.2; break;
	default: CA -= 0.3; break;
	}

	switch (paraD)
	{
	case 0: break;
	case 1: CA -= 0.3; break;
	default: CA -= 0.5; break;
	}
	return CA;
}