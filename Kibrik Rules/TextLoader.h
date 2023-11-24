#pragma once

#include "KNKernel.h"

#include <string>
#include <vector>

class TextLoader
{
public:
	TextLoader(std::string fileName);
	~TextLoader();

	//���������� ����� ����� ���������� � ������� (���������� �������� ����� ����)
	//first, second - ������� ������ ������ � ������ �������� (����� �������, � �������� ���������� ��������)
	int linearDistance(int first, int second);


private:
	std::string text;
	IKNManager* manager;
	IKNEngine* engine;
};

