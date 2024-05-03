#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class Etterem
{
	string etteremNev;
	int etteremID;
public:
	Etterem() = default;
	Etterem(int id, const string& nev);

	void kiir() const;
	bool tranzakcioKezelese() const;
	//const string& getNev() const;
};

