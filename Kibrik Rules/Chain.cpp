#include "Chain.h"

#include "KNKernel.h"

#include <vector>

Chain::Chain(int id) {
	this->id = id;
	std::vector<WordShell*> words;
	this->words = words;
}


int Chain::getId() const{
	return this->id;
}

std::vector<WordShell*> Chain::getWords() const{
	return this->words;
}

void Chain::pushBackToWords(WordShell* word) {
	this->words.push_back(word);
}
