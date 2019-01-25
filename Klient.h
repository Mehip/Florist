#pragma once


#include "stdafx.h"
#include <iostream>
#include <string>
#include "Osoba.h"

using namespace std;


class Klient :public Osoba
{
	string login;

public:
	friend class MenuKlient;
	Klient(string);
};
