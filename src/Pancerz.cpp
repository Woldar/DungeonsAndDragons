#include "Pancerz.h"

#include <string>
#include <string.h>
#include <iostream>

Pancerz::Pancerz(std::string _nazwa, int _pancerz, int _rzadkosc,int _numer)
{
	ustawNazwa(_numer, _rzadkosc);
	ustawPancerz(_numer, _rzadkosc);
}
Pancerz::Pancerz(std::string _nazwa)
{
	nazwa = _nazwa;
}
Pancerz::Pancerz()
{

}
Pancerz::~Pancerz()
{

}

std::string nazwyPancerzowPospolitych[10] = { "Mala Tarcza","Szybkie Okulary","Szyszak","Skorzana Zbroje","Grube Rekawice" };
const int pancerzPancerzowPospolitych[10] = { 2,1,2,2,1 };

std::string nazwyPancerzowRzadkich[10] = { "Stalowe Naramienniki","Kolczasta Zbroje","Stalowe Buty","Helm Krzyzacki","Rycerski Napiersnik" };
const int pancerzPancerzowRzadkich[10] = { 3,3,2,4,4 };

std::string nazwyPancerzowEpickich[10] = { "Magiczna Tarcza","Tarcza Krzyzowca","Pierscien Ochrony","Demoniczny Pancerz","Rogaty Helm" };
const int pancerzPancerzowEpickich[10] = { 6,5,7,8,5 };

void Pancerz::ustawNazwa(int numer, int rzadkosc)
{
	switch (rzadkosc)
	{
	case 1:
		numer = numer % 5;

		nazwa = nazwyPancerzowPospolitych[numer];
		break;
	case 2:
		numer = numer % 5;
		nazwa = nazwyPancerzowRzadkich[numer];
		break;
	case 3:
		numer = numer % 5;
		nazwa = nazwyPancerzowEpickich[numer];
		break;
	}
}
void Pancerz::ustawPancerz(int numer, int rzadkosc)
{
	switch (rzadkosc)
	{
	case 1:
		numer = numer % 5;

		pancerz = pancerzPancerzowPospolitych[numer];
		break;
	case 2:
		numer = numer % 5;
		pancerz = pancerzPancerzowRzadkich[numer];
		break;
	case 3:
		numer = numer % 5;
		pancerz = pancerzPancerzowEpickich[numer];
		break;
	}
}