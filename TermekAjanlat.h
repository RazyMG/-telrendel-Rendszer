#pragma once
#include "Ajanlat.h"
#include "Termek.h"
#include <sstream>
class TermekAjanlat:public Ajanlat
{
public:
	Termek termek;
	TermekAjanlat(int ar, int aID, bool el, int eID, const Termek& t);
	virtual void kiir() const override;
	virtual string getAdatokStringkent(bool kellIDk = true) const override;
	virtual const string& getNev() const override;

};

