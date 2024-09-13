#pragma once
#include "Bohater.h"
#include "Ekwipunek.h"
#include "Broñ.h"
#include "Pancerz.h"


class Przeciwnik : public Bohater
{
protected:

	bool wrogoœæ;
	int	trudnosc;
	int numer;



public:
	
	Przeciwnik(std::string _nazwa, int _zdrowie, int _obrazenia,int _numer,int _trudnosc);
	Przeciwnik(std::string _nazwa, int _zdrowie, int _obrazenia);
	Przeciwnik();
	~Przeciwnik();
	Bron ZwlokiB[1];
	Pancerz ZwlokiP[1];
	int zw³oki();
	void wypisz()  { std::cout << nazwa<<" "<<  zdrowie<<" "<<  obrazenia<<"  "; }
	int getWrogosc();
	int getTrudnosc();
	void setZdrowie(int aZdrowie);
	int getZdrowie();
	void ustawNazwa(int numer,int trudnosc);
	void ustawObrazenia(int numer,int trudnosc);
	void ustawZdrowie(int numer,int trudnosc);
	void dajPrzedmioty(int trudnosc);
		
};