#include "EtelrendeloRendszer.h"

vector<Etterem*> vektorInit() {
	vector<Etterem*> v;
	return v;
}

vector<Etterem*> EtelrendeloRendszer::ettermek = vektorInit();

EtelrendeloRendszer::EtelrendeloRendszer() {
	
}

map<string, string> EtelrendeloRendszer::felhasznalonevJelszoParokBetoltese() {

	ifstream in("felhasznalonevjelszo.txt");

	if (in.is_open()) {
		string felhasznalonev;
		in >> felhasznalonev;
		while (felhasznalonev != "*") {
			string jelszo;
			in >> jelszo;
			bejelentkezesiAdatok[felhasznalonev] = jelszo;

			in >> felhasznalonev;
		}

	}
	else {
		cout << "Nem sikerult megnyitni a fajlt." << endl;
	}


	return bejelentkezesiAdatok;
}

Felhasznalo* EtelrendeloRendszer::bejelentkezes() {
	cout << "BEJELENTKEZES" << endl;
	string felhasznalonev, jelszo;
	cout << "Felhasznalonev: ";
	cin >> felhasznalonev;
	cout << "Jelszo: ";
	cin >> jelszo;

	Felhasznalo* bejelentkezettFelhasznalo = nullptr;

	auto it = bejelentkezesiAdatok.find(felhasznalonev);
	if (it != bejelentkezesiAdatok.end()) {
		if (it->second == jelszo) // SIKERES BEJELENTKEZÉS !!
		{

			ifstream fileIn("felhasznaloiadatok.txt");

			if (fileIn.is_open()) {
				string felhasznalonev_temp;
				fileIn >> felhasznalonev_temp;

				while (felhasznalonev_temp != "*")
				{
					
					if (felhasznalonev_temp != felhasznalonev) {
						fileIn.ignore(numeric_limits<streamsize>::max(), '\n');
						fileIn >> felhasznalonev_temp;
						continue;
					}
					else {
						int szerepkorID;
						string emailcim;
						int felhasznaloID;
						fileIn >> szerepkorID >> felhasznaloID >> emailcim;
						int etteremID;
						switch (szerepkorID) {
						case 0: // ETTERMI DOLGOZO
							bool jogosultsag;
							fileIn >> jogosultsag >> etteremID;
							bejelentkezettFelhasznalo = new EttermiDolgozo(felhasznaloID, felhasznalonev, jelszo, emailcim, szerepkorID, etteremID, jogosultsag);
							break;
						case 1: // VASARLO
							bejelentkezettFelhasznalo = new Vasarlo(felhasznaloID, felhasznalonev, jelszo, emailcim, szerepkorID);
							break;
						case 2: // ADMIN
							bejelentkezettFelhasznalo = new Adminisztrator(felhasznaloID, felhasznalonev, jelszo, emailcim, szerepkorID);
							break;
						case 3: // FUTAR
							fileIn >> etteremID;
							bejelentkezettFelhasznalo = new Futar(felhasznaloID, felhasznalonev, jelszo, emailcim, szerepkorID, etteremID);
							break;
						}

					}

					fileIn >> felhasznalonev_temp;
				}
				// Ha valamiért mégse találja meg a felhasználónevet a fájlban
				if (bejelentkezettFelhasznalo == nullptr)
					cout << "HIBA: Nem talalhato a fiok." << endl;
			}
			else {
				// Nem sikerül megnyitni a fájlt
				cout << "HIBA: 'felhasznaloiadatok.txt' megnyitasa sikertelen." << endl;
			}


		}
		else {
			// Jelszó helytelen
			cout << "HIBA: Helytelen jelszo." << endl << endl;
		}
	}
	else {
		// Nincs olyan felhasználónév
		cout << "HIBA: Nincs ilyen regisztralt felhasznalonev." << endl << endl;
	}
	return bejelentkezettFelhasznalo;
}

// Ajánlatok betöltése

AjanlatLista EtelrendeloRendszer::ajanlatokBetolteseFajlbol() const {
	AjanlatLista lista;

	ifstream in("ajanlatok.txt");


	if (in.is_open()) {
		int kategoria;
		in >> kategoria;

		while (kategoria != -99) {
			string nev, leiras = "", leirasresz;
			int ar, ajanlatID, etteremID;
			bool elerhetoseg;

			in >> nev;
			in >> leirasresz >> leirasresz; //# majd leirás elsõ szava
			leiras = leirasresz;
			while (leirasresz != "#") {
				in >> leirasresz;
				if (leirasresz != "#")
					leiras += " " + leirasresz;
			}
			
			in >> ar >> ajanlatID >> elerhetoseg >> etteremID;
			if (kategoria == 0) { // TERMÉK

				string tipus;
				in >> tipus;
				Termek termek(nev, leiras, tipus, ajanlatID); // ha termékajánlat, a termék id-je maga az ajánlatID-je
				lista.ajanlatHozzadasa(etteremID, new TermekAjanlat(ar, ajanlatID, elerhetoseg, etteremID, termek));
			}
			else if (kategoria == 1) { // MENÜ
				list<Termek*> termekek;

				int termekID; //a menüben lévõ terméket tartalmazó ajánlat ID-je
				in >> termekID;
				while (termekID != -1) {
					// megkeresi az ajánlatlistában azt az ajánlatot, aminek ez az id-je az adott étteremben
					Ajanlat* ajanlat = lista.getAjanlat(etteremID, termekID);

					// ezt átalakítja TermékAjánlatra
					TermekAjanlat* termekajanlat = nullptr;
					termekajanlat = dynamic_cast<TermekAjanlat*>(ajanlat);

					if (termekajanlat) {
;						// mutatót készít a TermékAjánlatban eltárolt Termékre
						Termek* termek = &(termekajanlat->termek);

						// berakja a listába ezt a mutatót
						termekek.push_back(termek);
					}

					in >> termekID;
				}

				Menu menu(nev, leiras, termekek);
				lista.ajanlatHozzadasa(etteremID, new MenuAjanlat(ar, ajanlatID, elerhetoseg, etteremID, menu));
			}

			in >> kategoria;
		}
	}
	else {
		cout << "HIBA: 'ajanlatok.txt' megnyitasa sikertelen." << endl;
	}

	return lista;
}

// Rendelések betöltése
 
Rendelesek EtelrendeloRendszer::rendelesekBetolteseFajlbol(const AjanlatLista& lista) const {
	Rendelesek r;

	ifstream in("rendelesek.txt");

	if (in.is_open())
	{
		while (!in.eof())
		{
			int rendID, ettID, felhID, ajanlatID, futarID;
			in >> rendID >> ettID >> felhID >> futarID >> ajanlatID;

			list<Ajanlat*> ajanlatok;

			while (ajanlatID != -1) {
				Ajanlat* ajanlat = lista.getAjanlat(ettID, ajanlatID);
				ajanlatok.push_back(ajanlat);
				in >> ajanlatID;
			}
			string allapot;
			in >> allapot;
			int y, m, d, h, min;
			in >> y >> m >> d >> h >> min;

			r.rendelesHozzaadasa(new Rendeles(rendID, ettID, felhID, futarID, ajanlatok, allapot, Datum(y, m, d, h, min)));
		}
	}
	else {
		cout << "HIBA: 'rendelesek.txt' megnyitasa sikertelen." << endl;
	}

	return r;
}

 // Rendelések mentése

void EtelrendeloRendszer::rendelesekMenteseFajlba(const Rendelesek& rendelesek) const {
	fstream file("rendelesek.txt");

	if (file.is_open()) {
		unsigned i = 0;
		for (auto r : rendelesek.getRendelesek()) {
			file << r->getAdatokStringkent();
			if (++i < rendelesek.getRendelesek().size())
				file << endl;
		}
	}
	else {
		cout << "HIBA: 'rendelesek.txt' megnyitasa sikertelen." << endl;
	}
}

// Éttermek betöltése fájlból

void EtelrendeloRendszer::ettermekBetolteseFajlbol() {
	ifstream in("ettermek.txt");

	if (in.is_open()) {
		while (!in.eof()) {
			int ettID;
			string nev;
			in >> ettID >> nev;
			ettermek.push_back(new Etterem(ettID, nev));
		}
	}
	else {
		cout << "HIBA: 'ettermek.txt' megnyitasa sikertelen." << endl;
	}
}

// Éttermek kiírása

int EtelrendeloRendszer::ettermekKiirasa() {
	cout << "Ettermek: " << endl;

	for (auto e : ettermek) {
		e->kiir(); //ha írunk az étteremnek kiír függvényt
		//cout << e->getEtteremID() << ": " << e->getNev() << endl; //különben ezt a kettõt kell megírni
	}
 
 return ettermek.size();
}

Hibajegyzesek EtelrendeloRendszer::hibajegyzesekBetolteseFajlbol() const {
	fstream file("hibajegyzesek.txt");
	Hibajegyzesek hibak;

	if (file.is_open()) {
		int felhID;
		file >> felhID;
		while (felhID != -1) {
			string leiras;
			int y, m, d, h, min;

			file >> leiras >> y >> m >> d >> h >> min;

			hibak.hibaBejegyzese(new Hibajegyzes(leiras, felhID, Datum(y, m, d, h, min)));
			file >> felhID;
		}

	}
	else {
		cout << "HIBA: 'hibajegyzesek.txt' megnyitasa sikertelen!" << endl;
	}
	return hibak;

}

//const string& EtelrendeloRendszer::getEtteremNeve(int ettID) {
//	return ettermek[ettID]->getNev();
//}