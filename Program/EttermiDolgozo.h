#pragma once
#include "Felhasznalo.h"
#include "TermekAjanlat.h"
#include "MenuAjanlat.h"
#include "ValtoztatasiKerelem.h"

class EttermiDolgozo :public Felhasznalo
{
protected:
	int etteremID;
	bool jogosultsag;
public:
	EttermiDolgozo(int felhid, string felhnev, string jelszo, string email, int szID, int ettId, bool jog);
	virtual void start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek);

	int getEtteremID() const;

	void sajatAjanlatokMegtekintese(const AjanlatLista& lista) const;
	void rendelesekMegtekintese(const Rendelesek& rendelesek) const;

	TermekAjanlat* ajanlatInformacioMegadasa(const AjanlatLista& lista, const string& eddiginev = "") const;
	MenuAjanlat* ajanlatInformacioMegadasa(const AjanlatLista& lista, const list<int>& ajanlatIDk, const string& eddiginev = "") const;

	bool ajanlatHozzaadasa(AjanlatLista& lista, Hibajegyzesek& hibajegyzesek) const;
	bool ajanlatFrissitese(AjanlatLista& lista, Hibajegyzesek& hibajegyzesek) const;
	bool ajanlatTorlese(AjanlatLista& lista) const;

	void rendelesAllapotanakFrissitese(const Rendelesek& rendelesek);
	void futarMegbizasaRendelessel(const Rendelesek& rendelesek) const;
};

