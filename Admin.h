#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Osoba.h"

using namespace std;


class Admin :public Osoba
{
	string login;

public:
	friend class MenuAdmin;
	Admin(string);
};
