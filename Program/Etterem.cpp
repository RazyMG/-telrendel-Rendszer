#include "Etterem.h"

Etterem::Etterem(int id, const string& nev) :
	etteremNev(nev),
	etteremID(id)
{}

void Etterem::kiir() const {
	cout << etteremID << ": " << etteremNev << endl;
}

bool Etterem::tranzakcioKezelese() const {

	//véletlenszerûen generál egy számot, esetek 20%-ában hibás a fizetés
	srand((unsigned) time(NULL));

	int random = rand() % 5;

	return (random != 0);
}

//const string& Etterem::getNev() const {
//	return etteremNev;
//}