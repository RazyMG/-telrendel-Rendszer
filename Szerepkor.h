#pragma once
#include <string>
#include "SzerepkorTipus.h"

using namespace std;

class Szerepkor
{
	SzerepkorTipus szerepkorID;
	string megnevezes;
public:
	Szerepkor(SzerepkorTipus id);

	const string& getMegnevezes() const;
};

