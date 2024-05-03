#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Termek.h"
#include <sstream>

using namespace std;

class Menu
{
	string nev, leiras;
	list<Termek*> termekek;

public:
	//TODO: hogyan t�roljuk a term�keket? (f�jlban meg itt is)
	//TermekAjanlat adott ID-vel, abban elt�rolt Termekre mutat�t rakunk ide
	Menu(const string& nev, const string& leiras, const list<Termek*>& termekek);

	const string& getNev() const;
	const string& getLeiras() const;

	void kiiras() const;

	string getTermekIDkStringkent() const;
};

