#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class DataPatternRecognizerResult
{
public:
	u_long Adress;
	string Filename;
	DataPatternRecognizerResult(u_long Adress, string Filename);
	~DataPatternRecognizerResult();

};

DataPatternRecognizerResult::DataPatternRecognizerResult(u_long Adress, string Filename)
{
	this->Adress = Adress;
	this->Filename = Filename;
}

DataPatternRecognizerResult::~DataPatternRecognizerResult()
{
}