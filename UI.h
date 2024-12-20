#pragma once
enum SEASON
{
	SPRING = 0, SUMMER, FALL, WINTER, ALL
};
class UI
{
public:
	static CBitmap UIImage;
	static BITMAP UIImageInfo;
	static CBitmap boardImage;
	static BITMAP boardImageInfo;
	static SEASON season;
	static int day;
	static int money;
	static int size;

	static void setInit();
	static void setsize(CRect in);
	static void printUI(CDC* memdc);
};

