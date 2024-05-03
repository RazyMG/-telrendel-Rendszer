#include "Rendeles.h"

Rendeles::Rendeles(int felhID) :
	felhasznaloID(felhID)
{}

Rendeles::Rendeles(int rendID, int ettID, int felhID, int futarID, const list<Ajanlat*>& l, const string& alla, const Datum& d):
	rendelesID(rendID), etteremID(ettID), felhasznaloID(felhID), futarID(futarID), ajanlatok(l), allapot(alla), datum(d)
{

}

void Rendeles::ajanlatHozzaadasa(Ajanlat* ujAjanlat)
{
	ajanlatok.push_back(ujAjanlat);
	meret++;
}

void Rendeles::urites()
{
	ajanlatok.clear();
	etteremID = -1;
	cout << "Kosar uritve!" << endl;
}

void Rendeles::kiiras() const
{
	cout << "RENDELES " << rendelesID << endl;
	cout << "Felhasznalo: " << felhasznaloID << endl;
	cout << "Allapot: " << allapot << endl;
	cout << "Leadva: ";
	datum.kiir();
	cout << "Megbizott futar: ";
	if (futarID == -1)
		cout << "Nincs meg" << endl;
	else cout << futarID << endl;

	
	cout << "Rendelesben levo ajanlatok:" << endl;
	for (auto v : ajanlatok) {
		MenuAjanlat* m = dynamic_cast<MenuAjanlat*>(v);
		if (m) {
			cout << "\t" << m->getAjanlatID() <<": " << m->menu.getNev() << endl;
		}
		else {
			TermekAjanlat* t = dynamic_cast<TermekAjanlat*>(v);
			if (t) {
				cout << "\t" << t->getAjanlatID() << ": " << t->termek.getNev() << endl;
			}
		}
	}
	int sum = accumulate(ajanlatok.begin(), ajanlatok.end(), 0, [](int sum, const Ajanlat* a) {
		return sum += a->getAr();
		});
	cout << "Osszar: " << sum << " Ft" << endl << endl;
	
}

int Rendeles::getRendelesID() const {
	return rendelesID;
}

void Rendeles::setRendelesID(int id) {
	rendelesID = id;
}

int Rendeles::getEtteremID() const
{
	return etteremID;
}

void Rendeles::setEtteremID(int id) {
	etteremID = id;
}

string Rendeles::getAllapot() const
{
	return allapot;
}

void Rendeles::setAllapot(const string& ujAllapot) {
	allapot = ujAllapot;
}

int Rendeles::getFelhasznaloID() const
{
	return felhasznaloID;
}

void Rendeles::setDatum(const Datum& d) {
	datum = d;
}


int Rendeles::getFutarID() const {
	return futarID;
}

void Rendeles::setFutarID(int ujID) {
	futarID = ujID;
}

bool Rendeles::ajanlatKiszedese(Ajanlat* ajanlat)
{
	auto it = find_if(ajanlatok.begin(), ajanlatok.end(), [&](const Ajanlat* a) {
		return (a->getAjanlatID() == ajanlat->getAjanlatID() && a->getEtteremID() == ajanlat->getEtteremID()); ;
		});
	(*it)->kiir();
	cout << endl;
	if (it != ajanlatok.end()) {
		ajanlatok.erase(it);
		meret--;
		// ha ezzel kiürült a rendelés, akkor az étteremID-t visszaállítja -1-re, hogy utána bármilyen étteremtõl tudjon hozzáadni
		if (meret == 0) {
			etteremID = -1;
		}

		return true;

	}
	else {
		return false;
	}
}

string Rendeles::getAdatokStringkent() const {
	stringstream str;
	str << rendelesID << " " << etteremID << " " << felhasznaloID << " " << futarID << " ";
	for (auto a : ajanlatok) {
		str << a->getAjanlatID() << " ";
	}
	str << "-1 " << allapot << " " << datum.getAdatokStringkent();
	return str.str();
}