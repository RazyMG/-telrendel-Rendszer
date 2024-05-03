#pragma once
#include "Ajanlat.h"
#include "Menu.h"
#include <sstream>

class MenuAjanlat :public Ajanlat
{
public:
	Menu menu;
	MenuAjanlat(int ar, int aID, bool el, int eID, const Menu& m);
	virtual void kiir() const override;
	virtual string getAdatokStringkent(bool kellIDk = true) const override;
	virtual const string& getNev() const override;

};


