#pragma once
#include <string>
#include "DataPatternRecognizerWorker.hpp"

using namespace std;

class DataPatternRecognizer
{
public:
	DataPatternRecognizer(size_t wordSize, size_t patternLength);
	~DataPatternRecognizer();

	int AddFile(string fileName);
	int AddLogicPattern();
	int RemoveLogicPattern(int i);
	int AddLogicPatternItem(int i);
	int RemoveLogicPatternItem(int i);
	int Start();

private:
	size_t _iWordSize;
	size_t _iPatternLength;
	size_t _iSelectedLogicPatternIndex;
	vector<string> _filenames;
	vector<LogicPattern> _logicPatterns;
	DataPatternRecognizerWorker* _worker;

	int validationCheck();
};
