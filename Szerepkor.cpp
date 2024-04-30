#include "Szerepkor.h"

Szerepkor::Szerepkor(SzerepkorTipus id) : szerepkorID(id) {
	switch (szerepkorID) {
	 case vasarlo:
		megnevezes = "Vasarlo";
		break;
	 case ettermidolgozo:
		 megnevezes = "Ettermi dolgozo";
		 break;
	 case adminisztrator:
		 megnevezes = "Adminisztrator";
		 break;
	 case futar:
		 megnevezes = "Futar";
		 break;
	}
}

const string& Szerepkor::getMegnevezes() const {
	return megnevezes;
}