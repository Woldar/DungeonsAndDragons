#include "Przeciwnik.h"

Przeciwnik::Przeciwnik(std::string _nazwa, int _zdrowie, int _obrazenia,int _numer,int _trudnosc)
	/*:nazwa(_nazwa), zdrowie(_zdrowie), obrazenia(_obrazenia)*/
{

		ustawNazwa(_numer,_trudnosc);
		ustawZdrowie(_numer,_trudnosc);
		ustawObrazenia(_numer,_trudnosc);
		ZwlokiB[0] = Bron("Brak");
		ZwlokiP[0] = Pancerz("Brak");

	
}
Przeciwnik::Przeciwnik(std::string _nazwa, int _zdrowie, int _obrazenia)
{
	nazwa = _nazwa;
	zdrowie = _zdrowie;
	obrazenia = _obrazenia;

}

std::string nazwyPrzeciwnikowLatwych[10] = { "Szkaradztwo","Szlam","Wilk","Troll","Ork" };
const int zdrowiePrzeciwnikowLatwych[10] = { 30,50,40,45,70 };
const int obrazeniaPrzeciwnikowLatwych[10] = { 8,9,11,10,6 };

std::string nazwyPrzeciwnikowSrednich[10] = { "Cien","Olbrzymia Tarantula","Zywy Ogien","Wampir","Wiedzma" };
const int zdrowiePrzeciwnikowSrednich[10] = { 20,40,15,15,14 };
const int obrazeniaPrzeciwnikowSrednich[10] = { 20,15,24,30,40 };

std::string nazwyPrzeciwnikowTrudnych[10] = { "Smok","Wilkolak","Gigant","Golem","Wiwerna" };
const int zdrowiePrzeciwnikowTrudnych[10] = { 100,80,200,50,90 };
const int obrazeniaPrzeciwnikowTrudnych[10] = { 10,13,8,50,19 };


Przeciwnik::Przeciwnik()
{


}
Przeciwnik::~Przeciwnik()
{

}


void Przeciwnik::ustawNazwa(int numer,int trudnosc)
{
	switch (trudnosc)
	{
	case 1:
		numer = numer % 5;

		nazwa = nazwyPrzeciwnikowLatwych[numer];
		break;
	case 2:
		numer = numer % 5;
		nazwa = nazwyPrzeciwnikowSrednich[numer];
		break;
	case 3:
		numer = numer % 5;
		nazwa = nazwyPrzeciwnikowTrudnych[numer];
		break;
	}
	
}
void Przeciwnik::ustawZdrowie(int numer,int trudnosc)
{
	switch (trudnosc)
	{
	case 1:
		numer = numer % 5;


		zdrowie = zdrowiePrzeciwnikowLatwych[numer];
		break;
	case 2:
		numer = numer % 5;

		zdrowie = zdrowiePrzeciwnikowSrednich[numer];
		break;
	case 3:
		numer = numer % 5;

		zdrowie = zdrowiePrzeciwnikowTrudnych[numer];
		break;
	}

}


void Przeciwnik::ustawObrazenia(int numer,int trudnosc)
{
	switch (trudnosc)
	{
	case 1:
		numer = numer % 5;


		obrazenia = obrazeniaPrzeciwnikowLatwych[numer];
		break;
	case 2:
		numer = numer % 5;

		obrazenia = obrazeniaPrzeciwnikowSrednich[numer];
		break;
	case 3:
		numer = numer % 5;

		obrazenia = obrazeniaPrzeciwnikowTrudnych[numer];
		break;
	}

}

int Przeciwnik::getZdrowie()
{
	return zdrowie;
}

void Przeciwnik::setZdrowie(int aZdrowie)
{
	zdrowie = aZdrowie;
}




