#include "TermekAjanlat.h"

TermekAjanlat::TermekAjanlat(int ar, int aID, bool el, int eID, const Termek& t) :
	Ajanlat(ar, aID, el, eID),
	termek(t)
{}

void TermekAjanlat::kiir() const {
	cout << getAjanlatID() << ": " << getAr() << " Ft - ";
	termek.kiiras();
}

string TermekAjanlat::getAdatokStringkent(bool kellIDk) const {
	stringstream str;
	str << "0 " << termek.getNev() << " # " << termek.getLeiras() << " # " << getAr() << " ";
	if (kellIDk) {
		str << getAjanlatID() << " ";
	}
	str << getElerhetoseg() << " ";
	if (kellIDk) {
		str << getEtteremID() << " ";
	}
	str << termek.getTipus();
	return str.str();
}

const string& TermekAjanlat::getNev() const {
	return termek.getNev();
}