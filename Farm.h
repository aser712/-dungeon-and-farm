#pragma once
#include "Crop.h"

class Farm : public CWnd
{
public:
	static int size;

	static CBitmap wallImage;
	static BITMAP wallImageInfo;
	static CBitmap farmImage;
	static BITMAP farmImageInfo;
	static CBitmap houseImage;
	static BITMAP houseImageInfo;
	static CBitmap houseInnerImage;
	static BITMAP houseInnerImageInfo;
	static CBitmap soilImage;
	static BITMAP soilImageInfo;
	static CBitmap wettedSoilImage;
	static BITMAP wettedSoilImageInfo;
	static CBitmap caveImage;
	static BITMAP caveImageInfo;

	static void drawHouse(CDC* memdc);
	static void drawField(CDC* memdc);
public:
	static bool talkFlag;
	static int sleepFlag;
	static void setSize(CRect in);
	static int farmMap[15][25];
	static Crop* field1[5][8];
	static Crop* field2[5][12];
	static Crop* field3[5][16];
	static int fieldLevel;
	static int talkCount;
	static CWnd* pWnd;
	static int isBed;
	static int bedCount;


	static int houseMap[4][3];
	static void drawFarm(CDC* memdc);
	static void setInit();

	static void drawInnerHouse(CDC* memdc);
	static void sleepAlarm(CDC* memdc);
	static void moveFlag(UINT nChar, UINT nRepCnt, UINT nFlags);
	static void upgradeField();
};
