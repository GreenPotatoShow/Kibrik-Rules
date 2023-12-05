#pragma once
#include "KNKernel.h"

#include <vector>
class Chain
{
public:
	Chain(int id);
	std::vector<const IKNAtom*> getWords() const;
	int getId() const;
	void pushBackToWords(const IKNAtom* word);
private:
	int id;
	std::vector<const IKNAtom*> words;
};

