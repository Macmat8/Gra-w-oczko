#pragma once
#include <iostream>
#include "Gracz.h"
#include "Bot.h"

class Gracz;

class Kasyno {
private:
	int ilu_graczy = 0;
	int ile_boty = 0;
	Gracz* gracze = nullptr;
	Bot* boty = nullptr;
	Karta talia[52];
public:
	Kasyno();
	void zapros_graczy();
	void utworz_boty();
	void ustaw_ilosc_graczy(int _ilosc);
	void ustaw_ilosc_botow(int _ilosc);
	int podaj_liczbe_graczy();
	int podaj_liczbe_botow();
	void kto_wygral(int* _t_b, int* _t_g);
	Karta *dajKarte(int *_ktora);
	void tasowanie();
	void pokaz_talie();
	void rozdaj_karty(int* _t_b, int* _t_g);
	void poczatek_gry();
	void graj(int* _t_b, int* _t_g);
	void zapisz_stan_gry(int *_t_b, int* _t_g);
	void zabezpieczenie_1(int* wejscie);
	Kasyno& operator=(const Kasyno&)=delete;
	Kasyno(const Kasyno&)=delete;
	~Kasyno();
};