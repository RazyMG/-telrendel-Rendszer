#pragma once
#include "Datum.h"
#include "Ajanlat.h"
#include "AjanlatLista.h"
#include <string>
#include <list>

using namespace std;

class ValtoztatasiKerelem
{
	int etteremID, ajanlatID;
	Ajanlat* ajanlat;
	string tipus;
	Datum datum;
public:
	ValtoztatasiKerelem(int ettID, int ajID, Ajanlat* aj, const string& tip, const Datum& d); //TODO: datum hozzaadasa
	ValtoztatasiKerelem(int ettID, int ajID, const string& tip, const Datum& d);

	void kiiras() const;
	bool vegrehajtas(AjanlatLista& ajanlatLista);
	string getAdatokStringkent() const;
	void mentesFajlba() const;
};

