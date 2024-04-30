#include "Vasarlo.h"

Vasarlo::Vasarlo(int felhid, string felhnev, string jelszo, string email, int szID) :
	Felhasznalo(felhid, felhnev, jelszo, email, szID), kosar(Rendeles(felhid))
{
	kosar.setEtteremID(-1);
}

void Vasarlo::start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek) {
	bool befejezte = false;
	int kod = -1;
	cout << endl << "\nVasarlo menu:\n" << endl;
	while (!befejezte)
	{
		cout << "Adja meg a lefuttatni kivant parancs kodjat!\n" << endl;
		cout << "1: Ajanlatok megtekintese" << endl;
		cout << "2: Ajanlat hozzaadasa a kosarhoz" << endl;
		cout << "3: Ajanlat eltavolitasa a kosarbol" << endl;
		cout << "4: Kosar uritese" << endl;
		cout << "5: Rendeles allapotanak megtekintese" << endl;
		cout << "6: Rendeles veglegesitese" << endl;
		cout << "7: Kosar tartalmanak megtekintese" << endl;
		cout << "99: Kijelentkezes" << endl;
		cin >> kod;
		switch (kod)
		{
		case 1:
			ajanlatokMegtekintese(lista);
			break;
		case 2:
			if (ajanlatHozzaadasaRendeleshez(lista, hibajegyzesek))
				cout << endl << "Ajanlat sikeresen hozzadva!" << endl;
			else
				cout << endl << "Ajanlat hozzaadasa sikertelen." << endl;
			break;
		case 3:
			if (ajanlatKiszedeseRendelesbol(lista))
				cout << endl << "Ajanlat sikeresen eltavolitva!" << endl;
			else
				cout << endl << "Ajanlat eltavolitasa sikertelen." << endl;
			break;
		case 4:
			kosarUritese();
			break;
		case 5:
			rendelesAllapotanakMegtekintese(rendelesek);
			break;
		case 6:
			if (rendelesVeglegesitese(rendelesek, hibajegyzesek))
				cout << endl << "Rendeles elkuldve!" << endl;
			else
				cout << endl << "Rendeles veglegesitese sikertelen/megszakitva." << endl;
			break;
		case 7:
			kosarMegtekintese();
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

int Vasarlo::ajanlatokMegtekintese(const AjanlatLista& lista) const {

	int max = EtelrendeloRendszer::ettermekKiirasa();

	cout << "Adja meg a valasztott etterem szamat: ";
	int id;
	cin >> id;
	if (id >= 0 && id < max) {
		lista.ajanlatokKiirasa(id, false);
		return id;
	}
	else {
		cout << "HIBA: helytelen bemenet!" << endl;
		return -1;
	}
}

bool Vasarlo::ajanlatHozzaadasaRendeleshez(const AjanlatLista& lista, Hibajegyzesek& hibajegyzesek)
{
	int etteremID = ajanlatokMegtekintese(lista);
	cout << endl << "EtteremID: " << kosar.getEtteremID() << endl;
	if (kosar.getEtteremID() != -1) {
		if (etteremID != kosar.getEtteremID())
		{
			cout << "Egyszerre csak egy etterembol tud rendelni." << endl;
			return false;
		}
	}
	cout << "Adja meg a kosarhoz hozzaadni kivant elem ID-jet!\nAmennyiben nem szeretne tobbet hozzaadni, irja be a 99-es kodot" << endl;
	if (etteremID == -1)
		return false;
	bool befejezte = false;
	int ajanlatID = -1;
	Ajanlat* ujAjanlat;
	while (!befejezte)
	{
		cin >> ajanlatID;
		if (ajanlatID == 99)
		{
			befejezte = true;
			break;
		}
		ujAjanlat = lista.getAjanlat(etteremID, ajanlatID);
		if (ujAjanlat == nullptr)
		{
			cout << "HIBA: Nincs ilyen ajanlat ID" << endl;
			continue;
		}
		else if (!ujAjanlat->getElerhetoseg())
		{
			cout << "HIBA: A valasztott ajanlat nem elerheto." << endl;

			hibajegyzesek.hibaBejegyzese(new Hibajegyzes("Nem_elerheto_ajanlat_hozzaadasanak_kiserlete", felhasznaloID));
			continue;
		}
		kosar.ajanlatHozzaadasa(ujAjanlat);
		kosar.setEtteremID(etteremID);
	}
	if (befejezte)
		return true;
}

bool Vasarlo::ajanlatKiszedeseRendelesbol(const AjanlatLista& lista)
{
	cout << "Adja meg az eltavolitani kivant ajanlat ID-jet: ";
	int torlendoAjanlatID;
	cin >> torlendoAjanlatID;
	Ajanlat* torlendoAjanlat = lista.getAjanlat(kosar.getEtteremID(), torlendoAjanlatID);
	if (kosar.ajanlatKiszedese(torlendoAjanlat)) {
		return true;
	}
	return false;
}

void Vasarlo::kosarUritese()
{
	kosar.urites();
}

void Vasarlo::kosarMegtekintese() const {
	kosar.kiiras();
}
void Vasarlo::rendelesAllapotanakMegtekintese(const Rendelesek& rendelesek) const
{
	for (auto v : rendelesek.getRendelesek())
	{
		if (v->getFelhasznaloID() == felhasznaloID)
		{
			v->kiiras();
		}
	}
}

bool Vasarlo::megerosites() const
{
	int trueOrFalse;
	cin >> trueOrFalse;
	if (trueOrFalse == 1)
		return true;
	return false;
}

bool Vasarlo::rendelesVeglegesitese(Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek) {

	// üres?
	if (kosar.getEtteremID() == -1) {
		cout << "A kosar ures!" << endl;
		return false;
	}

	// rendelés tartalma
	kosar.kiiras();

	// rendelésnek tartalmának megerõsítése
	cout << "Megerositi a rendelest?\n0: Nem\n1: Igen" <<endl;
	if (!megerosites()) {
		cout << "Veglegesites elvetve." << endl;
		return false;
	}

	// fizetés megerõsítése
	cout << "Biztosan szeretne fizetni?\n0: Nem\n1: Igen" << endl;
	if (!megerosites()) {
		cout << "Veglegesites elvetve." << endl;
		return false;
	}

	// tranzakció
	Etterem ett;
	if (!ett.tranzakcioKezelese()) {
		cout << "Fizetes sikertelen." << endl;
		hibajegyzesek.hibaBejegyzese(new Hibajegyzes("Sikertelen_fizetes_rendeles_veglegesitesekor", felhasznaloID));
		return false;
	}

	// sikeresség jelzése
	cout << "Fizetes es rendeles sikeres!" << endl;
	kosar.setDatum(Datum());
	kosar.setAllapot("Leadva");
	kosar.setRendelesID(rendelesek.getRendelesek().size());
	rendelesek.rendelesHozzaadasa(new Rendeles(kosar));

	// kosár ürítése
	kosarUritese();



}