#include "hibajegyzes.h"

Hibajegyzes::Hibajegyzes(const string &l, const int &f):
    leiras(l), felhasznaloID(f)
{
}
Hibajegyzes::Hibajegyzes(const string& l, const int& f, const Datum& d) :
    leiras(l), felhasznaloID(f), datum(d)
{
}

void Hibajegyzes::kiir() const
{
    cout << "\tHiba leirasa: " << leiras << endl;
    cout << "\tFelhasznalo ID-je: " << felhasznaloID << endl;
    cout << "\tHiba letrejotte: ";
    datum.kiir();
    cout << endl;
}

string Hibajegyzes::getAdatokStringkent() const {
    stringstream str;
    str << felhasznaloID << " " << leiras << " " << datum.getAdatokStringkent();
    return str.str();
}
