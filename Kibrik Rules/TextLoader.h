#pragma once
#include "KNKernel.h"
#include "Rs3TreeSegment.h"

#include <string>
#include <list>
#include <map>

class TextLoader
{
public:
	TextLoader(std::string fileName);
	~TextLoader();

	const std::list<IKNWordShell*> getEntities() const;
	//Расстояние между двумя сущностями в клаузах (количество глаголов между ними)
	//first, second - позиция начала первой и второй сущности (номер символа, с которого начинается сущность)
	int linearDistance(int first, int second) const;

	//Расстояние между двумя сущностями в абзацах (количество \n между ними)
	//first, second - позиция начала первой и второй сущности (номер символа, с которого начинается сущность)
	int paragraphDistance(int first, int second) const;


	int rhetoricalDistance(int first, int second) const;

	//Коэффициент активации
	double activationСoeff(int first, int second, bool isFirstProtagonist, int sizeOfChain) const;
private:
	std::string fileName;
	std::string text;
	std::list<IKNWordShell*> entities;
	IKNManager* manager;
	IKNEngine* engine;
	std::map<int, Rs3TreeSegment*> RSTNodes;
};

