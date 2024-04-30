#include "Futar.h"

Futar::Futar(int felhid, string felhnev, string jelszo, string email, int szID, int ettID) :
	Felhasznalo(felhid, felhnev, jelszo, email, szID),
	etteremID(ettID)
{}

void Futar::start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek)
{
	bool befejezte = false;
	int kod = -1;
	cout << endl << "Futar menu:\n" << endl;
	while (!befejezte)
	{
		cout << "Adja meg a lefuttatni kivant parancs kodjat!\n" << endl;
		cout << "1: Rendelesek megtekintese" << endl;
		cout << "2: Rendeles allapotanak frissitese" << endl;
		cout << "99: Kijelentkezes" << endl;
		cin >> kod;
		switch (kod)
		{
		case 1:
			rendelesekMegtekintese(rendelesek);
			break;
		case 2:
			rendelesAllapotanakFrissitese(rendelesek);
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

void Futar::rendelesekMegtekintese(const Rendelesek& rendelesek) const
{
	rendelesek.rendelesekKiirasaFutar(felhasznaloID);
}

void Futar::rendelesAllapotanakFrissitese(const Rendelesek& rendelesek)
{
	rendelesekMegtekintese(rendelesek);

	cout << endl << "Frissitendo rendeles: " << endl;
	int id;
	cin >> id;
	auto it = find_if(rendelesek.getRendelesek().begin(), rendelesek.getRendelesek().end(), [=](const Rendeles* r) {
		return (r->getRendelesID() == id && r->getFutarID() == felhasznaloID);
		});
	if (it != rendelesek.getRendelesek().end()) {

		string allapotok[] = { "Megtekintve", "Keszul", "Elkeszult", "Szallitasra tovabbitva", "Kiszallitva" };

		cout << "Beallithato allapotok: " << endl;
		cout << "0: " << allapotok[0] << endl;
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
		cout << "HIBA: nincs ilyen ID-ju rendeles!" << endl;
	}
}