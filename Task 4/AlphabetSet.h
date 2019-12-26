#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

#define SYMBOL_COUNT_RUS 32

class AlphabetSet
{
private:
	unsigned char symbols[SYMBOL_COUNT_RUS];
	int size = 0;
public:
	string stringInput = "";
	AlphabetSet();
	AlphabetSet(string inputString);
	~AlphabetSet();

	void addSymbol(unsigned char symbol);
	void removeSymbol(unsigned char symbol);
	void parseString(string inputString);

	AlphabetSet operator + (const AlphabetSet &rSet) const;
	AlphabetSet operator - (const AlphabetSet &rSet) const;
	AlphabetSet operator * (const AlphabetSet &rSet) const;
	bool operator == (const AlphabetSet &rSet) const;

	friend std::istream& operator >> (std::istream &in, AlphabetSet &set);
	friend std::ostream& operator << (std::ostream &out, const AlphabetSet &set);
};

