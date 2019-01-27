#pragma once


#include "stdafx.h"
#include <iostream>
#include <string>
#include "Osoba.h"

using namespace std;


class Klient :public Osoba
{
	string login;
	string id;

public:
	friend class MenuKlient;
	Klient(string, string);
};
