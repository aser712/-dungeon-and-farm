#include "pch.h"
#include "Farm.h"
#include "resource.h"
#include "Player.h"
#include "EventManager.h"
#include "Village.h"

CBitmap Farm::wallImage;
BITMAP Farm::wallImageInfo;

CBitmap Farm::farmImage;
BITMAP Farm::farmImageInfo;
CBitmap Farm::houseImage;
BITMAP Farm::houseImageInfo;
CBitmap Farm::houseInnerImage;
BITMAP Farm::houseInnerImageInfo;
CBitmap Farm::soilImage;
BITMAP Farm::soilImageInfo;
CBitmap Farm::wettedSoilImage;
BITMAP Farm::wettedSoilImageInfo;
CBitmap Farm::caveImage;
BITMAP Farm::caveImageInfo;
CWnd* Farm::pWnd;


int Farm::farmMap[15][25] = {
      {0,0,0,0,0,0,0,0,0,4,4, 4, 4,4,4,0,0,0,0,0,0,0,0,0,0,},
      {0,0,0,0,0,6,0,0,0,4,4, 4, 4,4,4,0,0,0,0,0,0,0,0,0,0,},
      {5,5,5,5,5,6,5,5,5,4,4, 4, 4,4,4,5,5,5,5,5,5,5,5,5,5,},
      {0,0,0,0,0,0,0,0,0,4,4, 4, 4,4,4,0,0,0,0,0,0,0,0,0,0,},
      {0,0,0,0,0,0,0,0,0,4,4, 4, 4,4,4,0,0,0,0,0,0,5,0,0,0,},
      {0,0,0,0,0,0,0,0,0,0,0,-4,-4,0,0,0,0,0,0,0,0,5,0,0,0,},
      {0,0,0,0,0,0,0,0,1,1,1, 1, 1,1,1,1,0,0,0,0,0,0,0,0,3,},
      {0,0,0,0,0,0,0,0,1,1,1, 1, 1,1,1,1,0,0,0,0,0,0,0,0,3,},
      {0,0,0,0,0,0,0,0,1,1,1, 1, 1,1,1,1,0,0,0,0,0,0,0,0,0,},
      {0,0,0,0,0,0,0,0,1,1,1, 1, 1,1,1,1,0,0,0,0,0,0,0,0,0,},
      {0,0,0,0,0,0,0,0,1,1,1, 1, 1,1,1,1,0,0,0,0,0,0,0,0,0,},
      {0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,},
      {0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,},
      {0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,},
      {0,0,0,0,0,0,0,0,0,0,0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,}
};
int Farm::houseMap[4][3] = {
      {1,1,2,},
      {0,0,2},
      {0,0,0},
      {0,-1,0}
};
Crop* Farm::field1[5][8] = {};
Crop* Farm::field2[5][12] = {};
Crop* Farm::field3[5][16] = {};
int Farm::fieldLevel = 1;
int Farm::size;
bool Farm::talkFlag;
int Farm::sleepFlag;
int Farm::talkCount;
int Farm::isBed;
int Farm::bedCount;

void Farm::setSize(CRect in)
{
    size = in.Height() / 14 * 12 / 15;
}
void Farm::setInit()
{
    farmImage.LoadBitmap(IDB_Farm);
    farmImage.GetBitmap(&farmImageInfo);
    houseImage.LoadBitmap(IDB_House);
    houseImage.GetBitmap(&houseImageInfo);
    soilImage.LoadBitmap(IDB_Soil);
    soilImage.GetBitmap(&soilImageInfo);
    wettedSoilImage.LoadBitmap(IDB_WettedSoil);
    wettedSoilImage.GetBitmap(&wettedSoilImageInfo);
    houseInnerImage.LoadBitmap(IDB_HouseMap);
    houseInnerImage.GetBitmap(&houseInnerImageInfo);

    caveImage.LoadBitmap(IDB_Cave);
    caveImage.GetBitmap(&caveImageInfo);
    wallImage.LoadBitmap(IDB_Wall);
    wallImage.GetBitmap(&wallImageInfo);

    talkFlag = 0;
    sleepFlag = 0;
    fieldLevel = 1;
    talkCount = 0;
    isBed = 0;
    bedCount = 0;
}

void Farm::drawInnerHouse(CDC* memdc)
{
    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&houseInnerImage);

    memdc->StretchBlt(size * 8, 0, size * 9, size * 15, &imageDC, 0, 0, houseInnerImageInfo.bmWidth, houseInnerImageInfo.bmHeight, SRCCOPY);

    int x = size * 2;
    int y = size * 10;
    if (!(EventManager::EventFlag & FirstHouse))
    {

        LOGFONT logFont = { 0 };
        lstrcpy(logFont.lfFaceName, _T("굴림"));
        logFont.lfHeight = -size * 0.48;
        logFont.lfWidth = 0;
        logFont.lfWeight = FW_BOLD;
        logFont.lfItalic = FALSE;

        CFont font;
        font.CreateFontIndirectW(&logFont);
        memdc->SelectObject(font);
        memdc->SetTextColor(RGB(0, 0, 0));
        memdc->SetBkMode(TRANSPARENT);

        CBitmap boardImage;
        BITMAP boardImageInfo;
        boardImage.LoadBitmap(IDB_Frame);
        boardImage.GetBitmap(&boardImageInfo);
        CDC boardDC;
        boardDC.CreateCompatibleDC(memdc);
        boardDC.SelectObject(&boardImage);


        memdc->TransparentBlt(0, size * 9, size * 25, size * 6, &boardDC, 0, 0, boardImageInfo.bmWidth, boardImageInfo.bmHeight, SRCCOPY);

        memdc->TextOutW(x, y + size * 0.5, EventManager::HouseTalk[talkCount]);
        if (talkCount != 0)
        {
            talkCount++;
            memdc->TextOutW(x, y + size * 2, EventManager::HouseTalk[talkCount]);
        }
    }
}

void Farm::sleepAlarm(CDC* memdc)
{
    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&UI::boardImage);

    LOGFONT logFont = { 0 };
    lstrcpy(logFont.lfFaceName, _T("굴림"));
    logFont.lfHeight = -size * 0.48;
    logFont.lfWidth = 0;
    logFont.lfWeight = FW_BOLD;
    logFont.lfItalic = FALSE;

    CFont font;
    font.CreateFontIndirectW(&logFont);
    memdc->SetTextColor(RGB(0, 0, 0));
    memdc->SelectObject(&font);
    CString str = _T("이제 그만 잠에 들겠습니까");
    CString str2 = _T("예");
    CString str3 = _T("아니요");
    memdc->TransparentBlt(size * 7, size * 4, size * 11, size * 6, &imageDC, 0, 0, UI::boardImageInfo.bmWidth, UI::boardImageInfo.bmHeight, RGB(255, 255, 255));
    memdc->TextOutW(size * 9.5, size * 4.5, str);
    if (sleepFlag)
        memdc->SetTextColor(RGB(255, 0, 0));

    memdc->TextOutW(size * 10.2, size * 8.2, str2);
    memdc->SetTextColor(RGB(0, 0, 0));

    if (!sleepFlag)
        memdc->SetTextColor(RGB(255, 0, 0));

    memdc->TextOutW(size * 13.2, size * 8.2, str3);
    memdc->SetTextColor(RGB(0, 0, 0));

}

void Farm::moveFlag(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (nChar == VK_LEFT)
    {
        if (sleepFlag == 0)
            sleepFlag = !sleepFlag;
    }
    if (nChar == VK_RIGHT)
    {
        if (sleepFlag == 1)
            sleepFlag = !sleepFlag;
    }
    if (nChar == VK_RETURN)
    {
        if (sleepFlag == 1)
        {
            isBed = 1;
            Player::pos.X = 2;
            Player::pos.Y = 1;
            Player::look = DOWN;
            pWnd->SetTimer(16, 300, NULL);
            Player::toNextDay();
        }

        talkFlag = 0;
        sleepFlag = 0;
    }
}

void Farm::upgradeField()
{
    if (fieldLevel == 1)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                field2[i][j + 2] = field1[i][j];
                field1[i][j] = NULL;
            }
        }
        fieldLevel++;
    }
    else if (fieldLevel == 2)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                field3[i][j + 3] = field2[i][j];
                field2[i][j] = NULL;
            }
        }
        fieldLevel++;
    }
}

void Farm::drawHouse(CDC* memdc)
{
    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&houseImage);

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
            if (farmMap[i][j] == 4)
            {
                count++;
                if (upperLeft.X > j || upperLeft.Y > i)
                    upperLeft = { j,i };
                if (bottomRight.X < j || bottomRight.Y < i)
                    bottomRight = { j,i };
            }
        }
        if (count == 0)
            break;
    }

    tempBitmap.CreateCompatibleBitmap(memdc, (bottomRight.X - upperLeft.X + 1) * size, (bottomRight.Y - upperLeft.Y + 1) * size);
    tempDc.SelectObject(&tempBitmap);
    tempDc.StretchBlt(0, 0, (bottomRight.X - upperLeft.X + 1) * size, (bottomRight.Y - upperLeft.Y + 1) * size, &imageDC, 0, 0, houseImageInfo.bmWidth, houseImageInfo.bmHeight, SRCCOPY);
    memdc->TransparentBlt(upperLeft.X * size, upperLeft.Y * size, (bottomRight.X - upperLeft.X + 1) * size, (bottomRight.Y - upperLeft.Y + 1) * size, &tempDc, 0, 0, (bottomRight.X - upperLeft.X + 1) * size, (bottomRight.Y - upperLeft.Y + 1) * size, transparentColor);


}

void Farm::drawField(CDC* memdc)
{
    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&soilImage);

    CDC wallDC;
    wallDC.CreateCompatibleDC(memdc);
    wallDC.SelectObject(&wallImage);

    if (fieldLevel == 1)
    {
        int x = size * 8;
        int y = size * 8;
        for (int i = 0; i < 5; i++)
        {
            x = size * 8;
            for (int j = 0; j < 8; j++)
            {
                if (field1[i][j] != NULL)
                    field1[i][j]->draw(memdc, x, y, size, 0/*field[i][j]->growthDay*/);
                else
                    memdc->StretchBlt(x, y, size, size, &imageDC, 0, 0, soilImageInfo.bmWidth, soilImageInfo.bmHeight, SRCCOPY);
                x += size;
            }
            y += size;
        }
    }
    if (fieldLevel == 2)
    {
        int x = size * 6;
        int y = size * 8;
        for (int i = 0; i < 5; i++)
        {
            x = size * 6;
            for (int j = 0; j < 12; j++)
            {
                if (field2[i][j] != NULL)
                    field2[i][j]->draw(memdc, x, y, size, 0/*field[i][j]->growthDay*/);
                else
                    memdc->StretchBlt(x, y, size, size, &imageDC, 0, 0, soilImageInfo.bmWidth, soilImageInfo.bmHeight, SRCCOPY);
                x += size;
            }
            y += size;
        }
    }
    if (fieldLevel == 3)
    {
        int x = size * 3;
        int y = size * 8;
        for (int i = 0; i < 5; i++)
        {
            x = size * 3;
            for (int j = 0; j < 16; j++)
            {
                if (field3[i][j] != NULL)
                    field3[i][j]->draw(memdc, x, y, size, 0/*field[i][j]->growthDay*/);
                else
                    memdc->StretchBlt(x, y, size, size, &imageDC, 0, 0, soilImageInfo.bmWidth, soilImageInfo.bmHeight, SRCCOPY);
                x += size;
            }
            y += size;
        }
    }
}



void Farm::drawFarm(CDC* memdc)
{
    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    CDC imageDC;
    imageDC.CreateCompatibleDC(memdc);
    imageDC.SelectObject(&farmImage);
    CDC wallDC;
    wallDC.CreateCompatibleDC(memdc);
    wallDC.SelectObject(&wallImage);

    CDC caveDC;
    caveDC.CreateCompatibleDC(memdc);
    caveDC.SelectObject(&caveImage);
    int x = 0;


    if (!(EventManager::EventFlag & FirstSmithy))
    {
        Village::drawVillage(memdc);
        Player::mod = VILLAGE;
        Player::pos.X = 0;
        return;
    }



    memdc->StretchBlt(0, 0, size * 25, size * 15, &imageDC, 0, 0, farmImageInfo.bmWidth, farmImageInfo.bmHeight, SRCCOPY);
    for (int i = 0; i < 25; i++)
    {
        memdc->StretchBlt(x, size, size, size * 2, &wallDC, 0, 0, wallImageInfo.bmWidth, wallImageInfo.bmHeight, SRCCOPY);
        if (i == 6)
            memdc->TransparentBlt(x - size * 2, size, size * 3, size * 2, &caveDC, 0, 0, caveImageInfo.bmWidth, caveImageInfo.bmHeight, RGB(255, 255, 255));
        x += size;
    }

    drawField(memdc);
    drawHouse(memdc);


    x = size * 2;
    int y = size * 10;
    if (!(EventManager::EventFlag & FirstFarm))
    {

        LOGFONT logFont = { 0 };
        lstrcpy(logFont.lfFaceName, _T("굴림"));
        logFont.lfHeight = -size * 0.48;
        logFont.lfWidth = 0;
        logFont.lfWeight = FW_BOLD;
        logFont.lfItalic = FALSE;

        CFont font;
        font.CreateFontIndirectW(&logFont);
        memdc->SelectObject(font);
        memdc->SetTextColor(RGB(0, 0, 0));
        memdc->SetBkMode(TRANSPARENT);

        CBitmap boardImage;
        BITMAP boardImageInfo;
        boardImage.LoadBitmap(IDB_Frame);
        boardImage.GetBitmap(&boardImageInfo);
        CDC boardDC;
        boardDC.CreateCompatibleDC(memdc);
        boardDC.SelectObject(&boardImage);


        memdc->TransparentBlt(0, size * 9, size * 25, size * 6, &boardDC, 0, 0, boardImageInfo.bmWidth, boardImageInfo.bmHeight, SRCCOPY);

        memdc->TextOutW(x, y + size * 0.5, EventManager::FarmTalk[talkCount]);
    }
}