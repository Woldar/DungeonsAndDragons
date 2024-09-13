#include "Klasy.h"
#include <string>
#include <string.h>
#include <iostream>

Klasy::Klasy(int _numer)
{
	numer = _numer;
	ustawNazwa(_numer);
}
Klasy::Klasy()
{

}
Klasy::~Klasy()
{

}


	std::string nazwyKlas[5] = { "","Rycerz","Kaplan","Lotr" };

void Klasy::ustawNazwa(int numer)
	{
	nazwaKlasy = nazwyKlas[numer];
	}
/*void Klasy::umiejetnosci(std::string nazwaKlasy)
{
	if (nazwaKlasy == "Rycerz")
	{
		BohaterK[0]->pancerz = BohaterK[0]->pancerz + 1;
	}
	if (nazwaKlasy == "Kaplan")
	{
		BohaterK[0]->zdrowie = BohaterK[0]->zdrowie + 10;
	}
	if (nazwaKlasy == "Lotr")
	{
		Walczacy[0]->zdrowie = Walczacy[0]->zdrowie - 10;
	}
}*/
