#pragma once
#include "Przeciwnik.h"
class Poziom_Lochu
{
protected:
	
	
	
public:
	int kierunek;
	int poziom = 0;
	int numer = 0;
	int wybor;
	int los;
	Poziom_Lochu(int _poziom,int _kierunek);
	Poziom_Lochu(int _poziom);
	Poziom_Lochu();
	~Poziom_Lochu();

	//Przeciwnik Walczacy[1];
	//Przeciwnik Przeciwnicy[3];
	std::unique_ptr<Przeciwnik> mPrzeciwnik[3];
	//Bohater BohaterK[1];
	void wypiszprzeciwnikow();
	void wzmocnieniewrogow(int poziom);
	//void walka();
	void wybierzKierunek();
	void losujPrzeciwnika();
	void generujPrzedmiotyPrzeciwnikow(int numer,int i);
	void wyjatek();
};


