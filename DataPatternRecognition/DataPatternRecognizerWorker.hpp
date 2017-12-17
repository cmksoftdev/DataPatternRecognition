#pragma once
#include <algorithm>
#include <fstream>
#include "DataPatternRecognizerResult.hpp"
#include "LogicPattern.hpp"

class DataPatternRecognizerWorker
{
public:
	DataPatternRecognizerWorker(
		size_t _iWordSize,
		size_t _iPatternLength,
		vector<string> _filenames,
		vector<LogicPattern> _logicPatterns,
		bool _invertDirection);
	~DataPatternRecognizerWorker();
	int Seek();
	vector<DataPatternRecognizerResult> get_results();

private:
	size_t _iWordSize;
	size_t _iPatternLength;
	vector<string> _filenames;
	vector<LogicPattern> _logicPatterns;
	vector<DataPatternRecognizerResult> _results;
	bool _invertDirection;

	int seek(string _filename);
};