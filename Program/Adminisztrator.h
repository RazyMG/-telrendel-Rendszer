#pragma once
#include <sstream>

#include "EtelrendeloRendszer.h"
#include "EttermiDolgozo.h"
#include "TermekAjanlat.h"
#include "MenuAjanlat.h"

using namespace std;

class Adminisztrator :public EttermiDolgozo
{
	vector<ValtoztatasiKerelem*> kerelmek;

public:
	Adminisztrator(int felhid, string felhnev, string jelszo, string email, int szID);

	virtual void start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek) override;

	void etteremJogosultsagBeallitasa() const;
	void dolgozoJogosultsagBeallitasa() const;

	void kerelmekBetolteseFajlbol(const AjanlatLista& lista); //ez is térhet vissza voiddal
	void kerelmekMenteseFajlba() const;

	void valtoztatasiKerelmekMegtekintese() const;
	void valtoztatasiKerelemFelulbiralasa(AjanlatLista& lista);


	bool ajanlatHozzaadasa(AjanlatLista& lista, Hibajegyzesek& hibajegyzesek);
	bool ajanlatFrissitese(AjanlatLista& lista, Hibajegyzesek& hibajegyzesek);
	bool ajanlatTorlese(AjanlatLista& lista);

	void rendelesAllapotanakFrissitese(const Rendelesek& rendelesek);

	void hibajegyzesekMegtekintese(const Hibajegyzesek& hibak) const;
	
};


