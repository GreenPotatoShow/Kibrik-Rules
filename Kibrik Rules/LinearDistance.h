#pragma once
#include "KNKernel.h"

class LinearDistance
{
public:
	//�� ���� ������ ������� � ������� ����, ����� �������� ����� ��������� �������� ����������
	LinearDistance(IKNResultList* resultList, uint first, uint second);
	LinearDistance(IKNResultList* resultList) :LinearDistance(resultList, 0, 5000) {};
	int getValue();
private:
	int value;
};

