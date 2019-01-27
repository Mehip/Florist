#include "stdafx.h"
#include "Admin.h"

Admin::Admin(string login, string id) :Osoba(login,id)
{
	this->login = login;
	this->id = id;
}