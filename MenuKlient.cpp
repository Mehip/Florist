#include "stdafx.h"
#include <mysql.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

#include <vector>

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

	int zwrot; //zmienna zwracana do main
	vector <string> menuG;
	string menup1[3]; //podmenu 1 zamowienia
	string menup2[2]; //podmenu 2 statystyki

	HANDLE kolor; //uchwyt do koloru
	KlientDAO KDAO;

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////MENU ADMINA///////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	menuG.push_back("Edycja konta");
	menuG.push_back("Zamowienia");
	menuG.push_back("Statystyki");
	menuG.push_back("Wyloguj");
	menuG.push_back("Zakoncz");


	menup1[0] = "Zloz zamowienia";
	menup1[1] = "Wyswietl zamowienia";
	menup1[2] = "Historia zamowien";

	menup2[0] = "Ilosc zleconych,zatwierdzonych i wykonanych zlecen";


	while (1) //menu glowne
	{
		system("cls");
		//wyswietlenie daty i godziny
		SYSTEMTIME SystemTime;
		GetLocalTime(&SystemTime);
		SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
		cout << "Zalogowano jako: "<< osoba.login << "\t\t\t\t\t\t\t\t\t\t";
		cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
		cout << endl;

		SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

		strzalka = 0;

		for (int i = 0; i < 5; i++) //podswietlanie wybranej opcji
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
				pozycja = 4;
			break;
		case KEY_DOWN:
			if (pozycja < 4)
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
				cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
				cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
				cout << endl;

				KDAO.edytuj_konto(osoba);
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
					cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
					cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
					cout << endl;

					SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

					zatwierdzone = 0;

					/////////////////////////////////////////////////////////////////////
					for (int i = 0; i < 3; i++) //podswietlanie wybranej opcji
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
							pozycja = 2;
						break;
					case KEY_DOWN:
						if (pozycja < 2)
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
							KDAO.zloz_zamowienie(osoba);
							zatwierdzonep1 = 0;
						}

						if (pozycja == 1) //wyswietl zamowienia
						{
							KDAO.wysw_zamowienia(osoba);
							zatwierdzonep1 = 0;
						}

						if (pozycja == 2)
						{
							KDAO.historia_zamowien(osoba);
							zatwierdzonep1 = 0;
						}
					}
				}
			}

			if (pozycja == 2) //statystyki
			{
				pozycja = 0;

				zatwierdzone = 0;

				while (strzalka != 27) //warunek sprawdzajacy czy esc zostal nacisniety
				{

					system("cls");
					//wyswietlenie daty i godziny
					GetLocalTime(&SystemTime);
					SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
					cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
					cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
					cout << endl;

					SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

					/////////////////////////////////////////////////////////////////////
					for (int i = 0; i < 1; i++) //podswietlanie wybranej opcji
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
							pozycja = 0;
						break;
					case KEY_DOWN:
						if (pozycja < 0)
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
						if (pozycja == 0) //Ilosc zamowien
						{
							KDAO.ilosc_zak_rel_zle(osoba);
							zatwierdzonep2 = 0;
						}
					}
				}
			}

			if (pozycja == 3) //wyloguj
			{
				zwrot = 0;
				return zwrot;
			}

			if (pozycja == 4) //zakoncz
			{
				zwrot = 1;
				return zwrot;
			}
		}
	}
}