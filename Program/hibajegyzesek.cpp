#include "hibajegyzesek.h"

Hibajegyzesek::Hibajegyzesek()
{

}


void Hibajegyzesek::hibaBejegyzese(Hibajegyzes* hiba)
{
    bejegyzes.push_back(hiba);
}

void Hibajegyzesek::kiir() const
{
	unsigned i = 0;
    for(auto h : bejegyzes)
    {
		cout << "HIBAJEGYZES " << i++ <<endl;
        h->kiir();
    }
}

void Hibajegyzesek::hibajegyzesekMenteseFajlba() const {
	fstream file("hibajegyzesek.txt", ios::out | ios::trunc);

	if (file.is_open()) {

		for (auto b : bejegyzes) {
			file << b->getAdatokStringkent() <<endl;
		}
		file << -1;

	}
	else {
		cout << "HIBA: 'hibajegyzesek.txt' megnyitasa sikertelen!" << endl;
	}
}