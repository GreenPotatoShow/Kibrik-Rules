#pragma once
#include "KNKernel.h"
#include "WordShell.h"

#include <vector>
class Chain
{
public:
	Chain(int id);
	std::vector<WordShell*> getWords() const;
	int getId() const;
	void pushBackToWords(WordShell* word);
private:
	int id;
	std::vector<WordShell*> words;
};

