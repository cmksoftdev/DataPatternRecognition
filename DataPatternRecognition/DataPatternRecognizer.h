#pragma once
#include <string>
#include "LogicPattern.h"
#include "DataPatternRecognizerWorker.h"

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

DataPatternRecognizer::DataPatternRecognizer(size_t wordSize, size_t patternLength)
{
	_iWordSize = wordSize;
	_iPatternLength = patternLength;
	_iSelectedLogicPatternIndex = -1;
}

DataPatternRecognizer::~DataPatternRecognizer()
{
}

int DataPatternRecognizer::AddFile(string fileName)
{
	_filenames.push_back(fileName);
	return EXIT_SUCCESS;
}

int DataPatternRecognizer::AddLogicPattern()
{
	_logicPatterns.push_back(LogicPattern());
	_iSelectedLogicPatternIndex++;
	return EXIT_SUCCESS;
}

int DataPatternRecognizer::RemoveLogicPattern(int i)
{
	_logicPatterns.erase(_logicPatterns.begin() + i);
	return EXIT_SUCCESS;
}

int DataPatternRecognizer::AddLogicPatternItem(int i)
{
	return _logicPatterns.at(_iSelectedLogicPatternIndex).Add(i);
}

int DataPatternRecognizer::RemoveLogicPatternItem(int i)
{
	return _logicPatterns.at(_iSelectedLogicPatternIndex).Remove(i);
}

int DataPatternRecognizer::Start()
{
	_worker = new DataPatternRecognizerWorker(this->_iWordSize, this->_iPatternLength, this->_filenames, this->_logicPatterns, true);
	_worker->Seek();
	auto var = _worker->get_results();
	_worker->~DataPatternRecognizerWorker();
	return EXIT_SUCCESS;
}
