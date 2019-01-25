#pragma once

#include "stdafx.h"
#include <iostream>
#include "Osoba.h"

using namespace std;


class Menu
{
public:
	virtual int menu(Osoba) = 0;
};
