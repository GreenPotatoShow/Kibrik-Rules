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
	//���������� ����� ����� ���������� � ������� (���������� �������� ����� ����)
	//first, second - ������� ������ ������ � ������ �������� (����� �������, � �������� ���������� ��������)
	int linearDistance(int first, int second) const;

	//���������� ����� ����� ���������� � ������� (���������� \n ����� ����)
	//first, second - ������� ������ ������ � ������ �������� (����� �������, � �������� ���������� ��������)
	int paragraphDistance(int first, int second) const;


	int rhetoricalDistance(int first, int second) const;

	//����������� ���������
	double activation�oeff(int first, int second, bool isFirstProtagonist, int sizeOfChain) const;
private:
	std::string fileName;
	std::string text;
	std::list<IKNWordShell*> entities;
	IKNManager* manager;
	IKNEngine* engine;
	std::map<int, Rs3TreeSegment*> RSTNodes;
};

