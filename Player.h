#pragma once
#include <vector>
#include "Object.h"

using namespace std;

enum toLook
{
	LEFT, RIGHT, UP, DOWN
};
enum MOD
{
	MENU, FARM, VILLAGE, HOUSE, SHOP, HALL, SMITHY, CHEST, DUNGEON
};

class Player
{
private:
	static int size;
	static CBitmap image;
	static BITMAP imageInfo;
	static CBitmap walkImage1;
	static BITMAP walkImage1Info;
	static CBitmap walkImage2;
	static BITMAP walkImage2Info;
	static COORD ChestPos;
	static void plantCrop(int x, int y);
	static void waterCrop(int x, int y);
	static void digCrop(int x, int y);
	static int check;
public:
	static int moving;
	static COORD pos;
	static int toolbar;
	static vector<Object*> inven;
	static vector<Object*> storage;
	static toLook look;
	static MOD mod;
	static void setSize(CRect in);
	static void setInit();
	static void drawPlayer(CDC* memdc);
	static void movePlayer(CWnd* pWnd, UINT nChar, UINT nRepCnt, UINT nFlags);
	static void drawBigPlayer(CDC* memdc);
	static void drawInven(CDC* memdc);
	static void drawChest(CDC* memdc);
	static void moveInven(UINT nChar, UINT nRepCnt, UINT nFlags);
	static void moveChest(UINT nChar, UINT nRepCnt, UINT nFlags);
	static void toNextDay();
	static void managePlant(int x, int y);
};