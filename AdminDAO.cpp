#include "stdafx.h"
#include <mysql.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>

#include "AdminDAO.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13

//git
//done
unsigned int AdminDAO::hashValue(string key) //funkcja hashujaca
{
	unsigned int val = 0;
	for (int i = 0; i < key.length(); i++) {
		val += (unsigned int)(key[i]); // cast each character of key to unsigned int
	}
	return val;                        // return the sum over all characters in key
}

//done
string AdminDAO::walidacjaKodPocztowy(string kod)
{
	while (1)
	{
		if (kod[0] <= 57 && kod[0] >= 48 && kod.length() == 6 && kod[1] <= 57 && kod[1] >= 48)
		{
			if (kod[2] == 45 && kod[3] <= 57 && kod[3] >= 48 && kod[4] <= 57 && kod[4] >= 48 && kod[5] <= 57 && kod[5] >= 48)
			{
				return kod;
			}
		}
		
		cout << "Wprowadzono blednie kod pocztowy!!!" << endl;
		cout << "Kod pocztowy: ";
		cin >> kod;
		getchar();
	}
}

//done
string AdminDAO::walidacjaNrTel(string numer)
{
	int ilosc;

	while (1)
	{
		ilosc = 0;

		for (int i = 0; i < 9; i++)
		{
			if (numer[i] <= 57 && numer[i] >= 48 && numer.length() == 9)
				ilosc++;
		}

		if (ilosc == 9)
		{
			return numer;
		}
		else
		{
			cout << "Wprowadzono blednie numer telefonu!!!" << endl;
			cout << "Nr. telefonu: ";
			cin >> numer;
		}
	}
}

//done
string AdminDAO::walidacjaMail(string mail)
{
	int kropka = 0;
	int malpa = 0;
	int zapamietajMalpe;
	int zapamietajKropke;
	int blad = 0;

	while (1)
	{
		kropka = 0;
		malpa = 0;
		if (mail.length() >= 6)
		{
			for (int i = 0; i < mail.length(); i++)
			{
				if(mail[i] == 64)
					malpa = 1;

				if (mail[i] == '.')
					kropka = 1;

			}
		}
		else
		{
			blad = 1;
		}

		if (malpa == 1 && kropka == 1)
			return mail;
		else
		{
			blad = 1;
		}

		if (blad == 1)
		{
			cout << "Wprowadzono blednie mail!!!"<<endl;
			cout << "Mail: ";
			cin >> mail;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//done
void AdminDAO::edytuj_konto()
{
	MYSQL mysql;
	stringstream zapytanie;

	HANDLE kolor; //uchwyt do koloru

	string haslo;
	int hasloHASH;
	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	//////////////////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	cout << "Podaj nowe haslo: ";
	cin >> haslo;
	hasloHASH = hashValue(haslo);
	////////////////////////////////////laczenie z BD/////////////////////////////////////////////////////////////

	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	stringstream().swap(zapytanie);
	zapytanie << "UPDATE LOGOWANIE SET HASLO = '" << hasloHASH << "' WHERE ID_KLIENTA = 1";
	mysql_query(&mysql, zapytanie.str().c_str());

	cout << "Haslo zostalo zmienione!!!" << endl;
	system("Pause");
}

//done
void AdminDAO::dodaj_klienta()
{
	string imie;
	string nazwisko;
	string miasto;
	string adres;
	string kod_pocztowy;
	string login;
	string haslo;
	string nr_telefonu;
	string mail;

	MYSQL mysql;
	stringstream zapytanie;


	int i;
	int hasloHASH; //wynik hashowania hasla

	HANDLE kolor; //uchwyt do koloru

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	/////////////////////////////////////////pobranie danych//////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "DODAWANIE NOWEGO UZYTKOWNIKA " << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	cout << "Imie: ";
	cin >> imie;
	cout << "Nazwisko: ";
	cin >> nazwisko;

	getchar();
	cout << "Miasto: ";
	getline(cin, miasto);

	cout << "Adres: ";
	getline(cin, adres);

	cout << "Kod pocztowy: ";
	cin >> kod_pocztowy;
	if (kod_pocztowy != "")
	{
		kod_pocztowy = walidacjaKodPocztowy(kod_pocztowy);
	}

	getchar();
	cout << "Nr.telefonu: ";
	getline(cin, nr_telefonu);

	if (nr_telefonu != "")
	{
		nr_telefonu = walidacjaNrTel(nr_telefonu);
	}

	cout << "Mail: ";
	getline(cin, mail);

	if (mail != "")
	{
		mail = walidacjaMail(mail);
	}

	cout << "Login: ";
	cin >> login;

	cout << "Haslo: ";
	cin >> haslo;

	hasloHASH = hashValue(haslo);

	system("cls");

	/////////////////////////////////////////laczenie z BD////////////////////////////////////

	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	stringstream().swap(zapytanie);
	zapytanie << "INSERT INTO LOGOWANIE (LOGIN, HASLO, TYP_KONTA)VALUE ('" << login << "','" << hasloHASH << "', 'klient');";
	mysql_query(&mysql, zapytanie.str().c_str());

	stringstream().swap(zapytanie);
	zapytanie << "INSERT INTO KLIENT (IMIE,NAZWISKO,MIASTO,ADRES,KOD_POCZTOWY,NR_TELEFONU,MAIL) VALUE ('" << imie << "','" << nazwisko << "','" << miasto << "','" << adres << "','" << kod_pocztowy << "', '" << nr_telefonu << "', '" << mail << "');";
	mysql_query(&mysql, zapytanie.str().c_str());


	cout << "Uzytkownik zostal dodany!!!" << endl;
	system("Pause");

	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void AdminDAO::usun_klienta()
{
	HANDLE kolor; //uchwyt do koloru
	string imie;
	string nazwisko;
	string ID;

	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	int i;
	int konto_istnieje = 0; //sprawdza czy takie konto wgl istnieje
							
	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	//////////////////wyswietlenie daty i godziny///////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	/////////////////////////////pobranie danych///////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "USUWANIE UZYTKOWNIKA " << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	cout << "Imie: ";
	cin >> imie;
	cout << "Nazwisko: ";
	cin >> nazwisko;

	///////////////////laczenie z BD///////////////////////////////////////////////////////////

	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	////////////////////////WYSWIETLENIE LISTY OSOB O TAKIM IMIENIU I NAZWISKU////////////////////
	
	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM KLIENT WHERE IMIE = '" << imie << "' AND NAZWISKO = '" << nazwisko << "';";
	mysql_query(&mysql, zapytanie.str().c_str());

	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		konto_istnieje = 1;
		cout << wiersz[0] << " " << wiersz[1] << " " << wiersz[2] << " " << wiersz[3] << " " << wiersz[4] << " " << wiersz[5] << " " << wiersz[6] << " " << wiersz[7] << endl;
	}


	if (konto_istnieje == 0)
	{
		cout << "Podany pacjent nie znajduje sie w bazie danych!!!" << endl;
		system("Pause");
	}
	else
	{
		cout << endl;
		cout << "Podaj ID wybranej osoby: ";
		cin >> ID;

		system("cls");

		/////////////////////////////////////////USUWANIE Z BD////////////////////////////////////////

		stringstream().swap(zapytanie);
		zapytanie << "DELETE FROM KLIENT WHERE ID_KLIENTA = '" << ID << "';";
		mysql_query(&mysql, zapytanie.str().c_str());

		stringstream().swap(zapytanie);
		zapytanie << "DELETE FROM LOGOWANIE WHERE ID_KLIENTA = '" << stoi(ID)+1 << "';";
		mysql_query(&mysql, zapytanie.str().c_str());

		cout << "Uzytkownik zostal usuniety!!!" << endl;
		system("Pause");
	}
	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void AdminDAO::wyswietl_klientow()
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	HANDLE kolor; //uchwyt do koloru

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");
	//////////////////wyswietlenie daty i godziny///////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	///////////////////////////////////////TYTUL///////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "Lista klientow: " << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

	////////////////////////WYSWIETLENIE LISTY PACJENTOW////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM KLIENT;";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
		cout << wiersz[0] << " " << wiersz[1] << " " << wiersz[2] << " " << wiersz[3] << " " << wiersz[4] << " " << wiersz[5] << endl;

	system("Pause");
	system("cls");
	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void AdminDAO::wysw_zamowienia()
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string pesel;

	HANDLE kolor; //uchwyt do koloru

	 //ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	//////////////////wyswietlenie daty i godziny///////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;


	int i;

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	///////////////////////////////////////TYTUL///////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "Lista zamowien: " << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);


	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM ZAMOWIENIA WHERE STAT_ZAMOWIENIA <> 'ZAKONCZONE';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)	
		cout << wiersz[0] << " " << wiersz[1] << " " << wiersz[2] << " " << wiersz[3] << " " << endl;
			
	system("Pause");
	system("cls");
	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void AdminDAO::anuluj_zamowienie()
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	int ilosc_zam = 0;

	string nr_zamowienia;
	int zam_istnieje = 0;

	HANDLE kolor; //uchwyt do koloru
	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	//////////////////wyswietlenie daty i godziny///////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	////////////////////////WYSWIETLENIE LISTY ZAMOWIEN//////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "LISTA ZAMOWIEN:" << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM ZAMOWIENIA WHERE STAT_ZAMOWIENIA <> 'ZAKONCZONE';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_zam = 1;
		cout << wiersz[0] << " " << wiersz[1] << " " << wiersz[2] << " " << endl;
	}

	cout << endl;

	if (ilosc_zam == 1)
	{
		///////////////////////////////////////////////////////////////////////////////////////
		SetConsoleTextAttribute(kolor, FOREGROUND_RED);
		cout << "ANULOWANIE ZAMOWIENIA" << endl;

		SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
		cout << "Nr. zamowienia: ";
		cin >> nr_zamowienia;

		////////////////////////////SPRAWDZENIE CZY KONTO JUZ ISTNIEJE////////////////////////////
		stringstream().swap(zapytanie);
		zapytanie << "SELECT NR_ZAMOWIENIA FROM ZAMOWIENIA WHERE NR_ZAMOWIENIA = " << nr_zamowienia << " AND STAT_ZAMOWIENIA <> 'ZAKONCZONE';";
		mysql_query(&mysql, zapytanie.str().c_str());
		idZapytania = mysql_store_result(&mysql);

		while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
		{
			zam_istnieje = 1;
		}
		////////////////////////////////////////////////////////////////////////////////////////////
		if (zam_istnieje == 1)
		{
			stringstream().swap(zapytanie);
			zapytanie << "DELETE FROM ZAMOWIENIA WHERE NR_ZAMOWIENIA = '" << nr_zamowienia << "';";
			mysql_query(&mysql, zapytanie.str().c_str());

			system("cls");
			cout << "Zamowienie anulowane!" << endl;
			system("Pause");
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		else
		{
			system("cls");
			cout << "Podane zamowienie nie znajduje sie w systemie!!!" << endl;
			system("Pause");
		}
	}
	else
	{
		system("cls");
		cout << "Brak zamowien!!!" << endl;
		system("Pause");
	}
}

//done
void AdminDAO::zmien_status_zamowienia()
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string nr_zamowienia;
	string info = "";
	string status;

	int ilosc_zam = 0;

	HANDLE kolor; //uchwyt do koloru

	int wizyta_istnieje = 0; //sprawdza czy takie konto juz jest w BD

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	///////////////////////////////////////TYTUL///////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "Lista zamowien: " << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);

	////////////////////////WYSWIETLENIE LISTY ////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM ZAMOWIENIA WHERE STAT_ZAMOWIENIA <> 'ZAKONCZONE';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_zam = 1;
		cout << wiersz[0] << " " << wiersz[1] << " " << wiersz[2] << " " << wiersz[3] << endl;
		cout << endl;
	}

	if (ilosc_zam == 1)
	{
		cout << endl;
		SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

		cout << "Nr zamowienia: ";
		cin >> nr_zamowienia;

		////////////////////////////SPRAWDZENIE CZY KONTO ISTNIEJE////////////////////////////
		stringstream().swap(zapytanie);
		zapytanie << "SELECT * FROM ZAMOWIENIA WHERE NR_ZAMOWIENIA = '" << nr_zamowienia << "';";
		mysql_query(&mysql, zapytanie.str().c_str());
		idZapytania = mysql_store_result(&mysql);

		while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
		{
			wizyta_istnieje = 1;
		}


		if (wizyta_istnieje == 1) ///////////////////////GDY ISTNIEJE////////////////////////////////////////
		{
			system("cls");
			/////////////////////////////////////////pobranie danych//////////////////////////////////////////
			SetConsoleTextAttribute(kolor, FOREGROUND_RED);
			cout << "ZMIANA STATUSU ZAMOWIENIA" << endl;
			SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

			cout << "Status zamowienia (REALIZOWANE/ZAKONCZONE): ";
			cin >> status;

			stringstream().swap(zapytanie);
			zapytanie << "UPDATE ZAMOWIENIA SET STAT_ZAMOWIENIA = '" << status << "' WHERE NR_ZAMOWIENIA = " << nr_zamowienia << ";";
			mysql_query(&mysql, zapytanie.str().c_str());

			cout << "Status zamowienia zostal zmieniony!!!" << endl;
			system("Pause");

		}
		else
		{
			system("cls");
			cout << "Podane zamowienie nie znajduje sie w bazie danych!!!" << endl;
			system("Pause");
			system("cls");
		}
	}
	else
	{
		system("cls");
		cout << "Brak zamowien!!!" << endl;
		system("Pause");
	}

	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void AdminDAO::historia_zamowien()
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string pesel;

	HANDLE kolor; //uchwyt do koloru

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	//////////////////wyswietlenie daty i godziny///////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;


	int i;

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	///////////////////////////////////////TYTUL///////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "HISTORIA ZAMOWIEN: " << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);


	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM ZAMOWIENIA WHERE STAT_ZAMOWIENIA = 'ZAKONCZONE';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
		cout << wiersz[0] << " " << wiersz[1] << " " << wiersz[2] << " " << endl;

	system("Pause");
	system("cls");
	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void AdminDAO::ilosc_zak_rel_zle ()
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string ilosc_zle;
	string ilosc_wyk;
	string ilosc_rel;

	HANDLE kolor; //uchwyt do koloru

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	////////////////////////////////////////////////////////////////////////////////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(NR_ZAMOWIENIA) FROM ZAMOWIENIA WHERE STAT_ZAMOWIENIA = 'REALIZOWANE';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_rel = wiersz[0];
	}

	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(NR_ZAMOWIENIA) FROM ZAMOWIENIA WHERE STAT_ZAMOWIENIA = 'ZAKONCZONE';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_wyk = wiersz[0];
	}

	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(NR_ZAMOWIENIA) FROM ZAMOWIENIA WHERE STAT_ZAMOWIENIA = 'DO ZATWIERDZENIA';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_zle = wiersz[0];
	}

	cout << "Ilosc zleconych: " << ilosc_zle << endl;
	cout << "Ilosc realizowanych: " << ilosc_rel << endl;
	cout << "Ilosc zakonczonych: " << ilosc_wyk << endl;
	system("Pause");

	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void AdminDAO::ilosc_klientow()
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string ilosc_klientow;

	HANDLE kolor; //uchwyt do koloru

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: admin\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	////////////////////////////////////////////////////////////////////////////////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(*) FROM KLIENT;";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_klientow = wiersz[0];
	}

	cout << endl;

	cout << "Ilosc klientow: " << ilosc_klientow << endl;
	system("Pause");

	mysql_close(&mysql); // zamknij po³¹czenie
}
