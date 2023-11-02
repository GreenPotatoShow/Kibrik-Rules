#pragma once
#include<string>
#include "KNKernel.h"

class ParagraphDistance
{
public:
	//�� ���� ����� ������� ������ ������� � ������� ����, ����� �������� ����� ��������� �������� ����������
	ParagraphDistance(std::string text, int first, int second);
	ParagraphDistance(std::string text) :ParagraphDistance(text, 0, 50000) {};
	int getValue();
private:
	int value;
};

