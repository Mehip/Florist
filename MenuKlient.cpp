#include "stdafx.h"
#include <mysql.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

#include "MenuKlient.h"
#include "Osoba.h"
#include "Klient.h"
#include "KlientDAO.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13


int MenuKlient::menu(Osoba osoba)
{
	int strzalka = 0; //wcisniecie strzalki
	int pozycja = 0; //pozycja w menu
	int zatwierdzone = 0; //flaga sprawdzajaca czy dokonano wyboru w menu glownym
	int zatwierdzonep1 = 0; //flaga sprawdzajaca czy dykonano wybory w podmenu 1
	int zatwierdzonep2 = 0; //flaga sprawdzajaca czy dykonano wybory w podmenu 2
	int zatwierdzonep3 = 0; //flaga sprawdzajaca czy dykonano wybory w podmenu 3

	int zwrot; //zmienna zwracana do main
	string menuG[9]; //Menu glowne
	string menup1[4]; //podmenu 1 zamowienia
	string menup2[6]; //podmenu 2 klienci
	string menup3[3]; //podmenu 3 statystyki

	HANDLE kolor; //uchwyt do koloru
	Klient klient(osoba.login);
	AdminDAO ADAO;

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////MENU ADMINA///////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	menuG[0] = "Edycja konta";
	menuG[1] = "Zamowienia";
	menuG[2] = "Klienci";
	menuG[3] = "Statystyki";
	menuG[4] = "Wyloguj";
	menuG[5] = "Zakoncz";


	menup1[0] = "Zloz zamowienia";
	menup1[1] = "Wyswietl zamowienia";


	menup2[0] = "Dodaj klienta";
	menup2[1] = "Usun klienta";
	menup2[2] = "Wyswietl klientow";

	menup3[0] = "Ilosc zamowien";
	menup3[1] = "Ilosc klientow";


	while (1) //menu glowne
	{
		system("cls");
		//wyswietlenie daty i godziny
		SYSTEMTIME SystemTime;
		GetLocalTime(&SystemTime);
		SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
		cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
		cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
		cout << endl;

		SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

		strzalka = 0;

		for (int i = 0; i < 6; i++) //podswietlanie wybranej opcji
		{
			if (i == pozycja)
			{
				SetConsoleTextAttribute(kolor, FOREGROUND_RED);
				cout << menuG[i] << endl;
				SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
			}
			else
			{
				cout << menuG[i] << endl;
			}
		}


		switch ((strzalka = _getch())) //zmiana pozycji za pomoca strzalek
		{
		case KEY_UP:
			if (pozycja > 0)
				pozycja--;
			else
				pozycja = 5;
			break;
		case KEY_DOWN:
			if (pozycja < 5)
				pozycja++;
			else
				pozycja = 0;
			break;
		case ENTER:
			zatwierdzone = 1;
			break;
		}

		while (zatwierdzone == 1) //przejscie do podmenu
		{

			if (pozycja == 0) //Edycja konta
			{
				system("cls");
				//wyswietlenie daty i godziny
				GetLocalTime(&SystemTime);
				SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
				cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
				cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
				cout << endl;

				ADAO.edytuj_konto();
				zatwierdzone = 0;
			}

			if (pozycja == 1) //zamowienia
			{
				pozycja = 0;

				while (strzalka != 27) //warunek sprawdzajacy czy esc zostal nacisniety
				{
					system("cls");
					//wyswietlenie daty i godziny
					GetLocalTime(&SystemTime);
					SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
					cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
					cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
					cout << endl;

					SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

					zatwierdzone = 0;

					/////////////////////////////////////////////////////////////////////
					for (int i = 0; i < 2; i++) //podswietlanie wybranej opcji
					{
						if (i == pozycja)
						{
							SetConsoleTextAttribute(kolor, FOREGROUND_RED);
							cout << menup1[i] << endl;
							SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
						}
						else
						{
							cout << menup1[i] << endl;
						}
					}

					//////////////////////////////////////////////////////////////////////

					strzalka = 0;

					switch ((strzalka = _getch())) //zmiana pozycji za pomoca strzalek
					{
					case KEY_UP:
						if (pozycja > 0)
							pozycja--;
						else
							pozycja = 1;
						break;
					case KEY_DOWN:
						if (pozycja < 1)
							pozycja++;
						else
							pozycja = 0;
						break;
					case ENTER:
						zatwierdzonep1 = 1;
						break;
					}

					///////////////////////////////////////////////////////////////////////
					while (zatwierdzonep1 == 1) //przejscie do opcji
					{
						system("cls");
						if (pozycja == 0) //zloz zamowienie
						{
							cout << "Zloz zamowienie" << endl;
							zatwierdzonep1 = 0;
						}

						if (pozycja == 1) //wyswietl zamowienia
						{
							cout << "Wyswietl zamowienia" << endl;
							zatwierdzonep1 = 0;
						}
					}
				}
			}

			if (pozycja == 2) //klienci
			{
				pozycja = 0;

				zatwierdzone = 0;

				while (strzalka != 27) //warunek sprawdzajacy czy esc zostal nacisniety
				{
					system("cls");
					//wyswietlenie daty i godziny
					GetLocalTime(&SystemTime);
					SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
					cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
					cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
					cout << endl;

					SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

					/////////////////////////////////////////////////////////////////////
					for (int i = 0; i < 3; i++) //podswietlanie wybranej opcji
					{
						if (i == pozycja)
						{
							SetConsoleTextAttribute(kolor, FOREGROUND_RED);
							cout << menup2[i] << endl;
							SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
						}
						else
						{
							cout << menup2[i] << endl;
						}
					}

					//////////////////////////////////////////////////////////////////////

					strzalka = 0;

					switch ((strzalka = _getch())) //zmiana pozycji za pomoca strzalek
					{
					case KEY_UP:
						if (pozycja > 0)
							pozycja--;
						else
							pozycja = 2;
						break;
					case KEY_DOWN:
						if (pozycja < 2)
							pozycja++;
						else
							pozycja = 0;
						break;
					case ENTER:
						zatwierdzonep2 = 1;
						break;
					}

					///////////////////////////////////////////////////////////////////////
					while (zatwierdzonep2 == 1) //przejscie do opcji
					{
						system("cls");
						if (pozycja == 0) //dodaj klienta
						{
							ADAO.dodaj_klienta();
							zatwierdzonep2 = 0;
						}

						if (pozycja == 1) //usuwanie klientow
						{
							ADAO.usun_klienta();
							zatwierdzonep2 = 0;
						}

						if (pozycja == 2) //wyswietl klientow
						{
							ADAO.wyswietl_klientow();
							zatwierdzonep2 = 0;
						}
					}
				}
			}

			if (pozycja == 3) //statystyki
			{
				pozycja = 0;

				zatwierdzone = 0;

				while (strzalka != 27) //warunek sprawdzajacy czy esc zostal nacisniety
				{

					system("cls");
					//wyswietlenie daty i godziny
					GetLocalTime(&SystemTime);
					SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
					cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
					cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
					cout << endl;

					SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

					/////////////////////////////////////////////////////////////////////
					for (int i = 0; i < 2; i++) //podswietlanie wybranej opcji
					{
						if (i == pozycja)
						{
							SetConsoleTextAttribute(kolor, FOREGROUND_RED);
							cout << menup3[i] << endl;
							SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
						}
						else
						{
							cout << menup3[i] << endl;
						}
					}

					//////////////////////////////////////////////////////////////////////

					strzalka = 0;

					switch ((strzalka = _getch())) //zmiana pozycji za pomoca strzalek
					{
					case KEY_UP:
						if (pozycja > 0)
							pozycja--;
						else
							pozycja = 1;
						break;
					case KEY_DOWN:
						if (pozycja < 1)
							pozycja++;
						else
							pozycja = 0;
						break;
					case ENTER:
						zatwierdzonep3 = 1;
						break;
					}

					///////////////////////////////////////////////////////////////////////
					while (zatwierdzonep3 == 1) //przejscie do opcji
					{
						system("cls");
						if (pozycja == 0) //Ilosc zamowien
						{
							cout << "Ilosc zamowien" << endl;
							zatwierdzonep3 = 0;
						}

						if (pozycja == 1) //Ilosc klientow
						{
							cout << "Ilosc klientow" << endl;
							zatwierdzonep3 = 0;
						}
					}
				}
			}

			if (pozycja == 4) //wyloguj
			{
				zwrot = 0;
				return zwrot;
			}

			if (pozycja == 5) //zakoncz
			{
				zwrot = 1;
				return zwrot;
			}
		}
	}
}