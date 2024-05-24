#include "Rs3TreeSegment.h"

Rs3TreeSegment::Rs3TreeSegment(int id, int begin=0, int end=0): Rs3Tree(id) {
	this->characterRangeBegin = begin;
	this->characterRangeEnd = end;
}

Rs3TreeSegment::Rs3TreeSegment(Rs3Tree* rs3tree, int begin=0, int end=0) : Rs3Tree(*rs3tree) {
	this->characterRangeBegin = begin;
	this->characterRangeEnd=end;
}

void Rs3TreeSegment::setRangeBegin(int begin) {
	this->characterRangeBegin = begin;
}

void Rs3TreeSegment::setRangeEnd(int end) {
	this->characterRangeEnd = end;
}

int Rs3TreeSegment::getRangeBegin() {
	return this->characterRangeBegin;
}
int Rs3TreeSegment::getRangeEnd() {
	return this->characterRangeEnd;
}
