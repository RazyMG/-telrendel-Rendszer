#include "Felhasznalo.h"

Felhasznalo::Felhasznalo(int felhid, string felhnev, string jelszo, string email, int szID):
	felhasznaloID(felhid),
	nev(felhnev),
	jelszo(jelszo),
	emailcim(email)
{
	switch (szID) {
		case 0: // ETTERMI DOLGOZO
			szerepkorID = ettermidolgozo;
			break;
		case 1: // VASARLO
			szerepkorID = vasarlo;
			break;
		case 2: // ADMIN
			szerepkorID = adminisztrator;
			break;
		case 3: // FUTAR
			szerepkorID = futar;
			break;
	}
}


const string& Felhasznalo::szerepkorMegnevezesAzonositasa() const {
	Szerepkor s(szerepkorID);
	return s.getMegnevezes();
}

SzerepkorTipus Felhasznalo :: getSzerepkorID() const {
	return szerepkorID;
}

void Felhasznalo::start(AjanlatLista& lista, Rendelesek& rendelesek, Hibajegyzesek& hibajegyzesek) {

}