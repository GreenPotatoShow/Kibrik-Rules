#pragma once

#include "KNKernel.h"

#include <string>
#include <vector>

class TextLoader
{
public:
	TextLoader(std::string fileName);
	~TextLoader();

	//Расстояние между двумя сущностями в клаузах (количество глаголов между ними)
	//first, second - позиция начала первой и второй сущности (номер символа, с которого начинается сущность)
	int linearDistance(int first, int second);


private:
	std::string text;
	IKNManager* manager;
	IKNEngine* engine;
};

