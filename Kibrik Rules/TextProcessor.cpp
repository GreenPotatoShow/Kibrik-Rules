#include "TextProcessor.h"
#include "Chain.h"

#include "KNKernel.h"

#include <vector>
#include <iostream>

bool isProtagonist(std::string str) {
	const char* nominative = "èì";
	return (str.substr(0, 2) == nominative);
}


TextProcessor::TextProcessor(const TextLoader &textLoader) {
	int bestCAChainID;
	char* oProperty = new char;
	double currentCA, maxCA;
	bestCAChainID = -1;
	currentCA = 0;
	maxCA = -5;
	uint* end_pos = new uint;
	std::vector<Chain> chains;
	this->chains = chains;
	std::list<IKNWordShell*> entities = textLoader.getEntities();

	IKNWordShell* currentEntity;
	currentEntity = entities.front();

	this->chains.push_back(Chain(0));
	this->chains[0].pushBackToWords(currentEntity);
	entities.pop_front();

	while (!entities.empty()) {
		currentEntity = entities.front();
		for (auto &chain:this->chains) {
			chain.getWords().back()->GetPropertyAsString(oProperty);
			currentCA=textLoader.activationÑoeff(chain.getWords().back()->GetTextPos(end_pos), currentEntity->GetTextPos(end_pos), isProtagonist(std::string(oProperty)), chain.getWords().size());
			//currentCA = textLoader.activationÑoeff(chain.getWords().back()->GetTextPos(end_pos), currentEntity->GetTextPos(end_pos), true, 0);
			if (currentCA >= maxCA) {
				maxCA = currentCA;
				bestCAChainID = chain.getId();
			}
		}
		if (maxCA >= 0.7) {
			this->chains[bestCAChainID].pushBackToWords(currentEntity);
		}
		else {
			this->chains.push_back(Chain(this->chains.size()));
			this->chains[this->chains.size()-1].pushBackToWords(currentEntity);
		}
		entities.pop_front();
		maxCA = -5;
		bestCAChainID = -1;
	}
	for (auto &chain : this->chains) {
		std::cout << "\n" << chain.getId() << ". ";
		for (auto word : chain.getWords()) {
			std::cout << word->GetForm() << " ";
		}
	}
}