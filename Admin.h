#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Osoba.h"

using namespace std;


class Admin :public Osoba
{
	string login;
	string id;

public:
	friend class MenuAdmin;
	Admin(string, string);
};
