#pragma once
#include "KNKernel.h"

#include <string>
#include <list>

class TextLoader
{
public:
	TextLoader(std::string fileName);
	~TextLoader();

	const std::list<const IKNWordShell*> getEntities() const;
	//���������� ����� ����� ���������� � ������� (���������� �������� ����� ����)
	//first, second - ������� ������ ������ � ������ �������� (����� �������, � �������� ���������� ��������)
	int linearDistance(int first, int second) const;

	//���������� ����� ����� ���������� � ������� (���������� \n ����� ����)
	//first, second - ������� ������ ������ � ������ �������� (����� �������, � �������� ���������� ��������)
	int paragraphDistance(int first, int second) const;


	//����������� ���������
	double activation�oeff(int first, int second) const;
private:
	std::string text;
	std::list<const IKNWordShell*> entities;
	IKNManager* manager;
	IKNEngine* engine;
};

