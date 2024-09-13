#pragma once
#include "Ekwipunek.h"
#include <string>
#include <string.h>
#include <iostream>

class Bron : public Ekwipunek
{
protected:
	




public:
	void ustawNazwa(int numer,int rzadkosc);
	void ustawObrazenia(int numer, int rzadkosc);
	Bron(std::string _nazwa,int _obrazenia,int _rzadkosc,int _numer);
	Bron();
	~Bron();
	Bron(std::string _nazwa);
	int obrazenia;
	

};