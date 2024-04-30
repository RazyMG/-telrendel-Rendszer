#include "Adminisztrator.h"

Adminisztrator::Adminisztrator(int felhid, string felhnev, string jelszo, string email, int szID) :
	EttermiDolgozo(felhid, felhnev, jelszo, email, szID, -1, 1)
{}


void Adminisztrator::start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek) {
	kerelmekBetolteseFajlbol(lista);
	bool befejezte = false;
	int kod = -1;
	cout << endl << "Adminisztrator menu:\n" << endl;
	while (!befejezte)
	{
		cout << endl << "Adja meg a lefuttatni kivant parancs kodjat!" << endl;
		cout << "1: Uj ajanlat hozzaadasa" << endl;
		cout << "2: Meglevo ajanlat frissitese" << endl;
		cout << "3: Meglevo ajanlat torlese" << endl;
		cout << "4: Rendelesek megtekintese" << endl;
		cout << "5: Valtoztatasi kerelmek megtekintese" << endl;
		cout << "6: Valtoztatasi kerelem felulbiralasa" << endl;
		cout << "7: Ettermi dolgozo jogosultsaganak beallitasa" << endl;
		cout << "8: Etterem jogosultsaganak beallitasa" << endl;
		cout << "9: Hibajegyzesek megtekintese" << endl;
		cout << "10: Ettermek megtekintese" << endl;
		cout << "11: Osszes felvitt ajanlat megtekintese" << endl;
		cout << "12: Etterem ajanlatainak megtekintese" << endl;
		cout << "99: Kijelentkezes" << endl;

		cin >> kod;
		int n;
		switch (kod)
		{
		case 1:
			if (ajanlatHozzaadasa(lista, hibajegyzesek))
				cout << endl << "Ajanlat sikeresen hozzaadva!" << endl;
			else
				cout << endl << "Ajanlat hozzaadasa sikertelen." << endl;
			break;
		case 2:
			if (ajanlatFrissitese(lista, hibajegyzesek))
				cout << endl << "Ajanlat sikeresen frissitve!" << endl;
			else
				cout << endl << "Ajanlat frissitese sikertelen." << endl;
			break;
		case 3:
			if (ajanlatTorlese(lista))
				cout << endl << "Ajanlat sikeresen torolve!" << endl;
			else
				cout << endl << "Ajanlat torlese sikertelen." << endl;
			break;
		case 4:
			rendelesekMegtekintese(rendelesek);
			break;
		case 5:
			valtoztatasiKerelmekMegtekintese();
			break;
		case 6:
			valtoztatasiKerelemFelulbiralasa(lista);
			break;
		case 7:
			dolgozoJogosultsagBeallitasa();
			break;
		case 8:
			etteremJogosultsagBeallitasa();
			break;
		case 9:
			hibajegyzesekMegtekintese(hibajegyzesek);
			break;
		case 10:
			cout << endl;
			EtelrendeloRendszer::ettermekKiirasa();
			cout << endl;
			break;
		case 11:
			lista.ajanlatokKiirasa();
			break;
		case 12:
			n = EtelrendeloRendszer::ettermekKiirasa();
			cout << "Etterem: ";
			int id;
			cin >> id;
			if (id < 0 || id >= n) {
				cout << "HIBA: Nincs ilyen ID-ju etterem!" << endl;
				break;
			}
			lista.ajanlatokKiirasa(id, true);
			break;
		case 99:
			befejezte = true;
			break;
		default:
			cout << "Hib�s k�d" << endl;
			break;
		}
	}

	kerelmekMenteseFajlba();
}

// kerelmekBetolteseFajlbol()

void Adminisztrator::kerelmekBetolteseFajlbol(const AjanlatLista& lista) { //van egy AjanlatLista param�ter
	ifstream in("valtoztatasikerelmek.txt");

	if (in.is_open())
	{
		int ettID;
		in >> ettID;
		while (ettID != -99) {

			
			Ajanlat* ajanlat = nullptr;

			int ajanlatID;
			in >> ajanlatID;
			string tipus;
			in >> tipus;

			// ha friss�t�s vagy hozz�ad�s, be kell olvasni az �rintett aj�nlat adatait is
			// kiv�ve az �tterem �s aj�nlatID-t, mert azt m�r ismerj�k
			if (tipus == "Frissites" || tipus == "Hozzaadas")
			{
				int ajanlattipusa;
				in >> ajanlattipusa;

				string nev, leiras = "", leirasresz;
				int ar;
				bool elerhetoseg;

				in >> nev;
				in >> leirasresz >> leirasresz; //# majd leir�s els� szava
				leiras = leirasresz;
				while (leirasresz != "#") {
					in >> leirasresz;
					if (leirasresz != "#")
						leiras += " " + leirasresz;
				}

				in >> ar >> elerhetoseg;

				if (ajanlattipusa == 0) { // TERM�K

					string kategoria;
					in >> kategoria;
					Termek termek(nev, leiras, kategoria, ajanlatID);
					ajanlat = new TermekAjanlat(ar, ajanlatID, elerhetoseg, ettID, termek);
				}
				else if (ajanlattipusa == 1) { // MEN�
					list<Termek*> termekek;

					int termekID; //a men�ben l�v� term�ket tartalmaz� aj�nlat ID-je
					in >> termekID;
					while (termekID != -1) {
						// megkeresi az aj�nlatlist�ban azt az aj�nlatot, aminek ez az id-je az adott �tteremben
						Ajanlat* ajanlat = lista.getAjanlat(ettID, termekID);

						// ezt �talak�tja Term�kAj�nlatra
						TermekAjanlat* termekajanlat = nullptr;
						termekajanlat = dynamic_cast<TermekAjanlat*>(ajanlat);

						if (termekajanlat) {		
							// mutat�t k�sz�t a Term�kAj�nlatban elt�rolt Term�kre
							Termek* termek = &(termekajanlat->termek);

							// berakja a list�ba ezt a mutat�t
							termekek.push_back(termek);
						}

						in >> termekID;
					}

					Menu menu(nev, leiras, termekek);
					ajanlat = new MenuAjanlat(ar, ajanlatID, elerhetoseg, ettID, menu);

				}
			} // mostanra van l�trehozva a megfelel� Ajanlat* objektum

			int y, m, d, h, min;
			in >> y >> m >> d >> h >> min;

			kerelmek.push_back(new ValtoztatasiKerelem(ettID, ajanlatID, ajanlat, tipus, Datum(y, m, d, h, min)));

			in >> ettID;
		}
	}
	else {
		cout << "HIBA: Fajl megnyitasa sikertelen.";
	}


}

void Adminisztrator::valtoztatasiKerelmekMegtekintese() const {
	unsigned i = 0;
	cout << "Beerkezo valtoztatasi kerelmek: " << endl;
	for (auto k : kerelmek) {
		cout << "KERELEM " << i++ << ": " << endl;
		k->kiiras();
	}
}

// valtoztatasiKerelemFelulbiralasa()

void Adminisztrator::valtoztatasiKerelemFelulbiralasa(AjanlatLista& lista) {
	valtoztatasiKerelmekMegtekintese();

	cout << "Adja meg a kerelem sorszamat: ";
	int id;
	cin >> id;

	if (id >= 0 && id < kerelmek.size()) {
		cout << endl << "0 - Elutasit" << endl << "1 - Elfogad" << endl << endl;
		cout << "Valasztas: ";
		int valasztas;
		cin >> valasztas;

		if (valasztas) { // ELFOGADVA
			cout << "Elfogadva!" << endl;
			kerelmek[id]->vegrehajtas(lista);
		}

		kerelmek.erase(kerelmek.begin() + id);
		kerelmekMenteseFajlba();
	}
	else {
		cout << "HIBA: nincs ilyen sorszamu kerelem!" << endl;
	}
}

// K�relmek ment�se f�jlba

void Adminisztrator::kerelmekMenteseFajlba() const {
	fstream file("valtoztatasikerelmek.txt", ios::out | ios::trunc);

	if (file.is_open()) {
		for (auto vk : kerelmek) {
			file << vk->getAdatokStringkent() << endl;
		}
		file << -99;
	}
	else {
		cout << "HIBA: Fajl megnyitasa sikertelen" << endl;
	}
}

//// Aj�nlat t�rl�se azonnal
//
//bool Adminisztrator::ajanlatTorleseAzonnal(const AjanlatLista& lista) const {
//	lista.ajanlatokKiirasa();
//	cout << "Etterem id-je: ";
//	int ettID;
//	cin >> ettID;
//	cout << "Ajanlat id-je: ";
//	int ajanlatID;
//	cin >> ajanlatID;
//
//	if (lista.ajanlatTorlese(ettID, ajanlatID))
//		return true;
// else return false;
//
//}

// �ttermi dolgoz� jogosults�g�nak be�ll�t�sa

void Adminisztrator::dolgozoJogosultsagBeallitasa() const {

	// �sszes dolgoz� beolvas�sa �s ki�r�sa
	fstream file("felhasznaloiadatok.txt");

	if (file.is_open()) {

		vector< pair<string, pair<string, string> > > dolgozostringek;
		unsigned i = 0;

		// Dolgoz�k beolvas�sa 
		string felhnev;
		file >> felhnev;
		while (felhnev != "*")
		{
			
			int szerepkor;
			file >> szerepkor;

			// ha nem dolgoz�, ugrik a k�vetkez� sorra
			if (szerepkor != 0) {
				file.ignore(numeric_limits<streamsize>::max(), '\n');
				file >> felhnev;
				continue;
			}

			string email;
			bool jogosultsag;
			int felhID, etteremID;
			file >> felhID >> email >> jogosultsag >> etteremID;

			// �sszerakja a dolgoz� adatait egy stringg�, hogy majd k�nnyebb legyen k�s�bb kikeresni
			stringstream dolgozostringEredeti, dolgozostringTiltva, dolgozostringEngedelyezve;
			dolgozostringEredeti << felhnev << " " << szerepkor << " " << felhID << " " << email << " " << jogosultsag << " " << etteremID;
			dolgozostringTiltva << felhnev << " " << szerepkor << " " << felhID << " " << email << " " << "0" << " " << etteremID;
			dolgozostringEngedelyezve << felhnev << " " << szerepkor << " " << felhID << " " << email << " " << "1" << " " << etteremID;
			dolgozostringek.push_back(pair<string, pair<string, string> >(dolgozostringEredeti.str(), pair<string, string>(dolgozostringTiltva.str(), dolgozostringEngedelyezve.str())));


			// dolgoz� ki�r�sa (Felh. n�v, email, �tterem, jogosultsag)
			cout << i++ << ": " << felhnev << " " << email << ", etterem: " << etteremID << " " << (jogosultsag ? "ENGEDELYEZVE" : "TILTVA") << endl;
		
			file >> felhnev;
		}
		file.close();

		// vector index bek�r�se
		cout << "Sorszam: ";
		int idx;
		cin >> idx;
		if (idx < dolgozostringek.size() && idx >= 0) {
			// enged�lyez vagy letilt?
			cout << "0: Letiltas" << endl << "1: Engedelyezes" << endl;
			int engedelyezve;
			cin >> engedelyezve;

			if (engedelyezve == 0 || engedelyezve == 1) {

			
				// F�jl megnyit�sa �jra, megkeress�k az adott dolgoz�t, �s fel�l�rjuk az �j stringgel
				fstream file("felhasznaloiadatok.txt");
				string line;
				string replace = dolgozostringek[idx].first;
				string replacewith = (engedelyezve ? dolgozostringek[idx].second.second : dolgozostringek[idx].second.first);
				
				if (replace == replacewith) {
					cout << "HIBA: Ennek a felhasznalonak mar most is ez a jogosultsaga!" << endl;
					return;
				}

				vector<string> lines;
				while (getline(file, line) && line != "*") {
					if (line == replace) {
						line.replace(line.cbegin(), line.cend(), replacewith);
					}
					lines.push_back(line);
				}

				file.close();

				// F�jl sorait �jra be�rjuk a f�jlba
				file.open("felhasznaloiadatok.txt", ios::out | ios::trunc);
				for (const auto& l : lines) {
					file << l << endl;
				}
				file << "*";
			}
			else {
				cout << "HIBA: Ervenytelen bemenet!" << endl;
			}
		}
		else cout << "HIBA: Ilyen sorszam nincs!";

	}
	else {
		cout << "HIBA: Felhasznalok betoltese sikertelen." << endl;
	}
}

void Adminisztrator::etteremJogosultsagBeallitasa() const {

	int max = EtelrendeloRendszer::ettermekKiirasa();
	cout << "Valasztott etterem: ";
	int ettID;
	cin >> ettID;

	if (ettID >= 0 && ettID < max) {

		// enged�lyez vagy letilt?
		cout << "0: Letiltas" << endl << "1: Engedelyezes" << endl;
		int engedelyezve;
		cin >> engedelyezve;

		if (engedelyezve == 0 || engedelyezve == 1) {

			vector< pair<string, string> > dolgozostringek;

			fstream file("felhasznaloiadatok.txt");

			if (file.is_open()) {

				string felhnev;
				file >> felhnev;

				while (felhnev != "*")
				{

					
					int felhID, szerepkor;
					file >> szerepkor >> felhID;

					// ha nem dolgoz�, ugrik
					if (szerepkor != 0) {
						file.ignore(numeric_limits<streamsize>::max(), '\n');
						file >> felhnev;
						continue;
					}

					string email;
					int jogosultsag, ettID2;

					// ha nem a kiv�lasztott �tterem dolgoz�ja, ugrik
					file >> email >> jogosultsag >> ettID2;
					if (ettID2!= ettID) {
						file.ignore(numeric_limits<streamsize>::max(), '\n');
						file >> felhnev;
						continue;
					}

					stringstream dolgozostringEredeti, dolgozostringUj;
					dolgozostringEredeti << felhnev << " " << szerepkor << " " << felhID << " " << email << " " << jogosultsag << " " << ettID2;
					dolgozostringUj << felhnev << " " << szerepkor << " " << felhID << " " << email << " " << engedelyezve << " " << ettID2;
					dolgozostringek.push_back(pair<string, string>(dolgozostringEredeti.str(), dolgozostringUj.str()));

					file >> felhnev;
				}
				file.close();

				fstream file("felhasznaloiadatok.txt");
				string line;
				
				// v�gmigmegy�nk az �sszes soron
				// mivel a vektorban ugyanolyan sorrendben vannak a dolgoz�k, mint a f�jlban, indexet n�vel�nk
				// a jelenlegi indexen l�v� string lecser�lj�k a megv�ltoztatottra
				vector<string> lines;
				int idx = 0;
				while (getline(file, line) && line != "*") {
					if (idx < dolgozostringek.size()) {
						string replace = dolgozostringek[idx].first;
						string replacewith = dolgozostringek[idx].second;
						if (line == replace) {
							cout << idx << endl;
							line.replace(line.cbegin(), line.cend(), replacewith);
							idx++;
						}
					}
					lines.push_back(line);
				}

				file.close();

				// F�jl sorait �jra be�rjuk a f�jlba
				file.open("felhasznaloiadatok.txt", ios::out | ios::trunc);
				for (const auto& l : lines) {
					file << l << endl;
				}
				file << "*";
			}
			else {
				cout << "HIBA: fajl megnyitasa sikertlen" << endl;
			}


		}
		else {
			cout << "HIBA: helytelen bemenet!" << endl;
		}


	}
	else {
		cout << "HIBA: helytelen bemenet!" << endl;
	}
}

bool Adminisztrator::ajanlatHozzaadasa(AjanlatLista& lista, Hibajegyzesek& hibajegyzesek) {
	cout << "\nEtterem: ";
	cin >> etteremID;
	// Dolgoz�t�l �r�k�lt f�ggv�ny
	bool siker = EttermiDolgozo::ajanlatHozzaadasa(lista, hibajegyzesek);

	etteremID = -1;

	return siker;
}

bool Adminisztrator::ajanlatFrissitese(AjanlatLista& lista, Hibajegyzesek& hibajegyzesek) {
	cout << "\nEtterem: ";
	cin >> etteremID;
	// Dolgoz� �r�k�lt f�ggv�ny
	bool siker = EttermiDolgozo::ajanlatFrissitese(lista, hibajegyzesek);

	etteremID = -1;

	return siker;
}

bool Adminisztrator::ajanlatTorlese(AjanlatLista& lista) {
	cout << "\nEtterem: ";
	cin >> etteremID;

	// Dolgoz� �r�k�lt f�ggv�ny
	bool siker = EttermiDolgozo::ajanlatTorlese(lista);

	etteremID = -1;

	return siker;
}

void Adminisztrator::rendelesAllapotanakFrissitese(const Rendelesek& rendelesek) {
	cout << "\nEtterem: ";
	cin >> etteremID;

	// Dolgoz� �r�k�lt f�ggv�ny
	EttermiDolgozo::rendelesAllapotanakFrissitese(rendelesek);

	etteremID = -1;
}

void Adminisztrator::hibajegyzesekMegtekintese(const Hibajegyzesek& hibak) const {
	hibak.kiir();
}