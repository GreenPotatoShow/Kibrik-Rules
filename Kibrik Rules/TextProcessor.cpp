#include "TextProcessor.h"
#include "Chain.h"

#include "KNKernel.h"

#include <vector>
#include <iostream>



TextProcessor::TextProcessor(const TextLoader &textLoader) {
	int bestCAChainID;
	double currentCA, maxCA;
	bestCAChainID = -1;
	currentCA = 0;
	maxCA = -5;
	uint* end_pos = new uint;
	std::vector<Chain> chains;
	this->chains = chains;
	std::list<const IKNWordShell*> entities = textLoader.getEntities();

	const IKNWordShell* currentEntity;
	currentEntity = entities.front();

	this->chains.push_back(Chain(0));
	this->chains[0].pushBackToWords(currentEntity);
	entities.pop_front();

	while (!entities.empty()) {
		currentEntity = entities.front();
		for (auto &chain:this->chains) {
			currentCA=textLoader.activationÑoeff(chain.getWords().back()->GetTextPos(end_pos), currentEntity->GetTextPos(end_pos));
			if (currentCA >= maxCA) {
				maxCA = currentCA;
				bestCAChainID = chain.getId();
			}
		}
		if (maxCA >= 0) {
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