#include "LinearDistance.h"

#include<iostream>

LinearDistance::LinearDistance(IKNResultList* resultList, uint first, uint second) {
	resultList->InitWordsList();
	uint i = 1;
	uint* end_pos =&i;
	const char* infinitive = "ÈÍÔÈÍÈÒÈÂ";
	IKNWordShell* wordShell;
	wordShell = resultList->GetNextWordShell();
	IKNWord* iknWord;
	this->value = 0;
	while (wordShell != NULL) {
		iknWord = wordShell->GetWord();
		auto partSpeech = iknWord->GetPartSpeech();
		if ((wordShell->GetPosId() >= first) && (wordShell->GetPosId() < second)) {
			if ((*partSpeech == 'Ã')||(*partSpeech == *infinitive)) {
				this->value += 1;
			}
		}
		if (wordShell->GetPosId() >= second) {
			break;
		}
		std::cout << wordShell->GetTextPos(end_pos) << " " <<*end_pos<<"\n";
		wordShell = resultList->GetNextWordShell();
	}
}

int LinearDistance::getValue() {
	return this->value;
}