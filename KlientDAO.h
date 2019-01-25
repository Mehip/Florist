#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>

#include "Klient.h"

using namespace std;


class  KlientDAO
{
	unsigned int hashValue(string); //done
	string walidacjaKodPocztowy(string); //done
	string walidacjaNrTel(string); //done
	string walidacjaMail(string); //done
public:
	void edytuj_konto(); //done
	void dodaj_klienta();
	void wyswietl_klientow();
	void usun_klienta();
	void zloz_zamowienie();
	void wysw_zamowienia();
	void anuluj_zamowienie();
	void zmien_status_zamowienia();
	void wysw_opis_zamowienia();
	void ilosc_pac_lek();
	void ilosc_wiz_nfz_pryw();
	void ilosc_wyk_nwyk();
};
