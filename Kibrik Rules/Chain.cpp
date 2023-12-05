#include "Chain.h"

#include "KNKernel.h"

#include <vector>

Chain::Chain(int id) {
	this->id = id;
	std::vector<const IKNAtom*> words;
	this->words = words;
}

int Chain::getId() const{
	return this->id;
}

std::vector<const IKNAtom*> Chain::getWords() const{
	return this->words;
}

void Chain::pushBackToWords(const IKNAtom* word) {
	this->words.push_back(word);
}