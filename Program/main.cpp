#include <iostream>
#include "EtelrendeloRendszer.h"
#include "Hibajegyzesek.h"

using namespace std;

int main() {

	bool befejezve = false;

	while (!befejezve)
	{
		cout << "ETELRENDELO RENDSZER" << endl;
		cout << "0: Bejelentkezes" << endl;
		cout << "99: Kilepes a programbol" << endl;
		
		string valasz;
		cin >> valasz;

		EtelrendeloRendszer rendszer;
		AjanlatLista ajanlatlista;
		Rendelesek rendelesek;
		Hibajegyzesek hibajegyzesek;

		if (valasz == "0") {
			rendszer.felhasznalonevJelszoParokBetoltese();
			Felhasznalo* bejelentkezettFelhasznalo;

			do {
				bejelentkezettFelhasznalo = rendszer.bejelentkezes();
			} while (bejelentkezettFelhasznalo == nullptr);

			cout << "Sikeres bejelentkezes!" << endl;
			ajanlatlista = rendszer.ajanlatokBetolteseFajlbol();
			rendelesek = rendszer.rendelesekBetolteseFajlbol(ajanlatlista);
			hibajegyzesek = rendszer.hibajegyzesekBetolteseFajlbol();

			rendszer.ettermekBetolteseFajlbol();

			bejelentkezettFelhasznalo->start(ajanlatlista, rendelesek, hibajegyzesek);

			ajanlatlista.ajanlatokMenteseFajlba();
			rendszer.rendelesekMenteseFajlba(rendelesek);
			hibajegyzesek.hibajegyzesekMenteseFajlba();
		}
		else if (valasz == "99") {
			befejezve = true;
		}
		else {
			cout << "Hibas bemenet!" << endl;
		}
	}

	return 0;
}