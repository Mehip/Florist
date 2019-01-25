#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


class Osoba
{
	string login;

public:
	friend class MenuAdmin;
	friend class MenuKlient;

	Osoba(string login)
	{
		this->login = login;
	}
};
