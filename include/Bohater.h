#pragma once
#include <string>
#include <string.h>
#include <iostream>
#include "Broñ.h"
#include "Pancerz.h"


class Bohater {

protected:

	std::string klasa;
	
	std::string umiejetnosci;

public:
	Bohater();
	~Bohater();
	Bohater(std::string _nazwa, int _zdrowie,int _obrazenia,int _pancerz,int _mana,std::string _statusWalki,std::string _statusTury);
	std::string nazwa;
	std::string statusWalki;
	std::string statusTury;

	int mana;
	int zdrowie;
	int obrazenia;
	int pancerz;
	int iloscBroni=0;
	int iloscPancerzow = 0;
	Bron bronieBohatera[10];
	Pancerz pancerzBohatera[10];
	//Klasy klasaBohatera[1];
	void wprowadzNazwe();
	void bonusekwipunku();
	void atak();
	void umiejetnosc();
	bool smierc();
	int ubierzprzedmiot();
	int uzyjmiksture();
	
	//int getatrybuty();
	void setNazwa(char _nazwa);
	void ustawObrazenia();
	void ustawZdrowie();
	int getZdrowie() { return zdrowie; }
	int getObrazenia() { return obrazenia; }
	void wypisz() { std::cout << nazwa <<"\t"<< zdrowie; }
	void wybierzKlase();
};