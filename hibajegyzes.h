#ifndef HIBAJEGYZES_H
#define HIBAJEGYZES_H

#include <iostream>
#include "datum.h"

class Hibajegyzes
{
private:
    Datum datum;
    string leiras;
    int felhasznaloID;
public:
    Hibajegyzes(const string &l, const int &f);
    Hibajegyzes(const string& l, const int& f, const Datum& d);
    void kiir() const;
    string getAdatokStringkent() const;
};

#endif // HIBAJEGYZES_H
