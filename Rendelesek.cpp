#include "Rendelesek.h"

Rendelesek::Rendelesek(const list<Rendeles*>& r):
	rendelesek(r)
{

}

const list<Rendeles*>& Rendelesek::getRendelesek() const {
	return rendelesek;
}

void Rendelesek::rendelesHozzaadasa(Rendeles* ujRendeles)
{
	rendelesek.push_back(ujRendeles);
}

void Rendelesek::rendelesekKiirasa() const
{
	for (auto v : rendelesek) {
		v->kiiras();
		cout << endl;
	}
}

void Rendelesek::rendelesekKiirasa(int etteremID) const
{
	for (auto v : rendelesek) {
		if (v->getEtteremID() == etteremID) {
			v->kiiras();
		}
	}
}

void Rendelesek::rendelesekKiirasa(int etteremID, string allapot) const
{
	for (auto v : rendelesek) {
		if (v->getEtteremID() == etteremID && v->getAllapot()==allapot) {
			v->kiiras();
		}
	}
}

void Rendelesek::rendelesekKiirasaFutar(int futarID) const
{
	for (auto v : rendelesek) {
		if (v->getFutarID() == futarID) {
			v->kiiras();
		}
	}
}

