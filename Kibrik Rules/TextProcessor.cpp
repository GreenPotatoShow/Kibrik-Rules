#include "TextProcessor.h"
#include "Chain.h"
#include "WordShell.h"
#include "JSONCreator.h"
#include "macros.h"


#include "KNKernel.h"

#include <vector>
#include <iostream>

 

TextProcessor::TextProcessor(const TextLoader &textLoader) {

	std::string lexs;
	int bestCAChainID;
	double currentCA, maxCA;
	bestCAChainID = -1;
	currentCA = 0;
	maxCA = -5;
	std::vector<Chain> chains;
	this->chains = chains;
	std::list<WordShell*> entities = textLoader.getEntities();

	WordShell* currentEntity;
	WordShell* currentEntityFromChain;
    currentEntity = entities.front();

    this->chains.push_back(Chain(0));
    this->chains[0].pushBackToWords(currentEntity);
    entities.pop_front();

    while (!entities.empty()) {
        currentEntity = entities.front();
        for (auto& chain : this->chains) {

            currentEntityFromChain = chain.getWords().back();

            currentCA = textLoader.activationCoeff(currentEntityFromChain, currentEntity, chain.getWords().size());

            if (currentCA >= maxCA) {

                maxCA = currentCA;
                bestCAChainID = chain.getId();
            }
        }
        if (maxCA >=LIMIT_COEF_OF_ACTIVATION) {
            this->chains[bestCAChainID].pushBackToWords(currentEntity);
        }
        else {
            this->chains.push_back(Chain(this->chains.size()));
            this->chains[this->chains.size() - 1].pushBackToWords(currentEntity);
        }
        entities.pop_front();
        maxCA = -5;
        bestCAChainID = -1;
    }
    //for (auto& chain : this->chains) {
    //    std::cout << "\n" << chain.getId() << ". ";
    //    for (auto word : chain.getWords()) {
    //        std::cout << word->getWordShell()->GetForm() << " ";
    //    }
    //}
	JSONCreator jsonCreator(this->chains, textLoader.getText(), textLoader.getFileName());
    //std::cout << textLoader.getFileName() << "\n";
}

TextProcessor::~TextProcessor() {
	this->chains.clear();
};
