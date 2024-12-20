#include "pch.h"
#include "Crop.h"
#include "resource.h"

CBitmap Crop::Level1NonWatered;
CBitmap Crop::Level1Watered;
CBitmap Crop::Level2NonWatered;
CBitmap Crop::Level2Watered;

BITMAP Crop::Level1NonWateredInfo;
BITMAP Crop::Level1WateredInfo;
BITMAP Crop::Level2NonWateredInfo;
BITMAP Crop::Level2WateredInfo;

void Crop::setInit()
{
	Level1NonWatered.LoadBitmap(IDB_Level1NonWatered);
	Level1NonWatered.GetBitmap(&Level1NonWateredInfo);

	Level1Watered.LoadBitmap(IDB_Level1Watered);
	Level1Watered.GetBitmap(&Level1WateredInfo);

	Level2NonWatered.LoadBitmap(IDB_Level2NonWatered);
	Level2NonWatered.GetBitmap(&Level2NonWateredInfo);

	Level2Watered.LoadBitmap(IDB_Level2Watered);
	Level2Watered.GetBitmap(&Level2WateredInfo);
}

void Crop::draw(CDC* memdc, int x, int y, int size, int count)
{
	CDC imageDC;
	imageDC.CreateCompatibleDC(memdc);

	CDC temp;
	temp.CreateCompatibleDC(&imageDC);
	CBitmap tempBitmap;

	if(growthDay < untilGrow/2)
	{
		if(isWater)
			imageDC.SelectObject(&Level1Watered);
		else
			imageDC.SelectObject(&Level1NonWatered);
	}
	else if(growthDay != untilGrow)
	{
		if(isWater)
			imageDC.SelectObject(&Level2Watered);
		else
			imageDC.SelectObject(&Level2NonWatered);
	}
	else
	{
		if(isWater)
			imageDC.SelectObject(&Level3Watered);
		else
			imageDC.SelectObject(&Level3NonWatered);
	}

	tempBitmap.CreateCompatibleBitmap(&imageDC, imageInfo.bmWidth, imageInfo.bmHeight);
	temp.SelectObject(&tempBitmap);
	temp.BitBlt(0, 0, imageInfo.bmWidth, imageInfo.bmHeight, &imageDC, 0, 0, SRCCOPY);


	memdc->StretchBlt(x, y, size, size, &temp, 0, 0, imageInfo.bmWidth, imageInfo.bmHeight, SRCCOPY);

	/*if(isWater)
		memdc->Rectangle(x + size * 0.07, y + size * 0.07, x + size * 0.93, y + size * 0.93);
	else
		memdc->StretchBlt(x + size * 0.07, y + size * 0.07, size * 0.86, size * 0.86, &imageDC, 0, 0, imageInfo.bmWidth, imageInfo.bmHeight, SRCCOPY);*/

	memdc->SelectStockObject(WHITE_BRUSH);
}

PPotato::PPotato() : Crop(8)
{
	type = POTATO;
	price = 60;
	season = SPRING;
	image.LoadBitmap(IDB_Potato);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredPotato);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Potato);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PPotato::PPotato(int n) : PPotato()
{
	growthDay = n;
}
PCarrot::PCarrot() : Crop(5)
{
	type = CARROT;
	price = 60;
	season = SPRING;
	image.LoadBitmap(IDB_Carrot);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredCarrot);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Carrot);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PStrawberry::PStrawberry() : Crop(4)
{
	type = STRAWBERRY;
	price = 60;
	season = SPRING;
	image.LoadBitmap(IDB_Strawberry);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredStrawberry);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Strawberry);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PGoldenCarrot::PGoldenCarrot() : Crop(13)
{
	type = GOLDENCARROT;
	price = 60;
	season = SPRING;
	image.LoadBitmap(IDB_Golden_Carrot);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredGoldenCarrot);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3GoldenCarrot);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}


PWaterMelon::PWaterMelon() : Crop(11)
{
	type = WATERMELON;
	price = 60;
	season = SUMMER;
	image.LoadBitmap(IDB_Watermelon);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3Watermelon);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Watermelon);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PCorn::PCorn() : Crop(6)
{
	type = CORN;
	price = 60;
	season = SUMMER;
	image.LoadBitmap(IDB_Corn);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredCorn);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Corn);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PCabbage::PCabbage() : Crop(5)
{
	type = CABBAGE;
	price = 60;
	season = SUMMER;
	image.LoadBitmap(IDB_Cabbage);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredCabbage);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Cabbage);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PSeedlessWaterMelon::PSeedlessWaterMelon() : Crop(11)
{
	type = SEEDLESSWATERMELON;
	price = 60;
	season = SUMMER;
	image.LoadBitmap(IDB_Seedless_Watermelon);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredWatermelon);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Watermelon);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}


PSweetPotato::PSweetPotato() : Crop(8)
{
	type = SWEETPOTATO;
	price = 60;
	season = FALL;
	image.LoadBitmap(IDB_Sweet_Potato);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredSweetPotato);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3SweetPotato);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PSweetPotato::PSweetPotato(int n) : PSweetPotato()
{
	growthDay = n;
}
PMelon::PMelon() : Crop(12)
{
	type = MELON;
	price = 60;
	season = FALL;
	image.LoadBitmap(IDB_Melon);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredMelon);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Melon);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PWheat::PWheat() : Crop(8)
{
	type = WHEAT;
	price = 60;
	season = FALL;
	image.LoadBitmap(IDB_Wheat);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredWheat);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Wheat);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PSproutedSweetPotato::PSproutedSweetPotato() : Crop(6)
{
	type = SPROUTEDSWEETPOTATO;
	price = 60;
	season = FALL;
	image.LoadBitmap(IDB_Sprouted_Sweet_Potato);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredSweetPotato);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3SweetPotato);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PWhiteMelon::PWhiteMelon() : Crop(12)
{
	type = WHITEMELON;
	price = 60;
	season = FALL;
	image.LoadBitmap(IDB_White_Melon);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredWhiteMelon);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3WhiteMelon);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}


PSpinach::PSpinach() : Crop(7)
{
	type = SPINACH;
	price = 60;
	season = WINTER;
	image.LoadBitmap(IDB_Spinach);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredSpinach);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Spinach);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PGreenOnion::PGreenOnion() : Crop(5)
{
	type = GREENONION;
	price = 60;
	season = WINTER;
	image.LoadBitmap(IDB_Green_Onion);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3GreenOnion);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3GreenOnion);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PRadish::PRadish() : Crop(6)
{
	type = RADISH;
	price = 60;
	season = WINTER;
	image.LoadBitmap(IDB_Radish);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredRadish);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Radish);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PSativus::PSativus() : Crop(6)
{
	type = SATIVUS;
	price = 60;
	season = WINTER;
	image.LoadBitmap(IDB_Sativus);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredSativus);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Sativus);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
PRaspberry::PRaspberry() : Crop(4)
{
	type = RASPBERRY;
	price = 60;
	season = WINTER;
	image.LoadBitmap(IDB_Raspberry);
	image.GetBitmap(&imageInfo);
	Level3Watered.LoadBitmapW(IDB_Level3WateredRaspberry);
	Level3Watered.GetBitmap(&Level3WateredInfo);
	Level3NonWatered.LoadBitmapW(IDB_Level3Raspberry);
	Level3NonWatered.GetBitmap(&Level3NonWateredInfo);
}
