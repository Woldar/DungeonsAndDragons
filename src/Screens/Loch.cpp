#include "Screens/Loch.h"


Loch::Loch(ScreenManager& screenManager) : screenManager(screenManager)
{
	initMusic();
	initText();
	//mBohater = std::make_unique<Bohater>();
	//mWalczacy = std::make_unique<Przeciwnik>();
	//std::cout << "Budzisz sie w ciemnym pomieszczeniu, nie wiesz jak sie tu znalazles.. nic nie pamietasz..\n" << std::endl;
	//std::cout << "Probujesz przypomniec sobie kim byles i jak sie nazywasz\n" << std::endl;
	//wybierzBohatera();
}
Loch::~Loch()
{

}

void Loch::start()
{
	do
	{
		mPoziom[poziomLochu]->wybierzKierunek();
		walka();
		poziomLochu++;
	} while (mBohater->zdrowie > 0 && poziomLochu < 10);
}

void Loch :: generujLoch()
{
	for (int i=0;i<9;i++)
	{
		mPoziom[i] = std::make_unique<Poziom_Lochu>(i, 0);
	}
	mPoziom[9] = std::make_unique<Poziom_Lochu>(9);

}

void Loch::wybierzBohatera()
{
	mBohater->wprowadzNazwe();
	system("cls");
	mBohater->wybierzKlase();
}

void Loch::menuGracza()
{
	std::cout << "\n" << std::endl;
	std::cout << "Jaki ruch chcesz wykonac?\n" << std::endl;
	if (mBohater->mana >= 25)
	{
		std::cout << "1.Atakuj" << std::endl;
		std::cout << "\nUmiejetnosci klasowe:\n" << std::endl;
		switch (mBohater->klasaBohatera[0].numer)
		{
		case(1):
			std::cout << "2.Gruba Skora (Dodaj '1' punkt pancerza ,a nastepnie zaatakuj)\tKoszt: 25 many\n" << std::endl;
			std::cout << "3.Blok (Zredukuj o 10 punktow nastepne otrzymane obrazenia oraz zaatakuj)\tKoszt: 25 many\n" << std::endl;
			break;
		case(2):
			std::cout << "2.Leczenie (Dodaj 10 punktow zdrowia ,a nastepnie zaatakuj)\tKoszt: 25 many\n" << std::endl;
			std::cout << "3.Poswiecenie (Zwieksz swoja obrazenia o 25% do konca walki i zaatakuj)\tKoszt: 25 many\n" << std::endl;
			break;
		case(3):
			std::cout << "2.Cios krytyczny (Zadaj podwojne obrazenia)\tKoszt: 25 many \n" << std::endl;
			std::cout << "3.Oslepienie (Zredukuj obrazenia przeciwnika o 25% i zaatakuj)\tKoszt: 25 many \n" << std::endl;
			break;
		}
		wyjatek();
		switch (wybor)
		{
		case (1):
			//BohaterK[0].atak();
			mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie -= mBohater->obrazenia;
			//mWalczacy->zdrowie = mWalczacy->zdrowie - mBohater->obrazenia;
			//std::endl << Poziom[poziomLochu].Walczacy[1].getZdrowie;
			break;
		case (2):
			if (mBohater->klasaBohatera[0].nazwaKlasy == "Rycerz")
			{
				mBohater->pancerz = mBohater->pancerz + 1;
				mBohater->mana = mBohater->mana - 25;
			}
			if (mBohater->klasaBohatera[0].nazwaKlasy == "Kaplan")
			{
				mBohater->zdrowie = mBohater->zdrowie + 10;
				mBohater->mana = mBohater->mana - 25;
			}
			if (mBohater->klasaBohatera[0].nazwaKlasy == "Lotr")
			{
				mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie -= mBohater->obrazenia;
				mBohater->mana = mBohater->mana - 25;
			}

			mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie -= mBohater->obrazenia;
			break;

		case (3):
				if (mBohater->klasaBohatera[0].nazwaKlasy == "Rycerz")
					{
						mBohater->statusTury = "Blok";
						mBohater->mana = mBohater->mana - 25;
					}
				if (mBohater->klasaBohatera[0].nazwaKlasy == "Kaplan")
					{
					mBohater->statusWalki = "Poswiecenie";
					mBohater->mana = mBohater->mana - 25;
					mBohater->obrazenia = mBohater->obrazenia * 1.25;
					}
				if (mBohater->klasaBohatera[0].nazwaKlasy == "Lotr")
					{
					mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->obrazenia -= (0.25 * mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->obrazenia);
					mBohater->mana = mBohater->mana - 25;
					}
		
				mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie -= mBohater->obrazenia;
			
					break;
	}
	}

	else
	{
		std::cout << "1.Atakuj" << std::endl;
		wyjatek();
		switch (wybor)
		{
		case 1:
			//BohaterK[0].atak();

			mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie -= mBohater->obrazenia;
			//std::endl << Poziom[poziomLochu].Walczacy[1].getZdrowie;
			break;
		}
	}
}
void Loch::menuPrzeciwnika()
{
	
	if (mBohater->statusTury == "Blok")
	{
		int atak = mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->obrazenia - mBohater->pancerz-10;
		if (atak < 0)
		{
			atak = 0;
		}
		mBohater->zdrowie = mBohater->zdrowie - atak;
	}
	else
	{
		int atak = mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->obrazenia - mBohater->pancerz;
		if (atak < 0)
		{
			atak = 0;
		}
		mBohater->zdrowie = mBohater->zdrowie - atak;
	}
	

	
}
void Loch::walka()
{
	system("cls");
	std::cout << "\n"<< mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->nazwa<<" zwlowieszczo na Ciebie spoglada, gotuj sie do walki..\n" << std::endl;
	do
	{
		std::cout << "Statystyki przeciwnika: " << std::endl;
		std::cout << "Zdrowie: " << mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie << std::endl;
	
	
		std::cout << "Obrazenia: " << mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->obrazenia << "\n" << std::endl;
		std::cout << "\nTwoje " << mBohater->zdrowie << " punkty zdrowia" << std::endl;
		std::cout << "Twoje obrazenia:" << mBohater->obrazenia << std::endl;
		std::cout << "Twoj pancerz:" << mBohater->pancerz << std::endl;
		std::cout << "Twoja mana:" << mBohater->mana << "\n" << std::endl;
		menuGracza();
			if (mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie > 0)
		{
			menuPrzeciwnika();
		}
		system("cls");
		if (mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie <= 0)
		{
			std::cout << "\nPrzeciwnik umiera od Twoich ciosow\n" << std::endl;
		}
		mBohater->statusTury = "brak";

	} while (mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->zdrowie > 0 && mBohater->zdrowie > 0);

	if (mBohater->statusWalki == "Poswiecenie")
	{
		mBohater->statusWalki = "brak";
		mBohater->ustawObrazenia();
		for (int i=0; i < mBohater->iloscBroni; i++)
		{
			mBohater->obrazenia = mBohater->obrazenia + mBohater->bronieBohatera[i].obrazenia;
		}
	}

	if (mBohater->zdrowie > 0)
	{
	
		mBohater->mana = mBohater->mana + 50;
		grabujPrzeciwnika(mBohater->iloscPancerzow, mBohater->iloscBroni);
		//ubierzEkwipunek();
	}
	if (mBohater->zdrowie <= 0)
	{
		std::cout << "Wykrwawiasz sie na smierc" << std::endl;
	}

}
void Loch::grabujPrzeciwnika(int iloscP,int iloscB)
{
	if (poziomLochu < 9)
	{
		if (mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->ZwlokiB[0].nazwa != "Brak")
		{
			mBohater->bronieBohatera[iloscB] = mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->ZwlokiB[0];
			mBohater->obrazenia = mBohater->obrazenia + mBohater->bronieBohatera[mBohater->iloscBroni].obrazenia;
			mBohater->iloscBroni = mBohater->iloscBroni + 1;
			std::cout << "Przy zabitym potworze znajdujesz " << mBohater->bronieBohatera[iloscB].nazwa;
			std::cout << "\t+" << mBohater->bronieBohatera[iloscB].obrazenia << " obrazen\n" << std::endl;

		}
		if (mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->ZwlokiP[0].nazwa != "Brak")
		{
			mBohater->pancerzBohatera[iloscP] = mPoziom[poziomLochu]->mPrzeciwnik[mPoziom[poziomLochu]->kierunek]->ZwlokiP[0];
			mBohater->pancerz = mBohater->pancerz + mBohater->pancerzBohatera[mBohater->iloscPancerzow].pancerz;
			mBohater->iloscPancerzow = mBohater->iloscPancerzow + 1;
			std::cout << "Przy zabitym potworze znajdujesz " << mBohater->pancerzBohatera[iloscP].nazwa;
			std::cout << "\t+" << mBohater->pancerzBohatera[iloscP].pancerz << " pancerzu\n" << std::endl;

		}
		std::cout << "\n" << std::endl;
		std::cout << "Kontynujesz swoja przygode i znajdujesz skalniak przypominajacy schody, ktorym wchodzisz na wyzszy poziom" << std::endl;
	}
	else
	{
		std::cout << "Wycienczony spogladasz ponad nieruchome zwloki i widzisz swiatelko w tunelu" << std::endl;
		std::cout << "Moze to juz koniec tego koszmaru.." << std::endl;
		std::cout << "\n" << std::endl;
	}
}
void Loch::wyjatek()
{
	do
	{
		try
		{
			std::cin >> wybor;
			if (wybor >= 1 && wybor <= 3)
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
			//system("cls");
			std::cout << "Nie wybrano prawidlowego ruchu.." << std::endl;
			std::cout << "\n" << std::endl;
		}
	} while (wybor < 1 || wybor > 3);
}
void Loch::zwolnijPamiec()
{


}

void Loch::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	// Check if the event is a key press
	if (event.type == sf::Event::KeyPressed) {
		// Check if the key pressed is "Enter"
		if (event.key.code == sf::Keyboard::Enter) {
			// Handle the Enter key press
			std::cout << "Switching to Cutscene Screen!" << std::endl;
			screenManager.switchScreen("Cutscene");

			// Implement specific logic here, like changing screens
			// screenManager.pushScreen(std::make_unique<GameScreen>());
		}
	}
}

void Loch::update(float deltaTime)
{
}

void Loch::draw(sf::RenderWindow& target)
{
}

int Loch::initMusic()
{
	if (!music.openFromFile("assets/music/o-recinto-amaldicoado-189324.mp3"))
		return -1; // error
	music.play();
	music.setLoop(true);
}

void Loch::initText()
{
	//mText[0].initText("Budzisz sie w ciemnym pomieszczeniu, nie wiesz jak sie tu znalazles.. niczego nie pamietasz..", true, 48, "Middle");
	//mText[1].initText("Nacisnij ENTER by kontynuowac", false, 24,"RightDownCorner");
}