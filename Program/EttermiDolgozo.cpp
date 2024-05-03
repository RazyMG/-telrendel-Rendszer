#include "EttermiDolgozo.h"

EttermiDolgozo::EttermiDolgozo(int felhid, string felhnev, string jelszo, string email, int szID, int ettID, bool jog) :
	Felhasznalo(felhid, felhnev, jelszo, email, szID),
	etteremID(ettID),
	jogosultsag(jog)
{}

void EttermiDolgozo::start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek) {
	int sum = count_if(rendelesek.getRendelesek().begin(), rendelesek.getRendelesek().end(), [=](const Rendeles* r) {
		return (r->getAllapot() == "Leadva" && r->getEtteremID() == etteremID);
		});
	if (sum > 0) {
		cout << sum << " uj leadott rendeles van!" << endl << "Ezek az alabbiak: " << endl;
		rendelesek.rendelesekKiirasa(etteremID, "Leadva");
	}
	else {
		cout << "Nincs uj leadott rendeles." << endl;
	}
	bool befejezte = false;
	int kod = -1;
	cout << endl << "\nEttermi dolgozo menu:\n" << endl;
	while (!befejezte)
	{
		cout << "Adja meg a lefuttatni kivant parancs kodjat!\n" << endl;
		cout << "1: Uj ajanlat hozzaadasa" << endl;
		cout << "2: Meglevo ajanlat frissitese" << endl;
		cout << "3: Meglevo ajanlat torlese" << endl;
		cout << "4: Sajat ajanlatok megtekintese" << endl;
		cout << "5: Rendelesek megtekintese" << endl;
		cout << "6: Rendeles allapotanak frissitese" << endl;
		cout << "7: Futar megbizasa rendelessel" << endl;
		cout << "99: Kijelentkezes" << endl;

		cin >> kod;
		switch (kod)
		{
		case 1:
			if (ajanlatHozzaadasa(lista, hibajegyzesek))
				cout << endl << "Hozzaadasi kerelem elkuldve!" << endl;
			else
				cout << endl << "Hozzaadas kezdemenyezese sikertelen." << endl;
			break;
		case 2:
			if (ajanlatFrissitese(lista, hibajegyzesek))
				cout << endl << "Frissitesi kerelem elkuldve!" << endl;
			else
				cout << endl << "Frissites kezdemenyezese sikertelen." << endl;
			break;
		case 3:
			if (ajanlatTorlese(lista))
				cout << endl << "Torlesi kerelem elkuldve!" << endl;
			else
				cout << endl << "Torles kezdemenyezese sikertelen." << endl;
			break;
		case 4:
			sajatAjanlatokMegtekintese(lista);
			break;
		case 5:
			rendelesekMegtekintese(rendelesek);
			break;
		case 6:
			rendelesAllapotanakFrissitese(rendelesek);
			break;
		case 7:
			futarMegbizasaRendelessel(rendelesek);
			break;
		case 99:
			befejezte = true;
			break;
		default:
			cout << "Hibas kod" << endl;
			break;
		}
	}

}


int EttermiDolgozo::getEtteremID() const {
	return etteremID;
}

void EttermiDolgozo::sajatAjanlatokMegtekintese(const AjanlatLista& lista) const {
	cout << "FELVITT AJANLATOK: " << endl;
	lista.ajanlatokKiirasa(etteremID, true);
}

TermekAjanlat* EttermiDolgozo::ajanlatInformacioMegadasa(const AjanlatLista& lista, const string& eddiginev) const {
	cout << endl << "AJANLAT INFORMACIO MEGADASA" << endl;

	int valasz = 0;
	do {
		string nev;
		cout << "Ajanlat neve: ";
		cin >> nev;
		while (nev == "") {
			cout << "A nev nem lehet semmi!" << endl;
			cin >> nev;
		}

		while (eddiginev != nev && lista.vanOlyanNevuAjanlat(etteremID, nev)) {
			cout << "Ilyen nevu ajanlat mar letezik!" << endl;
			cout << "Ajanlat neve: ";
			cin >> nev;
		}

		cout << "Elerhetoseg (0/1): ";
		int elerhetoseg;
		cin >> elerhetoseg;
		if (elerhetoseg == 0 || elerhetoseg == 1) {
			cout << "Ajanlat leirasa: ";
			char leiras[100] = { 0 };
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.getline(leiras, 100);

			cout << "Ajanlat tipusa: ";
			string tipus;
			cin >> tipus;

			cout << "Ajanlat ara: ";
			int ar;
			cin >> ar;

			cout << "MEGADOTT INFORMACIO " << endl;
			cout << "Nev: " << nev << endl;
			cout << "Leiras: " << leiras << endl;
			cout << "Tipus: " << tipus << endl;
			cout << "Elerhetoseg: " << elerhetoseg << endl;
			cout << "Ar: " << ar << endl;

			cout << endl << "Helyes ez?" << endl << "0: Nem" << endl << "1: Igen" << endl << "2: Megse" << endl;
			
			cin >> valasz;
			if (valasz < 0 || valasz > 2) {
				cout << "HIBA: helytelen bemenet!" << endl;
				return nullptr;
			}
			else if (valasz == 2) {
				return nullptr;
			}
			else if (valasz == 1) {
				int ajanlatID = lista.szamolElsoID(etteremID);
				return new TermekAjanlat(ar, ajanlatID, elerhetoseg, etteremID, Termek(nev, leiras, tipus, ajanlatID));
			}
		}
		else {
			cout << "HIBA: helytelen bemenet!" << endl;
			return nullptr;
		}
	} while (valasz == 0);

}

MenuAjanlat* EttermiDolgozo::ajanlatInformacioMegadasa(const AjanlatLista& lista, const list<int>& ajanlatIDk, const string& eddiginev) const {
	cout << endl << "AJANLAT INFORMACIO MEGADASA" << endl;

	int valasz = 0;
	do {
		string nev;
		cout << "Ajanlat neve: ";
		cin >> nev;

		while (nev == "") {
			cout << "A nev nem lehet semmi!" << endl;
			cin >> nev;
		}

		while (eddiginev != nev && lista.vanOlyanNevuAjanlat(etteremID, nev)) {
			cout << "Ilyen nevu ajanlat mar letezik!" << endl;
			cout << "Ajanlat neve: ";
			cin >> nev;
		}

		cout << "Elerhetoseg (0/1): ";
		int elerhetoseg;
		cin >> elerhetoseg;
		if (elerhetoseg == 0 || elerhetoseg == 1) {
			cout << "Ajanlat leirasa: ";
			char leiras[100] = { 0 };
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.getline(leiras, 100);

			cout << "Ajanlat ara: ";
			int ar;
			cin >> ar;

			cout << endl << "MEGADOTT INFORMACIO " << endl;
			cout << "Nev: " << nev << endl;
			cout << "Leiras: " << leiras << endl;
			cout << "Elerhetoseg: " << elerhetoseg << endl;
			cout << "Ar: " << ar << endl;

			cout << "Helyes ez?" << endl << "0: Nem" << endl << "1: Igen" << endl << "2: Megse" << endl;

			cin >> valasz;
			if (valasz < 0 || valasz > 2) {
				cout << "HIBA: helytelen bemenet!" << endl;
				return nullptr;
			}
			else if (valasz == 2)
				return nullptr;
			else if (valasz == 1) {
				int ajanlatID = lista.szamolElsoID(etteremID);

				// termékek keresése adott id-vel
				list<Termek*> termekek;
				for (int id : ajanlatIDk) {
					// megkeresi az ajánlatlistában azt az ajánlatot, aminek ez az id-je az adott étteremben
					Ajanlat* ajanlat = lista.getAjanlat(etteremID, id);

					// ezt átalakítja TermékAjánlatra
					TermekAjanlat* termekajanlat = nullptr;
					termekajanlat = dynamic_cast<TermekAjanlat*>(ajanlat);

					if (termekajanlat) {
						// mutatót készít a TermékAjánlatban eltárolt Termékre
						Termek* termek = &(termekajanlat->termek);

						// berakja a listába ezt a mutatót
						termekek.push_back(termek);
					}
					else {
						cout << "HIBA: Menu nem tartalmazhat mas menut!" << endl;
						return nullptr;
					}

				}

				return new MenuAjanlat(ar, ajanlatID, elerhetoseg, etteremID, Menu(nev, leiras, termekek));
			}
		}
		else {
			cout << "HIBA: helytelen bemenet!" << endl;
		}
	} while (valasz == 0);

}

bool EttermiDolgozo::ajanlatHozzaadasa(AjanlatLista& lista, Hibajegyzesek& hibajegyzesek) const {
	if (jogosultsag) {
		Ajanlat* ajanlat;
		int tipus;
		cout << "Ajanlat tipusa: " << endl << "0: Termek" << endl << "1: Menu" << endl << "Valasztott tipus: ";
		cin >> tipus;
		if (tipus == 0) { // termék
			ajanlat = ajanlatInformacioMegadasa(lista);
		}
		else if (tipus == 1) { // menü
			cout << "Adja meg azon termekajanlatok ID-it, amelyeket a menu tartalmaz!" << endl << "Befejezeshez: -1" <<endl;
			int id;
			list<int> idk;
			do {
				do {
					cin >> id;
					if (id != -1) {
						// id érvényességének tesztje:
						Ajanlat* a = lista.getAjanlat(etteremID, id);

						if (a)
							idk.push_back(id);
						else
							cout << "HIBA: Nincs olyan ID-ju ajanlat!" <<endl;
					}
				} while (id != -1);
				if (idk.empty()) {
					cout << "HIBA: Legalabb egy termeket tartalmaznia kell!" << endl;
				}
			} while (idk.empty());

			ajanlat = ajanlatInformacioMegadasa(lista, idk);
		}	
		else {
			cout << "HIBA: helytelen bemenet!" << endl;
			return false;
		}

		// ha az ajánlatInformációMegadása nullptr-rel tért vissza
		if (!ajanlat) {
			return false;
		}

		// a kérelem automatikusan menti is magát;
		ValtoztatasiKerelem kerelem(etteremID, ajanlat->getAjanlatID(), ajanlat, "Hozzaadas", Datum());

		// ha admin hívja meg ezt a függvényt, akkor a kerelmet vegrehajtjuk
		if (getSzerepkorID() == adminisztrator) {
			kerelem.vegrehajtas(lista);
		}
		else {
			kerelem.mentesFajlba();
		}
			


		return true;
	}
	else {
		cout << "HIBA: Erre nincs jogosultsaga!" << endl;
		hibajegyzesek.hibaBejegyzese(new Hibajegyzes("Jogosultsag_nelkuli_ajanlathozzaadas_kiserlete", felhasznaloID));
		return false;
	}
}

bool EttermiDolgozo::ajanlatFrissitese(AjanlatLista& lista, Hibajegyzesek& hibajegyzesek) const {
	if (jogosultsag) {
		sajatAjanlatokMegtekintese(lista);
		cout << "Frissitendo ajanlat id-je: ";
		int ajanlatID;
		cin >> ajanlatID;

		Ajanlat* ajanlat = lista.getAjanlat(etteremID, ajanlatID);

		if (!ajanlat) {
			cout << "HIBA: Nincs ilyen ID-ju ajanlat!" << endl;
			return false;
		}

		MenuAjanlat* menuajanlat = dynamic_cast<MenuAjanlat*>(ajanlat);
		if (menuajanlat) // ez egy menüajánlat
		{
			// ilyenkor be kell olvasni az ajánlatok listáját, amit a menü tartalmazni fog
			cout << "Adja meg azon termekajanlatok ID-it, amelyeket a menu tartalmazni fog frissites utan!" << endl << "Befejezeshez: -1" << endl;
			int id;
			list<int> idk;
			do {
				do {
					cin >> id;
					if (id != -1) {
						// id érvényességének tesztje:
						Ajanlat* a = lista.getAjanlat(etteremID, id);

						if (a)
							idk.push_back(id);
						else
							cout << "Nincs olyan ID-jû ajanlat!" << endl;
					}
				} while (id != -1);
				if (idk.empty()) {
					cout << "Legalabb egy termeket tartalmaznia kell!";
				}
			} while (idk.empty());

			// többi információ beolvasása
			ajanlat = ajanlatInformacioMegadasa(lista, idk, ajanlat->getNev());
			if (!ajanlat) {
				return false;
			}
		}
		else { // ez egy termékajánlat

			// többi információ beolvasása
			ajanlat = ajanlatInformacioMegadasa(lista, ajanlat->getNev());
			if (!ajanlat) {
				return false;
			}
		}

		// a kérelem automatikusan menti is magát;
		ValtoztatasiKerelem kerelem(etteremID, ajanlatID, ajanlat, "Frissites", Datum());

		// ha admin hívja meg ezt a függvényt, akkor a kerelmet vegrehajtjuk
		if (getSzerepkorID() == adminisztrator) {
			kerelem.vegrehajtas(lista);
		}
		else {
			kerelem.mentesFajlba();
		}

		return true;

	}
	else {
		cout << "HIBA: Erre nincs jogosultsaga!" << endl;
		hibajegyzesek.hibaBejegyzese(new Hibajegyzes("Jogosultsag_nelkuli_ajanlatfrissites_kiserlete", felhasznaloID));
		return false;
	}
}

bool EttermiDolgozo::ajanlatTorlese(AjanlatLista& lista) const {
	if (jogosultsag) {
		sajatAjanlatokMegtekintese(lista);
		cout << "Torlendo ajanlat id-je: ";
		int ajanlatID;
		cin >> ajanlatID;

		// ez igazából csak azért kell, hogy megnézzük, érvényes-e a megadott ajanlatID
		Ajanlat* ajanlat = lista.getAjanlat(etteremID, ajanlatID);

		if (!ajanlat) {
			cout << "HIBA: Nincs ilyen ID-jû ajánlat!" << endl;
			return false;
		}

		// a kérelem automatikusan menti is magát;
		ValtoztatasiKerelem kerelem(etteremID, ajanlatID, "Torles", Datum());

		// ha admin hívja meg ezt a függvényt, akkor a kerelmet vegrehajtjuk
		if (getSzerepkorID() == adminisztrator) {
			kerelem.vegrehajtas(lista);
		}
		else {
			kerelem.mentesFajlba();
		}

		return true;

	}
	else {
		cout << "HIBA: Erre nincs jogosultsaga!" << endl;
		return false;
	}

}

void EttermiDolgozo::rendelesekMegtekintese(const Rendelesek& rendelesek) const {
	rendelesek.rendelesekKiirasa();
}

void EttermiDolgozo::rendelesAllapotanakFrissitese(const Rendelesek& rendelesek) {
	rendelesekMegtekintese(rendelesek);

	cout << endl << "Frissitendo rendeles: " << endl;
	int id;
	cin >> id;
	auto it = find_if(rendelesek.getRendelesek().begin(), rendelesek.getRendelesek().end(), [=](const Rendeles* r) {
		return r->getRendelesID() == id;
		}); 
	if (it != rendelesek.getRendelesek().end()) {
		
		string allapotok[] = { "Megtekintve", "Keszul", "Elkeszzult", "Szallitasra tovabbitva", "Kiszaliitva" };

		cout << "Beallithato allapotok: " << endl;
		cout << "0: " << allapotok[0] <<endl;
		cout << "1: " << allapotok[1] << endl;
		cout << "2: " << allapotok[2] << endl;
		cout << "3: " << allapotok[3] << endl;
		cout << "4: " << allapotok[4] << endl;

		cout << "Valasztas szama: ";
		int valasz;
		cin >> valasz;
		if (valasz < 0 || valasz > 4) {
			cout << "HIBA: helytelen bemenet!" << endl;
			return;
		}

		(*it)->setAllapot(allapotok[valasz]);

	}
	else {
		cout << "HIBA: nincs ilyen ID-jû rendelés!";
		}

}

void EttermiDolgozo::futarMegbizasaRendelessel(const Rendelesek& rendelesek) const {
	rendelesekMegtekintese(rendelesek);

	cout << endl << "Frissitendo rendeles: " << endl;
	int id;
	cin >> id;
	auto it = find_if(rendelesek.getRendelesek().begin(), rendelesek.getRendelesek().end(), [=](const Rendeles* r) {
		return r->getRendelesID() == id;
		});
	if (it != rendelesek.getRendelesek().end()) {

		// kilistázza az étterem összes futárát!
		fstream file("felhasznaloiadatok.txt");

		if (file.is_open()) {

			vector<int> futaridk;

			while (!file.eof()) {

				string felhnev;
				int felhID, szerepkor;
				file >> felhnev >> szerepkor;

				// ha nem futár, ugrik
				if (szerepkor != 3) {
					file.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}

				string email;
				int ettID;

				// ha nem az adott étterem futára, ugrik
				file >> felhID >> email >> ettID;
				if (etteremID != ettID) {
					file.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}

				cout << felhID << ": " << felhnev;
				futaridk.push_back(felhID);
			}

			cout << "\nKivalasztott futar ID-je: ";
			int id;
			cin >> id;
			if (any_of(futaridk.begin(), futaridk.end(), [=](int _id) {
				return _id == id; })) {

				(*it)->setFutarID(id);

			}
			else {
				cout << "HIBA: nincs ilyen ID-ju futar!" << endl;
			}

		}
		else {
			cout << "HIBA: nincs ilyen ID-jû rendelés!";
		}
	} else {
		cout << "HIBA: nincs ilyen ID-jû etterem!";
	}
}