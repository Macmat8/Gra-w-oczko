#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>
#include "Kasyno.h"
#include "Gracz.h"
#include "Bot.h"

void Kasyno::zabezpieczenie_1(int* wejscie) {
	while (std::cin.fail()) {
		std::cout << "Nieprawidlowe dane!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cin >> *wejscie;
	}
}

Kasyno::Kasyno() {
	int b;

	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 13; k++) {
			b = k + (13*j);
			talia[b] = Karta(j, k);
		}
	}
}

void Kasyno::zapros_graczy() {
	int ilu = podaj_liczbe_graczy();
	gracze = new Gracz[ilu];
}

void Kasyno::utworz_boty() {
	int ile = podaj_liczbe_botow();
	boty = new Bot[ile];
}

void Kasyno::ustaw_ilosc_botow(int _ilosc) {
	ile_boty = _ilosc;
}

int Kasyno::podaj_liczbe_botow() {
	return ile_boty;
}

Karta* Kasyno::dajKarte(int *_ktora) {
	Karta karta = Karta();

	karta = talia[*_ktora];
	(*_ktora)++;
	return &karta;
}

void Kasyno::tasowanie() {
	srand(time(NULL));
	Karta chwil_karta = Karta();
	int tas_1;
	int tas_2;

	for (int j = 0; j < 100; j++) {
		tas_1 = rand() % 51;
		tas_2 = rand() % 51;

		if (tas_1 == tas_2) {
			if (tas_1 == 51) {
				tas_2--;
			} else {
				tas_2++;
			}

		}

		chwil_karta = talia[tas_1];
		talia[tas_1] = talia[tas_2];
		talia[tas_2] = chwil_karta;
	}
}

void Kasyno::pokaz_talie() {
	for (int k = 0; k < 52; k++) {
		talia[k].wypisz();
	}
}

void Kasyno::rozdaj_karty(int* _t_b, int* _t_g) {
	Karta karta_chwil_1 = Karta();
	Karta karta_chwil_2 = Karta();
	Karta karta_chwil_3 = Karta();
	Karta karta_chwil_4 = Karta();

	int ktora = 0, liczba_1 = 0, liczba_2 = 0;
	int pasowanie = 0;
	int koniec_tury = 2;
	int ile_graczy = podaj_liczbe_graczy();
	int ile_boty = podaj_liczbe_botow();

	for (int i_1 = 0; i_1 < ile_graczy; i_1++) {
		_t_g[i_1] = 2;
	}

	for (int i_2 = 0; i_2 < ile_boty; i_2++) {
		_t_b[i_2] = 2;
	}

	for (int i_3 = 0; i_3 < ile_graczy; i_3++) {
		do {
			karta_chwil_1 = *dajKarte(&ktora);
			gracze[i_3].wez_Karte(&karta_chwil_1, &liczba_1);
			liczba_1++;
		} while (liczba_1 < 2);

		std::cout << "\n";
		std::cout << gracze[i_3].podaj_nazwe();
		std::cout << "\n";
		gracze[i_3].wyswietl_Karty(2);
		std::cout << "\n";
		int suma_g = gracze[i_3].wartosc_reki(_t_g, i_3);
		std::cout << "\nWartosc reki:" << suma_g << "\n\n";
		liczba_1 = 0;
	}

	for (int i_4 = 0; i_4 < ile_boty; i_4++) {
		do {
			karta_chwil_3 = *dajKarte(&ktora);
			boty[i_4].wez_Karte(&karta_chwil_3, &liczba_2);
			liczba_2++;
		} while (liczba_2 < 2);

		std::cout << "\n";
		std::cout << "Bot_";
		std::cout << boty[i_4].podaj_numer_bota();
		std::cout << "\n";
		boty[i_4].wyswietl_Karty(2);
		std::cout << "\n";
		int suma_b = boty[i_4].wartosc_reki(_t_b, i_4);
		std::cout << "\nWartosc reki:" << suma_b << "\n\n";
		liczba_2 = 0;
	}

	liczba_1 = 2;
	liczba_2 = 2;

	for (int tura = 0; tura < koniec_tury; tura++) {
		std::cout << "\n";

		for (int ktory_1 = 0; ktory_1 < ile_graczy; ktory_1++) {
			if (gracze[ktory_1].czy_pas() == false) {
				gracze[ktory_1].ustaw_pas(gracze[ktory_1].dobierz_czy_pas());
			}
		}

		for (int ktory_2 = 0; ktory_2 < ile_boty; ktory_2++) {
			if (boty[ktory_2].podaj_poziom_bota() == 1) {
				if (boty[ktory_2].wartosc_reki(_t_b, ktory_2) <= 15) {
					boty[ktory_2].ustaw_pas(false);
				} else {
					boty[ktory_2].ustaw_pas(true);
				}
			}

			if (boty[ktory_2].podaj_poziom_bota() == 2) {
				if (boty[ktory_2].wartosc_reki(_t_b, ktory_2) <= 17) {
					boty[ktory_2].ustaw_pas(false);
				}
				else {
					boty[ktory_2].ustaw_pas(true);
				}
			}

			if (boty[ktory_2].podaj_poziom_bota() == 3) {
				if (boty[ktory_2].wartosc_reki(_t_b, ktory_2) <= 19) {
					boty[ktory_2].ustaw_pas(false);
				}
				else {
					boty[ktory_2].ustaw_pas(true);
				}
			}
		}

		for (int i_5 = 0; i_5 < ile_graczy; i_5++) {

			if (gracze[i_5].czy_pas() == false) {
				karta_chwil_2 = *dajKarte(&ktora);
				gracze[i_5].wez_Karte(&karta_chwil_2, &liczba_1);
				(_t_g[i_5]) = _t_g[i_5] + 1;
				std::cout << "\n\n" << gracze[i_5].podaj_nazwe();
				std::cout << " dobral: ";
				karta_chwil_2.wypisz();
				std::cout << "\nAktualna wartosc reki:"  << std::endl;
				int reka_g = gracze[i_5].wartosc_reki(_t_g, i_5);
				std::cout << reka_g << "\n";
			}
			else {
				std::cout << "\nGracz " << gracze[i_5].podaj_nazwe() << " spasowal" << "\n";
				koniec_tury++;
			}
		}
		
		for (int i_6 = 0; i_6 < ile_boty; i_6++) {

			if (boty[i_6].czy_pas() == false) {
				karta_chwil_4 = *dajKarte(&ktora);
				boty[i_6].wez_Karte(&karta_chwil_4, &liczba_2);
				(_t_b[i_6]) = _t_b[i_6] + 1;
				std::cout << "Bot_";
				std::cout << boty[i_6].podaj_numer_bota();
				std::cout << " dobral: ";
				karta_chwil_4.wypisz();
				std::cout << "\nAktualna wartosc reki:" << std::endl;
				int reka_b = boty[i_6].wartosc_reki(_t_b, i_6);
				std::cout << reka_b << "\n";
			}
			else {
				std::cout << "\nBot_" << boty[i_6].podaj_numer_bota() << " spasowal" << "\n";
				koniec_tury++;
			}
		}

		for (int i_7 = 0; i_7 < ile_graczy; i_7++) {
			int suma = gracze[i_7].wartosc_reki(_t_g, i_7);

			if (suma > 21) {
				gracze[i_7].ustaw_pas(true);
			}
		}

		for (int i_8 = 0; i_8 < ile_boty; i_8++) {
			int suma = boty[i_8].wartosc_reki(_t_b, i_8);

			if (boty[i_8].podaj_poziom_bota() == 1) {
				if (suma <= 15) {
					boty[i_8].ustaw_pas(false);
				}
				else {
					boty[i_8].ustaw_pas(true);
				}
			}

			if (boty[i_8].podaj_poziom_bota() == 2) {
				if (suma <= 17) {
					boty[i_8].ustaw_pas(false);
				}
				else {
					boty[i_8].ustaw_pas(true);
				}
			}

			if (boty[i_8].podaj_poziom_bota() == 3) {
				if (suma <= 19) {
					boty[i_8].ustaw_pas(false);
				}
				else {
					boty[i_8].ustaw_pas(true);
				}
			}
		}

		for (int i_10 = 0; i_10 < ile_graczy; i_10++) {
			if (gracze[i_10].czy_pas() == true) {
				pasowanie++;
			}
		}

		for (int i_11 = 0; i_11 < ile_boty; i_11++) {
			if (boty[i_11].czy_pas() == true) {
				pasowanie++;
			}
		}

		int kiedy_pas = (podaj_liczbe_botow() + podaj_liczbe_graczy());
		if (pasowanie == kiedy_pas) {
			koniec_tury = -1;
		}

		liczba_1++;
		liczba_2++;
		pasowanie = 0;
	}
}

void Kasyno::ustaw_ilosc_graczy(int _ilosc) {
	ilu_graczy = _ilosc;
}

int Kasyno::podaj_liczbe_graczy() {
	return ilu_graczy;
}

void Kasyno::zapisz_stan_gry(int *_t_b, int *_t_g) {

	std::ofstream txt;
	txt.open("plik.txt", std::ifstream::out);

	for (int i = 0; i < podaj_liczbe_graczy(); i++) {
		txt.setf(std::ios::left, std::ios::adjustfield);
		txt.width(24);
		txt << gracze[i].podaj_nazwe();
		txt << "|";

		for (int t = 0; t < _t_g[i]; t++) {
			txt << gracze[i].podaj_karte(t).getFigura();
			txt.width(2);
			txt << gracze[i].podaj_karte(t).getKolor();
		}

		txt.width(20);
		txt << "|";
		txt << gracze[i].wartosc_reki( _t_g, i);
		txt << "\n";
	}

	for (int i = 0; i < podaj_liczbe_botow(); i++) {
		txt << "Bot_";
		txt.width(20);
		txt << boty[i].podaj_numer_bota();
		txt << "|";		

		for (int t = 0; t < _t_b[i]; t++) {
			txt << boty[i].podaj_karte(t).getFigura();
			txt.width(2);
			txt << boty[i].podaj_karte(t).getKolor();
		}

		txt.width(20);
		txt << "|";
		txt << boty[i].wartosc_reki(_t_b, i);
		txt << "\n";
	}

	txt.close();
}

void Kasyno::kto_wygral(int* _t_b, int* _t_g) {
	int max_suma = 0;

	for (int i = 0; i < podaj_liczbe_graczy(); i++) {
		if (gracze[i].wartosc_reki(_t_g, i) > max_suma && gracze[i].wartosc_reki(_t_g, i) < 22) {
			max_suma = gracze[i].wartosc_reki(_t_g, i);
		}
	}

	for (int j = 0; j < podaj_liczbe_botow(); j++) {
		if (boty[j].wartosc_reki(_t_b, j) > max_suma && boty[j].wartosc_reki(_t_b, j) < 22) {
			max_suma = boty[j].wartosc_reki(_t_b, j);
		}
	}

	for (int k = 0; k < podaj_liczbe_graczy(); k++) {
		if (gracze[k].wartosc_reki(_t_g, k) == max_suma) {
			std::cout << "\nGracz " << gracze[k].podaj_nazwe() << " wygral!!\n";
		}
	}


	for (int l = 0; l < podaj_liczbe_botow(); l++) {
		if (boty[l].wartosc_reki(_t_b, l) == max_suma) {
			std::cout << "\nGracz Bot_" << boty[l].podaj_numer_bota() << " wygral!!\n";
		}
	}

	if (max_suma == 0) {
		std::cout << "\nWszyscy gracze przegrali!!!\n" << std::endl;
	}
}

void Kasyno::poczatek_gry() {
	int ile_graczy = 0;
	int ile_boty = 0;

	do {
		std::cout << "Podaj liczbe graczy:" << std::endl;
		std::cin >> ile_graczy;
		zabezpieczenie_1(&ile_graczy);
	} while (ile_graczy != 1 && ile_graczy != 2 && ile_graczy != 3);
	ustaw_ilosc_graczy(ile_graczy);

	do {
		std::cout << "Podaj liczbe botow:" << std::endl;
		std::cin >> ile_boty;
		zabezpieczenie_1(&ile_boty);
	} while (ile_boty != 1 && ile_boty != 2 && ile_boty != 3);
	ustaw_ilosc_botow(ile_boty);

	zapros_graczy();
	utworz_boty();
	system("cls");

	for (int u = 0; u < podaj_liczbe_graczy(); u++) {
		std::string naz;
		std::cout << "Podaj nazwe gracza:" << std::endl;
		std::cin >> naz;
		gracze[u].ustaw_nazwe(naz);
		std::cout << "\n";
	}

	for (int y = 0; y < podaj_liczbe_botow(); y++) {
		int nr = y + 1;
		boty[y].ustaw_numer_bota(nr);
		boty[y].ustaw_poziom_bota();
	}
}

void Kasyno::graj(int* _t_b, int* _t_g) {
	int pasowanie = 0;

	for (int i = 0; i < podaj_liczbe_graczy(); i++) {
		gracze[i].ustaw_kasyno(this);
	}

	for (int j = 0; j < podaj_liczbe_botow(); j++) {
		boty[j].ustaw_kasyno(this);
	}

	for (int i = 0; i < podaj_liczbe_graczy(); i++) {
		int suma_reki = 0;
		suma_reki = gracze[i].wartosc_reki(_t_g, i);
		std::cout << "Wartosc reki gracza ";
		std::cout << gracze[i].podaj_nazwe();
		std::cout << ": " << "\n" << suma_reki << "\n";
		gracze[i].wyswietl_Karty(_t_g[i]);
		std::cout << "\n";
	}

	for (int j = 0; j < podaj_liczbe_botow(); j++) {
		int suma_reki = 0;
		suma_reki = boty[j].wartosc_reki(_t_b, j);
		std::cout << "Wartosc reki Bota_";
		int nr = boty[j].podaj_numer_bota();
		std::cout << nr;
		std::cout << ": " << "\n" << suma_reki << "\n";
		boty[j].wyswietl_Karty(_t_b[j]);
		std::cout << "\n";
	}
}

Kasyno::~Kasyno() {
	delete[] gracze;
	delete[] boty;
}