#include "pch.h"
#include "Village.h"
#include "resource.h"
#include "Player.h"
#include "Object.h"
#include "UI.h"
#include "EventManager.h"
#include "User.h"
#include "Farm.h"


int Village::size;
int Village::select;
int Village::talkCount;
SHOPMOD Village::shopMod;
CBitmap Village::wallImage;
BITMAP Village::wallImageInfo;
CBitmap Village::villageImage;
BITMAP Village::villageImageInfo;
CBitmap Village::shopImage;
BITMAP Village::shopImageInfo;
CBitmap Village::shopInnerImage;
BITMAP Village::shopInnerImageInfo;
CBitmap Village::hallImage;
BITMAP Village::hallImageInfo;
CBitmap Village::hallInnerImage;
BITMAP Village::hallInnerImageInfo;
CBitmap Village::smithyImage;
BITMAP Village::smithyImageInfo;
CBitmap Village::InnerSmithyImage;
BITMAP Village::InnerSmithyImageInfo;
CBitmap Village::Fountain;
BITMAP Village::FountainInfo;
vector<vector<CString>> Village::shopObj = {
       { _T("씨앗 구매"), _T("물약 구매"), _T("판  매")},
      { _T("감자"), _T("당근"), _T("딸기"), _T("싹감자"), _T("황금 당근")},
      { _T("수박"), _T("옥수수"), _T("양배추"), _T("씨없는 수박")},
      { _T("고구마"), _T("멜론"), _T("밀"), _T("싹고구마"), _T("화이트 멜론"),},
      { _T("시금치"), _T("파"), _T("무"), _T("산딸기"), _T("알타리 무")},
        { _T("체력 물약 x 1"), _T("마나 물약 x 1"), _T("약 x 1"), _T("부활초 x 1") }
};
vector<vector<int>> Village::buyPriceObj = {
   { 400, 300, 200, 600, 1500},
   { 700, 300, 300, 750},
   { 400, 800, 400, 600, 1100},
   { 350, 350, 400, 250, 200},
   { 500, 300, 700, 2000}
};
vector<vector<int>> Village::sellPriceObj = {
   { 800, 600, 450, 800, 3000},
   { 1400, 650, 550, 1800},
   { 800, 1600, 750, 800, 2300},
   { 750, 600, 800, 500, 400},
   { 500, 300, 700, 2000}
};
vector<vector<int>> Village::duringObj = {
   { 8, 5, 4, 4, 13 },
   { 11, 6, 5, 11},
   { 8, 12, 6, 4, 12},
   { 7, 5, 6, 4, 6}
};
int Village::sellIndex;
int Village::sellCount;
int Village::smithyFlag;    
int Village::smithySelectFlag;
int Village::itemIndex1;
int Village::itemIndex2;
int Village::hallMod;
int Village::hallSelectFlag;
CWnd* Village::pWnd;
int Village::unlock;
int Village::isEnding;
int Village::ENum;

int Village::villageMap[15][25] = {
{ 0, 0, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4 },
{ 0, 0, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4 },
{ 0, 0, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4 },
{ 0, 0, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4 },
{ 7, 7, 0, 0,-3,-3, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4 },
{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-6, 0, 0, 0, 0, 0, 0, 0, 0,-4, 0, 0 },
{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void Village::setInit()
{
    villageImage.LoadBitmap(IDB_Village);
    villageImage.GetBitmap(&villageImageInfo);

    shopImage.LoadBitmap(IDB_Shop);
    shopImage.GetBitmap(&shopImageInfo);

    shopInnerImage.LoadBitmap(IDB_ShopInner);
    shopInnerImage.GetBitmap(&shopInnerImageInfo);

    hallImage.LoadBitmap(IDB_VillageHall);
    hallImage.GetBitmap(&hallImageInfo);

    smithyImage.LoadBitmap(IDB_Smithy);
    smithyImage.GetBitmap(&smithyImageInfo);

    hallInnerImage.LoadBitmap(IDB_HallMap);
    hallInnerImage.GetBitmap(&hallInnerImageInfo);

    wallImage.LoadBitmap(IDB_Wall);
    wallImage.GetBitmap(&wallImageInfo);

    InnerSmithyImage.LoadBitmap(IDB_InnerSmithy);
    InnerSmithyImage.GetBitmap(&InnerSmithyImageInfo);

    Fountain.LoadBitmap(IDB_Fountain);
    Fountain.GetBitmap(&FountainInfo);

    shopMod = SHOPMENU;
    talkCount = 0;
    select = 1;
    sellCount = -1;
    sellIndex = -1;
    smithySelectFlag = 1;
    hallMod = 1;
    unlock = 0;
    isEnding = 0;
    ENum = 0;
}
void Village::setSize(CRect in)
{
    size = in.Height() / 14 * 12 / 15;
}

void Village::drawBuilding(CDC* memdc, CBitmap& bitmap, BITMAP info, int set)
{
    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&bitmap);

    CDC tempDc;
    tempDc.CreateCompatibleDC(memdc);
    CBitmap tempBitmap;
    COLORREF transparentColor = RGB(255, 255, 255);

    int count;
    COORD upperLeft = { 25,15 }, bottomRight = { 0,0 };
    for (short i = 0; i < 15; i++)
    {
        count = 0;
        for (short j = 0; j < 25; j++)
        {
            if (villageMap[i][j] == set)
            {
                count++;
                if (upperLeft.X > j || upperLeft.Y > i)
                    upperLeft = { j,i };
                if (bottomRight.X < j || bottomRight.Y < i)
                    bottomRight = { j,i };
            }
        }
        if (upperLeft.X < bottomRight.X && count == 0)
        {
            break;
        }
    }
    tempBitmap.CreateCompatibleBitmap(memdc, (bottomRight.X - upperLeft.X + 1) * size, (bottomRight.Y - upperLeft.Y + 1) * size);
    tempDc.SelectObject(&tempBitmap);
    tempDc.StretchBlt(0, 0, (bottomRight.X - upperLeft.X + 1) * size, (bottomRight.Y - upperLeft.Y + 1) * size, &imageDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
    memdc->TransparentBlt(upperLeft.X * size, upperLeft.Y * size, (bottomRight.X - upperLeft.X + 1) * size, (bottomRight.Y - upperLeft.Y + 1) * size, &tempDc, 0, 0, (bottomRight.X - upperLeft.X + 1) * size, (bottomRight.Y - upperLeft.Y + 1) * size, transparentColor);

}
void Village::drawVillage(CDC* memdc)
{
    int x = 0;
    int y = 0;
    memdc->SelectStockObject(WHITE_BRUSH);
    memdc->Rectangle(0, 0, size * 50, size * 50);


    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&villageImage);

    CDC wallDC;
    wallDC.CreateCompatibleDC(memdc);
    wallDC.SelectObject(&wallImage);

    memdc->StretchBlt(0, 0, size * 25, size * 15, &imageDC, 0, 0, villageImageInfo.bmWidth, villageImageInfo.bmHeight, SRCCOPY);
    for (int i = 0; i < 25; i++)
    {
        memdc->StretchBlt(x, size, size, size * 2, &wallDC, 0, 0, wallImageInfo.bmWidth, wallImageInfo.bmHeight, SRCCOPY);
        x += size;
    }
    x = 0;
    drawBuilding(memdc, shopImage, shopImageInfo, 3);
    drawBuilding(memdc, hallImage, hallImageInfo, 6);
    drawBuilding(memdc, smithyImage, smithyImageInfo, 4);
    drawBuilding(memdc, Fountain, FountainInfo, 5);
}

void Village::drawShop(CDC* memdc)
{
    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&shopInnerImage);
    memdc->StretchBlt(0, 0, size * 25, size * 15, &imageDC, 0, 0, shopInnerImageInfo.bmWidth, shopInnerImageInfo.bmHeight, SRCCOPY);

    CDC temp;
    temp.CreateCompatibleDC(&temp);
    CBitmap tempBIT;
    tempBIT.CreateBitmap(size * 4, size * 4, 1, 24, NULL);
    temp.SelectObject(&tempBIT);
    temp.SelectStockObject(WHITE_BRUSH);
    temp.Rectangle(0, 0, size * 4, size * 4);


    LOGFONT logFont = { 0 };
    lstrcpy(logFont.lfFaceName, _T("굴림"));
    logFont.lfHeight = -size * 0.5;
    logFont.lfWidth = 0;
    logFont.lfWeight = FW_BOLD;
    logFont.lfItalic = FALSE;

    CFont font;
    font.CreateFontIndirect(&logFont);
    memdc->SelectObject(font);
    memdc->SetTextColor(RGB(255, 255, 255));
    memdc->SetBkMode(TRANSPARENT);




    int x = size * 2;
    int y = size * 10;
    if ((EventManager::EventFlag & FirstShop) == false)
    {
        memdc->TextOutW(x, y + size * 1.5, EventManager::ShopTalk[talkCount]);
        if (talkCount == 5)
        {
            Player::inven[2] = new PotatoSeed();
            Player::inven[2]->count = 20;
        }
    }
    else
    {
        int set = 0;
        if (shopMod == SHOPMENU)
        {
            set = 0;
            for (int i = 0; i < shopObj[set].size(); i++)
            {
                memdc->TextOutW(x, y, shopObj[set][i]);
                if (select == i + 1)
                {
                    memdc->SelectStockObject(WHITE_PEN);
                    memdc->SelectStockObject(WHITE_BRUSH);
                    POINT triangle[3] = { {x - size * 1.3, y - size * 0.1}, {x - size * 0.7, y + size * 0.2}, {x - size * 1.3, y + size * 0.5} };  // 삼각형의 세 꼭짓점 좌표
                    memdc->Polygon(triangle, 3);
                }
                y += size * 1.5;
            }
        }
        if (shopMod == SEED)
        {
            switch (UI::season)
            {
            case SPRING:
                set = 1;
                break;
            case SUMMER:
                set = 2;
                break;
            case FALL:
                set = 3;
                break;
            case WINTER:
                set = 4;
                break;
            default:
                break;
            }
            for (int i = 0; i < shopObj[set].size(); i++)
            {
                if ((set == 1 && i < 3) || (set == 2 && i < 3) || (set == 3 && i < 3) || (set == 4 && i < 4))
                    memdc->TextOutW(x, y, shopObj[set][i] + _T(" 씨앗 X 5"));
                else if (set == 1 && i == 3 && (EventManager::EventFlag & SellPotato) == SellPotato)
                    memdc->TextOutW(x, y, shopObj[set][i] + _T(" 씨앗 X 5"));
                else if (set == 1 && i == 4 && (EventManager::EventFlag & AllSpring) == AllSpring)
                    memdc->TextOutW(x, y, shopObj[set][i] + _T(" 씨앗 X 5"));
                else if (set == 2 && i == 3 && (EventManager::EventFlag & AllSummer) == AllSummer)
                    memdc->TextOutW(x, y, shopObj[set][i] + _T(" 씨앗 X 5"));
                else if (set == 3 && i == 3 && (EventManager::EventFlag & SellSweetPotato) == SellSweetPotato)
                    memdc->TextOutW(x, y, shopObj[set][i] + _T(" 씨앗 X 5"));
                else if (set == 3 && i == 4 && (EventManager::EventFlag & OneFall) == OneFall)
                    memdc->TextOutW(x, y, shopObj[set][i] + _T(" 씨앗 X 5"));
                else if (set == 4 && i == 4 && (EventManager::EventFlag & SellSativus) == SellSativus)
                    memdc->TextOutW(x, y, shopObj[set][i] + _T(" 씨앗 X 5"));


                if (select == i + 1)
                {
                    memdc->SelectStockObject(WHITE_PEN);
                    memdc->SelectStockObject(WHITE_BRUSH);
                    POINT triangle[3] = { {x - size * 1.3, y - size * 0.1}, {x - size * 0.7, y + size * 0.2}, {x - size * 1.3, y + size * 0.5} };  // 삼각형의 세 꼭짓점 좌표
                    memdc->Polygon(triangle, 3);
                }
                y += size * 1.5;
                if (i == 2)
                {
                    x = size * 13;
                    y = size * 10;
                }
            }

            CBitmap info;
            CDC infoDC;
            BITMAP infoInfo;
            info.LoadBitmap(IDB_Frame);
            info.GetBitmap(&infoInfo);
            infoDC.CreateCompatibleDC(memdc);
            infoDC.SelectObject(info);

            memdc->SetTextColor(RGB(0, 0, 0));
            memdc->TransparentBlt(size * 0.3, size * 5.3, size * 7.4, size * 3, &infoDC, 0, 0, infoInfo.bmWidth, infoInfo.bmHeight, RGB(255, 255, 255));

            CString str1, str2, str3;
            str1.Format(_T("씨앗 개 당 구매 가격 : %d"), buyPriceObj[set - 1][select - 1]);
            str2.Format(_T("작물 개 당 판매 가격 : %d"), sellPriceObj[set - 1][select - 1]);
            str3.Format(_T("자라는 시간 : %d"), duringObj[set - 1][select - 1]);
            CSize textSize = memdc->GetTextExtent(str1);
            int text_W = size * 4 - (textSize.cx / 2);
            int text_H = size * 5.5;
            memdc->TextOutW(text_W, text_H, str1);

            textSize = memdc->GetTextExtent(str2);
            text_W = size * 4 - (textSize.cx / 2);
            text_H = size * 6.5;
            memdc->TextOutW(text_W, text_H, str2);

            textSize = memdc->GetTextExtent(str3);
            text_W = size * 4 - (textSize.cx / 2);
            text_H = size * 7.5;
            memdc->TextOutW(text_W, text_H, str3);
        }
        if (shopMod == POTION)
        {
            for (int i = 0; i < shopObj[5].size(); i++)
            {

                if (select == i + 1)
                {
                    memdc->SelectStockObject(WHITE_PEN);
                    memdc->SelectStockObject(WHITE_BRUSH);
                    POINT triangle[3] = { {x - size * 1.3, y - size * 0.1}, {x - size * 0.7, y + size * 0.2}, {x - size * 1.3, y + size * 0.5} };  // 삼각형의 세 꼭짓점 좌표
                    memdc->Polygon(triangle, 3);
                }
                memdc->TextOutW(x, y, shopObj[5][i]);

                y += size * 1.5;
                if (i == 2)
                {
                    x = size * 13;
                    y = size * 10;
                }
            }

            CBitmap info;
            CDC infoDC;
            BITMAP infoInfo;
            info.LoadBitmap(IDB_Frame);
            info.GetBitmap(&infoInfo);
            infoDC.CreateCompatibleDC(memdc);
            infoDC.SelectObject(info);

            memdc->SetTextColor(RGB(0, 0, 0));
            memdc->TransparentBlt(size * 0.3, size * 5.3, size * 7.4, size * 3, &infoDC, 0, 0, infoInfo.bmWidth, infoInfo.bmHeight, RGB(255, 255, 255));

            CString str1, str2;
            str1.Format(shopObj[5][select - 1] + _T("개 가격 : %d"), buyPriceObj[4][select - 1]);
            CSize textSize = memdc->GetTextExtent(str1);
            int text_W = size * 4 - (textSize.cx / 2);
            int text_H = size * 6.5;
            memdc->TextOutW(text_W, text_H, str1);
        }
        if (shopMod == SELL)
        {
            CPoint upTriangle[3] = { { (int)(x + size * 13.7),y + size}, {(int)(x + size * 14.7),y + size},{(int)(x + size * 14.2),(int)(y + size * 0.5)} };
            CPoint lowerTriangle[3] = { { (int)(x + size * 13.7),(int)(y + size * 3.2)}, {(int)(x + size * 14.7),(int)(y + size * 3.2)},{(int)(x + size * 14.2),(int)(y + size * 3.7)} };
            memdc->Rectangle(x + size * 2.9, y - size * 0.1, x + size * 7.1, y + size * 4.1);
            memdc->SelectStockObject(WHITE_BRUSH);
            memdc->Rectangle(x + size * 3, y, x + size * 7, y + size * 4);
            if (sellIndex != -1)
            {
                CFont num;
                num.CreatePointFont(size * 3, _T("배달의민족 주아"));
                memdc->SelectObject(num);
                Player::inven[sellIndex]->draw(memdc, x + size * 3, y, size * 4, 0);
                CString str;
                str.Format(_T("%d"), sellCount);
                memdc->SelectObject(font);
                memdc->TextOutW(x + size * 14, y + size * 1.7, str);
                if (sellCount != Player::inven[sellIndex]->count)
                    memdc->Polygon(upTriangle, 3);
                if (sellCount != 1)
                    memdc->Polygon(lowerTriangle, 3);
            }
        }
    }


    CBitmap lock;
    BITMAP lockInfo;
    CDC lockDC;
    lockDC.CreateCompatibleDC(memdc);
    switch (unlock)
    {
    case 1:
        lock.LoadBitmapW(IDB_Unlock1);
        break;
    case 2:
        lock.LoadBitmapW(IDB_Unlock6);
        break;
    case 3:
        lock.LoadBitmapW(IDB_Unlock2);
        break;
    case 4:
        lock.LoadBitmapW(IDB_Unlock5);
        break;
    case 5:
        lock.LoadBitmapW(IDB_Unlock4);
        break;
    case 6:
        lock.LoadBitmapW(IDB_Unlock3);
        break;
    default:
        break;
    }

    if (unlock != 0)
    {
        lock.GetBitmap(&lockInfo);
        lockDC.SelectObject(lock);

        memdc->TransparentBlt(size * 21, 0, size * 4, size * 2, &lockDC, 0, 0, lockInfo.bmWidth, lockInfo.bmHeight, RGB(255, 255, 255));
    }
}
void Village::shopSelect(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (!(EventManager::EventFlag & FirstShop) && nChar == VK_RETURN)
    {
        talkCount++;
        if (talkCount == EventManager::ShopTalk.size())
        {
            EventManager::EventFlag = EventManager::EventFlag | FirstShop;
            Player::mod = VILLAGE;
            Player::look = DOWN;
            talkCount = 0;
        }
        return;
    }
    if (EventManager::EventFlag & FirstShop)
    {
        if (nChar == VK_RETURN)
        {
            if (shopMod == SHOPMENU)
            {
                switch (select)
                {
                case 1:
                    shopMod = SEED;
                    break;
                case 2:
                    shopMod = POTION;
                    break;
                case 3:
                    shopMod = SELL;
                    sellIndex = -1;
                default:
                    break;
                }
                select = 1;
            }
            else if (shopMod == SEED || shopMod == POTION)
            {
                inputInven();
            }
            else if (shopMod == SELL)
            {
                if (sellIndex != -1)
                {
                    switch (Player::inven[sellIndex]->type)
                    {
                    case POTATO:
                        EventManager::springFlag = EventManager::springFlag | POTATOFLAG;
                        break;
                    case CARROT:
                        EventManager::springFlag = EventManager::springFlag | CARROTFLAG;
                        break;
                    case STRAWBERRY:
                        EventManager::springFlag = EventManager::springFlag | STRAWBERRYFLAG;
                        break;
                    case WATERMELON:
                        EventManager::summerFlag = EventManager::summerFlag | WATERMELONFLAG;
                        break;
                    case CORN:
                        EventManager::summerFlag = EventManager::summerFlag | CORNFLAG;
                        break;
                    case CABBAGE:
                        EventManager::summerFlag = EventManager::summerFlag | CABBAGEFLAG;
                        break;
                    case SWEETPOTATO:
                        if (SellSweetPotato != (EventManager::EventFlag & SellSweetPotato))
                        {
                            unlock = 4;
                            pWnd->SetTimer(12, 5000, NULL);
                        }
                        EventManager::EventFlag = EventManager::EventFlag | SellSweetPotato;
                        EventManager::EventFlag = EventManager::EventFlag | OneFall;
                        break;
                    case WHEAT:
                    case MELON:
                        if (OneFall != (EventManager::EventFlag & OneFall))
                        {
                            pWnd->SetTimer(13, 5000, NULL);
                            unlock = 5;
                        }
                        EventManager::EventFlag = EventManager::EventFlag | OneFall;
                        break;
                    case SATIVUS:
                        EventManager::EventFlag = EventManager::EventFlag | SellSativus;
                        pWnd->SetTimer(14, 5000, NULL);
                    default:
                        break;
                    }
                    if ((EventManager::springFlag & POTATOFLAG) == POTATOFLAG && SellPotato != (EventManager::EventFlag & SellPotato))
                    {
                        EventManager::EventFlag = EventManager::EventFlag | SellPotato;
                        pWnd->SetTimer(9, 5000, NULL);
                        unlock = 1;
                    }
                    if (EventManager::springFlag == 0b111 && AllSpring != (EventManager::EventFlag & AllSpring))
                    {
                        EventManager::EventFlag = EventManager::EventFlag | AllSpring;
                        if (unlock != 1)
                        {
                            pWnd->SetTimer(10, 5000, NULL);
                            unlock = 2;
                        }
                    }
                    if (EventManager::summerFlag == 0b111 && AllSummer != (EventManager::EventFlag & AllSummer))
                    {
                        EventManager::EventFlag = EventManager::EventFlag | AllSummer;
                        pWnd->SetTimer(11, 5000, NULL);
                        unlock = 3;
                    }
                    Player::inven[sellIndex]->count -= sellCount;
                    UI::money += Player::inven[sellIndex]->price * sellCount;
                    if (Player::inven[sellIndex]->count <= 0)
                    {
                        delete Player::inven[sellIndex];
                        Player::inven[sellIndex] = NULL;
                    }
                    sellIndex = -1;
                    sellCount = -1;
                }
                else if (Player::toolbar != 1 && Player::inven[Player::toolbar - 1] != NULL)
                {
                    sellIndex = Player::toolbar - 1;
                    sellCount = 1;
                }
            }
        }
        else if (nChar == VK_UP)
        {
            switch (shopMod)
            {
            case SHOPMENU:
                if (!(select == 1))
                    select--;


                break;
            case SEED:
                if (!(select == 1 || select == 4))
                    select--;

                if (UI::season == FALL && ((EventManager::EventFlag & SellSweetPotato) != SellSweetPotato) && select == 4)
                {
                    select = 5;
                }
                else if (UI::season == SPRING && ((EventManager::EventFlag & SellPotato) != SellPotato) && select == 4)
                {
                    select = 5;
                }
                break;
            case POTION:
                if (!(select == 1 || select == 4))
                    select--;
                break;
            case SELL:
                if (sellIndex != -1 && sellCount != Player::inven[sellIndex]->count)
                {
                    sellCount += 1;
                }
                break;
            default:
                break;
            }
        }
        else if (nChar == VK_DOWN)
        {
            switch (shopMod)
            {
            case SHOPMENU:
                if (!(select == 3))
                    select++;
                break;
            case SEED:
                if (!(select == 3 || select == 6 || shopObj[UI::season + 1].size() < select + 1))
                    select++;
                if (UI::season == WINTER && ((EventManager::EventFlag & SellSativus) != SellSativus) && select == 5)
                {
                    select = 4;
                }
                else if (UI::season == SPRING && ((EventManager::EventFlag & AllSpring) != AllSpring) && select == 5)
                {
                    select = 4;
                }
                else if (UI::season == FALL && ((EventManager::EventFlag & OneFall) != OneFall) && select == 5)
                {
                    select = 4;
                }
                break;
            case POTION:
                if (!(select == 3 || select == 4))
                    select++;
                break;
            case SELL:
                if (sellIndex != -1 && sellCount != 1)
                {
                    sellCount -= 1;
                }
                break;
            default:
                break;
            }
        }
        else if (nChar == VK_LEFT)
        {
            switch (shopMod)
            {
            case SHOPMENU:
                break;
            case SEED:
            case POTION:
                if (!(select <= 3))
                    select -= 3;
                break;
            case SELL:
                break;
            default:
                break;
            }
        }
        else if (nChar == VK_RIGHT)
        {
            switch (shopMod)
            {
            case SHOPMENU:
                break;
            case SEED:
                if (!(select >= 4 || shopObj[UI::season + 1].size() < select + 3))
                    select += 3;

                if (UI::season == WINTER && ((EventManager::EventFlag & SellSativus) != SellSativus) && select == 5)
                {
                    select = 2;
                }
                else if (UI::season == SPRING && ((EventManager::EventFlag & SellPotato) != SellPotato) && select == 4)
                {
                    select = 1;
                }
                else if (UI::season == SPRING && ((EventManager::EventFlag & AllSpring) != AllSpring) && select == 5)
                {
                    select = 2;
                }
                else if (UI::season == SUMMER && ((EventManager::EventFlag & AllSummer) != AllSummer) && select == 4)
                {
                    select = 1;
                }
                else if (UI::season == FALL && ((EventManager::EventFlag & SellSweetPotato) != SellSweetPotato) && select == 4)
                {
                    select = 1;
                }
                else if (UI::season == FALL && ((EventManager::EventFlag & OneFall) != OneFall) && select == 5)
                {
                    select = 2;
                }

                break;
            case POTION:
                if (select == 1)
                    select += 3;
                break;
            case SELL:
                break;
            default:
                break;
            }
        }
        else if (nChar == VK_BACK)
        {
            switch (shopMod)
            {
            case SHOPMENU:
                Player::mod = VILLAGE;
                Player::look = DOWN;
                break;
            case SEED:
            case POTION:
            case SELL:
                shopMod = SHOPMENU;
                select = 1;
                break;
            default:
                break;
            }
        }
    }

}

void Village::inputInven()
{
    Object* temp = NULL;
    int flag = 0;
    int inputIndex = -1;

    if (shopMod == SEED)
    {
        switch (UI::season)
        {
        case SPRING:
            if (select == 1)
                temp = new PotatoSeed();
            else if (select == 2)
                temp = new CarrotSeed();
            else if (select == 3)
                temp = new StrawberrySeed();
            else if (select == 4)
                temp = new SproutedPotatoSeed();
            else if (select == 5)
                temp = new GoldenCarrotSeed();
            break;
        case SUMMER:
            if (select == 1)
                temp = new WaterMelonSeed();
            else if (select == 2)
                temp = new CornSeed();
            else if (select == 3)
                temp = new CabbageSeed();
            else if (select == 4)
                temp = new SeedlessWatermelonSeed();
            break;
        case FALL:
            if (select == 1)
                temp = new SweetPotatoSeed();
            else if (select == 2)
                temp = new MelonSeed();
            else if (select == 3)
                temp = new WheatSeed();
            else if (select == 4)
                temp = new SproutedSweetPotatoSeed();
            else if (select == 5)
                temp = new WhiteMelonSeed();
            break;
        case WINTER:
            if (select == 1)
                temp = new SpinachSeed();
            else if (select == 2)
                temp = new GreenOnionSeed();
            else if (select == 3)
                temp = new RadishSeed();
            else if (select == 4)
                temp = new RaspberrySeed();
            else if (select == 5)
                temp = new SativusSeed();
            break;
        default:
            break;
        }
    }
    else if (shopMod == POTION)
    {
        if (select == 1)
            temp = new HPPotion();
        else if (select == 2)
            temp = new MPPotion();
        else if (select == 3)
            temp = new Panaacea();
        else if (select == 4)
        {
            temp = new Revival();
        }
    }

    if (temp->price * 5 > UI::money && shopMod == SEED)
    {
        return; //가격 안됨 메세지
    }
    else if (shopMod == SEED)
        UI::money -= temp->price * 5;

    if (temp->price > UI::money && shopMod == POTION)
    {
        return;
    }
    else if (shopMod == POTION)
        UI::money -= temp->price;
    for (int i = 1; temp != NULL && i < 9; i++)
    {
        if (Player::inven[i] != NULL && Player::inven[i]->type == temp->type)
        {
            flag = 1;
            if (shopMod == SEED)
                Player::inven[i]->count += 5;
            else if (shopMod == POTION)
                Player::inven[i]->count += 1;
        }
        if (inputIndex == -1 && Player::inven[i] == NULL)
            inputIndex = i;
    }
    if (inputIndex == -1)
    {
        if (temp == NULL)
            free(temp);
        return; // 메세지 상자 출력하기
    }
    if (flag == 0 && temp != NULL)
    {
        Player::inven[inputIndex] = temp;
        return;
    }
    if (temp == NULL)
        free(temp);
}

void Village::drawHall(CDC* memdc)
{
    CBitmap field;
    BITMAP fieldInfo;
    field.LoadBitmap(IDB_Soil);
    field.GetBitmap(&fieldInfo);


    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&hallInnerImage);

    CDC fieldDC;
    fieldDC.CreateCompatibleDC(memdc);
    fieldDC.SelectObject(&field);

    LOGFONT logFont = { 0 };
    lstrcpy(logFont.lfFaceName, _T("굴림"));
    logFont.lfHeight = -size * 0.48;
    logFont.lfWidth = 0;
    logFont.lfWeight = FW_BOLD;
    logFont.lfItalic = FALSE;

    CFont font;
    font.CreateFontIndirectW(&logFont);
    memdc->SelectObject(font);
    memdc->SetTextColor(RGB(255, 255, 255));
    memdc->SetBkMode(TRANSPARENT);

    memdc->StretchBlt(0, 0, size * 25, size * 15, &imageDC, 0, 0, hallInnerImageInfo.bmWidth, hallInnerImageInfo.bmHeight, SRCCOPY);

    int x = size * 2;
    int y = size * 10;
    if ((EventManager::EventFlag & FirstHall) == false)
    {
        if (talkCount == 4)
            Player::inven[1] = new HPPotion();
        memdc->TextOutW(x, y + size * 0.5, EventManager::HallTalk[talkCount]);
        if (talkCount == 1 || talkCount == 4 || talkCount == 9 || talkCount == 11 || talkCount == 13 || talkCount == 22)
        {
            talkCount++;
            memdc->TextOutW(x, y + size * 2, EventManager::HallTalk[talkCount]);
        }
    }
    else
    {

        if (hallMod == 1)
        {
            POINT triangle[3] = { {x + size, y + size * 0.4}, {x + size * 1.6, y + size * 0.7}, {x + size, y + size} };  // 삼각형의 세 꼭짓점 좌표
            if (hallSelectFlag == 2)
            {
                for (int i = 0; i < 3; i++)
                    triangle[i].y += size * 2.5;
            }
            memdc->TextOutW(x + size * 2, y + size * 0.5, _T("밭 확장하기"));
            memdc->TextOutW(x + size * 2, y + size * 3, _T("빚 갚기"));
            memdc->Polygon(triangle, 3);
        }
        else if (hallMod == 2)
        {
            POINT triangle[3] = { {x + size, y + size * 0.4}, {x + size * 1.6, y + size * 0.7}, {x + size, y + size} };  // 삼각형의 세 꼭짓점 좌표
            if (hallSelectFlag == 2)
            {
                for (int i = 0; i < 3; i++)
                    triangle[i].y += size * 2.5;
            }
            memdc->TextOutW(x + size * 2, y + size * 0.5, _T("확장하기"));
            memdc->TextOutW(x + size * 2, y + size * 3, _T("돌아가기"));
            memdc->Polygon(triangle, 3);

            CString price;
            if (Farm::fieldLevel == 1)
                price.Format(_T("%d / 10000"), UI::money);
            else if (Farm::fieldLevel == 2)
                price.Format(_T("%d / 20000"), UI::money);

            if ((Farm::fieldLevel == 1 && UI::money < 10000) || (Farm::fieldLevel == 2 && UI::money < 20000))
                memdc->SetTextColor(RGB(222, 0, 0));
            memdc->TextOutW(x + size * 5, y + size * 1.5, price);
            memdc->SetTextColor(RGB(255, 255, 255));
            memdc->StretchBlt(x + size * 12, y + size * 0.3, size * 3, size * 3, &fieldDC, 0, 0, fieldInfo.bmWidth, fieldInfo.bmHeight, SRCCOPY);

            LOGFONT logFont = { 0 };
            lstrcpy(logFont.lfFaceName, _T("굴림"));
            logFont.lfHeight = -size * 0.48;
            logFont.lfWidth = 0;
            logFont.lfWeight = FW_NORMAL;
            logFont.lfItalic = FALSE;

            CFont font2;
            logFont.lfHeight = -size * 2;
            font2.CreateFontIndirectW(&logFont);
            memdc->SelectObject(font2);
            memdc->TextOutW(x + size * 10, y + size * 0.5, _T("➨"));
            memdc->TextOutW(x + size * 16, y + size * 0.7, __T("X 20"));
        }
        else if (hallMod == 3)
        {
            POINT triangle[3] = { {x + size, y + size * 0.4}, {x + size * 1.6, y + size * 0.7}, {x + size, y + size} };  // 삼각형의 세 꼭짓점 좌표
            if (hallSelectFlag == 2)
            {
                for (int i = 0; i < 3; i++)
                    triangle[i].y += size * 2.5;
            }
            memdc->TextOutW(x + size * 2, y + size * 0.5, _T("빚을 갚는다"));
            memdc->TextOutW(x + size * 2, y + size * 3, _T("돌아가기"));
            memdc->Polygon(triangle, 3);



            CString price;
            if (UI::money < 200000 && isEnding != 2)
                memdc->SetTextColor(RGB(222, 0, 0));
            if (isEnding == 2)
                price.Format(_T("%d / 0"), UI::money);
            else
                price.Format(_T("%d / 200000"), UI::money);
            memdc->TextOutW(x + size * 10, y + size * 1.5, price);
            memdc->SetTextColor(RGB(255, 255, 255));
        }

    }
}
void Village::drawSmithy(CDC* memdc)
{
    if (!(EventManager::EventFlag & FirstShop))
    {
        Village::drawVillage(memdc);
        Player::mod = VILLAGE;
        return;
    }

    smithyFlag = 0;
    CBitmap bitmap1, bitmap2;
    Object* toPrint1 = NULL;
    Object* toPrint2 = NULL;
    itemIndex1 = -1;
    itemIndex2 = -1;

    if (User::level == 1)
    {
        toPrint1 = new BossItem1();
        toPrint2 = new BossItem2();
        bitmap1.LoadBitmap(IDB_Sword_2); // 첫 번째 비트맵 리소스
        bitmap2.LoadBitmap(IDB_Armor_2);
        for (int i = 1; i < 9; i++)
        {
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM1)
                itemIndex1 = i;
        }
    }
    else if (User::level == 2)
    {
        toPrint1 = new BossItem1();
        toPrint2 = new BossItem2();
        bitmap1.LoadBitmap(IDB_Sword_3); // 첫 번째 비트맵 리소스
        bitmap2.LoadBitmap(IDB_Armor_3);
        for (int i = 1; i < 9; i++)
        {
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM1)
                itemIndex1 = i;
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM2)
                itemIndex2 = i;
        }
    }
    else if (User::level == 3)
    {
        toPrint1 = new BossItem2();
        toPrint2 = new BossItem3();
        bitmap1.LoadBitmap(IDB_Sword_4); // 첫 번째 비트맵 리소스
        bitmap2.LoadBitmap(IDB_Armor_4);
        for (int i = 1; i < 9; i++)
        {
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM2)
                itemIndex1 = i;
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM3)
                itemIndex2 = i;
        }
    }
    else if (User::level == 4)
    {
        toPrint1 = new BossItem3();
        toPrint2 = new BossItem4();
        bitmap1.LoadBitmap(IDB_Sword_5); // 첫 번째 비트맵 리소스
        bitmap2.LoadBitmap(IDB_Armor_5);
        for (int i = 1; i < 9; i++)
        {
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM3)
                itemIndex1 = i;
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM4)
                itemIndex2 = i;
        }
    }
    else if (User::level == 5)
    {
        toPrint1 = new BossItem4();
        toPrint2 = new BossItem5();
        bitmap1.LoadBitmap(IDB_Sword_5); // 첫 번째 비트맵 리소스
        bitmap2.LoadBitmap(IDB_Armor_5);
        for (int i = 1; i < 9; i++)
        {
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM4)
                itemIndex1 = i;
            if (Player::inven[i] != NULL && Player::inven[i]->type == BOSSITEM5)
                itemIndex2 = i;
        }
    }

    BITMAP bmp1, bmp2;
    bitmap1.GetBitmap(&bmp1);
    bitmap2.GetBitmap(&bmp2);

    CDC Temp;
    CDC Temp2;
    CDC SwordDC;
    CDC ArmorDC;
    Temp.CreateCompatibleDC(memdc);
    Temp2.CreateCompatibleDC(memdc);
    Temp.SelectObject(bitmap1);
    Temp2.SelectObject(bitmap2);

    SwordDC.CreateCompatibleDC(&Temp2);
    CBitmap tempBitmap1;
    tempBitmap1.CreateCompatibleBitmap(&Temp, bmp1.bmWidth, bmp1.bmHeight);
    SwordDC.SelectObject(&tempBitmap1);
    SwordDC.BitBlt(0, 0, bmp1.bmWidth, bmp1.bmHeight, &Temp, 0, 0, SRCCOPY);

    ArmorDC.CreateCompatibleDC(&Temp);
    CBitmap tempBitmap2;
    tempBitmap2.CreateCompatibleBitmap(&Temp2, bmp2.bmWidth, bmp2.bmHeight);
    ArmorDC.SelectObject(&tempBitmap2);
    ArmorDC.BitBlt(0, 0, bmp2.bmWidth, bmp2.bmHeight, &Temp2, 0, 0, SRCCOPY);

    POINT triangle[3] = {
       {0,0},
       {bmp2.bmWidth,0},
       {bmp2.bmWidth,bmp2.bmHeight}
    };
    ArmorDC.Polygon(triangle, 3);


    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&InnerSmithyImage);

    LOGFONT logFont = { 0 };
    lstrcpy(logFont.lfFaceName, _T("굴림"));
    logFont.lfHeight = -size * 0.48;
    logFont.lfWidth = 0;
    logFont.lfWeight = FW_BOLD;
    logFont.lfItalic = FALSE;

    CFont font;
    CFont font2;
    font.CreateFontIndirectW(&logFont);
    logFont.lfHeight = -size * 2;
    font2.CreateFontIndirectW(&logFont);
    memdc->SelectObject(font);
    memdc->SetTextColor(RGB(255, 255, 255));
    memdc->SetBkMode(TRANSPARENT);

    memdc->StretchBlt(0, 0, size * 25, size * 15, &imageDC, 0, 0, InnerSmithyImageInfo.bmWidth, InnerSmithyImageInfo.bmHeight, SRCCOPY);

    int x = size * 2;
    int y = size * 10;
    if ((EventManager::EventFlag & FirstSmithy) == false)
    {
        memdc->TextOutW(x, y + size * 1.5, EventManager::SmithyTalk[talkCount]);
        if (talkCount == 5)
        {
            Player::inven[0] = new WaterCan();
        }
    }
    else
    {
        memdc->SelectStockObject(BLACK_BRUSH);
        memdc->Rectangle(x + size * 10.9, y - size * 0.1, x + size * 15.1, y + size * 4.1);
        memdc->SelectStockObject(WHITE_BRUSH);
        memdc->StretchBlt(x + size * 11, y, size * 4, size * 4, &SwordDC, 0, 0, bmp1.bmWidth, bmp1.bmHeight, SRCCOPY);
        memdc->TransparentBlt(x + size * 11, y, size * 4, size * 4, &ArmorDC, 0, 0, bmp2.bmWidth, bmp2.bmHeight, RGB(255, 255, 255));

        CString str1;
        CString str2;

        if (User::level != 1)
        {
            if (itemIndex1 == -1)
                str1.Format(_T("0 / 5"));
            else
            {
                str1.Format(_T("%d / 5"), Player::inven[itemIndex1]->count);
            }
        }
        else
        {
            if (itemIndex1 == -1)
                str1.Format(_T("0 / 2"));
            else
            {
                str1.Format(_T("%d / 2"), Player::inven[itemIndex1]->count);
                if (Player::inven[itemIndex1]->count >= 2)
                    smithyFlag = 1;
            }
        }

        if (User::level != 1)
        {
            if (itemIndex2 == -1)
                str2.Format(_T("0 / 2"));
            else
            {
                str2.Format(_T("%d / 2"), Player::inven[itemIndex2]->count);
                if (Player::inven[itemIndex1]->count >= 5 && Player::inven[itemIndex2]->count >= 2)
                    smithyFlag = 1;
            }
        }
        memdc->SelectObject(font);

        if (smithySelectFlag == 0)
            memdc->SetTextColor(RGB(255, 0, 0));
        memdc->TextOutW(x + size * 16.5, y + size * 0.5, _T("강화한다"));

        memdc->SetTextColor(RGB(255, 255, 255));

        if (smithySelectFlag == 1)
            memdc->SetTextColor(RGB(255, 0, 0));
        memdc->TextOutW(x + size * 16.5, y + size * 2.6, _T("아 니 오"));

        memdc->SetTextColor(RGB(255, 255, 255));

        toPrint1->draw(memdc, x, y - size * 0.5, size * 4, 0);
        memdc->TextOutW(x + size, y + size * 4, str1);
        if (User::level != 1)
        {
            toPrint2->draw(memdc, x + size * 4, y - size * 0.5, size * 4, 0);
            memdc->TextOutW(x + size * 5, y + size * 4, str2);
        }


        memdc->SelectObject(font2);
        memdc->TextOutW(x + size * 8, y + size * 0.8, _T("➨"));

    }
    delete toPrint1;
}
void Village::SmithySelect(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (!(EventManager::EventFlag & FirstSmithy) && nChar == VK_RETURN)
    {
        talkCount++;
        if (talkCount == EventManager::SmithyTalk.size())
        {
            EventManager::EventFlag = EventManager::EventFlag | FirstSmithy;
            Player::mod = VILLAGE;
            Player::look = DOWN;
            talkCount = 0;
        }
    }
    if (EventManager::EventFlag & FirstSmithy)
    {
        if (nChar == VK_BACK)
        {
            Player::mod = VILLAGE;
            Player::look = DOWN;
        }
        if (nChar == VK_UP)
        {
            smithySelectFlag = 0;
        }
        if (nChar == VK_DOWN)
        {
            smithySelectFlag = 1;
        }
        if (nChar == VK_RETURN && smithyFlag == 1 && smithySelectFlag == 0)
        {
            if (User::level == 1)
            {
                Player::inven[itemIndex1]->count -= 2;
                if (Player::inven[itemIndex1]->count == 0)
                {
                    delete Player::inven[itemIndex1];
                    Player::inven[itemIndex1] = NULL;
                }
            }
            else
            {
                Player::inven[itemIndex1]->count -= 5;
                if (Player::inven[itemIndex1]->count == 0)
                {
                    delete Player::inven[itemIndex1];
                    Player::inven[itemIndex1] = NULL;
                }
                Player::inven[itemIndex2]->count -= 2;
                if (Player::inven[itemIndex2]->count == 0)
                {
                    delete Player::inven[itemIndex2];
                    Player::inven[itemIndex2] = NULL;
                }
            }
            User::setItem(User::level + 1);

        }
    }
}
void Village::hallSelect(UINT nChar, UINT nRepCnt, UINT nFlags)
{

    if (!(EventManager::EventFlag & FirstHall) && nChar == VK_RETURN)
    {
        talkCount++;
        if (talkCount == EventManager::HallTalk.size())
        {
            EventManager::EventFlag = EventManager::EventFlag | FirstHall;
            Player::mod = VILLAGE;
            Player::look = DOWN;
            talkCount = 0;
        }
    }
    if (EventManager::EventFlag & FirstHall)
    {
        if (nChar == VK_BACK)
        {
            if (hallMod == 1)
            {
                Player::mod = VILLAGE;
                Player::look = DOWN;
            }
            else if (hallMod == 2 || hallMod == 3)
            {
                hallMod = 1;
            }
        }
        if (nChar == VK_UP)
        {
            hallSelectFlag = 1;
        }
        if (nChar == VK_DOWN)
        {
            hallSelectFlag = 2;
        }
        if (nChar == VK_RETURN)
        {
            if (hallMod == 1)
            {
                if (hallSelectFlag == 1)
                    hallMod = 2;
                else
                    hallMod = 3;

                hallSelectFlag = 2;
            }
            else if (hallMod == 2)
            {
                if (hallSelectFlag == 1)
                {
                    if (Farm::fieldLevel == 1 && UI::money >= 10000)
                    {
                        Farm::upgradeField();
                        UI::money -= 10000;
                    }
                    else if (Farm::fieldLevel == 2 && UI::money >= 20000)
                    {
                        Farm::upgradeField();
                        UI::money -= 20000;
                    }
                }
                else
                {
                    hallMod = 1;
                    hallSelectFlag = 1;
                }
            }
            else if (hallMod == 3)
            {
                if (hallSelectFlag == 1 && UI::money >= 200000 && isEnding != 2)
                {
                    UI::money -= 200000;
                    isEnding = 1;
                    pWnd->SetTimer(15, 2000, NULL);
                }
                else if (hallSelectFlag == 2)
                {
                    hallMod = 1;
                    hallSelectFlag = 1;
                }
            }
        }
    }
}