#include "Ajanlat.h"

Ajanlat::Ajanlat(int ar, int aID, bool el, int eID):
	ar(ar),
	ajanlatID(aID),
	elerhetoseg(el),
	etteremID(eID)
{}

int Ajanlat::getAr() const {
	return ar;
}

int Ajanlat::getAjanlatID() const {
	return ajanlatID;
}

int Ajanlat::getEtteremID() const {
	return etteremID;
}

bool Ajanlat::getElerhetoseg() const {
	return elerhetoseg;
}

void Ajanlat::kiir() const {
	
}
//
//string Ajanlat::getAdatokStringkent() const {
//	return "";
//}
