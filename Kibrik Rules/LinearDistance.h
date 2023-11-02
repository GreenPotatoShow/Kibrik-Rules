#pragma once
#include "KNKernel.h"

class LinearDistance
{
public:
	//Ќа вход индекс первого и второго слов, между которыми нужно посчитать линейное рассто€ние
	LinearDistance(IKNResultList* resultList, uint first, uint second);
	LinearDistance(IKNResultList* resultList) :LinearDistance(resultList, 0, 5000) {};
	int getValue();
private:
	int value;
};

