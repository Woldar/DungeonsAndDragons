# include "Broñ.h"
#include <string>
#include <string.h>
#include <iostream>

Bron::Bron(std::string _nazwa,int _obrazenia,int _rzadkosc,int _numer)
{
	rzadkosc=_rzadkosc;
	ustawNazwa(_numer, _rzadkosc);
	ustawObrazenia(_numer, _rzadkosc);
}
Bron::Bron(std::string _nazwa)
{
	nazwa = _nazwa;
}
Bron::Bron()
{

}
Bron::~Bron()
{

}

std::string nazwyBroniPospolitych[10] = { "Miecz","Sztylet","Maczuga","Siekiera","Luk" };
const int obrazeniaBroniPospolitych[10] = { 2,1,2,1,2 };

std::string nazwyBroniRzadkich[10] = { "Kusza","Szabla","Topor","Katana","Miecz Dwurecznny" };
const int obrazeniaBroniRzadkich[10] = { 3,3,2,4,4 };

std::string nazwyBroniEpickich[10] = { "Plomienny miecz","Strzelba","Miecz Przeznaczenia","Kula Mocy","Czakram" };
const int obrazeniaBroniEpickich[10] = { 6,5,7,8,5 };

void Bron::ustawNazwa(int numer, int rzadkosc)
{
	switch (rzadkosc)
	{
	case 1:
		numer = numer % 5;

		nazwa = nazwyBroniPospolitych[numer];
		break;
	case 2:
		numer = numer % 5;
		nazwa = nazwyBroniRzadkich[numer];
		break;
	case 3:
		numer = numer % 5;
		nazwa = nazwyBroniEpickich[numer];
		break;
	}
}
void Bron::ustawObrazenia(int numer, int rzadkosc)
{
	switch (rzadkosc)
	{
	case 1:
		numer = numer % 5;

		obrazenia = obrazeniaBroniPospolitych[numer];
		break;
	case 2:
		numer = numer % 5;
		obrazenia = obrazeniaBroniRzadkich[numer];
		break;
	case 3:
		numer = numer % 5;
		obrazenia = obrazeniaBroniEpickich[numer];
		break;
	}
}