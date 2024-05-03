#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Felhasznalo.h"
#include "Vasarlo.h"
#include "Futar.h"
#include "EttermiDolgozo.h"
#include "Adminisztrator.h"
#include "TermekAjanlat.h"
#include "MenuAjanlat.h"
#include "Etterem.h"
#include "hibajegyzesek.h"

using namespace std;

class EtelrendeloRendszer
{
	map<string, string> bejelentkezesiAdatok;
	static vector<Etterem*> ettermek;
public:
	EtelrendeloRendszer();

	map<string, string> felhasznalonevJelszoParokBetoltese();
	Felhasznalo* bejelentkezes();

	AjanlatLista ajanlatokBetolteseFajlbol() const;

	Rendelesek rendelesekBetolteseFajlbol(const AjanlatLista& lista) const;
	void rendelesekMenteseFajlba(const Rendelesek& rendelesek) const;

	static void ettermekBetolteseFajlbol(); //void-dal t�r vissza mert am�gy is � t�rolja a list�t
	static int ettermekKiirasa();
	//static const string& getEtteremNeve(int ettID);

	Hibajegyzesek hibajegyzesekBetolteseFajlbol() const;

};


