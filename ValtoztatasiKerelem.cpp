#include "ValtoztatasiKerelem.h"

ValtoztatasiKerelem::ValtoztatasiKerelem(int ettID, int ajID, Ajanlat* aj, const string& tip, const Datum& d):
	etteremID(ettID), ajanlatID(ajID), ajanlat(aj), tipus(tip), datum(d)
{
}

ValtoztatasiKerelem::ValtoztatasiKerelem(int ettID, int ajID, const string& tip, const Datum& d) :
	etteremID(ettID), ajanlatID(ajID), ajanlat(nullptr), tipus(tip), datum(d)
{
}

bool ValtoztatasiKerelem::vegrehajtas(AjanlatLista& ajanlatLista)
{
	bool siker = false;
	if (tipus.compare("Hozzaadas") == 0) {
		ajanlatLista.ajanlatHozzadasa(etteremID, ajanlat);
		return true;
	} 
	else if (tipus.compare("Frissites") == 0) {
		bool siker = ajanlatLista.ajanlatFelulirasa(etteremID, ajanlat, ajanlatID);
	}
	else if (tipus.compare("Torles") == 0) {
		bool siker = ajanlatLista.ajanlatTorlese(etteremID, ajanlatID);
	}
	else {
		cout << "\nHibás típus(?)" << endl;
		return false;
	}

	if (siker)
		ajanlatLista.ajanlatokMenteseFajlba();
	return siker;
}

void ValtoztatasiKerelem::kiiras() const {
	cout << "\tErintett etterem: " << etteremID << endl;
	cout << "\tErintett ajanlat: " << ajanlatID << endl;
	cout << "\tMuvelet: " << tipus << endl;
	if (tipus != "Torles") {
		cout << "\tAjanlatinformacio:\n\t\t";
		ajanlat->kiir();
	}
	cout << "\tBenyujtva: ";
	datum.kiir();
	cout << endl;
}

string ValtoztatasiKerelem::getAdatokStringkent() const {
	stringstream str;
	if (tipus != "Torles")
		str << etteremID << " " << ajanlatID << " " << tipus << " " << ajanlat->getAdatokStringkent(false) << " " << datum.getAdatokStringkent();
	else str << etteremID << " " << ajanlatID << " " << tipus << " " << datum.getAdatokStringkent();
	return str.str();

}

void ValtoztatasiKerelem::mentesFajlba() const {

	//append módban megnyitja a kérelmek fájlját
	fstream file("valtoztatasikerelmek.txt");

	if (file.is_open()) {
		list<string> lines;
		string line;
		while (getline(file, line)) {
			if (line != "-99") {
				lines.push_back(line);
			}
		}
		file.close();
		file.open("valtoztatasikerelmek.txt");
		for (auto l : lines) {
			file << l << endl;
		}
		file << getAdatokStringkent() <<endl;
		file << -99;
	}
	else {
		cout << "HIBA: fajl megnyitasa sikertelen." << endl;
	}
}