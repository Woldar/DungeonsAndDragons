#pragma once
#include <string>
#include <string.h>
#include <iostream>

class Ekwipunek
{
protected:

	int rzadkosc;
public:
	std::string nazwa;
	Ekwipunek(int _numer,int _rzadkosc);
	Ekwipunek();
	~Ekwipunek();
	//Bron Bronie[30];
};