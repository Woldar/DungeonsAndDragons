#pragma once

#include "Ekwipunek.h"
#include <string>
#include <string.h>
#include <iostream>

class Pancerz : public Ekwipunek
{
protected:




public:
	void ustawNazwa(int numer, int rzadkosc);
	void ustawPancerz(int numer, int rzadkosc);
	Pancerz(std::string _nazwa, int _pancerz, int _rzadkosc,int _numer);
	Pancerz();
	~Pancerz();
	Pancerz(std::string _nazwa);
	int pancerz;

};