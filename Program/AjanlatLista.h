#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Ajanlat.h"

using namespace std;

class AjanlatLista
{
	map<int, vector<Ajanlat*> > ajanlatok;
public:
	void ajanlatHozzadasa(int eID, Ajanlat* ujAjanlat);
	bool ajanlatFelulirasa(int etteremID, Ajanlat* ujAjanlat, int ajanlatID);
	bool ajanlatTorlese(int etteremID, int ajanlatID);


	void ajanlatokKiirasa() const;
	void ajanlatokKiirasa(int etteremID, bool mutatNemElerheto) const;

	Ajanlat* getAjanlat(int etteremID, int ajanlatID) const;

	void ajanlatokMenteseFajlba() const;

	int getMeret(int ettID) const;
	bool vanOlyanNevuAjanlat(int ettID, const string& nev) const;

	int szamolElsoID(int ettID) const;


};

