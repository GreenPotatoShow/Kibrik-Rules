#pragma once
#include "json.hpp"

#include "TextProcessor.h"

using json = nlohmann::json;

class JSONCreator
{
public:
	JSONCreator(std::vector<Chain> chains, std::wstring text, std::string fileName);

private:
};

