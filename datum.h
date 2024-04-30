#ifndef DATUM_H
#define DATUM_H
#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <string>
#include <sstream>
#include <map>
#include <iostream>

using namespace std;

class Datum
{
private:
    int ev;
    int honap;
    int nap;
    int ora;
    int perc;
public:
    Datum();
    Datum(int y, int m, int d, int h, int min);

    int getEv() const;
    int getHonap() const;
    int getNap() const;
    int getOra() const;
    int getPerc() const;
    void kiir() const;

    string getAdatokStringkent() const;
};

#endif // DATUM_H
