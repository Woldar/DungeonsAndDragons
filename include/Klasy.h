#pragma once
#include <string>
#include <string.h>
#include <iostream>

class Klasy
{
protected:



public:
	Klasy(int _numer);
	Klasy();
	~Klasy();
	std::string nazwaKlasy;
	int numer=0;
	void ustawNazwa(int numer);
	void umiejetnosci(std::string nazwaKlasy);
	//Bohater* BohaterK[1];
	//Przeciwnik* Walczacy[1];
};
