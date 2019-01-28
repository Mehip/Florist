#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>

#include "Admin.h"

using namespace std;


class  AdminDAO
{
	unsigned int hashValue(string); //done
	string walidacjaKodPocztowy(string); //done
	string walidacjaNrTel(string); //done
	string walidacjaMail(string); //done
public:
	void edytuj_konto(); //done
	void dodaj_klienta(); //done
	void wyswietl_klientow(); //done
	void usun_klienta(); //done
	void zloz_zamowienie(); //done
	void wysw_zamowienia(); //done
	void anuluj_zamowienie(); //done
	void zmien_status_zamowienia(); //done
	void historia_zamowien(); //done
	void ilosc_zak_rel_zle(); //done
	void ilosc_klientow(); //done
};
