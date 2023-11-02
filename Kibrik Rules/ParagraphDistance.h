#pragma once
#include<string>
#include "KNKernel.h"

class ParagraphDistance
{
public:
	//Ќа вход номер символа начала первого и второго слов, между которыми нужно посчитать линейное рассто€ние
	ParagraphDistance(std::string text, int first, int second);
	ParagraphDistance(std::string text) :ParagraphDistance(text, 0, 50000) {};
	int getValue();
private:
	int value;
};

