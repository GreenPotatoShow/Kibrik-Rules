#include "Rs3Tree.h"

Rs3Tree::Rs3Tree(int id) {
	std::vector< Rs3Tree*> vector;
	this->children = vector;
	this->id = id;
	this->parent = nullptr;
}

Rs3Tree::Rs3Tree(const Rs3Tree& rs3tree) {
	this->id = rs3tree.id;
	if (rs3tree.parent == NULL) {
		this->parent = NULL;
	}
	else {
		*this->parent = *rs3tree.parent;
	}
	std::vector< Rs3Tree*> vector(rs3tree.children);
	this->children = vector;
}

Rs3Tree::~Rs3Tree() {
	this->children.clear();
}


//bool Rs3Tree::operator<(const Rs3Tree& right)
//{
//	return this->id < right.id;
//}

void  Rs3Tree::setId(int id) {
	this->id = id;
};

int  Rs3Tree::getId() {
	return this->id;
};

Rs3Tree* Rs3Tree::getParent() {
	return this->parent;
};


void Rs3Tree::setChildOf(Rs3Tree* parent) {
	this->parent = new Rs3Tree;
	*this->parent = *parent;
	(this->parent->children).push_back(this);
}
