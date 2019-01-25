#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <mysql.h>

#include "Menu.h"
#include "Osoba.h"
#include "MenuAdmin.h"
#include "MenuKlient.h"

using namespace std;

template <class Typ>
Typ hashValue(string key) //funkcja hashujaca
{
	unsigned int val = 0;
	for (int i = 0; i < key.length(); i++) {
		val += (unsigned int)(key[i]); // cast each character of key to unsigned int
	}
	return val;                        // return the sum over all characters in key
}


int main(int argc, const char * argv[])
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////laczenie z BD///////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MYSQL mysql;

	mysql_init(&mysql); // incjalizacja

	//sprawdzanie polaczenia
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0)) //laczenie
	{
		cout << "Blad polaczenia z baza MySQL:" << mysql_errno(&mysql) << " " << mysql_error(&mysql) << endl;
		return 0;
	}

	mysql_select_db(&mysql, "kwiaciarnia");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////LOGOWANIE///////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int wyloguj = 0; //flaga wylogowujaca
	int koniec = 0; //flaga sprawdzajaca czy uzytkownik chce zakonczyc dzialanie programu
	int wybor; //wybor przychodni
	HANDLE kolor; //uchwyt do koloru
	string login;
	string haslo;
	string pesel;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	string typ_konta;


	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	//menu logowania
	while (1)
	{
		SetConsoleTextAttribute(kolor, FOREGROUND_RED);
		system("cls");
		cout << "LOGOWANIE:" << endl;
		SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
		cout << "LOGIN: ";
		cin >> login;
		cout << "HASLO: ";
		cin >> haslo;
		
		mysql_query(&mysql, "SELECT * FROM LOGOWANIE"); //wybranie wszystkich uzytkownikow z BD
		idZapytania = mysql_store_result(&mysql);

		while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
		{
			//przeszukanie bd
			for (int i = 0; i < mysql_num_fields(idZapytania); i++)
			{
				//porownywanie bd z wprowadzonymi danymi
				if (wiersz[i+1] == login && stoi(wiersz[i + 2]) == hashValue<unsigned int>(haslo))
				{
					//zalogowano
					pesel = wiersz[i];
					typ_konta = wiersz[i + 3];
					Menu *mglowne;
					Osoba osoba(pesel);
					//sprawdzanie typu konta i wybranie odpowiedniego menu
					if (typ_konta == "administrator") //konto admina
					{
						//tworzenie obiektow i przypisanie wskaznika polimorficznego
						MenuAdmin madmin;
						mglowne = &madmin;
						koniec = mglowne->menu(osoba);
						if (koniec == 1)
						{
							mysql_close(&mysql);
							return 0;
						}
					}

					if (typ_konta == "klient") //konto klienta
					{
						system("cls");
						cout << "Zalogowano jako: " << login << endl;
						MenuKlient mklient;
						mglowne = &mklient;
						koniec = mglowne->menu(osoba);
						if (koniec == 1)
						{
							mysql_close(&mysql);
							return 0;
						}
					}
				}
			}
		}
	}
	mysql_close(&mysql); // zamknij po³¹czenie
	return 0;
}