#pragma once
#include <iostream>
#include <string>
#include <string>
#include "Karta.h"

class Kasyno;

class Gracz {
private:
	bool pas = false;
	std::string nazwa;
	Karta* reka = nullptr;
	Kasyno* w_kasynie;
public:
	Gracz();
	std::string podaj_nazwe();
	void ustaw_nazwe(std::string _nazwa);
	Karta podaj_karte(int _i);
	bool czy_pas();
	void ustaw_pas(bool _pas);
	int wartosc_reki(int *_t, int _ktory);
	void wez_Karte(Karta *_karta, int* _liczba);
	void wyswietl_Karty(int _ile);
	bool dobierz_czy_pas();
	void zabezpieczenie(int* wejscie);
	void ustaw_kasyno(Kasyno* _w_kasynie);
	Gracz& operator=(const Gracz&) = delete;
	Gracz(const Gracz&) = delete;
	~Gracz();
};