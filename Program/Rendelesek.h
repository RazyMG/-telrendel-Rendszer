#pragma once
#include "Rendeles.h"

using namespace std;

class Rendelesek
{
	list<Rendeles*> rendelesek;
public:
	Rendelesek() = default;
	Rendelesek(const list<Rendeles*>& r);
	const list<Rendeles*>& getRendelesek() const;


	void rendelesHozzaadasa(Rendeles* ujRendeles);
	void rendelesekKiirasa() const;
	void rendelesekKiirasa(int etteremID) const;
	void rendelesekKiirasa(int etteremID, string allapot) const;
	void rendelesekKiirasaFutar(int futarID) const;
};

