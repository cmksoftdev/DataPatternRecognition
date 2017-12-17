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