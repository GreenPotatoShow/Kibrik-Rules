#pragma once
#include "KNKernel.h"

#include <vector>
class Chain
{
public:
	Chain(int id);
	std::vector<IKNWordShell*> getWords() const;
	int getId() const;
	void pushBackToWords(IKNWordShell* word);
private:
	int id;
	std::vector<IKNWordShell*> words;
};

