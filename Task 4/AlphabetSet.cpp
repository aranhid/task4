#include "pch.h"
#include "AlphabetSet.h"


AlphabetSet::AlphabetSet()
{
	for (int i = 0; i < SYMBOL_COUNT_RUS; i++)
	{
		symbols[i] = 0;
	}
	size = 0;
	stringInput = "";
}

AlphabetSet::AlphabetSet(string inputString)
{
	for (int i = 0; i < SYMBOL_COUNT_RUS; i++)
	{
		symbols[i] = 0;
	}
	size = 0;
	stringInput = inputString;
	parseString(inputString);
}


AlphabetSet::~AlphabetSet()
{
}

void AlphabetSet::addSymbol(unsigned char symbol)
{
	if (symbol >= 192 && symbol <= 223)
	{
		symbol += 32;
	}
	if (symbol < 224 || symbol > 255 || size == SYMBOL_COUNT_RUS)
		return;
	for (int i = 0; i < size; i++)
	{
		if (symbols[i] == symbol)
			return;
	}
	symbols[size] = symbol;
	size++;
	std::sort(symbols, symbols + size);
}

void AlphabetSet::removeSymbol(unsigned char symbol)
{
	if (symbol >= 192 && symbol <= 223)
	{
		symbol += 32;
	}
	if (symbol < 224 || symbol > 255 || size == SYMBOL_COUNT_RUS)
		return;
	for (int i = 0; i < size; i++)
	{
		if (symbols[i] == symbol)
		{
			symbols[i] = 255;
			std::sort(symbols, symbols + size);
			symbols[size-1] = 0;
			size--;
		}
	}
}

void AlphabetSet::parseString(string inputString)
{
	for (int i = 0; i<inputString.length();i++)
	{
		char temp = inputString[i];
		this->addSymbol(temp);
	}
}

AlphabetSet AlphabetSet::operator+(const AlphabetSet & rSet) const
{
	AlphabetSet temp = *this;
	for (int i = 0; i < rSet.size; i++)
	{
		temp.addSymbol(rSet.symbols[i]);
	}
	return temp;
}

AlphabetSet AlphabetSet::operator-(const AlphabetSet & rSet) const
{
	AlphabetSet temp = *this;
	for (int i = 0; i < rSet.size; i++)
	{
		temp.removeSymbol(rSet.symbols[i]);
	}
	return temp;
}

AlphabetSet AlphabetSet::operator*(const AlphabetSet & rSet) const
{
	AlphabetSet temp;
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < rSet.size; j++)
		{
			if (this->symbols[i] == rSet.symbols[j])
			{
				temp.addSymbol(this->symbols[i]);
			}
		}
	}
	return temp;
}

bool AlphabetSet::operator==(const AlphabetSet & rSet) const
{
	if(this->size != rSet.size)
		return false;

	for (int i = 0; i < this->size; i++)
	{
		if (this->symbols[i] != rSet.symbols[i])
			return false;
	}
	return true;
}

std::istream & operator>>(std::istream & in, AlphabetSet & set)
{
	string s;
	in.imbue(std::locale("Russian"));
	std::getline(in, s, '\r');
	set.parseString(s);
	set.stringInput = s;
	if (in.peek() == '\n')
		std::getline(in, s, '\n');
	return in;
}

std::ostream & operator<<(std::ostream & out, const AlphabetSet & set)
{
	for (int i = 0; i < set.size; i++)
	{
		out << set.symbols[i] << " ";
	}
	return out;
}
