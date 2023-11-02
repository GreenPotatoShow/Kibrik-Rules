#include "LinearDistance.h"

#include<iostream>

LinearDistance::LinearDistance(IKNResultList* resultList, uint first, uint second) {
	resultList->InitWordsList();
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
		wordShell = resultList->GetNextWordShell();
	}
}

int LinearDistance::getValue() {
	return this->value;
}