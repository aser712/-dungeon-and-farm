#pragma once
//#include "Dungeon.h"
//#include "User.h"
#include "resource.h"
#include "pch.h"

class Monster
{
public:
	BITMAP bmp;
	CBitmap bitmap;
	int health;
	int damage;
	static int size_W;
	static int size_H;
	static CRect rect;
	static int size;

	static void set(CRect& in)
	{
		rect = in;
		size = in.Height() / 14 * 12 / 15;
		size_W = size * 25;
		size_H = size * 15;
	}

	Monster(int health, int damage, int bitmapID)
	{
		this->health = health;
		this->damage = damage;
		bitmap.LoadBitmap(bitmapID);

		bitmap.GetBitmap(&bmp);
	}

	void render(CDC* memdc);
};

class Monster_1_1 : public Monster
{
public:
	Monster_1_1() : Monster(20, 5, IDB_1_1)
	{}
};

class Monster_1_2 : public Monster
{
public:
	Monster_1_2() : Monster(30, 7, IDB_1_2)
	{}
};

class Monster_1_3 : public Monster
{
public:
	Monster_1_3() : Monster(40, 9, IDB_1_3)
	{}
};

class Monster_1_4 : public Monster
{
public:
	Monster_1_4() : Monster(50, 11, IDB_1_4)
	{}
};

class Monster_1_5 : public Monster
{
public:
	Monster_1_5() : Monster(60, 13, IDB_1_5)
	{}
};

class Monster_2_1 : public Monster
{
public:
	Monster_2_1() : Monster(75, 20, IDB_2_1)
	{}
};

class Monster_2_2 : public Monster
{
public:
	Monster_2_2() : Monster(120, 30, IDB_2_2)
	{}
};

class Monster_2_3 : public Monster
{
public:
	Monster_2_3() : Monster(150, 20, IDB_2_3)
	{}
};

class Monster_2_4 : public Monster
{
public:
	Monster_2_4() : Monster(175, 25, IDB_2_4)
	{}
};

class Monster_2_5 : public Monster  //아누비스
{
public:
	Monster_2_5() : Monster(400, 40, IDB_2_5)
	{}
};

class Monster_3_1 : public Monster
{
public:
	Monster_3_1() : Monster(130, 35, IDB_3_1)
	{}
};

class Monster_3_2 : public Monster
{
public:
	Monster_3_2() : Monster(180, 50, IDB_3_2)
	{}
};

class Monster_3_3 : public Monster
{
public:
	Monster_3_3() : Monster(210, 70, IDB_3_3)
	{}
};

class Monster_3_4 : public Monster
{
public:
	Monster_3_4() : Monster(280, 90, IDB_3_4)
	{}
};

class Monster_3_5 : public Monster
{
public:
	Monster_3_5() : Monster(850, 130, IDB_3_5) // 코모도 도마뱀
	{}
};

class Monster_4_1 : public Monster
{
public:
	Monster_4_1() : Monster(200, 70, IDB_4_1)
	{}
};

class Monster_4_2 : public Monster
{
public:
	Monster_4_2() : Monster(300, 80, IDB_4_2)
	{}
};

class Monster_4_3 : public Monster
{
public:
	Monster_4_3() : Monster(400, 90, IDB_4_3)
	{}
};

class Monster_4_4 : public Monster
{
public:
	Monster_4_4() : Monster(500, 100, IDB_4_4)
	{}
};

class Monster_4_5 : public Monster
{
public:
	Monster_4_5() : Monster(1300, 230, IDB_4_5) //펌킹
	{}
};

class Monster_5_1 : public Monster
{
public:
	Monster_5_1() : Monster(500, 90, IDB_5_1)
	{}
};

class Monster_5_2 : public Monster
{
public:
	Monster_5_2() : Monster(700, 110, IDB_5_2)
	{}
};

class Monster_5_3 : public Monster
{
public:
	Monster_5_3() : Monster(900, 110, IDB_5_3)
	{}
};

class Monster_5_4 : public Monster
{
public:
	Monster_5_4() : Monster(1300, 220, IDB_5_4)
	{}
};

class Monster_5_5 : public Monster
{
public:
	Monster_5_5() : Monster(3000, 400, IDB_5_5)
	{}
};
class Monster_5_6 : public Monster
{
public:
	Monster_5_6() : Monster(1, 1, IDB_5_1)
	{}
};