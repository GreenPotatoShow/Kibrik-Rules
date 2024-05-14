#include "TreeCreator.h"
#include "Rs3Tree.h"
#include "Rs3TreeSegment.h"
#include "macros.h"


#include <iostream>
#include <fstream>
#include <string>
#include <map>

TreeCreator::TreeCreator(std::string fileName) {
	int indexBegin;
	int indexEnd;
	int id;
	int parent;
	int lastLineIndex;
	indexBegin=0;
	indexEnd=0;
	id=0;
	parent=0;
	lastLineIndex = 0;
	Rs3Tree* root=new Rs3Tree;
	std::map<int, Rs3Tree*> createdTreeNodes;
	std::map<int, Rs3TreeSegment*> RSTNodes;
	setlocale(LC_ALL, "Russian");
	std::ifstream file;
	std::string line;
	fileName = fileName.substr(0, fileName.size() - 4);
	file.open(RS3_DIRECTORY + fileName + ".rs3");
	while(line.find("<body>")==std::string::npos) {
		getline(file, line);
	}
	getline(file, line);
	while (line.find("</body>") == std::string::npos) {
		indexBegin =line.find(">");
		if (line[indexBegin - 1] != '/' ) { //segment
			indexEnd = line.find("<", indexBegin + 1);
			id=std::stoi(line.substr(line.find("id=\"") + 4, line.find("\"", line.find("id=\"") + 4) - line.find("id=\"") + 4));
			//std::cout << id << "\n";
			if (createdTreeNodes[id] == nullptr) { createdTreeNodes[id] = new Rs3Tree; }
			RSTNodes[id] = new Rs3TreeSegment(createdTreeNodes[id], lastLineIndex + 1, indexEnd - indexBegin);
			createdTreeNodes[id] = RSTNodes[id];
			createdTreeNodes[id]->setId(id);
			if (line.find("parent=\"") != std::string::npos) {
				parent = std::stoi(line.substr(line.find("parent=\"") + 8, line.find("\"", line.find("parent=\"") + 8) - line.find("parent=\"") + 8));
				if (createdTreeNodes[parent] == nullptr) { createdTreeNodes[parent] = new Rs3Tree; }
				createdTreeNodes[id]->setChildOf(createdTreeNodes[parent]);
				createdTreeNodes[parent]->setId(parent);
			}
			else {
				*root = *createdTreeNodes[id];
			}
			lastLineIndex += indexEnd - indexBegin;
		}
		else { //group
			id = std::stoi(line.substr(line.find("id=\"") + 4, line.find("\"", line.find("id=\"") + 4) - line.find("id=\"") + 4));
			if (createdTreeNodes[id] == nullptr) { createdTreeNodes[id] = new Rs3Tree; }
			createdTreeNodes[id] = new Rs3Tree(*createdTreeNodes[id]);
			createdTreeNodes[id]->setId(id);
			if (line.find("parent=\"") != std::string::npos) {
				parent = std::stoi(line.substr(line.find("parent=\"") + 8, line.find("\"", line.find("parent=\"") + 8) - line.find("parent=\"") + 8));
				if (createdTreeNodes[parent] == nullptr) { createdTreeNodes[parent] = new Rs3Tree; }
				createdTreeNodes[id]->setChildOf(createdTreeNodes[parent]);
				createdTreeNodes[parent]->setId(parent);
			}
			else {
				*root = *createdTreeNodes[id];
			}
		}
		getline(file, line);
	}
	//std::cout << lastLineIndex;
	this->RSTNodes = RSTNodes;
	file.close();
}

std::map<int, Rs3TreeSegment*> TreeCreator::getRSTNods() {
	return this->RSTNodes;
}