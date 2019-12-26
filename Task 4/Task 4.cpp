#include "pch.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "AlphabetSet.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream in("input.txt", ios::binary);
	// input.txt должен быть в ANSI кодировке
	ofstream out("output.txt");
	int stringCount = 0;
	while (!in.eof())
	{
		string s;
		getline(in, s, '\n');
		stringCount++;
	}
	in.seekg(0, in.beg);
	AlphabetSet *sets = new AlphabetSet[stringCount];
	stringCount = 0;

	while (!in.eof())
	{
		in >> sets[stringCount];
		stringCount++;
	}

	out << "Повторяющиеся:" << endl;
	for (int i = 0; i < stringCount; i++)
	{
		for (int j = i + 1; j < stringCount; j++)
		{
			if (sets[i] == sets[j])
				out << sets[i].stringInput << " | " <<sets[j].stringInput << endl;;
		}
	}
	out << endl;

	out << "Не содержат одинаковых букв:" << endl;
	for (int i = 0; i < stringCount; i++)
	{
		for (int j = i + 1; j < stringCount; j++)
		{
			if (sets[i] * sets[j] == AlphabetSet(""))
			{
				out << sets[i].stringInput << " | " << sets[j].stringInput << endl;
			}
		}
	}
}
