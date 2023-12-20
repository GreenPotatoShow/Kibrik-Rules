#pragma once
#include "KNKernel.h"

#include <vector>
class Chain
{
public:
	Chain(int id);
	std::vector<const IKNWordShell*> getWords() const;
	int getId() const;
	void pushBackToWords(const IKNWordShell* word);
private:
	int id;
	std::vector<const IKNWordShell*> words;
};

