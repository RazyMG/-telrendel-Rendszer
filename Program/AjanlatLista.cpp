#include "AjanlatLista.h"

void AjanlatLista::ajanlatHozzadasa(int eID, Ajanlat* ujAjanlat) {
	ajanlatok[eID].push_back(ujAjanlat);
	sort(ajanlatok[eID].begin(), ajanlatok[eID].end(), [](const Ajanlat* a1, const Ajanlat* a2) {
		return a1->getAjanlatID() < a2->getAjanlatID();
		});
}

bool AjanlatLista::ajanlatFelulirasa(int etteremID, Ajanlat* ujAjanlat, int ajanlatID) {

	auto it = (find_if(ajanlatok[etteremID].begin(), ajanlatok[etteremID].end(), [ajanlatID](const Ajanlat* a) {
		return a->getAjanlatID() == ajanlatID;
		}));
	if (it != ajanlatok[etteremID].end()) {

		*it = ujAjanlat;
		sort(ajanlatok[etteremID].begin(), ajanlatok[etteremID].end(), [](const Ajanlat* a1, const Ajanlat* a2) {
			return a1->getAjanlatID() < a2->getAjanlatID();
			});
		return true;
	}
	else {
		return false;
	}

}

bool AjanlatLista::ajanlatTorlese(int etteremID, int ajanlatID) {
	auto etterem_it = ajanlatok.find(etteremID);
	if (etterem_it != ajanlatok.end()) {
		auto it = find_if(etterem_it->second.begin(), etterem_it->second.end(), [&](const Ajanlat* a) {
			return (a->getAjanlatID() == ajanlatID && a->getEtteremID() == etteremID);
			});
		if (it != etterem_it->second.end()) {
			etterem_it->second.erase(it);
			return true;
		}
	}
	else {
		return false;
	}
}

void AjanlatLista::ajanlatokKiirasa() const {
	for (auto etterem : ajanlatok) {
		cout << "Etterem " << etterem.first << endl; // étterem neve?
		for (auto a : etterem.second) {
			if (a->getElerhetoseg()) {
				cout << "\t";
				a->kiir();
			}
		}
	}
}

void AjanlatLista::ajanlatokKiirasa(int etteremID, bool mutatNemElerheto) const {
	auto it = ajanlatok.find(etteremID);
	if (it != ajanlatok.end()) {
		cout << endl;
		for (auto a : it->second) {
			if (mutatNemElerheto || a->getElerhetoseg()) {
				a->kiir();
			}
		}
		cout << endl;
	}
}

Ajanlat* AjanlatLista::getAjanlat(int etteremID, int ajanlatID) const {
	auto etterem_it = ajanlatok.find(etteremID);
	if (etterem_it != ajanlatok.end()) {
		if (ajanlatID >= 0) {
			Ajanlat* a;
			auto it = find_if(etterem_it->second.begin(), etterem_it->second.end(), [=](const Ajanlat* ajanlat) {
				return ajanlat->getAjanlatID() == ajanlatID; });
			if (it != etterem_it->second.end()) {
				a = *it;
				return a;
			}
		}
	}
	else {
		cout << "HIBA: Nincs ilyen ID-ju etterem!" << endl;
	}
	return nullptr; //nincs olyan ID-jû ajánlat
}

void AjanlatLista::ajanlatokMenteseFajlba() const {
	fstream file("ajanlatok.txt", ios::out | ios::trunc);

	if (file.is_open()) {
		for (auto etterem : ajanlatok) {
			unsigned i = 0;
			for (auto a : etterem.second) {
				file << a->getAdatokStringkent();
				if (++i < etterem.second.size()) {
					file << endl;
				}
			}
			file << endl;
		}
		file << -99;
	}
	else {
		cout << "HIBA: fajl megnyitasa sikertelen.";
	}
}

int AjanlatLista::getMeret(int ettID) const {
	auto it = ajanlatok.find(ettID);
	if (it != ajanlatok.end()) {
		return it->second.size();
	}
	else {
		cout << "HIBA: nincs etterem ilyen ID-vel!" << endl;
		return -1;
	}
}

bool AjanlatLista::vanOlyanNevuAjanlat(int ettID, const string& nev) const {
	auto it = ajanlatok.find(ettID);
	if (it != ajanlatok.end()) {
		return any_of(it->second.begin(), it->second.end(), [&](const Ajanlat* a) {
			return a->getNev() == nev;
			});
	}
	else {
		cout << "HIBA: nincs etterem ilyen ID-vel!" << endl;
		return false;
	}
}

int AjanlatLista::szamolElsoID(int ettID) const {
	auto it = ajanlatok.find(ettID);

	if (it != ajanlatok.end()) {
		auto a_it = max_element(it->second.begin(), it->second.end(), [](const Ajanlat* a1, const Ajanlat* a2) {
			return a1->getAjanlatID() < a2->getAjanlatID();
			});
		return (*a_it)->getAjanlatID() + 1;
	}
}