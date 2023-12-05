#pragma once
#include "TextLoader.h"
#include "Chain.h"

#include "KNKernel.h"

#include <vector>

class TextProcessor
{
public:
	TextProcessor(const TextLoader& textLoader);

private:
	std::vector<Chain> chains;
};

