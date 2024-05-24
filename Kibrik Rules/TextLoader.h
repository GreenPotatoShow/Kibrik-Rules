#pragma once
#include "KNKernel.h"
#include "Rs3TreeSegment.h"
#include "WordShell.h"

#include <string>
#include <list>
#include <map>

class TextLoader
{
public:
	TextLoader(std::string fileName);
	//~TextLoader();

	const std::wstring getText() const;
	const std::string getFileName() const;
	const std::list<WordShell*> getEntities() const;
	//���������� ����� ����� ���������� � ������� (���������� �������� ����� ����)
	//first, second - ������� ������ ������ � ������ �������� (����� �������, � �������� ���������� ��������)
	int linearDistance(int first, int second) const;

	//���������� ����� ����� ���������� � ������� (���������� \n ����� ����)
	//first, second - ������� ������ ������ � ������ �������� (����� �������, � �������� ���������� ��������)
	int paragraphDistance(int first, int second) const;


	int rhetoricalDistance(int first, int second) const;

	//����������� ���������
	double activationCoeff(WordShell* antecedent, WordShell* referent, int sizeOfChain) const;
private:
	std::string fileName;
	std::wstring text;
	std::list<WordShell*> entities;
	IKNManager* manager;
	IKNEngine* engine;
	std::map<int, Rs3TreeSegment*> RSTNodes;
};

