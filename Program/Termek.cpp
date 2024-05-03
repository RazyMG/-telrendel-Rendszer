#include "Termek.h"

Termek::Termek(const string& nev, const string& leiras, const string& tipus, int id):
	nev(nev),
	leiras(leiras),
	tipus(tipus),
	id(id)
{

}

const string& Termek::getNev() const {
	return nev;
}

const string& Termek::getLeiras() const {
	return leiras;
}

const string& Termek::getTipus() const {
	return tipus;
}

void Termek::kiiras() const {
	cout << nev << " (" << tipus << "): " << leiras << endl;
}

int Termek::getID() const {
	return id;
}