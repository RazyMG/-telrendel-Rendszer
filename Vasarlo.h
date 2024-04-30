#pragma once
#include "Felhasznalo.h"
#include "EtelrendeloRendszer.h"
#include "Rendeles.h"

class Vasarlo:public Felhasznalo
{
	Rendeles kosar; 
public:
	Vasarlo(int felhid, string felhnev, string jelszo, string email, int szID);
	virtual void start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek) override;

	int ajanlatokMegtekintese(const AjanlatLista& lista) const;
	bool ajanlatHozzaadasaRendeleshez(const AjanlatLista& lista, Hibajegyzesek& hibajegyzesek);
	bool ajanlatKiszedeseRendelesbol(const AjanlatLista& lista);
	void kosarUritese();
	void kosarMegtekintese() const;
	void rendelesAllapotanakMegtekintese(const Rendelesek& rendeles) const;
	bool rendelesVeglegesitese(Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek);
	bool megerosites() const;
};

