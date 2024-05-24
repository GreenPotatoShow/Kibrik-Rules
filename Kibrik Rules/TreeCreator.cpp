#include "TreeCreator.h"
#include "Rs3Tree.h"
#include "Rs3TreeSegment.h"
#include "macros.h"


#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <codecvt>
#include <locale>
#include <windows.h>
#include <stringapiset.h>

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
	std::wifstream file;
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
	std::wstring line;
	fileName = fileName.substr(0, fileName.size() - 4);
	file.open(RS3_DIRECTORY + fileName + ".rs3");
	while(line.find(L"<body>")==std::string::npos) {
		getline(file, line);
	}
	getline(file, line);
	while (line.find(L"</body>") == std::string::npos) {
		indexBegin =line.find(L">");
		if (line[indexBegin - 1] != '/' ) { //segment
			indexEnd = line.find(L"<", indexBegin + 1);
			id=std::stoi(line.substr(line.find(L"id=\"") + 4, line.find(L"\"", line.find(L"id=\"") + 4) - line.find(L"id=\"") + 4));
			if (createdTreeNodes[id] == nullptr) { createdTreeNodes[id] = new Rs3Tree; }
			RSTNodes[id] = new Rs3TreeSegment(createdTreeNodes[id], lastLineIndex + 1, indexEnd - indexBegin);
			createdTreeNodes[id] = RSTNodes[id];
			createdTreeNodes[id]->setId(id);
			if (line.find(L"parent=\"") != std::string::npos) {
				parent = std::stoi(line.substr(line.find(L"parent=\"") + 8, line.find(L"\"", line.find(L"parent=\"") + 8) - line.find(L"parent=\"") + 8));
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
			id = std::stoi(line.substr(line.find(L"id=\"") + 4, line.find(L"\"", line.find(L"id=\"") + 4) - line.find(L"id=\"") + 4));
			if (createdTreeNodes[id] == nullptr) { createdTreeNodes[id] = new Rs3Tree; }
			createdTreeNodes[id] = new Rs3Tree(*createdTreeNodes[id]);
			createdTreeNodes[id]->setId(id);
			if (line.find(L"parent=\"") != std::string::npos) {
				parent = std::stoi(line.substr(line.find(L"parent=\"") + 8, line.find(L"\"", line.find(L"parent=\"") + 8) - line.find(L"parent=\"") + 8));
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
	this->RSTNodes = RSTNodes;
	file.close();
}

std::map<int, Rs3TreeSegment*> TreeCreator::getRSTNods() {
	return this->RSTNodes;
}
