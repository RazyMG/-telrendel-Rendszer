#pragma once
#include "Felhasznalo.h"

class Futar :public Felhasznalo
{
	int etteremID;
public:
	Futar(int felhid, string felhnev, string jelszo, string email, int szID, int ettId);

	virtual void start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek) override;
	void rendelesekMegtekintese(const Rendelesek& rendelesek) const;
	void rendelesAllapotanakFrissitese(const Rendelesek& rendelesek);
};

