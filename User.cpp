#include "pch.h"
#include "User.h"

int User::level;
int User::health;
int User::mana;
int User::damage;

void User::setItem(int num)
{
	if(num == 1)
	{
		level = 1;
		health = 150;
		damage = 10;
		mana = 50;
	}
	else if(num == 2)
	{
		level = 2;
		health = 350;
		damage = 35;
		mana = 100;
	}
	else if(num == 3)
	{
		level = 3;
		health = 700;
		damage = 60;
		mana = 200;
	}
	else if(num == 4)
	{
		level = 4;
		health = 1200;
		damage = 100;
		mana = 200;
	}
	else if(num == 5)
	{
		level = 5;
		health = 2000;
		damage = 200;
		mana = 250;
	}
}
