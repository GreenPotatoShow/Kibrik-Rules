#pragma once
#include<vector>

//узел rs3 дерева (базовый класс). Здесь хранятся group и отсюда наследуются segment

class Rs3Tree
{
public:
	Rs3Tree(int id);
	Rs3Tree() : Rs3Tree(0) {};
	Rs3Tree(const Rs3Tree& rs3tree);


	void setId(int id);
	int getId();
	Rs3Tree* getParent();

	void setChildOf(Rs3Tree* parent); //сделать узел parent родителем

private:
	int id;
	Rs3Tree* parent;
	std::vector<Rs3Tree*> children;
};

