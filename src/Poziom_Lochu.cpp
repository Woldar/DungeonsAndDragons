#include "Poziom_Lochu.h"
#include <time.h>
#include<limits>

Poziom_Lochu::Poziom_Lochu(int _poziom, int _kierunek)
	:poziom(_poziom), kierunek(_kierunek)
{

		for (int i = 0; i <= 2; i++)
		{
			losujPrzeciwnika();
			mPrzeciwnik[i] = std::make_unique<Przeciwnik>("cos", 100, 10, numer, i + 1);
			generujPrzedmiotyPrzeciwnikow(numer, i);
			//numer++; -> zweryfikuj jak to dziala
		}
		wzmocnieniewrogow(_poziom);
		wypiszprzeciwnikow();

}

Poziom_Lochu::Poziom_Lochu(int _poziom)
	:poziom(_poziom)
{
		mPrzeciwnik[0] = std::make_unique<Przeciwnik>("Boss", 400, 30);
		mPrzeciwnik[1] = std::make_unique<Przeciwnik>("Boss", 400, 30);
		mPrzeciwnik[2] = std::make_unique<Przeciwnik>("Boss", 400, 30);
}

Poziom_Lochu::Poziom_Lochu()
{

}
Poziom_Lochu::~Poziom_Lochu()
{
}
void Poziom_Lochu::wypiszprzeciwnikow()
{
	for (int i=0; i < 3; i++)
	{
		mPrzeciwnik[i]->wypisz();
	}
}

void Poziom_Lochu::wybierzKierunek()
{
	std::cout << "\n" << std::endl;
	std::cout << "Na jednej ze scian widzisz napis     Poziom: " << poziom << std::endl;
	std::cout << "\n" << std::endl;
	if (poziom < 9)
	{
		std::cout << "Widzisz przed soba trzy sciezki.." << std::endl;
		std::cout << "\n" << std::endl;
	
		los = rand() % 6;
		switch (los)
		{
		case (0):
			std::cout << "\n" << std::endl;
			std::cout << "'1'   W oddali widzisz niewielki obrys" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'2'   Widzisz cos wielkoscia przypominajacego czlowieka" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'3'   Wydobywaja sie glosne dzwieki, ciarki przechodza Ci po plecach" << std::endl;
			std::cout << "\n" << std::endl;
			break;
		case (1):
			std::cout << "\n" << std::endl;
			std::cout << "'1'   W oddali widzisz niewielki obrys" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'2'   Wydobywaja sie glosne dzwieki, ciarki przechodza Ci po plecach" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'3'   Widzisz cos wielkoscia przypominajacego czlowieka" << std::endl;
			std::cout << "\n" << std::endl;

			break;
		case (2):

			std::cout << "\n" << std::endl;
			std::cout << "'1'   Wydobywaja sie glosne dzwieki, ciarki przechodza Ci po plecach" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'2'   Widzisz cos wielkoscia przypominajacego czlowieka" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'3'   W oddali widzisz niewielki obrys" << std::endl;
			std::cout << "\n" << std::endl;
			break;
		case (3):
			std::cout << "\n" << std::endl;
			std::cout << "'1'   Wydobywaja sie glosne dzwieki, ciarki przechodza Ci po plecach" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'2'   W oddali widzisz niewielki obrys" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'3'   Widzisz cos wielkoscia przypominajacego czlowieka" << std::endl;
			std::cout << "\n" << std::endl;

			break;
		case (4):
			std::cout << "\n" << std::endl;
			std::cout << "'1'   Widzisz cos wielkoscia przypominajacego czlowieka" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'2'   W oddali widzisz niewielki obrys" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'3'   Wydobywaja sie glosne dzwieki, ciarki przechodza Ci po plecach" << std::endl;
			std::cout << "\n" << std::endl;
			break;
		case (5):
			std::cout << "\n" << std::endl;
			std::cout << "'1'   Widzisz cos wielkoscia przypominajacego czlowieka" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'2'   Wydobywaja sie glosne dzwieki, ciarki przechodza Ci po plecach" << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "'3'   W oddali widzisz niewielki obrys" << std::endl;
			std::cout << "\n" << std::endl;
			break;


		}
		std::cout << "\n" << std::endl;
		std::cout << "Wybierz droge ktora pojdziesz: " << std::endl;
		wyjatek();

	}
	else
	{
		std::cout << "\n" << std::endl;
		std::cout << "Ziemia drzy pod Twoimi stopami" << std::endl;
		std::cout << "\n" << std::endl;
		std::cout << "Wpisz liczbe by kontynuowac" << std::endl;
		std::cout << "\n" << std::endl;
		std::cin >> kierunek;
	}
}
void Poziom_Lochu::losujPrzeciwnika()
{
	numer = rand() % 100;
}
void Poziom_Lochu::wzmocnieniewrogow(int poziom)
{
	mPrzeciwnik[0]->zdrowie = mPrzeciwnik[0]->zdrowie + (mPrzeciwnik[0]->zdrowie/10*poziom);
	mPrzeciwnik[1]->zdrowie = mPrzeciwnik[1]->zdrowie + (mPrzeciwnik[1]->zdrowie / 10 * poziom);
	mPrzeciwnik[2]->zdrowie = mPrzeciwnik[2]->zdrowie + (mPrzeciwnik[2]->zdrowie / 10 * poziom);

	mPrzeciwnik[0]->obrazenia = mPrzeciwnik[0]->obrazenia + (mPrzeciwnik[0]->obrazenia / 10 * poziom);
	mPrzeciwnik[1]->obrazenia = mPrzeciwnik[1]->obrazenia + (mPrzeciwnik[1]->obrazenia / 10 * poziom);
	mPrzeciwnik[2]->obrazenia = mPrzeciwnik[2]->obrazenia + (mPrzeciwnik[2]->obrazenia / 10 * poziom);


}
void Poziom_Lochu::generujPrzedmiotyPrzeciwnikow(int numer,int i)
{
	int los=rand()%100;
	los = los % 2;

	switch (los)
	{
	case 0:
		mPrzeciwnik[i]->ZwlokiB[0] = Bron("cos", 0,i+1,numer);
		break;
	case 1:
		mPrzeciwnik[i]->ZwlokiP[0] = Pancerz("cos", 0, i+1,numer);
		break;
	}
}
void Poziom_Lochu::wyjatek()
{
	do
	{


		try
		{
			std::cin >> kierunek;
			if (kierunek >= 1 && kierunek <= 3)
			{
				
			}
			else
			{
				throw std::runtime_error("");
			}

		}
		catch (const std::runtime_error & e)
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Podano bledna droge.." << std::endl;
			std::cout << "\n" << std::endl;
			std::cout << "Wybierz droge ktora pojdziesz: " << std::endl;
			//std::cin >> kierunek;
		}
	} while (kierunek < 1 || kierunek > 3);
	kierunek -= 1;
}