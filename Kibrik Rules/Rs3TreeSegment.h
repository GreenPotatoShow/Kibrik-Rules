#pragma once
#include "Rs3Tree.h"

//�����-��������� �� Rs3Tree, ����� �������� segments. 

class Rs3TreeSegment : public Rs3Tree
{
public:
	Rs3TreeSegment(int id, int begin, int end);
	Rs3TreeSegment(Rs3Tree* rs3tree, int begin, int end);

	void setRangeBegin(int begin);
	void setRangeEnd(int end);

	int getRangeBegin();
	int getRangeEnd();
private:
	int characterRangeBegin; //������ ������ ��������� ������ � ���� ����
	int characterRangeEnd; //������ ����� ��������� ������ � ���� ����
};

