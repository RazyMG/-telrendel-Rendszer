#include "MenuAjanlat.h"

MenuAjanlat::MenuAjanlat(int ar, int aID, bool el, int eID, const Menu& m) :
	Ajanlat(ar, aID, el, eID),
	menu(m)
{

}

void MenuAjanlat::kiir() const {
	cout << getAjanlatID() << ": " << getAr() << " Ft - ";
	menu.kiiras();
}

string MenuAjanlat::getAdatokStringkent(bool kellIDk) const {
	stringstream str;
	str << "1 " << menu.getNev() << " # " << menu.getLeiras() << " # " << getAr() << " ";
	if (kellIDk) {
		str << getAjanlatID() << " ";
	}
	str << getElerhetoseg() << " ";
	if (kellIDk) {
		str << getEtteremID() << " ";
	}
	str << endl;
	str << menu.getTermekIDkStringkent();
	return str.str();
}

const string& MenuAjanlat::getNev() const {
	return menu.getNev();
}