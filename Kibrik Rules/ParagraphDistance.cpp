#include "ParagraphDistance.h"

#include<iostream>
#include<string>

ParagraphDistance::ParagraphDistance(std::string text, int first, int second) {
	this->value = 0;
	std::string cutText=text.substr(first,second-first);
	while (cutText.find("\\n") != std::string::npos) {
		cutText = cutText.substr(cutText.find("\\n")+2);
		this->value += 1;
	}
}

int ParagraphDistance::getValue() {
	return this->value;
}