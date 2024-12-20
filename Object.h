#pragma once
#include <vector>
#include "UI.h"

using namespace std;

enum TYPE
{
	WATERCAN,
	POTATO, CARROT, STRAWBERRY, SPROUTEDPOTATO, GOLDENCARROT, WATERMELON, CORN, CABBAGE, SEEDLESSWATERMELON, SWEETPOTATO, MELON, WHEAT, SPROUTEDSWEETPOTATO, 
	WHITEMELON, SPINACH, GREENONION, RADISH, RASPBERRY, SATIVUS,
	POTATOSEED, CARROTSEED, STRAWBERRYSEED, SPROUTEDPOTATOSEED, GOLDENCARROTSEED, WATERMELONSEED, CORNSEED, CABBAGESEED, SEEDLESSWATERMELONSEED, SWEETPOTATOSEED, MELONSEED, WHEATSEED, SPROUTEDSWEETPOTATOSEED, 
	WHITEMELONSEED, SPINACHSEED, GREENONIONSEED, RADISHSEED, RASPBERRYSEED, SATIVUSSEED,
	HP_POTION, MP_POTION, PANAACEA, REVIVAL,
	FERTILIZER, BOSSITEM1, BOSSITEM2, BOSSITEM3, BOSSITEM4, BOSSITEM5
};

enum TYPE2
{
	SEEDS, CROPS, POTIONS, ELSE
};

class Object
{
public:
	TYPE type;
	TYPE2 type2;
	int count;
	int price;
	SEASON season;
	CBitmap image;
	BITMAP imageInfo;
	static void swap(vector<Object*>& a, vector<Object*>& b, int inedxA, int indexB);
	virtual void draw(CDC* memdc,int x, int y, int size, int count);
	Object()
	{
		type2 = SEEDS;
	}
};

class WaterCan : public Object
{
public:
	WaterCan();
};

class PotatoSeed : public Object
{
public:
	PotatoSeed();
};
class CarrotSeed : public Object
{
public:
	CarrotSeed();
};
class StrawberrySeed : public Object
{
public:
	StrawberrySeed();
};
class SproutedPotatoSeed : public Object
{
public:
	SproutedPotatoSeed();
};
class GoldenCarrotSeed : public Object
{
public:
	GoldenCarrotSeed();
};

class WaterMelonSeed : public Object
{
public:
	WaterMelonSeed();
};
class CornSeed : public Object
{
public:
	CornSeed();
};
class CabbageSeed : public Object
{
public:
	CabbageSeed();
};
class SeedlessWatermelonSeed : public Object
{
public:
	SeedlessWatermelonSeed();
};

class SweetPotatoSeed : public Object
{
public:
	SweetPotatoSeed();
};
class MelonSeed : public Object
{
public:
	MelonSeed();
};
class WheatSeed : public Object
{
public:
	WheatSeed();
};
class SproutedSweetPotatoSeed : public Object
{
public:
	SproutedSweetPotatoSeed();
};
class WhiteMelonSeed : public Object
{
public:
	WhiteMelonSeed();
};


class SpinachSeed : public Object
{
public:
	SpinachSeed();
};
class GreenOnionSeed : public Object
{
public:
	GreenOnionSeed();
};
class RadishSeed : public Object
{
public:
	RadishSeed();
};
class RaspberrySeed : public Object
{
public:
	RaspberrySeed();
};
class SativusSeed : public Object
{
public:
	SativusSeed();
};



class Potato : public Object
{
public:
	Potato();
};
class Carrot : public Object
{
public:
	Carrot();
};
class Strawberry : public Object
{
public:
	Strawberry();
};
class SproutedPotato : public Object
{
public:
	SproutedPotato();
};
class GoldenCarrot : public Object
{
public:
	GoldenCarrot();
};

class WaterMelon : public Object
{
public:
	WaterMelon();
};
class Corn : public Object
{
public:
	Corn();
};
class Cabbage : public Object
{
public:
	Cabbage();
};
class SeedlessWatermelon : public Object
{
public:
	SeedlessWatermelon();
};

class SweetPotato : public Object
{
public:
	SweetPotato();
};
class Melon : public Object
{
public:
	Melon();
};
class Wheat : public Object
{
public:
	Wheat();
};
class SproutedSweetPotato : public Object
{
public:
	SproutedSweetPotato();
};
class WhiteMelon : public Object
{
public:
	WhiteMelon();
};

class Spinach : public Object
{
public:
	Spinach();
};
class GreenOnion : public Object
{
public:
	GreenOnion();
};
class Radish : public Object
{
public:
	Radish();
};
class Raspberry : public Object
{
public:
	Raspberry();
};
class Sativus : public Object
{
public:
	Sativus();
};




class HPPotion : public Object
{
public:
	HPPotion();
};
class MPPotion : public Object
{
public:
	MPPotion();
};
class Panaacea : public Object
{
public:
	Panaacea();
};
class Revival : public Object
{
public:
	Revival();
};

class Fertilizer : public Object
{
public:
	Fertilizer();
};
class BossItem1 : public Object
{
public:
	BossItem1();
};
class BossItem2 : public Object
{
public:
	BossItem2();
};
class BossItem3 : public Object
{
public:
	BossItem3();
};
class BossItem4 : public Object
{
public:
	BossItem4();
};
class BossItem5 : public Object
{
public:
	BossItem5();
};