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
	void edytuj_konto(Osoba osoba); //done
	void zloz_zamowienie(Osoba osoba);
	void wysw_zamowienia(Osoba osoba);
	void anuluj_zamowienie(Osoba osoba);
	void historia_zamowien(Osoba osoba);
	void ilosc_pac_lek(Osoba osoba);
	void ilosc_wiz_nfz_pryw(Osoba osoba);
	void ilosc_wyk_nwyk(Osoba osoba);
};
