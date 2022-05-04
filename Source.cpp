#include <iostream>
#include <cstdlib>
#include "Kasyno.h"

void menu(int* wybierz) {

	int wybor, dane;

	do
	{
		std::cout << "\nMenu uzytkownika: \n\n";
		std::cout << "1. Nowa gra\n2. Zakoncz";
		std::cout << "\n\n";

		while (scanf_s("%d", &wybor) != 1)
		{
			do {
				dane = wybor;
			} while ((dane = getchar()) != '\n' && dane != EOF);
			printf("Wprowadz liczbe!!!\n");
		}

		*wybierz = wybor;
	} while (wybor != 1 && wybor != 2);

}

int main() {
	int wybor = 0;

	do {
		Kasyno kas;

		menu(&wybor);


		while (wybor == 1) {
			int* tab_reka_boty;
			int* tab_reka_gracze;
			int b;
			int g;

			std::cout << "Przed przystapieniem do rozgrywki wprowadz dane:" << std::endl;
			kas.poczatek_gry();
			b = kas.podaj_liczbe_botow();
			g = kas.podaj_liczbe_graczy();
			tab_reka_boty = new int[b];
			tab_reka_gracze = new int[g];

			system("cls");

			kas.pokaz_talie();
			std::cout << "\n\n";
			kas.tasowanie();
			kas.pokaz_talie();
			std::cout << "\n\n";

			kas.rozdaj_karty(tab_reka_boty, tab_reka_gracze);
			kas.graj(tab_reka_boty, tab_reka_gracze);
			std::cout << "\n";
			kas.kto_wygral(tab_reka_boty, tab_reka_gracze);

			kas.zapisz_stan_gry(tab_reka_boty, tab_reka_gracze);
			std::cout << "\nStan gry zapisany w pliku txt\n";

			delete[] tab_reka_boty;
			delete[] tab_reka_gracze;
			wybor = 0;
		}

	} while (wybor != 2);

	return 0;
}