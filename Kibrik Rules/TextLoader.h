#pragma once
#include "KNKernel.h"

#include <string>
#include <list>

class TextLoader
{
public:
	TextLoader(std::string fileName);
	~TextLoader();

	const std::list<const IKNAtom*> getEntities() const;
	//Расстояние между двумя сущностями в клаузах (количество глаголов между ними)
	//first, second - позиция начала первой и второй сущности (номер символа, с которого начинается сущность)
	int linearDistance(int first, int second) const;

	//Расстояние между двумя сущностями в абзацах (количество \n между ними)
	//first, second - позиция начала первой и второй сущности (номер символа, с которого начинается сущность)
	int paragraphDistance(int first, int second) const;


	//Коэффициент активации
	double activationСoeff(int first, int second) const;
private:
	std::string text;
	std::list<const IKNAtom*> entities;
	IKNManager* manager;
	IKNEngine* engine;
};

