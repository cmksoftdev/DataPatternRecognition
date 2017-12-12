#pragma once
#include <algorithm>
#include <fstream>
#include "DataPatternRecognizerResult.h"

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

DataPatternRecognizerWorker::DataPatternRecognizerWorker(
	size_t _iWordSize,
	size_t _iPatternLength,
	vector<string> _filenames,
	vector<LogicPattern> _logicPatterns,
	bool _invertDirection)
{
	this->_iWordSize = _iWordSize;
	this->_iPatternLength = _iPatternLength;
	this->_filenames = _filenames;
	this->_logicPatterns = _logicPatterns;
	this->_invertDirection = _invertDirection;
}

DataPatternRecognizerWorker::~DataPatternRecognizerWorker()
{
}

int DataPatternRecognizerWorker::Seek()
{
	for (size_t i = 0; i < _filenames.capacity(); i++)
	{
		seek(_filenames.at(i));
	}
	return 0;
}

inline vector<DataPatternRecognizerResult> DataPatternRecognizerWorker::get_results()
{
	return this->_results;
}

int DataPatternRecognizerWorker::seek(string _filename)
{
	ifstream file(_filename, ifstream::ate | ifstream::binary); //
	if (file.is_open())
	{
		u_long _lFilesize = file.tellg();
		u_long _lCount = _lFilesize / _iWordSize;
		file.clear();
		file.seekg(0, ios::beg);
		BYTE** _currentData = new BYTE*[_iPatternLength];
		for (size_t i = 0; i < _iPatternLength; i++)
			_currentData[i] = new BYTE[_iWordSize];
		for (u_long i = 0; i < _lCount; i++)
		{
			delete(_currentData[0]);
			for (size_t j = 0; j < _iPatternLength-1; j++)
				_currentData[j] = _currentData[j + 1];
			_currentData[_iPatternLength-1] = new BYTE[_iWordSize];
			file.read((char*)_currentData[_iPatternLength - 1],_iWordSize);
			if (i >= _iPatternLength)
			{
				size_t _matches1 = 0;
				for (size_t j = 0; j < _logicPatterns.capacity(); j++)
				{
					size_t _matches2 = 0;
					for (size_t k = 0; k < _logicPatterns.at(j).get_length(); k++)
						if (_invertDirection)
							for (size_t l = 0; l < _iWordSize; l++)
							{
								if (l >= _iWordSize - 1 && 
									_currentData[_logicPatterns.at(j).get_at(0)][l] == 
									_currentData[_logicPatterns.at(j).get_at(k)][l])
										_matches2++;
								else if (_currentData[_logicPatterns.at(j).get_at(0)][l] != 
									_currentData[_logicPatterns.at(j).get_at(k)][l])
										break;
							}
						else
							for (size_t l = 0; l < _iWordSize; l++)
							{
								if (l >= _iWordSize - 1 && 
									_currentData[_logicPatterns.at(j).get_length() - 1][l] == 
									_currentData[_logicPatterns.at(j).get_at(_logicPatterns.at(j).get_length() - k - 1)][l])
										_matches2++;
								else if (_currentData[_logicPatterns.at(j).get_length() - 1][l] != 
									_currentData[_logicPatterns.at(j).get_at(_logicPatterns.at(j).get_length() - k - 1)][l])
										break;
							}
							_matches2++;
					if (_matches2 >= _logicPatterns.at(j).get_length())
						_matches1++;
				}
				if (_matches1 >= _logicPatterns.capacity() - 1)
				{
					for (size_t j = 0; j < _logicPatterns.capacity() - 1; j++)
					{
						for (size_t k = 0; k < _iWordSize; k++)
							if (j >= _logicPatterns.capacity() - 2 &&
								_currentData[_logicPatterns.at(j).get_at(0)][k] !=
								_currentData[_logicPatterns.at(j + 1).get_at(0)][k])
									_matches1++;
							else if (_currentData[_logicPatterns.at(j).get_at(0)][k] ==
								_currentData[_logicPatterns.at(j + 1).get_at(0)][k])
									break;
					}
					if (_matches1 >= _logicPatterns.capacity() + 1)
						_results.push_back(DataPatternRecognizerResult(i*_iWordSize - _iPatternLength*_iWordSize, _filename));
				}
			}
		}
		for (size_t i = 0; i < _iPatternLength; i++)
			delete(_currentData[i]);
		delete(_currentData);
		file.close();
	}
	return 0;
}
