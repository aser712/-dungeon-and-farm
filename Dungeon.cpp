#include "pch.h"
#include "User.h"
#include "Dungeon.h"
#include "resource.h"
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Object.h"
#include "AttackMotion.h"
#include "EventManager.h"

CRect Dungeon::rect;
int Dungeon::size;
int Dungeon::mod = 0;
int Dungeon::toolbar = 1;
int Dungeon::current_player_HP;
int Dungeon::current_player_MP;
int Dungeon::enemy_HP;
int Dungeon::current_enemy_HP;
int Dungeon::difficulty;
int Dungeon::current_Level = 1;
int Dungeon::duration = 0;
int Dungeon::enemy_duration = 0;
int Dungeon::tutorialFlag = 0;
bool Dungeon::start_tutorial = 0;
bool Dungeon::tutorial = 0;
bool Dungeon::tutorialCleared = 0;
bool Dungeon::cleared[5] = { false, false, false, false, false };
bool Dungeon::paralyze = 0;
bool Dungeon::poison = 0;
bool Dungeon::burning = 0;
bool Dungeon::flag = 0;
bool Dungeon::deathFlag = 0;
int Dungeon::revive = 1;
Monster* Dungeon::monster[26];
vector<Object*> Dungeon::itemCounter(4);
vector<int> Dungeon::itemCounterIndex(4);
int Dungeon::inputIndex1;
int Dungeon::emptyIndex;
int Dungeon::bossItemIndex[5];
int Dungeon::enterDungeon = 0;
int Dungeon::attackflag = 0;
ACTION Dungeon::t;
TURN Dungeon::turn;
int Dungeon::canMove;
CWnd* Dungeon::pWnd;
int Dungeon::whatAttack = 0;
int Dungeon::isEnemyDeath = 0;

//���� ���׸���
void Dungeon::draw(CDC* memdc)
{
    int size_W = size * 25;
    int size_H = size * 15;

    //�۾� ������ �߾ӹ�ġ
    CSize textSize;
    int text_W;
    int text_H;

    //�� ����, �Ķ�, ���, ����
    CBrush brush = RGB(255, 0, 0), brush2 = RGB(0, 0, 255), brush3 = RGB(255, 255, 0), brush4 = RGB(255, 0, 255);
    //�۾� �� ����
    memdc->SetBkMode(TRANSPARENT);
    //�۾� ũ��
    LOGFONT logFont = { 0 };
    lstrcpy(logFont.lfFaceName, _T("����"));
    logFont.lfHeight = -size * 0.48;
    logFont.lfWidth = 0;
    logFont.lfWeight = FW_BOLD;
    logFont.lfItalic = FALSE;
    CFont font;
    font.CreateFontIndirect(&logFont);
    // ���� �۾�ü ����
    CFont* pOldFont = memdc->SelectObject(&font);
    //������
    if (mod != 0)
    {   //������
        BITMAP bk;
        CBitmap bkMap;
        bkMap.LoadBitmap(IDB_BK);
        bkMap.GetBitmap(&bk);
        CDC bkmemDC;
        bkmemDC.CreateCompatibleDC(memdc);
        CBitmap* pOldBitmap1 = bkmemDC.SelectObject(&bkMap);
        BITMAP bkbmp;
        bkMap.GetBitmap(&bkbmp);
        memdc->StretchBlt(0, 0, size_W, size_H * 7 / 10, &bkmemDC, 0, 0, bk.bmWidth, bk.bmHeight, SRCCOPY);
        bkmemDC.SelectObject(pOldBitmap1);

        //�ؽ�Ʈ
        CString player_str, enemy_str, show_player_hp, show_enemy_hp, show_player_mp, tutorialText;

        //�⺻ ��
        //memdc->SelectStockObject(NULL_BRUSH);
        CBrush transparentBrush(RGB(255, 255, 255));

        //Ʃ�丮�� or ����â ǥ��
        if (start_tutorial)
        {
            memdc->SelectObject(transparentBrush); // ���� �귯��
            memdc->Rectangle(0, size_H * 7 / 10, size_W, size_H);
            if (tutorialFlag == 1)
            {
                tutorialText.Format(_T("����â : �̰��� �����Դϴ�. ���� �������� ��Ÿ������ �ο�������."));
            }
            else if (tutorialFlag == 2)
            {
                tutorialText.Format(_T("����â : ����� �������� ũ�� �� 4���Դϴ�. ����, ��ų, ����, ������ �ֽ��ϴ�."));
            }
            else if (tutorialFlag == 3)
            {
                tutorialText.Format(_T("����â : �������� ���� ������ �� ������ �����ϱ�� ���͸� �����մϴ�."));
            }
            else if (tutorialFlag == 4)
            {
                tutorialText.Format(_T("����â : ��ų�� ������ �̿��� �� ���� ������ �� �� �ֽ��ϴ�. ������ �ڿ������� ȸ������ �ʽ��ϴ�."));
            }
            else if (tutorialFlag == 5)
            {
                tutorialText.Format(_T("����â : ������ ������ ������ �ִ� ������ ����� �� �ֽ��ϴ�."));
            }
            else if (tutorialFlag == 6)
            {
                tutorialText.Format(_T("����â : ����ģ�ٴ� �������� ��Ż�� �� �ֽ��ϴ�."));
            }
            else if (tutorialFlag == 7)
            {
                tutorialText.Format(_T("����â : �������� ��� �� ���簡���� �ִ� ���� ������(����)�� ���θ� �Ҿ�����ϴ�."));
            }
            else if (tutorialFlag == 8)
            {
                tutorialText.Format(_T("����â: ������ Ŭ���� �� ���� ���� �λ깰�� ���� �� �ְ� �̸� ���� ���⸦ ��ȭ �� �� �ֽ��ϴ�."));
            }
            else if (tutorialFlag == 9)
            {
                tutorialText.Format(_T("����â: ���������� ������ �Ϸ翡 �� ���� �� �� �ֽ��ϴ�."));
            }
            textSize = memdc->GetTextExtent(tutorialText);
            text_W = (size_W * 1 / 2) - (textSize.cx / 2);
            text_H = (size_H * 17 / 20) - (textSize.cy / 2);
            memdc->TextOutW(text_W, text_H, tutorialText);
        }
        else
        {   //���� ���� ����
            CBitmap frameMap, frameMap2;
            CDC framememDC, framememDC2;
            BITMAP frame, frame2;
            if (poison && duration != 0)
                frameMap.LoadBitmap(IDB_Frame_Poison);
            else if (paralyze && duration != 0)
                frameMap.LoadBitmap(IDB_Frame_Paralyze);
            else
                frameMap.LoadBitmap(IDB_Frame);
            frameMap.GetBitmap(&frame);
            framememDC.CreateCompatibleDC(memdc);
            CBitmap* pOldBitmap0 = framememDC.SelectObject(&frameMap);
            memdc->TransparentBlt(0, size_H * 7 / 10, size_W, size_H * 3 / 10, &framememDC, 0, 0, frame.bmWidth, frame.bmHeight, RGB(255, 255, 255));
            framememDC.SelectObject(pOldBitmap0);
            if (burning && enemy_duration != 0)
                frameMap2.LoadBitmap(IDB_Frame_Burn);
            else
                frameMap2.LoadBitmap(IDB_Frame2);
            frameMap2.GetBitmap(&frame2);
            framememDC2.CreateCompatibleDC(memdc);
            CBitmap* pOldBitmap1 = framememDC2.SelectObject(&frameMap2);
            memdc->TransparentBlt(0, 0, size_W * 1 / 2, size_H * 1 / 8, &framememDC2, 0, 0, frame2.bmWidth, frame2.bmHeight, RGB(255, 255, 255));
            framememDC2.SelectObject(pOldBitmap1);


            //ü�¹� or Ʃ�丮�� ���� ǥ��
            if (tutorial)
            {   //ü�� �������� Ʃ�丮��
                if (tutorialFlag == 1)
                {
                    tutorialText.Format(_T("����â : ���� ü���� �����մϴ�. ������ �������."));
                }
                else if (tutorialFlag == 2)
                {
                    tutorialText.Format(_T("����â : ���濡 �ִ� �̻��� ���� ����Ͽ� ü���� ȸ���� ������."));
                }
                textSize = memdc->GetTextExtent(tutorialText);
                text_W = (size_W * 7 / 24) - (textSize.cx / 2);
                text_H = (size_H * 17 / 20) - (textSize.cy / 2);
                memdc->TextOutW(text_W, text_H, tutorialText);
            }
            else
            {   //�� ü�¹�
                player_str.Format(_T("���� �÷��̾��� ü�� : "));
                memdc->TextOutW(size_W * 1 / 35, size_H * 18 / 24, player_str);
                memdc->SelectStockObject(NULL_BRUSH);
                memdc->Rectangle(size_W * 5 / 21, size_H * 18 / 24, size_W * 12 / 21, size_H * 19 / 24);
                double MyHealthBar = (size_W * 5 / 21) + (size_W * 7 / 21) * (static_cast<double>(current_player_HP) / User::health);
                MyHealthBar = max(size_W * 5 / 21, MyHealthBar);
                memdc->SelectObject(brush);
                memdc->Rectangle(size_W * 5 / 21, size_H * 18 / 24, MyHealthBar, size_H * 19 / 24);
                show_player_hp.Format(_T("%d / %d"), current_player_HP, User::health);
                memdc->TextOutW(size_W * 1 / 3, size_H * 18 / 24, show_player_hp);

                //�� ������
                player_str.Format(_T("���� �÷��̾��� ���� : "));
                memdc->TextOutW(size_W * 1 / 35, size_H * 22 / 24, player_str);
                memdc->SelectStockObject(NULL_BRUSH);
                memdc->Rectangle(size_W * 5 / 21, size_H * 22 / 24, size_W * 4 / 7, size_H * 23 / 24);
                double MyManaBar = (size_W * 5 / 21) + (size_W * 4 / 7 - size_W * 5 / 21) * (static_cast<double>(current_player_MP) / User::mana);
                MyManaBar = max(size_W * 5 / 21, MyManaBar);
                memdc->SelectObject(brush2);
                memdc->Rectangle(size_W * 5 / 21, size_H * 22 / 24, MyManaBar, size_H * 23 / 24);
                show_player_mp.Format(_T("%d / %d"), current_player_MP, User::mana);
                memdc->TextOutW(size_W * 17 / 48, size_H * 22 / 24, show_player_mp);
            }

            //�� ü�¹�
            enemy_str.Format(_T("HP : "));
            memdc->TextOutW(size_W * 1 / 35, size_H * 1 / 35, enemy_str);
            memdc->SelectStockObject(NULL_BRUSH);
            memdc->Rectangle(size_W * 3 / 35, size_H * 2 / 70, size_W * 14 / 35, size_H * 5 / 70);
            double HealthBar = size_W * 3 / 35 + (size_W * 11 / 35) * (static_cast<double>(current_enemy_HP) / enemy_HP);
            HealthBar = max(size_W * 3 / 35, HealthBar);
            if (isEnemyDeath == 0)
                memdc->SelectObject(brush);
            memdc->Rectangle(size_W * 3 / 35, size_H * 2 / 70, HealthBar, size_H * 5 / 70);
            if (isEnemyDeath == 0)
                show_enemy_hp.Format(_T("%d / %d"), current_enemy_HP, enemy_HP);
            else
                show_enemy_hp.Format(_T("0 / %d"), monster[current_Level - 2]->health);
            memdc->TextOutW(size_W * 14 / 70, size_H * 2 / 70, show_enemy_hp);

            //���̵� ���� ���� ���
            if (isEnemyDeath == 1)
            {
                renderCurrentMonster(memdc, current_Level - 1);
            }
            else if (isEnemyDeath == 0)
            {
                if (difficulty == 1)
                {   //�� ��� 5����
                    if (current_Level == 6)
                    {   //Ŭ����
                        if (!cleared[0])
                        {
                            cleared[0] = true;
                        }
                        toolbar = 1;
                        Player::mod = FARM;
                        Player::look = DOWN;
                        if (inputIndex1 != -1)
                        {
                            if (Player::inven[inputIndex1] == NULL)
                            {
                                Player::inven[inputIndex1] = new Fertilizer();
                                Player::inven[inputIndex1]->count = 5;
                            }
                            else
                            {
                                Player::inven[inputIndex1]->count += 5;
                            }
                        }
                        if (bossItemIndex[0] != -1)
                        {
                            Player::inven[bossItemIndex[0]]->count++;
                        }
                        else if (emptyIndex != -1)
                        {
                            Player::inven[emptyIndex] = new BossItem1();
                            Player::inven[emptyIndex]->count = 1;
                        }

                        if (attackflag != 0)
                            pWnd->KillTimer(2);
                        attackflag = 0;
                        pWnd->Invalidate();
                    }
                    else
                    {
                        renderCurrentMonster(memdc, current_Level);
                    }
                }
                else if (difficulty == 2)
                {
                    if (current_Level == 11)
                    {
                        Player::mod = FARM;
                        Player::look = DOWN;
                        if (!cleared[1])
                        {
                            //item::rank1 = 1; //����
                            cleared[1] = true;
                        }
                        if (inputIndex1 != -1)
                        {
                            if (Player::inven[inputIndex1] == NULL)
                            {
                                Player::inven[inputIndex1] = new Fertilizer();
                                Player::inven[inputIndex1]->count = 10;
                            }
                            else
                            {
                                Player::inven[inputIndex1]->count += 10;
                            }
                        }
                        if (bossItemIndex[1] != -1)
                        {
                            Player::inven[bossItemIndex[1]]->count++;
                        }
                        else if (emptyIndex != -1)
                        {
                            Player::inven[emptyIndex] = new BossItem2();
                            Player::inven[emptyIndex]->count = 1;
                        }
                        pWnd->Invalidate();
                    }
                    else
                    {
                        renderCurrentMonster(memdc, current_Level);
                    }
                }
                else if (difficulty == 3)
                {
                    if (current_Level == 16)
                    {
                        Player::mod = FARM;
                        Player::look = DOWN;
                        if (!cleared[2])
                        {
                            //item::rank2 = 1;
                            cleared[2] = true;

                        }
                        if (inputIndex1 != -1)
                        {
                            if (Player::inven[inputIndex1] == NULL)
                            {
                                Player::inven[inputIndex1] = new Fertilizer();
                                Player::inven[inputIndex1]->count = 15;
                            }
                            else
                            {
                                Player::inven[inputIndex1]->count += 15;
                            }
                        }
                        if (bossItemIndex[2] != -1)
                        {
                            Player::inven[bossItemIndex[2]]->count++;
                        }
                        else if (emptyIndex != -1)
                        {
                            Player::inven[emptyIndex] = new BossItem3();
                            Player::inven[emptyIndex]->count = 1;
                        }
                        pWnd->Invalidate();
                    }
                    else
                    {
                        renderCurrentMonster(memdc, current_Level);
                    }
                }
                else if (difficulty == 4)
                {
                    if (current_Level == 21)
                    {
                        Player::mod = FARM;
                        Player::look = DOWN;
                        if (!cleared[3])
                        {
                            //item::rank3 = 1;
                            cleared[3] = true;
                        }
                        if (inputIndex1 != -1)
                        {
                            if (Player::inven[inputIndex1] == NULL)
                            {
                                Player::inven[inputIndex1] = new Fertilizer();
                                Player::inven[inputIndex1]->count = 20;
                            }
                            else
                            {
                                Player::inven[inputIndex1]->count += 20;
                            }
                        }

                        if (bossItemIndex[3] != -1)
                        {
                            Player::inven[bossItemIndex[3]]->count++;
                        }
                        else if (emptyIndex != -1)
                        {
                            Player::inven[emptyIndex] = new BossItem4();
                            Player::inven[emptyIndex]->count = 1;
                        }
                        pWnd->Invalidate();
                    }
                    else
                    {
                        renderCurrentMonster(memdc, current_Level);
                    }
                }
                else if (difficulty == 5)
                {
                    if (current_Level == 26)
                    {
                        Player::mod = FARM;
                        Player::look = DOWN;

                        if (!cleared[4])
                        {
                            //item::rank4 = 1;
                            cleared[4] = true;
                        }
                        if (inputIndex1 != -1)
                        {
                            if (Player::inven[inputIndex1] == NULL)
                            {
                                Player::inven[inputIndex1] = new Fertilizer();
                                Player::inven[inputIndex1]->count = 25;
                            }
                            else
                            {
                                Player::inven[inputIndex1]->count += 25;
                            }
                        }

                        if (bossItemIndex[4] != -1)
                        {
                            Player::inven[bossItemIndex[4]]->count++;
                        }
                        else if (emptyIndex != -1)
                        {
                            Player::inven[emptyIndex] = new BossItem5();
                            Player::inven[emptyIndex]->count = 1;
                        }
                        pWnd->Invalidate();
                    }
                    else
                    {
                        renderCurrentMonster(memdc, current_Level);
                    }
                }
            }

            if (mod != 0)
            {   //������ ���
                CString text[4] = { _T("����"), _T("��ų"), _T("����"), _T("����") };
                CString skill[4] = { _T("�Ŀ� ������"), _T("�÷��� ������"), _T("�����ε� ������"), _T("��Ʈ ������") };
                CString item[4] = { _T("HP����"), _T("������ġ��"), _T("MP����"), _T("��Ȱ ����") };
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {   //������ ��ġ
                        int left_W = size_W * 22 / 36 + j * (size_W * 7 / 36);
                        int right_W = size_W * 28 / 36 + j * (size_W * 7 / 36);
                        int top_H = size_H * 22 / 30 + i * (size_H * 4 / 30);
                        int bottom_H = size_H * 25 / 30 + i * (size_H * 4 / 30);

                        if (toolbar == i * 2 + j + 1)
                            memdc->SelectStockObject(GRAY_BRUSH);
                        else
                            memdc->SelectStockObject(WHITE_BRUSH);
                        memdc->Rectangle(left_W, top_H, right_W, bottom_H);

                        int center_W = (left_W + right_W) / 2;
                        int center_H = (top_H + bottom_H) / 2;

                        //(���� | ��ų | ����) �۾� ǥ��
                        if (mod == 1)
                        {
                            textSize = memdc->GetTextExtent(text[i * 2 + j]);
                            text_W = center_W - (textSize.cx / 2);
                            text_H = center_H - (textSize.cy / 2);
                            memdc->TextOutW(text_W, text_H, text[i * 2 + j]);
                        }
                        else if (mod == 2)
                        {
                            if (User::level == 1)
                            {
                                if (i == 0 && j == 0)
                                {
                                    textSize = memdc->GetTextExtent(skill[i * 2 + j]);
                                    text_W = center_W - (textSize.cx / 2);
                                    text_H = center_H - (textSize.cy / 2);
                                    memdc->TextOutW(text_W, text_H, skill[i * 2 + j]);
                                }
                                else
                                {
                                    memdc->MoveTo(left_W, top_H);
                                    memdc->LineTo(right_W, bottom_H);
                                    memdc->MoveTo(right_W, top_H);
                                    memdc->LineTo(left_W, bottom_H);
                                }
                            }
                            else if (User::level == 2)
                            {
                                if (i == 0)
                                {
                                    textSize = memdc->GetTextExtent(skill[i * 2 + j]);
                                    text_W = center_W - (textSize.cx / 2);
                                    text_H = center_H - (textSize.cy / 2);
                                    memdc->TextOutW(text_W, text_H, skill[i * 2 + j]);
                                }
                                else
                                {
                                    memdc->MoveTo(left_W, top_H);
                                    memdc->LineTo(right_W, bottom_H);
                                    memdc->MoveTo(right_W, top_H);
                                    memdc->LineTo(left_W, bottom_H);
                                }
                            }
                            else if (User::level == 3)
                            {
                                if (i != 1 || j != 1)
                                {
                                    textSize = memdc->GetTextExtent(skill[i * 2 + j]);
                                    text_W = center_W - (textSize.cx / 2);
                                    text_H = center_H - (textSize.cy / 2);
                                    memdc->TextOutW(text_W, text_H, skill[i * 2 + j]);
                                }
                                else
                                {
                                    memdc->MoveTo(left_W, top_H);
                                    memdc->LineTo(right_W, bottom_H);
                                    memdc->MoveTo(right_W, top_H);
                                    memdc->LineTo(left_W, bottom_H);
                                }
                            }
                            else if (User::level == 4)
                            {
                                if (i != 1 || j != 1)
                                {
                                    textSize = memdc->GetTextExtent(skill[i * 2 + j]);
                                    text_W = center_W - (textSize.cx / 2);
                                    text_H = center_H - (textSize.cy / 2);
                                    memdc->TextOutW(text_W, text_H, skill[i * 2 + j]);
                                }
                                else
                                {
                                    memdc->MoveTo(left_W, top_H);
                                    memdc->LineTo(right_W, bottom_H);
                                    memdc->MoveTo(right_W, top_H);
                                    memdc->LineTo(left_W, bottom_H);
                                }
                            }
                            if (User::level == 5)
                            {
                                textSize = memdc->GetTextExtent(skill[i * 2 + j]);
                                text_W = center_W - (textSize.cx / 2);
                                text_H = center_H - (textSize.cy / 2);
                                memdc->TextOutW(text_W, text_H, skill[i * 2 + j]);
                            }

                            if (toolbar == 1 || (toolbar == 2 && User::level >= 2) || (toolbar == 3 && User::level >= 3) || (toolbar == 4 && User::level == 5))
                            {
                                CBitmap info;
                                CDC infoDC;
                                BITMAP infoInfo;
                                info.LoadBitmap(IDB_Frame);
                                info.GetBitmap(&infoInfo);
                                infoDC.CreateCompatibleDC(memdc);
                                infoDC.SelectObject(info);

                                memdc->TransparentBlt(size_W * 22 / 36 + 0 * (size_W * 7 / 36), size_H * 5.5 / 10, (size_W * 28 / 36 + 1 * (size_W * 7 / 36)) - (size_W * 22 / 36 + 0 * (size_W * 7 / 36)), size_H * 1.5 / 10, &infoDC, 0, 0, infoInfo.bmWidth, infoInfo.bmHeight, RGB(255, 255, 255));

                                textSize = memdc->GetTextExtent(EventManager::skillTalk[2 * (toolbar - 1)]);
                                text_W = ((size_W * 22 / 36 + 0 * (size_W * 7 / 36)) + (size_W * 28 / 36 + 1 * (size_W * 7 / 36))) / 2 - (textSize.cx / 2);
                                text_H = size_H * 47 / 80 - (textSize.cy / 2);
                                memdc->TextOutW(text_W, text_H, EventManager::skillTalk[2 * (toolbar - 1)]);
                                text_H = size_H * 53 / 80 - (textSize.cy / 2);
                                memdc->TextOutW(text_W, text_H, EventManager::skillTalk[2 * (toolbar - 1) + 1]);
                            }
                        }
                        else if (mod == 3)
                        {
                            CString str = NULL;
                            if (itemCounter[i * 2 + j] != NULL)
                                str.Format(_T(" (%d��)"), itemCounter[i * 2 + j]->count);
                            else
                                str.Format(_T(" (0��)"));
                            CSize textSize = memdc->GetTextExtent(item[i * 2 + j] + str);
                            text_W = center_W - (textSize.cx / 2);
                            text_H = center_H - (textSize.cy / 2);

                            memdc->TextOutW(text_W, text_H, item[i * 2 + j] + str);

                            if (i * 2 + j == 3 && revive == 0)
                            {
                                memdc->MoveTo(left_W, top_H);
                                memdc->LineTo(right_W, bottom_H);
                                memdc->MoveTo(right_W, top_H);
                                memdc->LineTo(left_W, bottom_H);

                            }


                            CBitmap info;
                            CDC infoDC;
                            BITMAP infoInfo;
                            info.LoadBitmap(IDB_Frame);
                            info.GetBitmap(&infoInfo);
                            infoDC.CreateCompatibleDC(memdc);
                            infoDC.SelectObject(info);

                            memdc->TransparentBlt(size_W * 22 / 36 + 0 * (size_W * 7 / 36), size_H * 5.5 / 10, (size_W * 28 / 36 + 1 * (size_W * 7 / 36)) - (size_W * 22 / 36 + 0 * (size_W * 7 / 36)), size_H * 1.5 / 10, &infoDC, 0, 0, infoInfo.bmWidth, infoInfo.bmHeight, RGB(255, 255, 255));


                            if (toolbar == 4)
                            {
                                memdc->TransparentBlt(size_W * 22 / 36 + 0 * (size_W * 7 / 36), size_H * 4 / 10, (size_W * 28 / 36 + 1 * (size_W * 7 / 36)) - (size_W * 22 / 36 + 0 * (size_W * 7 / 36)), size_H * 3 / 10, &infoDC, 0, 0, infoInfo.bmWidth, infoInfo.bmHeight, RGB(255, 255, 255));

                                textSize = memdc->GetTextExtent(EventManager::itemTalk[4]);
                                text_W = ((size_W * 22 / 36 + 0 * (size_W * 7 / 36)) + (size_W * 28 / 36 + 1 * (size_W * 7 / 36))) / 2 - (textSize.cx / 2);
                                text_H = size_H * 35 / 80 - (textSize.cy / 2);
                                memdc->TextOutW(text_W, text_H, EventManager::itemTalk[3]);
                                text_H = size_H * 41 / 80 - (textSize.cy / 2);
                                memdc->TextOutW(text_W, text_H, EventManager::itemTalk[4]);
                                text_H = size_H * 47 / 80 - (textSize.cy / 2);
                                memdc->TextOutW(text_W, text_H, EventManager::itemTalk[5]);
                                text_H = size_H * 53 / 80 - (textSize.cy / 2);
                                memdc->TextOutW(text_W, text_H, EventManager::itemTalk[6]);
                            }
                            else
                            {
                                memdc->TransparentBlt(size_W * 22 / 36 + 0 * (size_W * 7 / 36), size_H * 5.5 / 10, (size_W * 28 / 36 + 1 * (size_W * 7 / 36)) - (size_W * 22 / 36 + 0 * (size_W * 7 / 36)), size_H * 1.5 / 10, &infoDC, 0, 0, infoInfo.bmWidth, infoInfo.bmHeight, RGB(255, 255, 255));

                                textSize = memdc->GetTextExtent(EventManager::itemTalk[toolbar - 1]);
                                text_W = ((size_W * 22 / 36 + 0 * (size_W * 7 / 36)) + (size_W * 28 / 36 + 1 * (size_W * 7 / 36))) / 2 - (textSize.cx / 2);
                                text_H = size_H * 0.625 - (textSize.cy / 2);
                                memdc->TextOutW(text_W, text_H, EventManager::itemTalk[toolbar - 1]);
                            }

                        }
                    }
                }
            }


        }

        if ((0 < attackflag && attackflag < 8) && whatAttack == 1)
        {
            CDC attackDC;
            attackDC.CreateCompatibleDC(memdc);
            attackDC.SelectObject(AttackMotion::attackMotion1[attackflag - 1]);
            int x = (size_W - size * 5) / 2;
            int y = (size_H - size * 5) / 2;
            COLORREF color = RGB(255, 255, 255);
            memdc->TransparentBlt(x, y, 5 * size, 5 * size, &attackDC, 0, 0, AttackMotion::attackMotionInfo1[attackflag - 1].bmWidth, AttackMotion::attackMotionInfo1[attackflag - 1].bmHeight, color);
        }
        else if ((0 < attackflag && attackflag < 8) && whatAttack == 2)
        {
            CDC attackDC;
            attackDC.CreateCompatibleDC(memdc);
            attackDC.SelectObject(AttackMotion::attackMotion2[attackflag - 1]);
            int x = (size_W - size * 5) / 2;
            int y = (size_H - size * 5) / 2;
            COLORREF color = RGB(255, 255, 255);
            memdc->TransparentBlt(x, y, 5 * size, 5 * size, &attackDC, 0, 0, AttackMotion::attackMotionInfo2[attackflag - 1].bmWidth, AttackMotion::attackMotionInfo2[attackflag - 1].bmHeight, color);
        }
        else if ((0 < attackflag && attackflag < 8) && whatAttack == 3)
        {
            CDC attackDC;
            attackDC.CreateCompatibleDC(memdc);
            attackDC.SelectObject(AttackMotion::attackMotion3[attackflag - 1]);
            int x = (size_W - size * 5) / 2;
            int y = (size_H - size * 5) / 2;
            COLORREF color = RGB(255, 255, 255);
            memdc->TransparentBlt(x, y, 5 * size, 5 * size, &attackDC, 0, 0, AttackMotion::attackMotionInfo3[attackflag - 1].bmWidth, AttackMotion::attackMotionInfo3[attackflag - 1].bmHeight, color);
        }
        else if ((0 < attackflag && attackflag < 10) && whatAttack == 4)
        {
            CDC attackDC;
            attackDC.CreateCompatibleDC(memdc);
            attackDC.SelectObject(AttackMotion::attackMotion4[attackflag - 1]);
            int x = (size_W - size * 5) / 2;
            int y = (size_H - size * 5) / 2;
            COLORREF color = RGB(255, 255, 255);
            memdc->TransparentBlt(x, y, 5 * size, 5 * size, &attackDC, 0, 0, AttackMotion::attackMotionInfo4[attackflag - 1].bmWidth, AttackMotion::attackMotionInfo4[attackflag - 1].bmHeight, color);
        }
        else if ((0 < attackflag && attackflag < 17) && whatAttack == 5)
        {
            CDC attackDC;
            attackDC.CreateCompatibleDC(memdc);
            attackDC.SelectObject(AttackMotion::attackMotion5[attackflag - 1]);
            int x = (size_W - size * 5) / 2;
            int y = (size_H - size * 5) / 2;
            COLORREF color = RGB(255, 255, 255);
            memdc->TransparentBlt(x, y, 5 * size, 5 * size, &attackDC, 0, 0, AttackMotion::attackMotionInfo5[attackflag - 1].bmWidth, AttackMotion::attackMotionInfo5[attackflag - 1].bmHeight, color);
        }
        else if (isEnemyDeath)
        {
            CDC deathDC;
            deathDC.CreateCompatibleDC(memdc);
            deathDC.SelectObject(AttackMotion::deathMotion[current_Level - 2]);
            int x = (size_W - size * 5) / 2;
            int y = (size_H - size * 5) / 2;
            COLORREF color = RGB(255, 255, 255);
            memdc->TransparentBlt(x, y, 5 * size, 5 * size, &deathDC, 0, 0, AttackMotion::deathMotionInfo[current_Level - 2].bmWidth, AttackMotion::deathMotionInfo[current_Level - 2].bmHeight, color);

        }
    }
    //���̵� ����â
    if (mod == 0)
    {
        CString text[6] = { _T("Stage 1"), _T("Stage 2"), _T("Stage 3"), _T("Stage 4"), _T("Stage 5"), _T("������") };
        memdc->Rectangle(0, 0, size_W, size_H);

        BITMAP bk;
        CBitmap bkMap;
        bkMap.LoadBitmap(IDB_BK);
        bkMap.GetBitmap(&bk);
        CDC bkmemDC;
        bkmemDC.CreateCompatibleDC(memdc);
        CBitmap* pOldBitmap1 = bkmemDC.SelectObject(&bkMap);
        BITMAP bkbmp;
        bkMap.GetBitmap(&bkbmp);
        memdc->StretchBlt(0, 0, size_W, size_H, &bkmemDC, 0, 0, bk.bmWidth, bk.bmHeight, SRCCOPY);
        bkmemDC.SelectObject(pOldBitmap1);

        memdc->SetTextColor(RGB(255, 255, 255));
        //���̵� 1~5���� ǥ��
        for (int i = 0; i < 5; i++)
        {   //���̵�
            if (toolbar == i + 1)
                memdc->SelectStockObject(GRAY_BRUSH);
            else
                memdc->SelectStockObject(NULL_BRUSH);
            int middle_W = (size_W * 33 / 75 + size_W * 42 / 75) / 2;
            int middle_H = (size_H * (5 + 14 * i) / 75 + size_H * (14 + 14 * i) / 75) / 2;
            memdc->Rectangle(size_W * 33 / 75, size_H * (5 + 14 * i) / 75, size_W * 42 / 75, size_H * (14 + 14 * i) / 75);
            if (i == 0 || cleared[i - 1])
                textSize = memdc->GetTextExtent(text[i]);
            else
                textSize = memdc->GetTextExtent(_T("Closed"));
            text_W = middle_W - (textSize.cx / 2);
            text_H = middle_H - (textSize.cy / 2);
            if (i == 0 || cleared[i - 1])
                memdc->TextOutW(text_W, text_H, text[i]);
            else
                memdc->TextOutW(text_W, text_H, _T("Closed"));

        }

        //������ ���� ǥ��
        if (toolbar == 6)
        {   //������
            memdc->SelectStockObject(GRAY_BRUSH);
        }
        else
        {   //�ٸ���
            memdc->SelectStockObject(NULL_BRUSH);
        }
        memdc->Rectangle(size_W * 60 / 75, size_H * 33 / 75, size_W * 69 / 75, size_H * 42 / 75);
        int middle_W = (size_W * 60 / 75 + size_W * 69 / 75) / 2;
        int middle_H = (size_H * 33 / 75 + size_H * 42 / 75) / 2;
        textSize = memdc->GetTextExtent(text[5]);
        text_W = middle_W - (textSize.cx / 2);
        text_H = middle_H - (textSize.cy / 2);
        memdc->TextOutW(text_W, text_H, text[5]);

        //�÷��̾� ���� ǥ��
        CString playerStats;
        for (int i = 0; i < 2; i++)
        {   //���� ��
            int start_W = size_W / 50;
            int end_W = size_W * 7 / 50;
            int start_H = size_H * (2 + 4 * i) / 15;
            int end_H = size_H * (5 + 4 * i) / 15;
            memdc->SelectStockObject(NULL_BRUSH);
            memdc->Rectangle(start_W, start_H, end_W, end_H);
            BITMAP bmp;
            CBitmap bitmap;
            CDC memDC;
            COLORREF color = RGB(255, 255, 255);
            if (User::level == 1)
            {
                if (i == 0)
                    bitmap.LoadBitmap(IDB_Sword_1);
                else if (i == 1)
                    bitmap.LoadBitmap(IDB_Armor_1);
            }
            else if (User::level == 2)
            {
                if (i == 0)
                    bitmap.LoadBitmap(IDB_Sword_2);
                else if (i == 1)
                    bitmap.LoadBitmap(IDB_Armor_2);
            }
            else if (User::level == 3)
            {
                if (i == 0)
                    bitmap.LoadBitmap(IDB_Sword_3);
                else if (i == 1)
                    bitmap.LoadBitmap(IDB_Armor_3);
            }
            else if (User::level == 4)
            {
                if (i == 0)
                    bitmap.LoadBitmap(IDB_Sword_4);
                else if (i == 1)
                    bitmap.LoadBitmap(IDB_Armor_4);
            }
            else if (User::level == 5)
            {
                if (i == 0)
                    bitmap.LoadBitmap(IDB_Sword_5);
                else if (i == 1)
                    bitmap.LoadBitmap(IDB_Armor_5);
            }
            bitmap.GetBitmap(&bmp);
            memDC.CreateCompatibleDC(memdc);
            memDC.SelectObject(&bitmap);
            memdc->TransparentBlt(start_W + 1, start_H + 1, end_W - start_W - 2, end_H - start_H - 2, &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, color);
        }
        playerStats.Format(_T("�÷��̾��� ü�� : %d "), User::health);
        memdc->TextOutW(size_W / 50, size_H * (2 + 4 * 2) / 15, playerStats);
        playerStats.Format(_T("�÷��̾��� ���ݷ� : %d "), User::damage);
        memdc->TextOutW(size_W / 50, size_H * (2 + 4 * 2.2) / 15, playerStats);
        playerStats.Format(_T("�÷��̾��� ���� : %d "), User::mana);
        memdc->TextOutW(size_W / 50, size_H * (2 + 4 * 2.4) / 15, playerStats);
    }
}

//����
ACTION Dungeon::interact()
{   //������ 4�� ǥ��
    if (mod == 0)
    {   //���̵� ����
        if (toolbar == 1)
        {
            difficulty = 1;
            current_Level = 1;
            enemy_HP = monster[current_Level - 1]->health;
            current_enemy_HP = enemy_HP;
            toolbar = 1;
            mod = 1;
        }
        else if (toolbar == 2)
        {
            difficulty = 2;
            current_Level = 6;
            enemy_HP = monster[current_Level - 1]->health;
            current_enemy_HP = enemy_HP;
            toolbar = 1;
            mod = 1;
        }
        else if (toolbar == 3)
        {
            difficulty = 3;
            current_Level = 11;
            enemy_HP = monster[current_Level - 1]->health;
            current_enemy_HP = enemy_HP;
            toolbar = 1;
            mod = 1;
        }
        else if (toolbar == 4)
        {
            difficulty = 4;
            current_Level = 16;
            enemy_HP = monster[current_Level - 1]->health;
            current_enemy_HP = enemy_HP;
            toolbar = 1;
            mod = 1;
        }
        else if (toolbar == 5)
        {
            difficulty = 5;
            current_Level = 21;
            enemy_HP = monster[current_Level - 1]->health;
            current_enemy_HP = enemy_HP;
            toolbar = 1;
            mod = 1;
        }
        else if (toolbar == 6) //����
        {
            Player::mod = FARM;
            Player::look = DOWN;
        }
        if (toolbar != 6)
            enterDungeon = 1;

        return NONE;
    }
    else if (mod == 1)
    {   //����
        if (toolbar == 1)
        {   //�⺻ ����
            whatAttack = 1;
            return ATTACK;
        }
        else if (toolbar == 2)
        {   //��ųâ
            mod = 2;
        }
        else if (toolbar == 3)
        {   //����
            mod = 3;
        }
        else if (toolbar == 4)
        {   //���̵� ��������
            mod = 0;
            toolbar = 1;
            return RUN;
        }
        return NONE;
    }
    else if (mod == 2)
    {   //��ųâ
        if (toolbar == 1)
        {
            whatAttack = 2;
            return SKILL1;
        }
        else if (toolbar == 2)
        {
            whatAttack = 3;
            return SKILL2;
        }
        else if (toolbar == 3)
        {
            whatAttack = 4;
            return SKILL3;
        }
        else
        {
            whatAttack = 5;
            return SKILL4;
        }
    }
    else if (mod == 3)
    {   //����
        if (toolbar == 1)
        {   //ü�¹���
            return ITEM1;
        }
        else if (toolbar == 2)
        {   //������ġ��
            return ITEM2;
        }
        else if (toolbar == 3)
        {   //��������
            return ITEM3;
        }
        else if (toolbar == 4)
        {   //��Ȱ
            return ITEM4;
        }
    }

    if (mod == 2 || mod == 3)
    {
        mod = 1;
        toolbar = 1;
    }

}

//���� ���
void Dungeon::cancel()
{
    if (mod == 2 || mod == 3)
        mod = 1;
}

//Ű �Է�
ACTION Dungeon::keyDown(CWnd* pWnd, UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // ����(1) ��ų(2)
    // ����(3) ����ģ��(4)
    if (nChar == VK_UP || nChar == 'W')
    {
        if (mod == 0)
        {
            if (Dungeon::toolbar >= 2 && Dungeon::toolbar <= 5) Dungeon::toolbar--;
        }
        else
        {
            if (Dungeon::toolbar == 3) Dungeon::toolbar = 1;
            else if (Dungeon::toolbar == 4) Dungeon::toolbar = 2;
        }
    }
    if (nChar == VK_LEFT || nChar == 'A')
    {
        if (mod == 0)
        {
            if (Dungeon::toolbar == 6) Dungeon::toolbar = 1;
        }
        else
        {
            if (Dungeon::toolbar == 2) Dungeon::toolbar = 1;
            else if (Dungeon::toolbar == 4) Dungeon::toolbar = 3;
        }
    }
    if (nChar == VK_DOWN || nChar == 'S')
    {
        if (mod == 0)
        {
            if (Dungeon::toolbar >= 1 && Dungeon::toolbar <= 4 && Dungeon::cleared[toolbar - 1]) Dungeon::toolbar++;
        }
        else
        {
            if (Dungeon::toolbar == 1) Dungeon::toolbar = 3;
            else if (Dungeon::toolbar == 2) Dungeon::toolbar = 4;
        }
    }
    if (nChar == VK_RIGHT || nChar == 'D')
    {
        if (mod == 0)
        {
            if (Dungeon::toolbar != 6) Dungeon::toolbar = 6;
        }
        else
        {
            if (Dungeon::toolbar == 1) Dungeon::toolbar = 2;
            else if (Dungeon::toolbar == 3) Dungeon::toolbar = 4;
        }
    }
    if (nChar == VK_RETURN)
    {
        if (start_tutorial == 1 && mod == 1)
        {
            if (tutorialFlag >= 1 && tutorialFlag <= 8)
            {
                tutorialFlag++;
            }
            else if (tutorialFlag == 9)
            {
                start_tutorial = 0;
                tutorialFlag = 0;
            }
        }
        else if (tutorial)
        {   //1������������ ü���� 30%�̸��̸�
            if (tutorialFlag == 1)
            {
                if (toolbar == 3)
                {   //���� ����
                    tutorialFlag = 2;
                    return Dungeon::interact();
                }
            }
            if (tutorialFlag == 2)
            {
                if (toolbar == 1)
                {   //HP���� ������
                    tutorialFlag = 0;
                    tutorial = 0;
                    current_player_HP = User::health;
                    return Dungeon::interact();
                }
            }
        }
        else if (mod == 1)
        {
            return Dungeon::interact();
        }
        else if (mod == 2)
        {   //��ų���� ���� or ���� �ȵǸ� ��ȣ�ۿ� X
            int manause[4] = { 20, 30, 60, 100 };
            if (User::level == 1)
            {
                if (toolbar == 1 && current_player_MP >= manause[toolbar - 1])
                    return Dungeon::interact();
            }
            if (User::level == 2)
            {
                if ((toolbar == 1 || toolbar == 2) && current_player_MP >= manause[toolbar - 1])
                    return Dungeon::interact();
            }
            if (User::level == 3 || User::level == 4)
            {
                if ((toolbar == 1 || toolbar == 2 || toolbar == 3) && current_player_MP >= manause[toolbar - 1])
                    return Dungeon::interact();
            }
            if (User::level == 5 && current_player_MP >= manause[toolbar - 1])
            {
                return Dungeon::interact();
            }
        }
        else if (mod == 3)
        {
            if (toolbar == 4)
            {   //��Ȱ����
                if (revive)
                {   //��� ��������
                    return Dungeon::interact();
                }
                else
                {   //������ ��ŵ
                    ;
                }
            }
            else
            {
                return Dungeon::interact();
            }
        }
        else
        {
            Dungeon::interact();
        }
    }
    if (nChar == VK_BACK)
    {
        if (!tutorial)
        {
            Dungeon::cancel();
        }
    }

    return NONE;
}

//������
void Dungeon::nextLevel()
{   //�����ܰ�, ȭ�� ����
    current_Level++;
    enemy_HP = monster[current_Level - 1]->health;
    current_enemy_HP = enemy_HP;
    burning = 0;
    enemy_duration = 0;
}

void Dungeon::myAttack(ACTION in)
{
    int damage = 0;

    switch (in)
    {
    case ATTACK:
        damage = User::damage;
        pWnd->SetTimer(2, 70, NULL);
        break;
    case SKILL1:
        if (current_player_MP >= 20)
        {
            damage = User::damage * 1.5;
            current_player_MP -= 20;
            pWnd->SetTimer(3, 70, NULL);
        }
        break;
    case SKILL2:
        if (current_player_MP >= 30)
        {
            damage = User::damage * 0.7;
            burning = 1;
            enemy_duration = 5;
            current_player_MP -= 30;
            pWnd->SetTimer(4, 70, NULL);
        }
        break;
    case SKILL3:
        if (current_player_MP >= 60)
        {
            damage = User::damage * 3;
            paralyze = 1;
            duration = 3;
            current_player_MP -= 60;
            pWnd->SetTimer(5, 70, NULL);
        }
        break;
    case SKILL4:
        if (current_player_MP >= 100)
        {
            damage = User::damage * 5;
            current_player_MP = 0;
            pWnd->SetTimer(6, 70, NULL);
        }
        break;
    default:
        break;
    }


    int r; //���� ����
    r = rand() % 5;
    if (r == 0)
    {   //������ ����
        damage = damage * 9 / 10;
    }
    else if (r == 1)
    {
        damage = damage * 10 / 10;
    }
    else if (r == 2)
    {
        damage = damage * 11 / 10;
    }
    else if (r == 3)
    {
        damage = damage * 12 / 10;
    }
    else if (r == 4)
    {
        damage = damage * 13 / 10;
    }

    if (current_enemy_HP <= damage)
    {
        isEnemyDeath = 1;
        nextLevel();
    }
    else
    {
        current_enemy_HP -= damage;
    }

    attackflag = 1;
}


//�� ��
void Dungeon::enemyTurn()
{   //�� ����
    int r; //���� ����
    r = rand() % 3;
    if (r == 0)
    {   //������ ����
        current_player_HP -= (monster[current_Level - 1]->damage) * 9 / 10;
    }
    else if (r == 1)
    {
        current_player_HP -= (monster[current_Level - 1]->damage);
    }
    else if (r == 2)
    {
        current_player_HP -= (monster[current_Level - 1]->damage) * 11 / 10;
    }
    //������
    if (current_player_HP <= 0)
    {
        if (deathFlag)
        {   //��Ȱ����
            current_player_HP = User::health * 6 / 10;
            current_player_MP = User::mana * 6 / 10;
            deathFlag = 0;
            poison = 0;
            paralyze = 0;
            duration = 0;
        }
        else
        {
            Player::mod = FARM;
            Player::look = LEFT;
            Player::pos.X = 5;
            Player::pos.Y = 3;
            Player::toNextDay();
			for(int i = 0; i < 4; i++)
			{
				if(itemCounter[i] != NULL)
				{
					delete itemCounter[i];
					Player::inven[itemCounterIndex[i]] = NULL;
				}
			}
        }
        return;
    }
    //1���������� Ʃ�丮��
    if (difficulty == 1)
    {   //1�ܰ��϶� Ʃ�丮��
        if (current_player_HP < User::health * 3 / 10)
        {
            if (!tutorialCleared)
            {
                mod = 1;
                tutorial = 1;
                tutorialFlag = 1;
                tutorialCleared = 1;
            }
        }
    }
    //���Ͱ� �Ŵ� �����
    if (current_Level == 8)
    {
        if (!poison)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 29)
            {
                poison = 1;
                duration = 3;
            }
        }
    }
    else if (current_Level == 9)
    {
        if (!paralyze)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                paralyze = 1;
                duration = 4;
            }
        }
    }
    else if (current_Level == 10)
    {
        if (!poison && !paralyze)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                poison = 1;
                duration = 3;
            }
            else if (r >= 15 && r <= 30)
            {
                paralyze = 1;
                duration = 4;
            }
        }
    }
    else if (current_Level == 11)
    {
        if (!poison && !paralyze)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                poison = 1;
                duration = 3;
            }
        }
    }
    else if (current_Level == 12)
    {
        if (!poison && !paralyze)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                poison = 1;
                duration = 3;
            }
        }
    }
    else if (current_Level == 15)
    {
        if (!poison && !paralyze)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                poison = 1;
                duration = 3;
            }
        }
    }
    else if (current_Level == 18)
    {
        if (!poison)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                poison = 1;
                duration = 3;
            }
        }
    }
    else if (current_Level == 19)
    {
        if (!poison)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                poison = 1;
                duration = 3;
            }
        }
    }
    else if (current_Level == 20)
    {
        if (!poison)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 29)
            {
                poison = 1;
                duration = 3;
            }
        }
    }
    else if (current_Level == 23)
    {
        if (!paralyze)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                paralyze = 1;
                duration = 4;
            }
        }
    }
    else if (current_Level == 24)
    {
        if (!paralyze)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 14)
            {
                paralyze = 1;
                duration = 4;
            }
        }
    }
    else if (current_Level == 25)
    {
        if (!poison)
        {
            r = rand() % 100;

            if (r >= 0 && r <= 29)
            {
                poison = 1;
                duration = 3;
            }
        }
    }
}

int Dungeon::useItem(ACTION in)
{
    switch (in)
    {
    case ITEM1:
        if (itemCounter[0] == NULL)
            return 0;
        if (itemCounter[0] != NULL && itemCounter[0]->count != 0)
        {
            itemCounter[0]->count--;
            if (itemCounter[0]->count == 0)
            {
                delete itemCounter[0];
                itemCounter[0] = NULL;
                Player::inven[itemCounterIndex[0]] = NULL;
            }
            current_player_HP += User::health * 60 / 100;
            if (current_player_HP > User::health)
                current_player_HP = User::health;
            return 1;
        }
        break;
    case ITEM2:
        if (itemCounter[1] == NULL)
            return 0;
        if (itemCounter[1] != NULL && itemCounter[1]->count != 0)
        {
            itemCounter[1]->count--;
            if (itemCounter[1]->count == 0)
            {
                delete itemCounter[1];
                itemCounter[1] = NULL;
                Player::inven[itemCounterIndex[1]] = NULL;
            }

            duration = 0;
            paralyze = 0;
            poison = 0;

            return 1;
        }
    case ITEM3:
        if (itemCounter[2] == NULL)
            return 0;
        if (itemCounter[2] != NULL && itemCounter[2]->count != 0)
        {
            itemCounter[2]->count--;
            if (itemCounter[2]->count == 1)
            {
                delete itemCounter[2];
                itemCounter[2] = NULL;
                Player::inven[itemCounterIndex[2]] = NULL;
            }

            current_player_MP += User::mana * 60 / 100;
            if (current_player_MP > User::mana)
                current_player_MP = User::mana;

            return 1;
        }
        break;
    case ITEM4:
        if (itemCounter[3] == NULL || revive == 0)
            return 0;
        if (itemCounter[3] != NULL && itemCounter[3]->count != 0)
        {
            itemCounter[3]->count--;
            if (itemCounter[3]->count == 0)
            {
                delete itemCounter[3];
                itemCounter[3] = NULL;
                Player::inven[itemCounterIndex[3]] = NULL;
            }
            deathFlag = 1;
            revive = 0;

            return 1;
        }
        break;
    default:
        break;
    }
}

//�� or ȭ�󵥹���
void Dungeon::dot_damage()
{
    if (poison)
    {   //��
        current_player_HP -= User::health * 5 / 100;
        if (current_player_HP <= 0)
        {
            if (deathFlag)
            {   //��Ȱ����
                current_player_HP = User::health * 6 / 10;
                current_player_MP = User::mana * 6 / 10;
                deathFlag = 0;
                poison = 0;
                paralyze = 0;
                duration = 0;
            }
            else
            {
                Player::mod = HOUSE;
                Player::look = LEFT;
                Player::pos.X = 1;
                Player::pos.Y = 1;
                Player::toNextDay();
            }
        }
        duration--;
    }
    if (paralyze)
        duration--;

    if (burning)
    {   //�� ȭ��
        current_enemy_HP -= enemy_HP * 5 / 100;
        if (current_enemy_HP <= 0)
        {
            isEnemyDeath = 1;
            nextLevel();
        }
        enemy_duration--;
    }

    if (duration == 0)
    {
        paralyze = 0;
        poison = 0;
    }

    if (enemy_duration == 0)
    {
        burning = 0;
    }
    deathFlag = 0;//�������� ��Ȱ���� ��
}
//���� ����
void Dungeon::initStats()
{
    current_player_HP = User::health;
    current_player_MP = User::mana;
}

void Dungeon::turnProgress()
{
    if (0 < attackflag && attackflag < 8 || t == NONE || isEnemyDeath == 2)
        return;
    canMove = 1;
    if (turn == CHECKPARALYZE)
    {
        turn = MYACTION;
        if (paralyze == true)
        {
            int temp = rand() % 10000;
            if (0 <= temp && temp < 3000)
            {
                canMove = 0;
                turn = ENEMYATTACK;
            }
        }
    }

    if (turn == MYACTION && canMove)
    {
        if (t == ATTACK || t == SKILL1 || t == SKILL2 || t == SKILL3 || t == SKILL4)
            myAttack(t);
        else if (t == ITEM1 || t == ITEM2 || t == ITEM3 || t == ITEM4)
        {
            int check = useItem(t);
            if (t != ITEM4 && check == 1)
            {
                pWnd->SetTimer(2, 70, NULL);
                attackflag = 7;
                mod = 1;
            }
            whatAttack = 0;
        }

        else if (t == RUN)
        {
            Player::mod = FARM;
            Player::look = DOWN;
        }
    }
    else if (turn == ENEMYATTACK)
    {
        if (!(canMove == 1 && current_enemy_HP == enemy_HP && (t == ATTACK || t == SKILL1 || t == SKILL2 || t == SKILL3 || t == SKILL4)))
            enemyTurn();
        else if (isEnemyDeath == 1)
        {
            isEnemyDeath = 2;
            pWnd->SetTimer(7, 100, NULL);
        }
        turn = DOTDAMAGE;
    }
    else
    {
        dot_damage();
        turn = CHECKPARALYZE;
    }
}

/*
���� ����
���� or ����
��������
��Ʈ��
*/