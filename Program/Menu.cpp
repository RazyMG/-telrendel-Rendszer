#include "Menu.h"

Menu::Menu(const string& nev, const string& leiras, const list<Termek*>& termekek):
	nev(nev),
	leiras(leiras),
	termekek(termekek)
{

}

const string& Menu::getNev() const {
	return nev;
}

const string& Menu::getLeiras() const {
	return leiras;
}

void Menu::kiiras() const {
	cout << nev << " (Menu): " << leiras << endl;

	for (auto t : termekek) {
		cout << "\t\t";
		t->kiiras();
	}
}

string Menu::getTermekIDkStringkent() const {
	stringstream str;
	for (auto termek : termekek) {
		str << termek->getID() << endl;
	}
	str << "-1";
	return str.str();
}