#include "pch.h"
#include "Object.h"
#include "resource.h"
#include <time.h>
#include <Windows.h>

void Object::swap(vector<Object*> &a, vector<Object*> &b, int indexA, int indexB)
{
	if(&a[indexA] == &b[indexB])
		return;
	if(a[indexA] != NULL && b[indexB] != NULL && a[indexA]->type == b[indexB]->type)
	{
		b[indexB]->count += a[indexA]->count;
		delete(a[indexA]);
		a[indexA] = NULL;

		return;
	}
	Object* temp = a[indexA];
	a[indexA] = b[indexB];
	b[indexB] = temp;
}
void Object::draw(CDC* memdc, int x, int y, int size, int count)
{
	CDC temp;
	CDC imageDC;
	imageDC.CreateCompatibleDC(memdc);
	imageDC.SelectObject(&image);
	temp.CreateCompatibleDC(&imageDC);
	CBitmap tempBitmap;
	tempBitmap.CreateCompatibleBitmap(&imageDC, imageInfo.bmWidth, imageInfo.bmHeight);
	temp.SelectObject(&tempBitmap);
	temp.BitBlt(0, 0, imageInfo.bmWidth, imageInfo.bmHeight, &imageDC, 0, 0, SRCCOPY);




	memdc->StretchBlt(x + size * 0.07, y + size * 0.07, size * 0.86, size * 0.86, &temp, 0, 0, imageInfo.bmWidth, imageInfo.bmHeight, SRCCOPY);
	if(count != 0)
	{
		CString str;
		str.Format(_T("%d"), count);
		CFont font;
		font.CreatePointFont(size, _T("배달의민족 주아"));
		memdc->SelectObject(font);
		memdc->SetTextColor(RGB(0, 0, 0));
		memdc->SetBkMode(OPAQUE);
		memdc->TextOut(x + size * 0.05, y + size * 0.05, str);
	}
	memdc->SelectStockObject(WHITE_BRUSH);
}


WaterCan::WaterCan()
{
	type = WATERCAN;
	count = 0;
	price = 0;
	image.LoadBitmap(IDB_WaterCan);
	image.GetBitmap(&imageInfo);
}


PotatoSeed::PotatoSeed()
{
	type = POTATOSEED;
	price = 400;
	season = SPRING;
	count = 5;
	image.LoadBitmap(IDB_Potato_Seed);
	image.GetBitmap(&imageInfo);
}
CarrotSeed::CarrotSeed()
{
	type = CARROTSEED;
	price = 300;
	season = SPRING;
	count = 5;
	image.LoadBitmap(IDB_Carrot_Seed);
	image.GetBitmap(&imageInfo);
}
StrawberrySeed::StrawberrySeed()
{
	type = STRAWBERRYSEED;
	price = 200;
	season = SPRING;
	count = 5;
	image.LoadBitmap(IDB_Strawberry_Seed);
	image.GetBitmap(&imageInfo);
}
SproutedPotatoSeed::SproutedPotatoSeed()
{
	type = SPROUTEDPOTATOSEED;
	price = 600;
	season = SPRING;
	count = 5;
	image.LoadBitmap(IDB_Sprouted_Potatoes_Seed);
	image.GetBitmap(&imageInfo);
}
GoldenCarrotSeed::GoldenCarrotSeed()
{
	type = GOLDENCARROTSEED;
	price = 1500;
	season = SPRING;
	count = 5;
	image.LoadBitmap(IDB_Golden_Carrot_Seed);
	image.GetBitmap(&imageInfo);
}

WaterMelonSeed::WaterMelonSeed()
{
	type = WATERMELONSEED;
	price = 700;
	season = SUMMER;
	count = 5;
	image.LoadBitmap(IDB_WaterMelon_Seed);
	image.GetBitmap(&imageInfo);
}
CornSeed::CornSeed()
{
	type = CORNSEED;
	price = 300;
	season = SUMMER;
	count = 5;
	image.LoadBitmap(IDB_Corn_Seed);
	image.GetBitmap(&imageInfo);
}
CabbageSeed::CabbageSeed()
{
	type = CABBAGESEED;
	price = 300;
	season = SUMMER;
	count = 5;
	image.LoadBitmap(IDB_Cabbage_Seed);
	image.GetBitmap(&imageInfo);
}
SeedlessWatermelonSeed::SeedlessWatermelonSeed()
{
	type = SEEDLESSWATERMELONSEED;
	price = 750;
	season = SUMMER;
	count = 5;
	image.LoadBitmap(IDB_Seedless_WaterMelon_Seed);
	image.GetBitmap(&imageInfo);
}

SweetPotatoSeed::SweetPotatoSeed()
{
	type = SWEETPOTATOSEED;
	price = 400;
	season = FALL;
	count = 5;
	image.LoadBitmap(IDB_Sweet_Potato_Seed);
	image.GetBitmap(&imageInfo);
}
MelonSeed::MelonSeed()
{
	type = MELONSEED;
	price = 800;
	season = FALL;
	count = 5;
	image.LoadBitmap(IDB_Melon_Seed);
	image.GetBitmap(&imageInfo);
}
WheatSeed::WheatSeed()
{
	type = WHEATSEED;
	price = 550;
	season = FALL;
	count = 5;
	image.LoadBitmap(IDB_Wheat_Seed);
	image.GetBitmap(&imageInfo);
}
SproutedSweetPotatoSeed::SproutedSweetPotatoSeed()
{
	type = SPROUTEDSWEETPOTATOSEED;
	price = 600;
	season = FALL;
	count = 5;
	image.LoadBitmap(IDB_Sprouted_Sweet_Potato_Seed);
	image.GetBitmap(&imageInfo);
}
WhiteMelonSeed::WhiteMelonSeed()
{
	type = WHITEMELONSEED;
	price = 1100;
	season = FALL;
	count = 5;
	image.LoadBitmap(IDB_White_Melon_Seed);
	image.GetBitmap(&imageInfo);
}

SpinachSeed::SpinachSeed()
{
	type = SPINACHSEED;
	price = 350;
	season = WINTER;
	count = 5;
	image.LoadBitmap(IDB_Spinach_Seed);
	image.GetBitmap(&imageInfo);
}
GreenOnionSeed::GreenOnionSeed()
{
	type = GREENONIONSEED;
	price = 350;
	season = WINTER;
	count = 5;
	image.LoadBitmap(IDB_Green_Onion_Seed);
	image.GetBitmap(&imageInfo);
}
RadishSeed::RadishSeed()
{
	type = RADISHSEED;
	price = 400;
	season = WINTER;
	count = 5;
	image.LoadBitmap(IDB_Radish_Seed);
	image.GetBitmap(&imageInfo);
}
RaspberrySeed::RaspberrySeed()
{
	type = RASPBERRYSEED;
	price = 250;
	season = WINTER;
	count = 5;
	image.LoadBitmap(IDB_Raspberry_Seed);
	image.GetBitmap(&imageInfo);
}
SativusSeed::SativusSeed()
{
	type = SATIVUSSEED;
	price = 200;
	season = WINTER;
	count = 5;
	image.LoadBitmap(IDB_Sativus_Seed);
	image.GetBitmap(&imageInfo);
}



Potato::Potato()
{
	type = POTATO;
	price = 800;
	season = SPRING;
	count = 1;
	image.LoadBitmap(IDB_Potato);
	image.GetBitmap(&imageInfo);
}
Carrot::Carrot()
{
	type = CARROT;
	price = 600;
	season = SPRING;
	count = 1;
	image.LoadBitmap(IDB_Carrot);
	image.GetBitmap(&imageInfo);
}
Strawberry::Strawberry()
{
	type = STRAWBERRY;
	price = 450;
	season = SPRING;
	count = 1;
	image.LoadBitmap(IDB_Strawberry);
	image.GetBitmap(&imageInfo);
}
SproutedPotato::SproutedPotato()
{
	type = POTATO;
	price = 800;
	season = SPRING;
	count = 1;
	image.LoadBitmap(IDB_SproutedPotato);
	image.GetBitmap(&imageInfo);
}
GoldenCarrot::GoldenCarrot()
{
	type = GOLDENCARROT;
	price = 3000;
	season = SPRING;
	count = 1;
	image.LoadBitmap(IDB_Golden_Carrot);
	image.GetBitmap(&imageInfo);
}

WaterMelon::WaterMelon()
{
	type = WATERMELON;
	price = 1400;
	SEASON season = SUMMER;
	count = 1;
	image.LoadBitmap(IDB_Watermelon);
	image.GetBitmap(&imageInfo);
}
Corn::Corn()
{
	type = CORN;
	price = 650;
	SEASON season = SUMMER;
	count = 1;
	image.LoadBitmap(IDB_Corn);
	image.GetBitmap(&imageInfo);
}
Cabbage::Cabbage()
{
	type = CABBAGE;
	price = 550;
	SEASON season = SUMMER;
	count = 1;
	image.LoadBitmap(IDB_Cabbage);
	image.GetBitmap(&imageInfo);
}
SeedlessWatermelon::SeedlessWatermelon()
{
	type = SEEDLESSWATERMELON;
	price = 1800;
	SEASON season = SUMMER;
	count = 1;
	image.LoadBitmap(IDB_Seedless_Watermelon);
	image.GetBitmap(&imageInfo);
}

SweetPotato::SweetPotato()
{
	type = SWEETPOTATO;
	price = 800;
	SEASON season = FALL;
	count = 1;
	image.LoadBitmap(IDB_Sweet_Potato);
	image.GetBitmap(&imageInfo);
}
Melon::Melon()
{
	type = MELON;
	price = 1600;
	SEASON season = FALL;
	count = 1;
	image.LoadBitmap(IDB_Melon);
	image.GetBitmap(&imageInfo);
}
Wheat::Wheat()
{
	type = WHEAT;
	price = 1000;
	SEASON season = FALL;
	count = 1;
	image.LoadBitmap(IDB_Wheat);
	image.GetBitmap(&imageInfo);
}
SproutedSweetPotato::SproutedSweetPotato()
{
	type = SWEETPOTATO;
	price = 800;
	SEASON season = FALL;
	count = 1;
	image.LoadBitmap(IDB_Sweet_Potato);
	image.GetBitmap(&imageInfo);
}
WhiteMelon::WhiteMelon()
{
	type = WHITEMELON;
	price = 2300;
	SEASON season = FALL;
	count = 1;
	image.LoadBitmap(IDB_White_Melon);
	image.GetBitmap(&imageInfo);
}

Spinach::Spinach()
{
	type = SPINACH;
	price = 750;
	SEASON season = WINTER;
	count = 1;
	image.LoadBitmap(IDB_Spinach);
	image.GetBitmap(&imageInfo);
}
GreenOnion::GreenOnion()
{
	type = GREENONION;
	price = 600;
	SEASON season = WINTER;
	count = 1;
	image.LoadBitmap(IDB_Green_Onion);
	image.GetBitmap(&imageInfo);
}
Radish::Radish()
{
	type = RADISH;
	price = 800;
	SEASON season = WINTER;
	count = 1;
	image.LoadBitmap(IDB_Radish);
	image.GetBitmap(&imageInfo);
}
Raspberry::Raspberry()
{
	type = RASPBERRY;
	price = 500;
	SEASON season = WINTER;
	count = 1;
	image.LoadBitmap(IDB_Raspberry);
	image.GetBitmap(&imageInfo);
}
Sativus::Sativus()
{
	type = SATIVUS;
	price = 450;
	SEASON season = WINTER;
	count = (rand()%3) + 1;
	image.LoadBitmap(IDB_Sativus);
	image.GetBitmap(&imageInfo);
}



HPPotion::HPPotion()
{
	type = HP_POTION;
	type2 = POTIONS;
	price = 500;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_HP_Potion);
	image.GetBitmap(&imageInfo);
}
MPPotion::MPPotion()
{
	type = MP_POTION;
	type2 = POTIONS;
	price = 300;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_MP_Potion);
	image.GetBitmap(&imageInfo);
}
Panaacea::Panaacea()
{
	type = PANAACEA;
	type2 = POTIONS;
	price = 700;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_Panaacea);
	image.GetBitmap(&imageInfo);
}
Revival::Revival()
{
	type = REVIVAL;
	type2 = POTIONS;
	price = 2000;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_Revival);
	image.GetBitmap(&imageInfo);
}


Fertilizer::Fertilizer()
{
	type = FERTILIZER;
	type2 = ELSE;
	price = 60;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_Fertilizer);
	image.GetBitmap(&imageInfo);
}
BossItem1::BossItem1()
{
	type = BOSSITEM1;
	type2 = ELSE;
	price = 60;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_BossItem1);
	image.GetBitmap(&imageInfo);
}
BossItem2::BossItem2()
{
	type = BOSSITEM2;
	type2 = ELSE;
	price = 60;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_BossItem2);
	image.GetBitmap(&imageInfo);
}
BossItem3::BossItem3()
{
	type = BOSSITEM3;
	type2 = ELSE;
	price = 60;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_BossItem3);
	image.GetBitmap(&imageInfo);
}
BossItem4::BossItem4()
{
	type = BOSSITEM4;
	type2 = ELSE;
	price = 60;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_BossItem4);
	image.GetBitmap(&imageInfo);
}
BossItem5::BossItem5()
{
	type = BOSSITEM5;
	type2 = ELSE;
	price = 60;
	season = ALL;
	count = 1;
	image.LoadBitmap(IDB_BossItem5);
	image.GetBitmap(&imageInfo);
}
