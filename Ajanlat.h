#pragma once
#include <string>

using namespace std;

class Ajanlat
{
	int ar, ajanlatID, etteremID; // ajanlatID csak éttermen belül egyedi
	bool elerhetoseg;
public:
	Ajanlat(int ar, int aID, bool el, int eID);

	int getAr() const;
	int getAjanlatID() const;
	int getEtteremID() const;
	bool getElerhetoseg() const;
	virtual const string& getNev() const = 0;

	virtual void kiir() const = 0; // lehet tisztán virtuális?
	virtual string getAdatokStringkent(bool kellIDk = true) const = 0;

};

