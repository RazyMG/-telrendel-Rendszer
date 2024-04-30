#include "datum.h"

int Datum::getEv() const
{
    return ev;
}

int Datum::getHonap() const
{
    return honap;
}

int Datum::getNap() const
{
    return nap;
}

int Datum::getOra() const
{
    return ora;
}

int Datum::getPerc() const
{
    return perc;
}

void Datum::kiir() const
{
    cout << nap << "/" << honap << "/" << ev << " " << ora << ":" << perc << endl;
}

Datum::Datum()
{
    //jelenlegi időpont lekérése
    time_t now = time(0);
    string date_time = ctime(&now);

    int e = stoi(date_time.substr(20, 4));
    int n = stoi(date_time.substr(8, 2));
    int o = stoi(date_time.substr(11, 2));
    int p = stoi(date_time.substr(14, 2));

    //honapok szám szerinti megkülönböztetése
    string temp = date_time.substr(4, 3);
    map<string, int> honapok;
    honapok["Jan"] = 1;
    honapok["Feb"] = 2;
    honapok["Mar"] = 3;
    honapok["Apr"] = 4;
    honapok["May"] = 5;
    honapok["Jun"] = 6;
    honapok["Jul"] = 7;
    honapok["Aug"] = 8;
    honapok["Sep"] = 9;
    honapok["Okt"] = 10;
    honapok["Nov"] = 11;
    honapok["Dec"] = 12;

    int h = honapok[temp];

    //objektum adatainak a feltöltése
    ev = e;
    honap = h;
    nap = n;
    ora = o;
    perc = p;
}

Datum::Datum(int y, int m, int d, int h, int min) :
    ev(y),
    honap(m),
    nap(d),
    ora(h),
    perc(min)
{}

string Datum::getAdatokStringkent() const {
    stringstream str;
    str << ev << " " << honap << " " << nap << " " << ora << " " << perc;
    return str.str();
}