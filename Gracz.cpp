#include <string>
#include "Gracz.h"
#include "Kasyno.h"

void Gracz::zabezpieczenie(int* wejscie) {
	while (std::cin.fail()) {
		std::cout << "Nieprawidlowe dane!\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cin >> *wejscie;
	}
}

Gracz::Gracz() {
	int roz = 10;
	reka = new Karta[roz];
}

void Gracz::ustaw_kasyno(Kasyno* _w_kasynie) {
	this->w_kasynie = _w_kasynie;
}

int Gracz::wartosc_reki(int *_t, int _ktory) {
	int suma_reki = 0;

	for (int p = 0; p < _t[_ktory]; p++) {
		suma_reki += reka[p].getWartosc();
	}

	return suma_reki;
}

void Gracz::wez_Karte(Karta *_karta, int *_liczba) {
	reka[*_liczba] = *_karta;
}

void Gracz::wyswietl_Karty(int _ile) {
	for (int t = 0; t < _ile; t++) {
		reka[t].wypisz();
	}
}

bool Gracz::dobierz_czy_pas() {
	int x = 0;
	do {
		std::cout << "\n";
		std::cout << "Tura gracza " << podaj_nazwe() << " :" << std::endl;
		std::cout << "1.Dobierz karte\n2.Pas" << std::endl;
		std::cin >> x;
		zabezpieczenie(&x);
	} while (x != 1 && x != 2);

	if (x == 2) {
		std::cout << "\nGracz " << podaj_nazwe() << " spasowal!" << std::endl;
		return true;
	} else {
		std::cout << "\nGracz " << podaj_nazwe() << " dobiera karte!" << std::endl;
		return false;
	}
}

bool Gracz::czy_pas() {
	return pas;
}

void Gracz::ustaw_pas(bool _pas) {
	pas = _pas;
}

std::string Gracz::podaj_nazwe() {
	return nazwa;
}

void Gracz::ustaw_nazwe(std::string _nazwa) {
	nazwa = _nazwa;
}

Karta Gracz::podaj_karte(int _i) {
	return reka[_i];
}

Gracz::~Gracz() {
	delete []reka;
}