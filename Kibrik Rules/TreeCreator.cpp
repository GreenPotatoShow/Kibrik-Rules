#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "TreeCreator.h"
#include "Rs3Tree.h"
#include "Rs3TreeSegment.h"
#include "macros.h"


#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <codecvt>
#include <windows.h>
#include <locale.h>
#include <cstdlib>

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
    setlocale(LC_ALL, "");
	std::ifstream file;
	std::string line;
	fileName = fileName.substr(0, fileName.size() - 4);
	file.open(RS3_DIRECTORY + fileName + ".rs3");
    if (!file.is_open()) {
        this->RSTNodes = RSTNodes;
    }
    else {
        while (line.find("<body>") == std::string::npos) {
            getline(file, line);
        }
        getline(file, line);


        std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
        std::wstring wline = myconv.from_bytes(line);

        while (wline.find(L"</body>") == std::string::npos) {
            indexBegin = wline.find(L">");
            if (wline[indexBegin - 1] != '/') { //segment
                indexEnd = wline.find(L"<", indexBegin + 1);
                id = std::stoi(wline.substr(wline.find(L"id=\"") + 4, wline.find(L"\"", wline.find(L"id=\"") + 4) - wline.find(L"id=\"") + 4));
                if (createdTreeNodes[id] == nullptr) { createdTreeNodes[id] = new Rs3Tree; }
                RSTNodes[id] = new Rs3TreeSegment(createdTreeNodes[id], lastLineIndex + 1, indexEnd - indexBegin);
                createdTreeNodes[id] = RSTNodes[id];
                createdTreeNodes[id]->setId(id);
                if (wline.find(L"parent=\"") != std::string::npos) {
                    parent = std::stoi(wline.substr(wline.find(L"parent=\"") + 8, wline.find(L"\"", wline.find(L"parent=\"") + 8) - wline.find(L"parent=\"") + 8));
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
                id = std::stoi(wline.substr(wline.find(L"id=\"") + 4, wline.find(L"\"", wline.find(L"id=\"") + 4) - wline.find(L"id=\"") + 4));
                if (createdTreeNodes[id] == nullptr) { createdTreeNodes[id] = new Rs3Tree; }
                createdTreeNodes[id] = new Rs3Tree(*createdTreeNodes[id]);
                createdTreeNodes[id]->setId(id);
                if (wline.find(L"parent=\"") != std::string::npos) {
                    parent = std::stoi(wline.substr(wline.find(L"parent=\"") + 8, wline.find(L"\"", wline.find(L"parent=\"") + 8) - wline.find(L"parent=\"") + 8));
                    if (createdTreeNodes[parent] == nullptr) { createdTreeNodes[parent] = new Rs3Tree; }
                    createdTreeNodes[id]->setChildOf(createdTreeNodes[parent]);
                    createdTreeNodes[parent]->setId(parent);
                }
                else {
                    *root = *createdTreeNodes[id];
                }
            }
            getline(file, line);
            wline = myconv.from_bytes(line);
        }
        this->RSTNodes = RSTNodes;
        file.close();
    }
}

std::map<int, Rs3TreeSegment*> TreeCreator::getRSTNodes() {
	return this->RSTNodes;
}
