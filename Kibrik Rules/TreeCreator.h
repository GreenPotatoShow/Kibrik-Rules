#pragma once
#include "Rs3Tree.h"
#include "Rs3TreeSegment.h"

#include<string>
#include<map>
class TreeCreator
{
public:
	TreeCreator(std::string fileName);
	std::map<int, Rs3TreeSegment*> getRSTNodes();
private:
	std::map<int, Rs3TreeSegment*> RSTNodes;
};

