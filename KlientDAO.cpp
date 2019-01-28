#include "stdafx.h"
#include <mysql.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>

#include "KlientDAO.h"
#include "Klient.h"
#include "Osoba.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13

//done
unsigned int KlientDAO::hashValue(string key) //funkcja hashujaca
{
	unsigned int val = 0;
	for (int i = 0; i < key.length(); i++) {
		val += (unsigned int)(key[i]); // cast each character of key to unsigned int
	}
	return val;                        // return the sum over all characters in key
}

//done
string KlientDAO::walidacjaKodPocztowy(string kod)
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
string KlientDAO::walidacjaNrTel(string numer)
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
string KlientDAO::walidacjaMail(string mail)
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
				if (mail[i] == 64)
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
			cout << "Wprowadzono blednie mail!!!" << endl;
			cout << "Mail: ";
			cin >> mail;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//done
void KlientDAO::edytuj_konto(Osoba osoba)
{
	MYSQL mysql;
	stringstream zapytanie;

	HANDLE kolor; //uchwyt do koloru

	string imie;
	string nazwisko;
	string miasto;
	string adres;
	string kod_pocztowy;
	string login;
	string haslo;
	string nr_telefonu;
	string mail;

	int hasloHASH;
	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	//////////////////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

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
	////////////////////////////////////laczenie z BD/////////////////////////////////////////////////////////////

	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	stringstream().swap(zapytanie);
	zapytanie << "UPDATE LOGOWANIE SET HASLO = '" << hasloHASH << "', LOGIN = '" << login << "' WHERE ID_KLIENTA = " << osoba.id << ";";
	mysql_query(&mysql, zapytanie.str().c_str());
	stringstream().swap(zapytanie);
	zapytanie << "UPDATE KLIENT SET IMIE = '" << imie << "', nazwisko = '" << nazwisko << "', MIASTO = '" << miasto << "', ADRES = '" << adres << "', KOD_POCZTOWY = '" << kod_pocztowy << "', NR_TELEFONU = '" << nr_telefonu << "', mail = '" << mail << "' WHERE " << osoba.id << ";";
	mysql_query(&mysql, zapytanie.str().c_str());

	cout << "Dane zosta³y zmienione!!!" << endl;
	system("Pause");
}

//done
void KlientDAO::zloz_zamowienie(Osoba osoba)
{
	string ID;
	string zamowienie = "";
	int konto_istnieje_klient = 0;

	MYSQL mysql;
	stringstream zapytanie;

	HANDLE kolor; //uchwyt do koloru
	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	//////////////////wyswietlenie daty i godziny///////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: "<< osoba.login << "\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	///////////////////////////////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	cout << "SKLADANIE ZAMOWIENIA" << endl;

	cout << "Wprowadz opis (po zakonczeniu nacisnij `): " << endl;;

	char znak;

	while ((znak = getchar()) != 96)
	{
		zamowienie += znak;
	};

	stringstream().swap(zapytanie);
	zapytanie << "INSERT INTO ZAMOWIENIA (ID_KLIENTA, STAT_ZAMOWIENIA, OPIS) VALUE ('" << stoi(osoba.id)-1 << "', 'DO ZATWIERDZENIA','" << zamowienie << "');";
	mysql_query(&mysql, zapytanie.str().c_str());

	cout << endl << "Dodano zamowienie." << endl;
	system("Pause");
	system("cls");
	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void KlientDAO::wysw_zamowienia(Osoba osoba)
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
	cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;


	int i;

	//ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	///////////////////////////////////////TYTUL///////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "ZAMOWIENIA: " << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);


	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM ZAMOWIENIA WHERE ID_KLIENTA = '" << stoi(osoba.id)-1 << "' AND STAT_ZAMOWIENIA <> 'ZAKONCZONE';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		cout << wiersz[0] << " " << wiersz[2] << " " << wiersz[3] << endl;
		cout << endl;
	}

	system("Pause");
	system("cls");
	mysql_close(&mysql); // zamknij po³¹czenie
}

//done
void KlientDAO::anuluj_zamowienie(Osoba osoba)
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string nr_zamowienia;
	int zam_istnieje = 0;

	HANDLE kolor; //uchwyt do koloru

	system("cls");

	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "kwiaciarnia", 0, NULL, 0);
	mysql_select_db(&mysql, "kwiaciarnia");

	//////////////////wyswietlenie daty i godziny///////////////////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	////////////////////////WYSWIETLENIE LISTY ZAMOWIEN//////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM ZAMOWIENIA;";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		cout << wiersz[0] << " " << wiersz[1] << " " << wiersz[2] << " " << endl;
	}

	cout << endl;
	///////////////////////////////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "ANULOWANIE ZAMOWIENIA" << endl;

	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	cout << "Nr. zamowienia: ";
	cin >> nr_zamowienia;

	////////////////////////////SPRAWDZENIE CZY KONTO JUZ ISTNIEJE////////////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT NR_ZAMOWIENIA FROM ZAMOWIENIA WHERE NR_ZAMOWIENIA = '" << nr_zamowienia << "';";
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

//done
void KlientDAO::historia_zamowien(Osoba osoba)
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string nr_zamowienia;

	int i;
	int hasloHASH; //wynik hashowania hasla
	int wizyta_istnieje = 0; //sprawdza czy takie konto juz jest w BD

	HANDLE kolor; //uchwyt do koloru

				  //ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	///////////////////////////////////////TYTUL///////////////////////////////////////////////
	SetConsoleTextAttribute(kolor, FOREGROUND_RED);
	cout << "Lista wizyt: " << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);

	////////////////////////WYSWIETLENIE LISTY PACJENTOW////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT * FROM ZAMOWIENIA;";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		cout << wiersz[0] << " " << wiersz[1] << " " << wiersz[2] << endl;
	}

	cout << endl;
	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);

	cout << "Nr. zamowienia: ";
	cin >> nr_zamowienia;

	////////////////////////////SPRAWDZENIE CZY KONTO ISTNIEJE////////////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT NR_ZAMOWIENIA FROM ZAMOWIENIA WHERE NR_ZAMOWIENIA = '" << nr_zamowienia << "';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		wizyta_istnieje = 1;
	}


	if (wizyta_istnieje == 1) ///////////////////////GDY KONTO ISTNIEJE////////////////////////////////////////
	{
		system("cls");
		cout << "OPIS WIZYTY: " << endl << endl;
		stringstream().swap(zapytanie);
		zapytanie << "SELECT OPIS FROM ZAMOWIENIA WHERE NR_ZAMOWIENIA = '" << nr_zamowienia << "';";
		mysql_query(&mysql, zapytanie.str().c_str());
		idZapytania = mysql_store_result(&mysql);

		while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
		{
			cout << wiersz[0] << endl;
		}

		system("Pause");
	}
	else
	{
		cout << "Podana wizyta nie znajduje sie w bazie danych!!!" << endl;
		system("Pause");
		system("cls");
	}

	mysql_close(&mysql); // zamknij po³¹czenie
}


void KlientDAO::ilosc_pac_lek(Osoba osoba)
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string ilosc_pac;
	string ilosc_lek;
	int pac_ilosc;
	int lek_ilosc;

	HANDLE kolor; //uchwyt do koloru

				  //ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "przychodnie", 0, NULL, 0);
	mysql_select_db(&mysql, "przychodnie");

	////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	////////////////////////////////////////////////////////////////////////////////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(PESEL) FROM LEKARZ;";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_lek = wiersz[0];
	}

	cout << endl;

	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(PESEL) FROM PACJENT;";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_pac = wiersz[0];
	}

	cout << endl;

	pac_ilosc = stoi(ilosc_pac);
	lek_ilosc = stoi(ilosc_lek);

	cout << "Ilosc lekarzy: " << lek_ilosc << endl;
	cout << "Ilosc pacjentow: " << pac_ilosc << endl;
	cout << "Ilosc pacjentow na jednego lekarza: " << pac_ilosc / lek_ilosc << endl;
	system("Pause");

	mysql_close(&mysql); // zamknij po³¹czenie
}


void KlientDAO::ilosc_wiz_nfz_pryw(Osoba osoba)
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string ilosc_nfz;
	string ilosc_pryw;
	int nfz;
	int pryw;

	HANDLE kolor; //uchwyt do koloru

				  //ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "przychodnie", 0, NULL, 0);
	mysql_select_db(&mysql, "przychodnie");

	////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	////////////////////////////////////////////////////////////////////////////////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(NR_WIZYTY) FROM WIZYTY WHERE TYP_WIZYTY = 'nfz';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_nfz = wiersz[0];
	}

	cout << endl;

	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(NR_WIZYTY) FROM WIZYTY WHERE TYP_WIZYTY = 'prywatna';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_pryw = wiersz[0];
	}

	cout << endl;

	nfz = stoi(ilosc_nfz);
	pryw = stoi(ilosc_pryw);

	cout << "Ilosc wizyt nfz: " << nfz << endl;
	cout << "Ilosc wizyt prywatnych: " << pryw << endl;
	system("Pause");

	mysql_close(&mysql); // zamknij po³¹czenie
}


void KlientDAO::ilosc_wyk_nwyk(Osoba osoba)
{
	MYSQL mysql;
	MYSQL_RES *idZapytania;
	MYSQL_ROW  wiersz;
	stringstream zapytanie;

	string ilosc_wyk;
	string ilosc_nwyk;
	int wyk;
	int nwyk;

	HANDLE kolor; //uchwyt do koloru

				  //ustawienie koloru
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");

	///////////////////laczenie z BD///////////////////////////////////////////////////////////
	mysql_init(&mysql); // incjalizacja
	mysql_real_connect(&mysql, "127.0.0.1", "root", "maciek", "przychodnie", 0, NULL, 0);
	mysql_select_db(&mysql, "przychodnie");

	////////////////////////////////////wyswietlenie daty i godziny///////////////////////////////////
	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	SetConsoleTextAttribute(kolor, FOREGROUND_BLUE);
	cout << "Zalogowano jako: " << osoba.login << "\t\t\t\t\t\t\t\t\t\t";
	cout << SystemTime.wHour << ":" << SystemTime.wMinute << "\t" << SystemTime.wYear << "/" << SystemTime.wDay << "/" << SystemTime.wMonth << endl;
	cout << endl;

	SetConsoleTextAttribute(kolor, FOREGROUND_GREEN);
	////////////////////////////////////////////////////////////////////////////////////////////////
	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(NR_WIZYTY) FROM WIZYTY WHERE STATUS_WIZ = 'Wykonana';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_wyk = wiersz[0];
	}

	cout << endl;

	stringstream().swap(zapytanie);
	zapytanie << "SELECT COUNT(NR_WIZYTY) FROM WIZYTY WHERE STATUS_WIZ = 'Wykonana';";
	mysql_query(&mysql, zapytanie.str().c_str());
	idZapytania = mysql_store_result(&mysql);

	while ((wiersz = mysql_fetch_row(idZapytania)) != NULL)
	{
		ilosc_nwyk = wiersz[0];
	}

	cout << endl;

	wyk = stoi(ilosc_wyk);
	nwyk = stoi(ilosc_nwyk);

	cout << "Ilosc wizyt wykonanych: " << wyk << endl;
	cout << "Ilosc wizyt niewykonanych: " << nwyk << endl;
	cout << "Stosunek wizyt wykonanych do niewykonanych: " << wyk / nwyk << endl;
	system("Pause");

	mysql_close(&mysql); // zamknij po³¹czenie
}