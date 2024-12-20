#pragma once
#include <vector>

#define FirstHall        0b000000000001
#define FirstShop        0b000000000010
#define FirstSmithy      0b000000000100
#define FirstFarm        0b000000001000
#define FirstDungeon     0b000000010000
#define AllSpring        0b000000100000
#define SellPotato       0b000001000000
#define AllSummer        0b000010000000
#define SellSweetPotato  0b000100000000
#define OneFall          0b001000000000           
#define SellSativus      0b010000000000
#define FirstHouse       0b100000000000


#define POTATOFLAG     0b001
#define CARROTFLAG     0b010
#define STRAWBERRYFLAG 0b100

#define WATERMELONFLAG 0b001
#define CORNFLAG       0b010
#define CABBAGEFLAG    0b100


using namespace std;

class EventManager
{
public:
	static int EventFlag;
	static int springFlag;
	static int summerFlag;
	static int Savitus;

	static vector<CString> ShopTalk;
	static vector<CString> HallTalk;
	static vector<CString> SmithyTalk;
	static vector<CString> FarmTalk;
	static vector<CString> skillTalk;
	static vector<CString> HouseTalk;
	static vector<CString> itemTalk;

};

