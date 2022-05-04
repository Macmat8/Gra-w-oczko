#pragma once
#include "Gracz.h"

class Bot : public Gracz
{
private:
	int numer = 0;
	int odwaga = 0;
public:
	void ustaw_numer_bota(int _nr);
	int podaj_numer_bota();
	void ustaw_poziom_bota();
	int podaj_poziom_bota();
};

