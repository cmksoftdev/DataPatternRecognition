#include "DataPatternRecognizerResult.hpp"

DataPatternRecognizerResult::DataPatternRecognizerResult(u_long Adress, string Filename)
{
	this->Adress = Adress;
	this->Filename = Filename;
}

DataPatternRecognizerResult::~DataPatternRecognizerResult()
{
}