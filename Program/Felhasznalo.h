#pragma once
#include "Szerepkor.h"
#include "AjanlatLista.h"
#include "Rendelesek.h"
#include "hibajegyzesek.h"

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

class Felhasznalo
{
	SzerepkorTipus szerepkorID;
	string nev, emailcim, jelszo;
protected:
	int felhasznaloID;
public:
	Felhasznalo() = default;
	Felhasznalo(int felhid, string felhnev, string jelszo, string email, int szID);
	virtual ~Felhasznalo() = default;

	//Felhasznalo * bejelentkezes(const map<string, string>& bejelentkezesiAdatok);
	const string& szerepkorMegnevezesAzonositasa() const;
	SzerepkorTipus getSzerepkorID() const;
	virtual void start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek);
};

