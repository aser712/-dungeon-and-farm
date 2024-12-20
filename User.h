#pragma once
#include "Dungeon.h"
#include "resource.h"
#include "pch.h"

class User
{
public:
	static int level;
	static int health;
	static int damage;
	static int mana;

	static void setItem(int num);
};
