
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "ChildView.h"
#include "Farm.h"
#include "Player.h"
#include "Village.h"
#include "UI.h"
#include "Crop.h"
#include <time.h>
#include "Dungeon.h"
#include "Monster.h"
#include "EventManager.h"
#include "AttackMotion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define endingCount 4

// CChildView

CChildView::CChildView()
{
    inputlook = 0;
    check = 0;
    menuFlag = true;

    AttackMotion::setInit();
    Dungeon::pWnd = this;
    Village::pWnd = this;
    Farm::pWnd = this;
    Player::setInit();
    Farm::setInit();
    Village::setInit();
    UI::setInit();
    Crop::setInit();
    Dungeon::initMonster();
    User::setItem(1);
    Dungeon::initStats();
    srand(time(NULL));
    setPrologue();
    setEnding();
    isPrologue = 0;
    PNum = 0;

    isEnding = 0;
    ENum = 0;
    Dungeon::tutorialCleared = 0;
    Dungeon::start_tutorial = 1;
    Dungeon::tutorialFlag = 1;

}

void CChildView::InitializeGDIPlus()
{
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
}
void CChildView::ShutdownGDIPlus()
{
    GdiplusShutdown(gdiplusToken);
}
CChildView::~CChildView()
{
    ShutdownGDIPlus();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_KEYDOWN()
    ON_WM_ERASEBKGND()
    ON_WM_TIMER()
    ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

void CChildView::setPrologue()
{
    Prologue[0].LoadBitmap(IDB_Prologue1);
    Prologue[1].LoadBitmap(IDB_Prologue2);
    Prologue[2].LoadBitmap(IDB_Prologue3);
    Prologue[3].LoadBitmap(IDB_Prologue4);
    Prologue[4].LoadBitmap(IDB_Prologue5);
    Prologue[5].LoadBitmap(IDB_Prologue6);
    Prologue[6].LoadBitmap(IDB_Prologue7);
    Prologue[7].LoadBitmap(IDB_Prologue8);
    Prologue[8].LoadBitmap(IDB_Prologue9);
    Prologue[9].LoadBitmap(IDB_Prologue10);
    Prologue[10].LoadBitmap(IDB_Prologue11);
    Prologue[11].LoadBitmap(IDB_Prologue12);
    Prologue[12].LoadBitmap(IDB_Prologue13);
    Prologue[13].LoadBitmap(IDB_Prologue14);
    Prologue[14].LoadBitmap(IDB_Prologue15);
    Prologue[15].LoadBitmap(IDB_Prologue15);
    Prologue[16].LoadBitmap(IDB_Prologue15);

}
void CChildView::setEnding()
{
    Ending[0].LoadBitmapW(IDB_Ending1);
    Ending[1].LoadBitmapW(IDB_Ending2);
    Ending[2].LoadBitmapW(IDB_Ending3);
    Ending[3].LoadBitmapW(IDB_Ending4);
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        ::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

    return TRUE;
}

void CChildView::OnPaint()
{
    CPaintDC dc(this);

    CRect rect;
    GetClientRect(&rect);

    CDC memdc;
    memdc.CreateCompatibleDC(&dc);
    CBitmap bitmap;
    bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
    memdc.SelectObject(&bitmap);
    memdc.Rectangle(rect);

    Farm::setSize(rect);
    Village::setSize(rect);
    Player::setSize(rect);
    UI::setsize(rect);
    Dungeon::set(rect);
    Monster::set(rect);

    CDC PrologueDC;
    CDC EndingDC;

    if (isPrologue == 0)
    {
        BITMAP info;
        Prologue[PNum].GetBitmap(&info);
        PrologueDC.CreateCompatibleDC(&memdc);
        PrologueDC.SelectObject(Prologue[PNum]);

        //if(PNum != 0)

        memdc.StretchBlt(0, 0, rect.Width(), rect.Height(), &PrologueDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);

        if (PNum == 16)
        {
            isPrologue = 1;
        }
    }
    else if (Village::isEnding == 1)
    {
        BITMAP info;
        Prologue[PNum].GetBitmap(&info);
        EndingDC.CreateCompatibleDC(&memdc);
        EndingDC.SelectObject(Ending[Village::ENum]);

        //if(PNum != 0)

        memdc.StretchBlt(0, 0, rect.Width(), rect.Height(), &EndingDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);

        if (Village::ENum == endingCount)  //그림 숫자 
        {
            memdc.SelectStockObject(BLACK_BRUSH);
            memdc.Rectangle(rect);
            Player::mod = MENU;
            SetTimer(8, 500, NULL);
            Village::isEnding = 2;
        }
    }
    else if (Player::mod == MENU)
    {
        CBitmap start;
        BITMAP startInfo;
        if (menuFlag)
            start.LoadBitmap(IDB_startScreen);
        else
            start.LoadBitmap(IDB_startScreen2);
        start.GetBitmap(&startInfo);

        CDC startDC;
        startDC.CreateCompatibleDC(&memdc);
        startDC.SelectObject(start);
        memdc.StretchBlt(0, 0, rect.right, rect.bottom, &startDC, 0, 0, startInfo.bmWidth, startInfo.bmHeight, SRCCOPY);
    }
    else
    {
        switch (Player::mod)
        {
        case FARM:
            Farm::drawFarm(&memdc);
            break;
        case VILLAGE:
            Village::drawVillage(&memdc);
            break;
        case HOUSE:
            memdc.SelectStockObject(BLACK_BRUSH);
            memdc.Rectangle(0, 0, rect.Height() / 14 * 12 / 15 * 25, rect.Height() / 14 * 12);
            Farm::drawInnerHouse(&memdc);
            break;
        case SHOP:
            memdc.SelectStockObject(BLACK_BRUSH);
            memdc.Rectangle(rect);
            Village::drawShop(&memdc);
            break;
        case HALL:
            Village::drawHall(&memdc);
            break;
        case SMITHY:
            Village::drawSmithy(&memdc);
            break;
        case CHEST:
            memdc.SelectStockObject(BLACK_BRUSH);
            memdc.Rectangle(0, 0, rect.Height() / 14 * 12 / 15 * 25, rect.Height() / 14 * 12);
            Farm::drawInnerHouse(&memdc);
            Player::drawChest(&memdc);
            break;
        case DUNGEON:
            memdc.SelectStockObject(BLACK_BRUSH);
            memdc.Rectangle(rect);
            Dungeon::draw(&memdc);
            break;
        default:
            break;
        }


        UI::printUI(&memdc);
        if (Player::mod != DUNGEON)
            Player::drawInven(&memdc);
        memdc.SelectStockObject(NULL_BRUSH);
        if (Player::mod == FARM || Player::mod == VILLAGE || Player::mod == HOUSE)
        {
            if (Player::mod == HOUSE)
            {
                if ((EventManager::EventFlag & FirstHouse))
                    Player::drawBigPlayer(&memdc);
            }
            else
                Player::drawPlayer(&memdc);
            if (Farm::talkFlag)
                Farm::sleepAlarm(&memdc);
        }
    }

    if (Farm::isBed == 1)
    {
        memdc.SelectStockObject(BLACK_BRUSH);
        switch (Farm::bedCount)
        {
        case 1:
            memdc.Rectangle(0, 0, Farm::size * 25, Farm::size * 3);
            memdc.Rectangle(0, Farm::size * 12, Farm::size * 25, Farm::size * 15);
            break;
        case 2:
            memdc.Rectangle(0, 0, Farm::size * 25, Farm::size * 6);
            memdc.Rectangle(0, Farm::size * 9, Farm::size * 25, Farm::size * 15);
            break;
        case 3:
            memdc.Rectangle(0, 0, Farm::size * 25, Farm::size * 15);
            break;
        case 4:
            memdc.Rectangle(0, 0, Farm::size * 25, Farm::size * 6);
            memdc.Rectangle(0, Farm::size * 9, Farm::size * 25, Farm::size * 15);
            break;
        case 5:
            memdc.Rectangle(0, 0, Farm::size * 25, Farm::size * 3);
            memdc.Rectangle(0, Farm::size * 12, Farm::size * 25, Farm::size * 15);
            break;
        default:
            break;
        }
    }

    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);

    // 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void DelayWithMessagePump(int milliseconds)
{
    DWORD start = GetTickCount();
    MSG msg;

    // 지정된 시간 동안 메시지 큐를 처리하면서 대기
    while (GetTickCount() - start < milliseconds)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    int canMove = 1;
    if (inputlook == 1 || Prologue == 0)
        return;
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    switch (Player::mod)
    {
    case FARM:
    case VILLAGE:
        Player::movePlayer(this, nChar, nRepCnt, nFlags);
        break;
    case HOUSE:
        if (Farm::isBed == 1)
            return;
        if (!Farm::talkFlag)
            Player::movePlayer(this, nChar, nRepCnt, nFlags);
        else
            Farm::moveFlag(nChar, nRepCnt, nFlags);
        break;
    case SHOP:
        Village::shopSelect(nChar, nRepCnt, nFlags);
        break;
    case HALL:
        Village::hallSelect(nChar, nRepCnt, nFlags);
        break;
    case SMITHY:
        Village::SmithySelect(nChar, nRepCnt, nFlags);
        break;
    case CHEST:
        Player::moveChest(nChar, nRepCnt, nFlags);
        break;
    case DUNGEON:
        inputlook = 1;

        Dungeon::t = Dungeon::keyDown(this, nChar, nRepCnt, nFlags);
        Dungeon::turnProgress();

        inputlook = 0;
        break;
    case MENU:
        if (isPrologue)
        {
            Player::movePlayer(this, nChar, nRepCnt, nFlags);
            if (nChar == VK_RETURN);
            KillTimer(8);
        }
    default:
        break;
    }
    if (Player::mod != CHEST)
        Player::moveInven(nChar, nRepCnt, nFlags);
    
    Invalidate();

    CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    return true;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    if (nIDEvent == 0)
    {
        PNum++;
        Invalidate();
        if (PNum == 17)
        {
            KillTimer(0);
            SetTimer(8, 500, NULL);
        }
    }
    if (nIDEvent == 1)
    {
        Invalidate();
        Player::moving = 0;
        KillTimer(1);
    }
    if (nIDEvent == 2)
    {
        Dungeon::attackflag++;
        if (Dungeon::attackflag == 8)
        {
            Dungeon::turn = ENEMYATTACK;
            Dungeon::turnProgress();

            if (Dungeon::duration == 0 && Dungeon::enemy_duration == 0)
            {
                KillTimer(2);
                Dungeon::turn = CHECKPARALYZE;
            }
        }
        else if (Dungeon::attackflag == 9)
        {
            Dungeon::turn = DOTDAMAGE;
            Dungeon::turnProgress();
            KillTimer(2);
            Dungeon::attackflag = 0;
        }
        Invalidate();
    }
    if (nIDEvent == 3)
    {
        Dungeon::attackflag++;
        if (Dungeon::attackflag == 8)
        {
            Dungeon::turn = ENEMYATTACK;
            Dungeon::turnProgress();
            if (Dungeon::duration == 0 && Dungeon::enemy_duration == 0)
            {
                KillTimer(3);
                Dungeon::turn = CHECKPARALYZE;
            }
        }
        else if (Dungeon::attackflag == 9)
        {
            Dungeon::turn = DOTDAMAGE;
            Dungeon::turnProgress();
            KillTimer(3);
            Dungeon::attackflag = 0;
        }
        Invalidate();
    }
    if (nIDEvent == 4)
    {
        Dungeon::attackflag++;
        if (Dungeon::attackflag == 8)
        {
            Dungeon::turn = ENEMYATTACK;
            Dungeon::turnProgress();
            if (Dungeon::duration == 0 && Dungeon::enemy_duration == 0)
            {
                KillTimer(4);
                Dungeon::turn = CHECKPARALYZE;
            }
        }
        else if (Dungeon::attackflag == 9)
        {
            Dungeon::turn = DOTDAMAGE;
            Dungeon::turnProgress();
            KillTimer(4);
            Dungeon::attackflag = 0;
        }
        Invalidate();
    }
    if (nIDEvent == 5)
    {
        Dungeon::attackflag++;
        if (Dungeon::attackflag == 10)
        {
            Dungeon::turn = ENEMYATTACK;
            Dungeon::turnProgress();
            if (Dungeon::duration == 0 && Dungeon::enemy_duration == 0)
            {
                KillTimer(5);
                Dungeon::turn = CHECKPARALYZE;
            }
        }
        else if (Dungeon::attackflag == 11)
        {
            Dungeon::turn = DOTDAMAGE;
            Dungeon::turnProgress();
            KillTimer(5);
            Dungeon::attackflag = 0;
        }
        Invalidate();
    }
    if (nIDEvent == 6)
    {
        Dungeon::attackflag++;
        if (Dungeon::attackflag == 17)
        {
            Dungeon::turn = ENEMYATTACK;
            Dungeon::turnProgress();
            if (Dungeon::duration == 0 && Dungeon::enemy_duration == 0)
            {
                KillTimer(6);
                Dungeon::turn = CHECKPARALYZE;
            }
        }
        else if (Dungeon::attackflag == 18)
        {
            Dungeon::turn = DOTDAMAGE;
            Dungeon::turnProgress();
            KillTimer(6);
            Dungeon::attackflag = 0;
        }
        Invalidate();
    }
    if (nIDEvent == 7)
    {
        check++;
        if (check >= 3)
        {
            check = 0;
            Dungeon::isEnemyDeath = 0;
            KillTimer(7);
        }
        Invalidate();
    }
    if (nIDEvent == 8)
    {
        menuFlag = !menuFlag;
        Invalidate();
    }
    if (nIDEvent == 9)
    {
        KillTimer(9);
        if (AllSpring == (EventManager::EventFlag & AllSpring))
        {
            Village::unlock = 2;
            SetTimer(10, 5000, NULL);
        }
        Village::unlock = 0;
        Invalidate();
    }
    if (nIDEvent == 10)
    {
        KillTimer(10);
        Village::unlock = 0;
        Invalidate();
    }
    if (nIDEvent == 11)
    {
        KillTimer(11);
        Village::unlock = 0;
        Invalidate();
    }
    if (nIDEvent == 12)
    {
        SetTimer(13, 5000, NULL);
        KillTimer(12);
        Village::unlock = 5;
        Invalidate();
    }
    if (nIDEvent == 13)
    {
        KillTimer(13);
        Village::unlock = 0;
        Invalidate();
    }
    if (nIDEvent == 14)
    {
        KillTimer(14);
        Village::unlock = 0;
        Invalidate();
    }
    if (nIDEvent == 15)
    {
        Village::ENum++;
        Invalidate();
        if (Village::ENum == endingCount) //엔딩 그림수
        {
            KillTimer(15);
        }

    }
    if (nIDEvent == 16)
    {
        Farm::bedCount++;
        if (Farm::bedCount == 6)
        {
            Farm::isBed = 0;
            Farm::bedCount = 0;
            Player::pos.X = 1;
            Player::pos.Y = 1;
            Player::look = LEFT;
            KillTimer(16);
        }
        Invalidate();
    }
    CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  여기에 특수화된 작성 코드를 추가합니다.
    SetTimer(0, 1500, NULL);

    return 0;
}
