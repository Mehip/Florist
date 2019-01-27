#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


class Osoba
{
public:
	string login;
	string id;

	friend class MenuAdmin;
	friend class MenuKlient;

	Osoba(string login, string id)
	{
		this->login = login;
		this->id = id;
	}
};
