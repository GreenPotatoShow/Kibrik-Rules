#pragma once
#include<string>
#include <vector>
class TextLoader
{
public:
	TextLoader(std::string fileName);

private:
	std::vector<std::string> clauses;
};

