#pragma once

#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "MenuAjanlat.h"
#include "TermekAjanlat.h"
#include "Datum.h"
#include "Ajanlat.h"

using namespace std;


class Rendeles
{
	int rendelesID, etteremID, felhasznaloID, futarID = -1;
	int meret = 0;
	list<Ajanlat*> ajanlatok;
	string allapot;
	Datum datum;
public:
	Rendeles(int rendID, int ettID, int felhID, int futarID, const list<Ajanlat*>& l, const string& alla, const Datum& d);
	
	// ezt a konstruktort a vásárló kosár adattagja használja
	Rendeles(int felhID);

	void ajanlatHozzaadasa(Ajanlat* ujAjanlat);
	bool ajanlatKiszedese(Ajanlat* ajanlat); //TODO: benne van-e a törölni kívánt ajánlat

	void urites();
	void kiiras() const;

	int getRendelesID() const;
	void setRendelesID(int id);

	int getEtteremID() const;
	void setEtteremID(int id);
	string getAllapot() const;
	void setAllapot(const string& ujAllapot);
	void setDatum(const Datum& d);

	int getFelhasznaloID() const;

	int getFutarID() const;
	void setFutarID(int ujID);
	
	string getAdatokStringkent() const;
};

