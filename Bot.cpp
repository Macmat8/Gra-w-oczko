#include "Bot.h"
#include <iostream>

int Bot::podaj_numer_bota() {
	return numer;
}

void Bot::ustaw_numer_bota(int _nr) {
	numer = _nr;
}

void Bot::ustaw_poziom_bota() {
	int x = 0;

	do {
		std::cout << "\nWybierz poziom Bota_" << podaj_numer_bota() << ":\n";
		std::cout << "1.Zachowawczy\n2.Normalny\n3.Ryzykujacy\n";
		std::cin >> x;
		zabezpieczenie(&x);
	} while (x != 1 && x != 2 && x != 3);

	odwaga = x;
}

int Bot::podaj_poziom_bota() {
	return odwaga;
}