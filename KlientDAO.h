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
	int walidacjaNrTel(int); //done
	string walidacjaMail(string); //done
public:
	void edytuj_konto(Osoba osoba); //done
	void zloz_zamowienie(Osoba osoba); //done
	void wysw_zamowienia(Osoba osoba); //done
	void anuluj_zamowienie(Osoba osoba); //done
	void historia_zamowien(Osoba osoba); //done
	void ilosc_zak_rel_zle(Osoba osoba); //done
};
