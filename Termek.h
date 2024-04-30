#pragma once
#include <iostream>
#include <string>

using namespace std;

class Termek
{

	string nev, leiras, tipus;
	int id;
public:
	Termek(const string& nev, const string& leiras, const string& tipus, int id);

	const string& getNev() const;
	const string& getLeiras() const;
	const string& getTipus() const;
	int getID() const;


	void kiiras() const;
};

