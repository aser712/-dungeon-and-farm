#pragma once
#include <vector>

using namespace std;

enum SHOPMOD
{
	SHOPMENU = 0, SEED, POTION, SELL
};
enum HALLMOD
{
	HALLMENU = 0,
};

class Village
{
	static vector<vector<CString>> shopObj;
	static int size;
	static int talkCount;

	static CBitmap wallImage;
	static BITMAP wallImageInfo;

	static CBitmap villageImage;
	static BITMAP villageImageInfo;

	static CBitmap shopImage;
	static BITMAP shopImageInfo;
	static CBitmap shopInnerImage;
	static BITMAP shopInnerImageInfo;

	static CBitmap hallImage;
	static BITMAP hallImageInfo;
	static CBitmap hallInnerImage;
	static BITMAP hallInnerImageInfo;

	static CBitmap smithyImage;
	static BITMAP smithyImageInfo;
	static CBitmap InnerSmithyImage;
	static BITMAP InnerSmithyImageInfo;

	static CBitmap Fountain;
	static BITMAP FountainInfo;
	static int smithyFlag;
	static int smithySelectFlag;
	static int itemIndex1;
	static int itemIndex2;

	static vector<vector<int>> buyPriceObj;
	static vector<vector<int>> sellPriceObj;
	static vector<vector<int>> duringObj;

	static void drawBuilding(CDC* memdc, CBitmap& bitmap, BITMAP info, int set);
	static void inputInven();
public:
	static int unlock;
	static CWnd* pWnd;
	static int villageMap[15][25];
	static int select;
	static SHOPMOD shopMod;
	static int sellIndex;
	static int sellCount;
	static int hallMod;
	static int hallSelectFlag;
	static int isEnding;
	static int ENum;

	static void setInit();
	static void setSize(CRect in);
	static void drawVillage(CDC* memdc);
	static void drawShop(CDC* memdc);
	static void shopSelect(UINT nChar, UINT nRepCnt, UINT nFlags);
	static void hallSelect(UINT nChar, UINT nRepCnt, UINT nFlags);
	static void SmithySelect(UINT nChar, UINT nRepCnt, UINT nFlags);

	static void drawHall(CDC* memdc);
	static void drawSmithy(CDC* memdc);
};

