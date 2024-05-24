#include "WordShell.h"


WordShell::WordShell(IKNWordShell* iknWordShell) {
	this->wordShell = iknWordShell;
	this->isActor = "";
};

void WordShell::makeActor() {
	this->isActor = "Actor";
}

void WordShell::makeSubjectNoActor() {
	this->isActor = "subjectNoActor";
}

std::string WordShell::getIsActor() {
	return this->isActor;
}

IKNWordShell* WordShell::getWordShell() {
	return this->wordShell;
}

bool WordShell::isSubject() {
	std::string morphs;
	char* oProperty = new char[500];
	this->wordShell->GetPropertyAsString(oProperty);
	morphs = std::string(oProperty);
	const char* nominative = "им";
	delete[] oProperty;
	return (morphs.substr(0, 2) == nominative);
}

bool WordShell::isAnimate() {
	std::string lexs;
	char* oProperty = new char[500];
	IKNWord* word;

	word = this->wordShell->GetWord();
	word->GetLex(oProperty);
	lexs = std::string(oProperty);

	int index = lexs.find("Одушевленность:");
	if (index != std::string::npos) {
		if (lexs.substr(index + 16, 2) == "од") {
			return true;
		}
	}
	delete[] oProperty;
	return false;
}
