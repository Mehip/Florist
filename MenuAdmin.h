#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Menu.h"
#include "Osoba.h"

using namespace std;


class MenuAdmin :public Menu
{
public:
	int menu(Osoba);
};
