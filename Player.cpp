#include "pch.h"
#include "Player.h"
#include "Farm.h"
#include "Village.h"
#include "resource.h"
#include "Dungeon.h"
#include "Crop.h"
#include "EventManager.h"

MOD Player::mod;
int Player::size;
CBitmap Player::image;
BITMAP Player::imageInfo;
CBitmap Player::walkImage1;
BITMAP Player::walkImage1Info;
CBitmap Player::walkImage2;
BITMAP Player::walkImage2Info;
toLook Player::look = LEFT;
vector<Object*> Player::inven(9);
vector<Object*> Player::storage(60);
COORD Player::pos;
COORD Player::ChestPos;
int Player::toolbar;
int Player::check;
int Player::moving = 0;

void Player::plantCrop(int x, int y)
{
	Crop* temp = NULL;
	switch (inven[toolbar - 1]->type)
	{
	case POTATOSEED:
		temp = new PPotato();
		break;
	case CARROTSEED:
		temp = new PCarrot();
		break;
	case STRAWBERRYSEED:
		temp = new PStrawberry();
		break;
	case GOLDENCARROTSEED:
		temp = new PGoldenCarrot();
		break;
	case SPROUTEDPOTATOSEED:
		temp = new PPotato(3);
		break;
	case WATERMELONSEED:
		temp = new PWaterMelon();
		break;
	case CORNSEED:
		temp = new PCorn();
		break;
	case CABBAGESEED:
		temp = new PCabbage();
		break;
	case SEEDLESSWATERMELONSEED:
		temp = new PSeedlessWaterMelon();
		break;
	case SWEETPOTATOSEED:
		temp = new PSweetPotato();
		break;
	case MELONSEED:
		temp = new PMelon();
		break;
	case WHEATSEED:
		temp = new PWheat();
		break;	
	case SPROUTEDSWEETPOTATOSEED:
		temp = new PSweetPotato(4);
		break;
	case WHITEMELONSEED:
		temp = new PWhiteMelon();
		break;
	case SPINACHSEED:
		temp = new PSpinach();
		break;
	case GREENONIONSEED:
		temp = new PGreenOnion();
		break;
	case RADISHSEED:
		temp = new PRadish();
		break;
	case SATIVUSSEED:
		temp = new PSativus();
		break;
	case RASPBERRYSEED:
		temp = new PRaspberry();
		break;
	default:
		break;
	}
	if(temp == NULL)
		return;
	if(temp->season != UI::season)
	{
		delete temp;
		return;
	}
	if (Farm::fieldLevel == 1 && temp != NULL)
	{
		Farm::field1[y][x] = temp;
		inven[toolbar - 1]->count--;
		if (inven[toolbar - 1]->count == 0)
		{
			free(inven[toolbar - 1]);
			inven[toolbar - 1] = NULL;
		}
	}
	else if(Farm::fieldLevel == 2 && temp != NULL)
	{
		Farm::field2[y][x] = temp;
		inven[toolbar - 1]->count--;
		if(inven[toolbar - 1]->count == 0)
		{
			free(inven[toolbar - 1]);
			inven[toolbar - 1] = NULL;
		}
	}
	else if(Farm::fieldLevel == 3 && temp != NULL)
	{
		Farm::field3[y][x] = temp;
		inven[toolbar - 1]->count--;
		if(inven[toolbar - 1]->count == 0)
		{
			free(inven[toolbar - 1]);
			inven[toolbar - 1] = NULL;
		}
	}
}
void Player::waterCrop(int x, int y)
{
	if(Farm::fieldLevel == 1)
	{
		if(Farm::field1[y][x]->growthDay != Farm::field1[y][x]->untilGrow && toolbar == 1)
			Farm::field1[y][x]->isWater = 1;
		else if(Farm::field1[y][x]->growthDay != Farm::field1[y][x]->untilGrow && inven[toolbar - 1] != NULL && inven[toolbar - 1]->type == FERTILIZER)
		{
			Farm::field1[y][x]->growthDay++;
			if(Farm::field1[y][x]->growthDay == Farm::field1[y][x]->untilGrow)
				Farm::field1[y][x]->isWater = 0;
			inven[toolbar - 1]->count--;
			if(inven[toolbar - 1]->count == 0)
			{
				delete inven[toolbar - 1];
				inven[toolbar - 1] = NULL;
			}
		}
	}
	if(Farm::fieldLevel == 2)
	{
		if(Farm::field2[y][x]->growthDay != Farm::field2[y][x]->untilGrow && toolbar == 1)
			Farm::field2[y][x]->isWater = 1;
		else if(Farm::field2[y][x]->growthDay != Farm::field2[y][x]->untilGrow && inven[toolbar - 1] != NULL && inven[toolbar - 1]->type == FERTILIZER)
		{
			Farm::field2[y][x]->growthDay++;
			if(Farm::field2[y][x]->growthDay == Farm::field2[y][x]->untilGrow)
				Farm::field2[y][x]->isWater = 0;
			inven[toolbar - 1]->count--;
			if(inven[toolbar - 1]->count == 0)
			{
				delete inven[toolbar - 1];
				inven[toolbar - 1] = NULL;
			}
		}
	}
	if(Farm::fieldLevel == 3)
	{
		if(Farm::field3[y][x]->growthDay != Farm::field3[y][x]->untilGrow && toolbar == 1)
			Farm::field3[y][x]->isWater = 1;
		else if(Farm::field3[y][x]->growthDay != Farm::field3[y][x]->untilGrow && inven[toolbar - 1] != NULL && inven[toolbar - 1]->type == FERTILIZER)
		{
			Farm::field3[y][x]->growthDay++;
			if(Farm::field3[y][x]->growthDay == Farm::field3[y][x]->untilGrow)
				Farm::field3[y][x]->isWater = 0;
			inven[toolbar - 1]->count--;
			if(inven[toolbar - 1]->count == 0)
			{
				delete inven[toolbar - 1];
				inven[toolbar - 1] = NULL;
			}
		}
	}

}
void Player::digCrop(int x, int y)
{
	Object* temp = NULL;
	int flag = 0;
	int inputIndex = -1;

	if(Farm::fieldLevel == 1)
	{
		switch(Farm::field1[y][x]->type)
		{
			case POTATO:
				temp = new Potato();
				break;
			case CARROT:
				temp = new Carrot();
				break;
			case STRAWBERRY:
				temp = new Strawberry();
				break;
			case GOLDENCARROT:
				temp = new GoldenCarrot();
				break;
			case WATERMELON:
				temp = new WaterMelon();
				break;
			case CORN:
				temp = new Corn();
				break;
			case CABBAGE:
				temp = new Cabbage();
				break;
			case SEEDLESSWATERMELON:
				temp = new SeedlessWatermelon();
				break;
			case SWEETPOTATO:
				temp = new SweetPotato();
				break;
			case MELON:
				temp = new Melon();
				break;
			case WHEAT:
				temp = new Wheat();
				break;
			case WHITEMELON:
				temp = new WhiteMelon();
				break;
			case SPINACH:
				temp = new Spinach();
				break;
			case GREENONION:
				temp = new GreenOnion();
				break;
			case RADISH:
				temp = new Radish();
				break;
			case RASPBERRY:
				temp = new Raspberry();
				break;
			case SATIVUS:
				temp = new Sativus();
				break;
			default:
				break;
		}
		if(temp->type == RADISH)
		{
			int q = rand() % 1000;
			if(0 <= q && q <= 49)
			{
				delete temp;
				temp = new Sativus();
				temp->count = 2;
			}
		}
		for(int i = 1; temp != NULL && i < 9; i++)
		{
			if(Player::inven[i] != NULL && Player::inven[i]->type == temp->type)
			{
				flag = 1;
				Player::inven[i]->count += temp->count;
			}
			if(inputIndex == -1 && Player::inven[i] == NULL)
				inputIndex = i;
		}
		if(flag == 0 && inputIndex == -1)
		{
			if(temp != NULL)
				delete temp;

			return;
		}
		if(flag == 0 && temp != NULL)
		{
			Player::inven[inputIndex] = temp;
		}
		if(flag == 1 && temp != NULL)
		{
			delete temp;
		}

		delete Farm::field1[y][x];
		Farm::field1[y][x] = NULL;
	}
	else if(Farm::fieldLevel == 2)
	{
		switch(Farm::field2[y][x]->type)
		{
			case POTATO:
				temp = new Potato();
				break;
			case CARROT:
				temp = new Carrot();
				break;
			case STRAWBERRY:
				temp = new Strawberry();
				break;
			case GOLDENCARROT:
				temp = new GoldenCarrot();
				break;
			case WATERMELON:
				temp = new WaterMelon();
				break;
			case CORN:
				temp = new Corn();
				break;
			case CABBAGE:
				temp = new Cabbage();
				break;
			case SEEDLESSWATERMELON:
				temp = new SeedlessWatermelon();
				break;
			case SWEETPOTATO:
				temp = new SweetPotato();
				break;
			case MELON:
				temp = new Melon();
				break;
			case WHEAT:
				temp = new Wheat();
				break;
			case WHITEMELON:
				temp = new WhiteMelon();
				break;
			case SPINACH:
				temp = new Spinach();
				break;
			case GREENONION:
				temp = new GreenOnion();
				break;
			case RADISH:
				temp = new Radish();
				break;
			case RASPBERRY:
				temp = new Raspberry();
				break;
			case SATIVUS:
				temp = new Sativus();
				break;
			default:
				break;
		}
		if(temp->type == RADISH)
		{
			int q = rand() % 1000;
			if(0 <= q && q <= 49)
			{
				delete temp;
				temp = new Sativus();
				temp->count = 2;
			}
		}
		for(int i = 1; temp != NULL && i < 9; i++)
		{
			if(Player::inven[i] != NULL && Player::inven[i]->type == temp->type)
			{
				flag = 1;
				Player::inven[i]->count += temp->count;
			}
			if(inputIndex == -1 && Player::inven[i] == NULL)
				inputIndex = i;
		}
		if(flag == 0 && inputIndex == -1)
		{
			if(temp != NULL)
				delete temp;

			return;
		}
		if(flag == 0 && temp != NULL)
		{
			Player::inven[inputIndex] = temp;
		}
		if(flag == 1 && temp != NULL)
		{
			delete temp;
		}

		delete Farm::field2[y][x];
		Farm::field2[y][x] = NULL;
	}
	else if(Farm::fieldLevel == 3)
	{
		switch(Farm::field3[y][x]->type)
		{
			case POTATO:
				temp = new Potato();
				break;
			case CARROT:
				temp = new Carrot();
				break;
			case STRAWBERRY:
				temp = new Strawberry();
				break;
			case GOLDENCARROT:
				temp = new GoldenCarrot();
				break;
			case WATERMELON:
				temp = new WaterMelon();
				break;
			case CORN:
				temp = new Corn();
				break;
			case CABBAGE:
				temp = new Cabbage();
				break;
			case SEEDLESSWATERMELON:
				temp = new SeedlessWatermelon();
				break;
			case SWEETPOTATO:
				temp = new SweetPotato();
				break;
			case MELON:
				temp = new Melon();
				break;
			case WHEAT:
				temp = new Wheat();
				break;
			case WHITEMELON:
				temp = new WhiteMelon();
				break;
			case SPINACH:
				temp = new Spinach();
				break;
			case GREENONION:
				temp = new GreenOnion();
				break;
			case RADISH:
				temp = new Radish();
				break;
			case RASPBERRY:
				temp = new Raspberry();
				break;
			case SATIVUS:
				temp = new Sativus();
				break;
			default:
				break;
		}
		if(temp->type == RADISH)
		{
			int q = rand() % 1000;
			if(0 <= q && q <= 49)
			{
				delete temp;
				temp = new Sativus();
				temp->count = 2;
			}
		}
		for(int i = 1; temp != NULL && i < 9; i++)
		{
			if(Player::inven[i] != NULL && Player::inven[i]->type == temp->type)
			{
				flag = 1;
				Player::inven[i]->count += temp->count;
			}
			if(inputIndex == -1 && Player::inven[i] == NULL)
				inputIndex = i;
		}
		if(flag == 0 && inputIndex == -1)
		{
			if(temp != NULL)
				delete temp;

			return;
		}
		if(flag == 0 && temp != NULL)
		{
			Player::inven[inputIndex] = temp;
		}
		if(flag == 1 && temp != NULL)
		{
			delete temp;
		}

		delete Farm::field3[y][x];
		Farm::field3[y][x] = NULL;
	}
}
void Player::managePlant(int x, int y)
{
	if(Farm::fieldLevel == 1)
	{
		if((x >= 8 || x < 0 || y >= 5 || y < 0))
			return;
		if(Farm::field1[y][x] != NULL && Farm::field1[y][x]->growthDay == Farm::field1[y][x]->untilGrow)
		{
			digCrop(x, y);
			return;
		}
		if(inven[toolbar - 1] == NULL)
			return;
		if(Farm::field1[y][x] != NULL)
		{
			waterCrop(x, y);
		}
		else if(toolbar != 1)
		{
			plantCrop(x, y);
		}
	}
	else if(Farm::fieldLevel == 2)
	{
		if((x >= 12 || x < 0 || y >= 5 || y < 0))
			return;
		if(Farm::field2[y][x] != NULL && Farm::field2[y][x]->growthDay == Farm::field2[y][x]->untilGrow)
		{
			digCrop(x, y);
			return;
		}
		if(inven[toolbar - 1] == NULL)
			return;
		if(Farm::field2[y][x] != NULL)
		{
			waterCrop(x, y);
		}
		else
		{
			plantCrop(x, y);
		}
	}
	else if(Farm::fieldLevel == 3)
	{
		if((x >= 16 || x < 0 || y >= 5 || y < 0))
			return;
		if(Farm::field3[y][x] != NULL && Farm::field3[y][x]->growthDay == Farm::field3[y][x]->untilGrow)
		{
			digCrop(x, y);
			return;
		}
		if(inven[toolbar - 1] == NULL)
			return;
		if(Farm::field3[y][x] != NULL)
		{
			waterCrop(x, y);
		}
		else
		{
			plantCrop(x, y);
		}
	}
}


void Player::setSize(CRect in)
{
	size = in.Height() / 14 * 12 / 15;
}
void Player::setInit()
{
	pos.X = 13;
	pos.Y = 6;
	look = LEFT;
	image.LoadBitmap(IDB_Character);
	image.GetBitmap(&imageInfo);
	walkImage1.LoadBitmap(IDB_WalkCharacter1);
	walkImage1.GetBitmap(&imageInfo);
	walkImage2.LoadBitmap(IDB_WalkCharacter2);
	walkImage2.GetBitmap(&imageInfo);
	mod = MENU;
	toolbar = 1;
	ChestPos = { 0,0 };
	check = -1;
}


void Player::drawPlayer(CDC* memdc)
{
	CDC imageDC;
	if(!moving)
	{
		imageDC.CreateCompatibleDC(memdc);
		imageDC.SelectObject(&image);
	}
	else if((pos.X + pos.Y) % 2)
	{
		imageDC.CreateCompatibleDC(memdc);
		imageDC.SelectObject(walkImage1);
	}
	else
	{
		imageDC.CreateCompatibleDC(memdc);
		imageDC.SelectObject(walkImage2);
	}

	CDC tempDc;
	tempDc.CreateCompatibleDC(memdc);
	CBitmap tempBitmap;
	tempBitmap.CreateCompatibleBitmap(memdc, imageInfo.bmWidth, imageInfo.bmHeight*2);
	tempDc.SelectObject(&tempBitmap);
	
	COLORREF transparentColor = RGB(255, 255, 255);

	switch (look)	
	{
	case LEFT:
		tempDc.StretchBlt(0, 0, size, size*2, &imageDC, imageInfo.bmWidth / 4 * 2 , imageInfo.bmHeight / 8, imageInfo.bmWidth / 4, imageInfo.bmHeight/8*5, SRCCOPY);
		break;
	case RIGHT:	
		tempDc.StretchBlt(0, 0, size, size*2, &imageDC, imageInfo.bmWidth / 4 * 3, imageInfo.bmHeight / 8, imageInfo.bmWidth / 4, imageInfo.bmHeight/8*5, SRCCOPY);
		break;
	case UP:
		tempDc.StretchBlt(0, 0, size, size*2, &imageDC, imageInfo.bmWidth / 4 * 1, imageInfo.bmHeight / 8, imageInfo.bmWidth / 4, imageInfo.bmHeight/8*5, SRCCOPY);
		break;
	case DOWN:
		tempDc.StretchBlt(0, 0, size, size*2, &imageDC, 0 , imageInfo.bmHeight / 8, imageInfo.bmWidth / 4, imageInfo.bmHeight/8*5, SRCCOPY);
		break;
	default:
		break;
	}
	if(moving == 0)
		memdc->TransparentBlt(size * pos.X, size * (pos.Y - 1), size, size * 2, &tempDc, 0, 0, size, size * 2, transparentColor);
	else
	{
		switch(look)
		{
			case LEFT:
				memdc->TransparentBlt(size * pos.X + size*0.5, size * (pos.Y - 1), size, size * 2, &tempDc, 0, 0, size, size * 2, transparentColor);
				break;
			case RIGHT:
				memdc->TransparentBlt(size * pos.X - size*0.5, size * (pos.Y - 1), size, size * 2, &tempDc, 0, 0, size, size * 2, transparentColor);
				break;
			case UP:
				memdc->TransparentBlt(size * pos.X, size * (pos.Y - 0.5), size, size * 2, &tempDc, 0, 0, size, size * 2, transparentColor);
				break;
			case DOWN:
				memdc->TransparentBlt(size * pos.X, size * (pos.Y - 1.5), size, size * 2, &tempDc, 0, 0, size, size * 2, transparentColor);
				break;
			default:
				break;
		}
	}
}
void Player::drawBigPlayer(CDC* memdc) 
{
	CDC imageDC;
	if(!moving)
	{
		imageDC.CreateCompatibleDC(memdc);
		imageDC.SelectObject(&image);
	}
	else if((pos.X + pos.Y) % 2)
	{
		imageDC.CreateCompatibleDC(memdc);
		imageDC.SelectObject(walkImage1);
	}
	else
	{
		imageDC.CreateCompatibleDC(memdc);
		imageDC.SelectObject(walkImage2);
	}

	CDC tempDc;
	tempDc.CreateCompatibleDC(memdc);
	CBitmap tempBitmap;
	tempBitmap.CreateCompatibleBitmap(memdc, imageInfo.bmWidth*3, imageInfo.bmHeight * 6);
	tempDc.SelectObject(&tempBitmap);

	COLORREF transparentColor = RGB(255, 255, 255);

	switch (look)
	{
	case LEFT:
		tempDc.StretchBlt(0, 0, size*3, size * 6, &imageDC, imageInfo.bmWidth / 4 * 2, imageInfo.bmHeight / 8, imageInfo.bmWidth / 4, imageInfo.bmHeight / 8 * 5, SRCCOPY);
		break;
	case RIGHT:
		tempDc.StretchBlt(0, 0, size*3, size * 6, &imageDC, imageInfo.bmWidth / 4 * 3, imageInfo.bmHeight / 8, imageInfo.bmWidth / 4, imageInfo.bmHeight / 8 * 5, SRCCOPY);
		break;
	case UP:
		tempDc.StretchBlt(0, 0, size*3, size * 6, &imageDC, imageInfo.bmWidth / 4 * 1, imageInfo.bmHeight / 8, imageInfo.bmWidth / 4, imageInfo.bmHeight / 8 * 5, SRCCOPY);
		break;
	case DOWN:
		tempDc.StretchBlt(0, 0, size*3, size * 6, &imageDC, 0, imageInfo.bmHeight / 8, imageInfo.bmWidth / 4, imageInfo.bmHeight / 8 * 5, SRCCOPY);
		break;
	default:
		break;
	}
	if(moving == 0)
		memdc->TransparentBlt(size * (pos.X * 3 + 8), size * (pos.Y * 3), size * 3, size * 6, &tempDc, 0, 0, size * 3, size * 6, transparentColor);
	else
	{
		switch(look)
		{
			case LEFT:
				memdc->TransparentBlt(size * (pos.X * 3 + 8) + size * 1.5, size * (pos.Y * 3), size * 3, size * 6, &tempDc, 0, 0, size * 3, size * 6, transparentColor);
				break;
			case RIGHT:
				memdc->TransparentBlt(size * (pos.X * 3 + 8) - size * 1.5, size * (pos.Y * 3), size * 3, size * 6, &tempDc, 0, 0, size * 3, size * 6, transparentColor);
				break;
			case UP:
				memdc->TransparentBlt(size * (pos.X * 3 + 8), size * (pos.Y * 3) + size*1.5, size * 3, size * 6, &tempDc, 0, 0, size * 3, size * 6, transparentColor);
				break;
			case DOWN:
				memdc->TransparentBlt(size * (pos.X * 3 + 8), size * (pos.Y * 3) - size*1.5, size * 3, size * 6, &tempDc, 0, 0, size * 3, size * 6, transparentColor);
				break;
			default:
				break;
		}
	}
}
void Player::movePlayer(CWnd* pWnd, UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(!moving)
	{
		if(nChar == VK_LEFT)
		{
			switch(mod)
			{
				case FARM:
					if(pos.X != 0 && Farm::farmMap[pos.Y][pos.X - 1] < 4 && EventManager::EventFlag & FirstFarm)
					{
						pos.X--;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					else
					{
						look = LEFT;
						return;
					}
					break;
				case VILLAGE:
					if(Village::villageMap[pos.Y][pos.X] == 2)
					{
						mod = FARM;
						pos.X = 24;
					}
					else if(pos.X != 0 && Village::villageMap[pos.Y][pos.X - 1] < 3)
					{
						pos.X--;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					break;
				case HOUSE:
					if(pos.X != 0 && Farm::houseMap[pos.Y][pos.X - 1] < 1 && EventManager::EventFlag & FirstHouse)
					{
						pos.X--;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					else
					{
						look = LEFT;
						return;
					}
					break;
				default:
					break;
			}
			look = LEFT;
		}
		if(nChar == VK_RIGHT)
		{
			switch(mod)
			{
				case FARM:
					if(Farm::farmMap[pos.Y][pos.X] == 3 && EventManager::EventFlag & FirstFarm)
					{
						mod = VILLAGE;
						pos.X = 0;
					}
					else if(pos.X != 24 && Farm::farmMap[pos.Y][pos.X + 1] < 4)
					{
						pos.X++;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					else
					{
						look = RIGHT;
						return;
					}
					break;
				case VILLAGE:
					if(pos.X != 24 && Village::villageMap[pos.Y][pos.X + 1] < 3)
					{
						pos.X++;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					break;
				case HOUSE:
					if(pos.X != 2 && Farm::houseMap[pos.Y][pos.X + 1] < 1 && EventManager::EventFlag & FirstHouse)
					{
						pos.X++;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					else
					{
						look = RIGHT;
						return;
					}
					break;
				default:
					break;
			}
			look = RIGHT;
		}
		if(nChar == VK_UP)
		{
			switch(mod)
			{
				case FARM:
					if(Farm::farmMap[pos.Y - 1][pos.X] == 6 && Dungeon::enterDungeon == 0)
					{
						Dungeon::inputIndex1 = -1;
						Dungeon::emptyIndex = -1;
						Dungeon::bossItemIndex[0] = -1;
						Dungeon::bossItemIndex[1] = -1;
						Dungeon::bossItemIndex[2] = -1;
						Dungeon::bossItemIndex[3] = -1;
						Dungeon::bossItemIndex[4] = -1;

						Dungeon::itemCounter[0] = NULL;
						Dungeon::itemCounter[1] = NULL;
						Dungeon::itemCounter[2] = NULL;
						Dungeon::itemCounter[3] = NULL;
						for(int i = 1; i < 9; i++)
						{
							if(inven[i] != NULL)
							{
								if(inven[i]->type == HP_POTION)
								{
									Dungeon::itemCounter[0] = inven[i];
									Dungeon::itemCounterIndex[0] = i;
								}
								else if(inven[i]->type == MP_POTION)
								{
									Dungeon::itemCounter[2] = inven[i];
									Dungeon::itemCounterIndex[2] = i;
								}

								else if(inven[i]->type == PANAACEA)
								{
									Dungeon::itemCounter[1] = inven[i];
									Dungeon::itemCounterIndex[1] = i;
								}

								else if(inven[i]->type == REVIVAL)
								{
									Dungeon::itemCounter[3] = inven[i];
									Dungeon::itemCounterIndex[3] = i;
								}
								else if(inven[i]->type == FERTILIZER)
								{
									Dungeon::inputIndex1 = i;
								}
								if(inven[i]->type == BOSSITEM1)
								{
									Dungeon::bossItemIndex[0] = i;
								}
								if(inven[i]->type == BOSSITEM2)
								{
									Dungeon::bossItemIndex[1] = i;
								}
								if(inven[i]->type == BOSSITEM3)
								{
									Dungeon::bossItemIndex[2] = i;
								}
								if(inven[i]->type == BOSSITEM4)
								{
									Dungeon::bossItemIndex[3] = i;
								}
								if(inven[i]->type == BOSSITEM5)
								{
									Dungeon::bossItemIndex[4] = i;
								}
							}
						}
						for(int i = 0; i < 9; i++)
						{
							if(inven[i] != NULL)
								continue;
							if(Dungeon::inputIndex1 == -1)
							{
								Dungeon::inputIndex1 = i;
							}
							else if(Dungeon::inputIndex1 != -1 && Dungeon::emptyIndex == -1)
							{
								Dungeon::emptyIndex = i;
							}
						}
						mod = DUNGEON;
						Dungeon::revive = 1;
						Dungeon::mod = 0;
						Dungeon::current_player_HP = User::health;
						Dungeon::current_player_MP = User::mana;
						Dungeon::burning = 0;
						Dungeon::paralyze = 0;
						Dungeon::poison = 0;
						Dungeon::duration = 0;
						Dungeon::toolbar = 1;
					}
					if(Farm::farmMap[pos.Y][pos.X] == -4)
					{
						Player::mod = HOUSE;
						pos.Y = 3;
						pos.X = 1;
					}
					else if(pos.Y != 1 && Farm::farmMap[pos.Y - 1][pos.X] < 4 && EventManager::EventFlag & FirstFarm)
					{
						pos.Y--;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					else
					{
						look = UP;
						return;
					}
					break;
				case VILLAGE:
					if(Village::villageMap[pos.Y][pos.X] == -3)
					{
						Player::mod = SHOP;
						Village::select = 1;
					}
					else if(Village::villageMap[pos.Y][pos.X] == -6)
					{
						Player::mod = HALL;
						Village::hallSelectFlag = 1;
						Village::hallMod = 1;
					}
					else if(Village::villageMap[pos.Y][pos.X] == -4)
					{
						Player::mod = SMITHY;
					}
					else if(pos.Y != 1 && Village::villageMap[pos.Y - 1][pos.X] < 3)
					{
						pos.Y--;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					break;
				case HOUSE:
					if(pos.Y != 1 && Farm::houseMap[pos.Y - 1][pos.X] < 1 && EventManager::EventFlag & FirstHouse)
					{
						pos.Y--;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					else
					{
						look = UP;
						return;
					}
					break;
				default:
					break;
			}
			look = UP;
		}
		if(nChar == VK_DOWN)
		{
			switch(mod)
			{
				case FARM:
					if(pos.Y != 14 && Farm::farmMap[pos.Y + 1][pos.X] < 4 && EventManager::EventFlag & FirstFarm)
					{
						pos.Y++;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					else
					{
						look = DOWN;
						return;
					}
					break;
				case VILLAGE:
					if(pos.Y != 14 && Village::villageMap[pos.Y + 1][pos.X] < 3)
					{
						pos.Y++;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					break;
				case HOUSE:
					if(Farm::houseMap[pos.Y][pos.X] == -1 && EventManager::EventFlag & FirstHouse)
					{
						Player::mod = FARM;
						pos.X = 11;
						pos.Y = 5;
					}
					else if(pos.Y != 3 && Farm::houseMap[pos.Y + 1][pos.X] < 1 && EventManager::EventFlag & FirstHouse)
					{
						pos.Y++;
						pWnd->SetTimer(1, 50, nullptr);
						moving = 1;
					}
					else
					{
						look = DOWN;
						return;
					}
				case SMITHY:

				default:
					break;
			}
			look = DOWN;
		}
		if(nChar == VK_BACK)
		{
			switch(mod)
			{
				case HOUSE:
					break;
				case SHOP:
				case HALL:
				case SMITHY:
					mod = VILLAGE;
					look = DOWN;
					break;
				default:
					break;
			}
		}
		if(nChar == VK_SPACE)
		{
			if(Player::mod == FARM)
			{
				switch(look)
				{
					case LEFT:
						if(Farm::fieldLevel == 1)
							managePlant(pos.X - 9, pos.Y - 8);
						else if(Farm::fieldLevel == 2)
							managePlant(pos.X - 7, pos.Y - 8);
						else if(Farm::fieldLevel == 3)
							managePlant(pos.X - 4, pos.Y - 8);
						break;
					case RIGHT:
						if(Farm::fieldLevel == 1)
							managePlant(pos.X - 7, pos.Y - 8);
						else if(Farm::fieldLevel == 2)
							managePlant(pos.X - 5, pos.Y - 8);
						else if(Farm::fieldLevel == 3)
							managePlant(pos.X - 2, pos.Y - 8);
						break;
					case UP:
						if(Farm::fieldLevel == 1)
							managePlant(pos.X - 8, pos.Y - 9);
						else if(Farm::fieldLevel == 2)
							managePlant(pos.X - 6, pos.Y - 9);
						else if(Farm::fieldLevel == 3)
							managePlant(pos.X - 3, pos.Y - 9);
						break;
					case DOWN:
						if(Farm::fieldLevel == 1)
							managePlant(pos.X - 8, pos.Y - 7);
						else if(Farm::fieldLevel == 2)
							managePlant(pos.X - 6, pos.Y - 7);
						else if(Farm::fieldLevel == 3)
							managePlant(pos.X - 3, pos.Y - 7);
						break;
					default:
						break;
				}
			}

		}
		if(nChar == VK_RETURN)
		{
			if(Player::mod == FARM && !(EventManager::EventFlag & FirstFarm))
			{
				Farm::talkCount++;
				if(Farm::talkCount == EventManager::FarmTalk.size())
				{
					EventManager::EventFlag = EventManager::EventFlag | FirstFarm;
					Farm::talkCount = 0;
				}
			}
			if(Player::mod == MENU)
			{
				if(Village::isEnding != 2)
					Player::mod = HALL;
				else
				{
					Player::mod = VILLAGE;
					Player::look = DOWN;
				}
			}
			if(Player::mod == HOUSE)
			{
				if(Player::mod == HOUSE && !(EventManager::EventFlag & FirstHouse))
				{
					Farm::talkCount++;
					if(Farm::talkCount == EventManager::HouseTalk.size())
					{
						EventManager::EventFlag = EventManager::EventFlag | FirstHouse;
					}
				}
				else
				{
					if((look == RIGHT && Farm::houseMap[pos.Y][pos.X + 1] == 2) || (look == UP && Farm::houseMap[pos.Y - 1][pos.X] == 2))
					{
						if(Farm::talkFlag)
							toNextDay();

						Farm::talkFlag = !Farm::talkFlag;
					}
					if(look == UP && Farm::houseMap[pos.Y - 1][pos.X] == 1)
					{
						mod = CHEST;
						check = -1;
					}
				}
			}
		}
	}
}

void Player::drawInven(CDC* memdc)
{
	int x = size * 5.8;
	int y = size * 15.1;
	for (int i = 0; i < inven.size(); i++)
	{
		CBrush color = RGB(255, 0, 0);
		if (toolbar == i + 1 && Player::mod != CHEST)
			memdc->SelectObject(color);
		else
			memdc->SelectStockObject(WHITE_BRUSH);
		memdc->SelectStockObject(BLACK_PEN);

		memdc->Rectangle(x, y, x + size*1.5, y + size*1.5);
		memdc->SelectStockObject(WHITE_BRUSH);

		if (inven[i] != NULL)
			inven[i]->draw(memdc, x, y, size*1.5, inven[i]->count);
		else
			memdc->Rectangle(x + size*0.11, y + size*0.11, x + size*1.39, y + size*1.39);
		x += size*1.5;
	}
}
void Player::drawChest(CDC* memdc)
{
	memdc->SelectStockObject(WHITE_BRUSH);
	CBrush color = RGB(0xff, 0xe8, 0x5f);
	CBrush red = RGB(255, 0, 0);
	int x = size * 5;
	int y = size * 2;
	for(int i = 0; i < 7; i++)
	{
		x = size * 5.05;
		for(int j = 0; j < 10; j++)
		{
			int t = i*10 + j;
			if(i == 6 && (j == 0 || j == 9))
			{
				x += size * 1.5;
				continue;
			}
			
			if(check == t)
				memdc->SelectObject(red);
			else if(i == ChestPos.Y && j == ChestPos.X)
				memdc->SelectObject(&color);
			memdc->Rectangle(x, y, x + size * 1.5, y + size * 1.5);
			memdc->SelectStockObject(WHITE_BRUSH);

			if(t < 60 && storage[t] != NULL)
				storage[t]->draw(memdc, x, y , size*1.47, storage[t]->count);
			else if(t > 60 && inven[t - 60] != NULL)
			{
				inven[t - 60]->draw(memdc, x, y, size * 1.47, inven[t-60]->count);
			}
			else
				memdc->Rectangle(x + 0.07 * size, y + 0.07 * size, x + size * 1.43, y + size * 1.43);
			x += size * 1.5;
		}
		if(i != 5)
			y += size * 1.5;
		else
			y += size * 1.7;
	}

	
}

void Player::moveInven(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == '1')
	{
		toolbar = 1;
	}
	else if (nChar == '2')
	{
		toolbar = 2;
	}
	else if (nChar == '3')
	{
		toolbar = 3;
	}
	else if (nChar == '4')
	{
		toolbar = 4;
	}
	else if (nChar == '5')
	{
		toolbar = 5;
	}
	else if (nChar == '6')
	{
		toolbar = 6;
	}
	else if (nChar == '7')
	{
		toolbar = 7;
	}
	else if (nChar == '8')
	{
		toolbar = 8;
	}
	else if (nChar == '9')
	{
		toolbar = 9;
	}
}
void Player::moveChest(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_UP)
	{
		if(ChestPos.Y != 0)
			ChestPos.Y -= 1;
	}
	if(nChar == VK_DOWN)
	{
		if(!(ChestPos.Y == 5 && (ChestPos.X == 0 || ChestPos.X == 9)) && !(ChestPos.Y == 6))
			ChestPos.Y += 1;
	}
	if(nChar == VK_LEFT)
	{
		if(ChestPos.X != 0 && !(ChestPos.Y == 6 && ChestPos.X == 1))
			ChestPos.X -= 1;
	}
	if(nChar == VK_RIGHT)
	{
		if(ChestPos.X != 9 && !(ChestPos.Y == 6 && ChestPos.X == 8))
			ChestPos.X += 1;
	}
	if(nChar == VK_BACK)
	{
		mod = HOUSE;
	}
	if(nChar == VK_RETURN)
	{
		if(check == -1)
		{
			check = ChestPos.Y * 10 + ChestPos.X;
		}
		else
		{
			int check2 = ChestPos.Y * 10 + ChestPos.X;
			if(check < 60 && check2 < 60)
				Object::swap(storage, storage, check, check2);
			else if(check > 60 && check2 < 60)
				Object::swap(inven, storage, check - 60, check2);
			else if(check < 60 && check2 > 60)
				Object::swap(storage, inven, check, check2 - 60);
			else
				Object::swap(inven, inven, check - 60, check2 - 60);

			check = -1;
		}
	}
}
void Player::toNextDay()
{
	if (UI::day == 30)
	{
		switch (UI::season)
		{
		case SPRING:
			UI::season = SUMMER;
			break;
		case SUMMER:
			UI::season = FALL;
			break;
		case FALL:
			UI::season = WINTER;
			break;
		case WINTER:
			UI::season = SPRING;
			break;
		default:
			break;
		}
		switch(Farm::fieldLevel)
		{
			case 1:
				for(int i = 0; i < 5; i++)
				{
					for(int j = 0; j < 8; j++)
					{
						if(Farm::field1[i][j] != NULL)
							delete Farm::field1[i][j];
						Farm::field1[i][j] = NULL;
					}
				}
				break;
			case 2:
				for(int i = 0; i < 5; i++)
				{
					for(int j = 0; j < 12; j++)
					{
						if(Farm::field2[i][j] != NULL)
							delete Farm::field2[i][j];
						Farm::field2[i][j] = NULL;
					}
				}
				break;
			case 3:
				for(int i = 0; i < 5; i++)
				{
					for(int j = 0; j < 16; j++)
					{
						if(Farm::field3[i][j] != NULL)
							delete Farm::field3[i][j];
						Farm::field3[i][j] = NULL;
					}
				}
				break;
			default:
				break;
		}
		UI::day = 1;
	}
	else UI::day++;

	if(Farm::fieldLevel == 1)
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(Farm::field1[i][j] != NULL && Farm::field1[i][j]->growthDay < Farm::field1[i][j]->untilGrow && Farm::field1[i][j]->isWater)
				{
					Farm::field1[i][j]->growthDay++;
					Farm::field1[i][j]->isWater = 0;
				}
			}
		}
	}
	if(Farm::fieldLevel == 2)
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 12; j++)
			{
				if(Farm::field2[i][j] != NULL && Farm::field2[i][j]->growthDay < Farm::field2[i][j]->untilGrow && Farm::field2[i][j]->isWater)
				{
					Farm::field2[i][j]->growthDay++;
					Farm::field2[i][j]->isWater = 0;
				}
			}
		}
	}
	if(Farm::fieldLevel == 3)
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 16; j++)
			{
				if(Farm::field3[i][j] != NULL && Farm::field3[i][j]->growthDay < Farm::field3[i][j]->untilGrow && Farm::field3[i][j]->isWater)
				{
					Farm::field3[i][j]->growthDay++;
					Farm::field3[i][j]->isWater = 0;
				}
			}
		}
	}
	Dungeon::enterDungeon = 0;
}
