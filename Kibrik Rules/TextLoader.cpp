#include "TextLoader.h"
#include "TreeCreator.h"
#include "macros.h"

#include "KNKernel.h"

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

bool isEntity(const IKNWordShell* wordShell) {
	const char* noun = "Сущ";
	const char* pronoun = "Мест-Сущ";
	IKNWord* iknWord = wordShell->GetWord();
	auto partSpeech = iknWord->GetPartSpeech();
	return ((*partSpeech == *noun) || (*partSpeech == *pronoun));
}



TextLoader::TextLoader(std::string fileName) {
	setlocale(LC_ALL, "Russian");
	char* oProperty = new char;
	uint lastPosId = 0;
	uint* end_pos = new uint;
	int position;
	position = 0;
	uint* len=new uint;
	std::string textStr, line, word;
	bool isVerb = false;
	std::ifstream file;
	this->fileName = fileName;
	file.open(INPUT_DIRECTORY+fileName);
	while (!file.eof()) {
		getline(file, line);
		textStr += line;
	}
	this->text = textStr;
	
	char * text = const_cast<char*>(textStr.c_str());
	this->manager= GenerateAPIManager();
	this->manager->Create();
	this->engine = manager->GetEngine();
	this->engine->Run(text, 0, len);

	//ищем сущности
	std::list<IKNWordShell*> entities;
	this->entities = entities;

	IKNResultList* resultList = engine->GetResultList();
	resultList->InitWordsList();
	IKNWordShell* wordShell;
	wordShell = resultList->GetNextWordShell();
	lastPosId = wordShell->GetPosId();
	IKNWord* iknWord = wordShell->GetWord();
	auto partSpeech = iknWord->GetPartSpeech();
	while (wordShell != NULL) {
		iknWord = wordShell->GetWord();
		//std::cout << wordShell->GetForm() << " " << oProperty << "\n";
		partSpeech = iknWord->GetPartSpeech();
		if (isEntity(wordShell)) {
			this->entities.push_back(wordShell);
		}
		lastPosId = wordShell->GetTextPos(end_pos); //первый символ нумеруется как 1
		//std::cout << wordShell->GetForm() << " " << lastPosId << "\n";
		wordShell = resultList->GetNextWordShell();
		while (wordShell->GetTextPos(end_pos) == lastPosId) {
			lastPosId = wordShell->GetTextPos(end_pos);
			wordShell = resultList->GetNextWordShell();
			if (!wordShell) { break; }
		}
	}
	TreeCreator treeCreator(fileName);
	this-> RSTNodes=treeCreator.getRSTNods();

	file.close();
}

TextLoader::~TextLoader() {
	this->manager->Release();
}

const std::list<IKNWordShell*> TextLoader::getEntities() const{
	return this->entities;
};

int TextLoader::linearDistance(int first, int second) const{
	uint lastPosId = 0;
	std::string word, text;
	int value = 1;
	uint* end_pos = new uint;
	text = this->text;
	IKNResultList* resultList;
	resultList = this->engine->GetResultList();
	resultList->InitWordsList();
	const char* verb = "Глаг";
	const char* infinitive = "Инф";
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
			if ((*partSpeech == *verb) || (*partSpeech == *infinitive)) {
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

int TextLoader::rhetoricalDistance(int first, int second) const {
	int value = 1;

	int commonNodeId=0;
	std::vector<int> idsGoingUp;
	Rs3Tree* nodeForFirst=new Rs3Tree;
	Rs3Tree* nodeForSecond = new Rs3Tree;
	for (const auto& pairobj : this->RSTNodes) {
		if ((first >= pairobj.second->getRangeBegin()) && (first <= pairobj.second->getRangeEnd())) {
			*nodeForFirst=*pairobj.second;
		}
		if ((second >= pairobj.second->getRangeBegin()) && (second <= pairobj.second->getRangeEnd())) {
			*nodeForSecond = *pairobj.second;
			break;
		}
	}
	while (nodeForFirst != nullptr) {
		idsGoingUp.push_back(nodeForFirst->getId());
		nodeForFirst = nodeForFirst->getParent();
	}
	while (nodeForSecond != nullptr) {
		if (std::binary_search(idsGoingUp.begin(), idsGoingUp.end(), nodeForSecond->getId())) {
			commonNodeId = nodeForSecond->getId();
			break;
		};
		value += 1;
		nodeForSecond = nodeForSecond->getParent();
	}

	value += std::find(idsGoingUp.begin(), idsGoingUp.end(), commonNodeId)- idsGoingUp.begin();


	return value;
}

double TextLoader::activationСoeff(int first, int second, bool isFirstProtagonist, int sizeOfChain) const{
	double CA = 0;
	int linD = this->linearDistance(first, second);
	int paraD = this->paragraphDistance(first, second);
	int RhD = this->rhetoricalDistance(first, second);

	switch (linD)
	{
	case 1: break;
	case 2: CA -= 0.1; break;
	case 3: CA -= 0.2; break;
	case 4: CA -= 0.3; break;
	default: CA -= 0.5; break;
	}

	switch (paraD)
	{
	case 0: break;
	case 1: CA -= 0.2; break;
	default: CA -= 0.4; break;
	}

	switch (RhD)
	{
	case 1: CA += 0.7; break;
	case 2: CA += 0.4; break;
	case 3: CA += 0; break;
	default: CA -= 0.3; break;
	}

	//protagonism
	if ((isFirstProtagonist) && (sizeOfChain == 1)) {
		CA += 0.3;
	}
	else if ((isFirstProtagonist) && (sizeOfChain == 2)) {
		CA += 0.1;
	}

	return CA;
}