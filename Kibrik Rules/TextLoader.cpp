#define _CRT_SECURE_NO_WARNINGS

#include "TextLoader.h"
#include "TreeCreator.h"
#include "macros.h"

#include "KNKernel.h"

#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <codecvt>
#include <locale>
#include <windows.h>
#include <stringapiset.h>
#include <cstdlib>

bool isEntity(const IKNWordShell* wordShell) {
    const char* noun = "Сущ";
	const char* pronoun = "Мест-Сущ";
	IKNWord* iknWord = wordShell->GetWord();
	auto partSpeech = iknWord->GetPartSpeech();
    std::string SPartSpeech = std::string(partSpeech);
	//std::cout << wordShell->GetForm() << " " << iknWord->GetPartSpeech() << "\n";
	return ((*partSpeech == *noun) || (*partSpeech == *pronoun));
}

bool checkIsPassive(IKNWordShell* iknWordShell) {
	const char* shortParticiple = "Кратк_Прич";
	char* oProperty = new char[500];
	std::string morphs;
	IKNWord* iknWord = iknWordShell->GetWord();
	auto partSpeech = iknWord->GetPartSpeech();
	if (*partSpeech == *shortParticiple) {
		iknWordShell->GetPropertyAsString(oProperty);
		morphs = std::string(oProperty);
		return (morphs.find("стр") != std::string::npos);
	}
	return false;
}

void findActor(std::list < WordShell*> &list) {
	char* oProperty = new char[500];
	bool actorFound = false;
	std::string morphs;
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		//std::cout << (*iter)->getWordShell()->GetForm() << " ";
		(*iter)->getWordShell()->GetPropertyAsString(oProperty);
		morphs = std::string(oProperty);
		if (morphs.find("тв") != std::string::npos) {
			(*iter)->makeActor();
			actorFound = true;
		}
		if (morphs.find("им") != std::string::npos) {
			(*iter)->makeSubjectNoActor();
			if (actorFound) { break; }
		}
	}
}

TextLoader::TextLoader(std::string fileName) {
	setlocale(LC_ALL, "Russian");
	char* oProperty = new char[500];
	uint lastPosId = 0;
	uint* end_pos = new uint;
	int position;
	position = 0;
	uint* len=new uint;
	std::wstring word, stringForSentence;
    std::wstring textStr, line;
	std::wifstream file;
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
	bool isEndOfSentence;
	bool isPassive = false;
	this->fileName = fileName;
	file.open(INPUT_DIRECTORY+fileName);
	while (!file.eof()) {
		getline(file, line);
		textStr += line;
	}
	this->text = textStr;

    const wchar_t* textWchar =textStr.c_str();


    // Count required buffer size (plus one for null-terminator).
    size_t size = (wcslen(textWchar) + 1) * sizeof(wchar_t);
    char* text = new char[size];

    #ifdef __STDC_LIB_EXT1__
        // wcstombs_s is only guaranteed to be available if __STDC_LIB_EXT1__ is defined
        size_t convertedSize;
        std::wcstombs_s(&convertedSize, buffer, size, input, size);
    #else
        std::wcstombs(text, textWchar, size);
    #endif



	this->manager= GenerateAPIManager();
	this->manager->Create();
	this->engine = manager->GetEngine();
	this->engine->Run(text, 0, len);

	//ищем сущности
	std::list<WordShell*> entities;
	this->entities = entities;

	//предложение
	std::list<WordShell*> currentSentence;

	IKNResultList* resultList = engine->GetResultList();
	resultList->InitWordsList();
	IKNWordShell* iknWordShell;
	IKNWord* iknWord;
	iknWordShell = resultList->GetNextWordShell();

	WordShell* wordShell;

	while (iknWordShell != NULL) {
		//iknWordShell->GetPropertyAsString(oProperty); //посвящен прш,стр,но,мр,ед;прш,стр,од,мр,ед;
		//std::cout << iknWordShell->GetForm() << " " << oProperty << "\n"; //был дст,прш,мр,ед;

		iknWord = iknWordShell->GetWord();
		if (isEntity(iknWordShell)) {
			wordShell =new WordShell(iknWordShell);
			this->entities.push_back(wordShell);
		}
		lastPosId = iknWordShell->GetTextPos(end_pos); //первый символ нумеруется как 1

		//std::cout << this->text.substr(lastPosId, *end_pos - lastPosId+1)<<"\n";
		stringForSentence = this->text.substr(lastPosId, *end_pos - lastPosId + 1);
		isEndOfSentence = (
			(stringForSentence.find(L".") != std::string::npos) ||
			(stringForSentence.find(L"!") != std::string::npos) ||
			(stringForSentence.find(L"?") != std::string::npos) ||
			(stringForSentence.find(L"…") != std::string::npos)
			);

		if (isEndOfSentence) {
			if (isPassive) {
				findActor(currentSentence);
			}
			//for (auto iter = currentSentence.begin(); iter != currentSentence.end(); iter++) {
			//	std::cout << (*iter)->getWordShell()->GetForm() << " ";
			//}
			currentSentence.clear();

			isPassive = false;
		}
		else if (isEntity(iknWordShell)) {
			currentSentence.push_back(this->entities.back());
		}
		if (!isPassive) {
			isPassive = checkIsPassive(iknWordShell);
		}
		//std::cout<< iknWordShell->GetForm()
		iknWordShell = resultList->GetNextWordShell();
        if (iknWordShell == nullptr) { break; }
		while (iknWordShell->GetTextPos(end_pos) == lastPosId) {
			lastPosId = iknWordShell->GetTextPos(end_pos);
			iknWordShell = resultList->GetNextWordShell();
			if (!iknWordShell) { break; }
		}
	}
	TreeCreator treeCreator(fileName);
	this-> RSTNodes=treeCreator.getRSTNods();

	delete len;
	delete[] oProperty;
	delete end_pos;
    delete[] text;
	file.close();
}

//TextLoader::~TextLoader() {
//	this->manager->Release();
//}

const std::list<WordShell*> TextLoader::getEntities() const{
	return this->entities;
};

const std::wstring TextLoader::getText() const {
	return this->text;
};

const std::string TextLoader::getFileName() const {
	return this->fileName;
}

int TextLoader::linearDistance(int first, int second) const{
	uint lastPosId = 0;
	std::wstring word, text;
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
	while (text.find(L" ") == 0) { text=text.substr(1); }
	while (wordShell != NULL) {
		word = text.substr(0, text.find(L" "));
		text = text.substr(text.find(L" ") + 1);
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
	delete end_pos;
	return value;
}

int TextLoader::paragraphDistance(int first, int second) const{
	int value = 0;
	std::wstring cutText = this->text.substr(first, second - first);
	while (cutText.find(L"\\n") != std::string::npos) {
		cutText = cutText.substr(cutText.find(L"\\n") + 2);
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

	delete nodeForFirst;
	delete nodeForSecond;
	return value;
}

double TextLoader::activationCoeff(WordShell* antecedent, WordShell* referent, int sizeOfChain) const{
	uint* end_pos = new uint;

	//проверим род
	char* oProperty1 = new char[500];
	char* oProperty2 = new char[500];
	antecedent->getWordShell()->GetPropertyAsString(oProperty1); //посвящен прш,стр,но,мр,ед;прш,стр,од,мр,ед;
	referent->getWordShell()->GetPropertyAsString(oProperty2);
	std::string morphs1 = std::string(oProperty1);
	std::string morphs2 = std::string(oProperty2);

	if (
		((morphs1.find("мр") != std::string::npos) && (morphs2.find("мр") == std::string::npos))||
		((morphs1.find("мр") == std::string::npos) && (morphs2.find("мр") != std::string::npos))||
		((morphs1.find("жр") != std::string::npos) && (morphs2.find("жр") == std::string::npos))||
		((morphs1.find("жр") == std::string::npos) && (morphs2.find("жр") != std::string::npos))||
		((morphs1.find("ср") != std::string::npos) && (morphs2.find("ср") == std::string::npos))||
		((morphs1.find("ср") == std::string::npos) && (morphs2.find("ср") != std::string::npos))
		) 
	{
		return -5;
	}



	delete[] oProperty1;
	delete[] oProperty2;
	double CA = 0;

	int firstPos = antecedent->getWordShell()->GetTextPos(end_pos);
	int secondPos = referent->getWordShell()->GetTextPos(end_pos);

	bool isFirstSubject = antecedent->isSubject();
	bool isSecondSubject= referent->isSubject();

	bool isFirstAnimate= antecedent->isAnimate();
	bool isSecondAnimate = referent->isAnimate();

	std::string isFirstActor = antecedent->getIsActor();
	std::string isSecondActor = referent->getIsActor();


	bool isFirstProtagonist = ((isFirstSubject) && (isFirstAnimate));
	bool isSecondProtagonist = ((isSecondSubject) && (isSecondAnimate));

	int linD = this->linearDistance(firstPos, secondPos);
	int paraD = this->paragraphDistance(firstPos, secondPos);
	int RhD = this->rhetoricalDistance(firstPos, secondPos);

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

	//animacy

	if (isFirstAnimate) {
		if (RhD >= 3) {
			CA += 0.2;
		}
		else if (RhD == 2) {
			CA += 0.1;
		}
	}

	//semantic role
	if ((isFirstProtagonist)&& (isFirstActor == "")) {
		if ((isSecondProtagonist) && (isSecondActor == "")) {
			CA += 0.4;
		}
		else {
			CA += 0.3;
		}
	}
	else if (isFirstActor!="") {
		CA += 0.2;
	}
	delete end_pos;
	return CA;
}
