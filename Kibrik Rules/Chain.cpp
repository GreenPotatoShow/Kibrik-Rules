#include "Chain.h"

#include "KNKernel.h"

#include <vector>

Chain::Chain(int id) {
	this->id = id;
	std::vector<IKNWordShell*> words;
	this->words = words;
}

int Chain::getId() const{
	return this->id;
}

std::vector<IKNWordShell*> Chain::getWords() const{
	return this->words;
}

void Chain::pushBackToWords(IKNWordShell* word) {
	this->words.push_back(word);
}