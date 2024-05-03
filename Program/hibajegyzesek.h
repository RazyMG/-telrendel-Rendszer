#ifndef HIBAJEGYZESEK_H
#define HIBAJEGYZESEK_H

#include <iostream>
#include <fstream>
#include <list>
#include "hibajegyzes.h"

class Hibajegyzesek
{
private:
    list<Hibajegyzes*> bejegyzes;
public:
    Hibajegyzesek();
    void hibaBejegyzese(Hibajegyzes* hiba);
    void kiir() const;

    void hibajegyzesekMenteseFajlba() const;
};

#endif // HIBAJEGYZESEK_H
