#pragma once
#include "TextLoader.h"
#include "Chain.h"

#include "KNKernel.h"

#include <vector>

class TextProcessor
{
public:
	TextProcessor(const TextLoader& textLoader);
	~TextProcessor();
private:
	std::vector<Chain> chains;
};

