#include "Etterem.h"

Etterem::Etterem(int id, const string& nev) :
	etteremNev(nev),
	etteremID(id)
{}

void Etterem::kiir() const {
	cout << etteremID << ": " << etteremNev << endl;
}

bool Etterem::tranzakcioKezelese() const {

	//v�letlenszer�en gener�l egy sz�mot, esetek 20%-�ban hib�s a fizet�s
	srand((unsigned) time(NULL));

	int random = rand() % 5;

	return (random != 0);
}

//const string& Etterem::getNev() const {
//	return etteremNev;
//}