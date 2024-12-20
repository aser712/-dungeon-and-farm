#pragma once
#include "UI.h"
#include "Object.h"

class Crop : public Object
{
public:
	static void setInit();
	static CBitmap Level1NonWatered;
	static CBitmap Level1Watered;
	static CBitmap Level2NonWatered;
	static CBitmap Level2Watered; 
	
	static BITMAP Level1NonWateredInfo;
	static BITMAP Level1WateredInfo;
	static BITMAP Level2NonWateredInfo;
	static BITMAP Level2WateredInfo;


	CBitmap Level3NonWatered;
	CBitmap Level3Watered;
	BITMAP Level3NonWateredInfo;
	BITMAP Level3WateredInfo;

	int untilGrow;
	int growthDay;
	bool isWater;
	Crop(int t) {
		isWater = false;
		growthDay = 0;
		untilGrow = t;
		type2 = CROPS;
	};
	void draw(CDC* memdc, int x, int y, int size, int count);
};

class PPotato : public Crop
{
public:
	PPotato();
	PPotato(int n);
};
class PCarrot : public Crop
{
public:
	PCarrot();
};
class PStrawberry : public Crop
{
public:
	PStrawberry();
};
class PGoldenCarrot : public Crop
{
public:
	PGoldenCarrot();
};

class PWaterMelon : public Crop
{
public:
	PWaterMelon();
};
class PCorn : public Crop
{
public:
	PCorn();
};
class PCabbage : public Crop
{
public:
	PCabbage();
};
class PSeedlessWaterMelon : public Crop
{
public:
	PSeedlessWaterMelon();
};

class PSweetPotato : public Crop
{
public:
	PSweetPotato();
	PSweetPotato(int n);
};
class PMelon : public Crop
{
public:
	PMelon();
};
class PWheat : public Crop
{
public:
	PWheat();
};
class PSproutedSweetPotato : public Crop
{
public:
	PSproutedSweetPotato();
};
class PWhiteMelon : public Crop
{
public:
	PWhiteMelon();
};

class PSpinach : public Crop
{
public:
	PSpinach();
};
class PGreenOnion : public Crop
{
public:
	PGreenOnion();
};
class PRadish : public Crop
{
public:
	PRadish();
};
class PSativus : public Crop
{
public:
	PSativus();
};
class PRaspberry : public Crop
{
public:
	PRaspberry();
};