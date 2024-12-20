#pragma once
#include "Monster.h"
#include "User.h"
#include <cstdlib>
#include <ctime>
#include "Object.h"
#include <vector>

enum ACTION
{
    ATTACK, SKILL1, SKILL2, SKILL3, SKILL4, ITEM1, ITEM2, ITEM3, ITEM4, RUN, NONE
};

enum TURN
{
    CHECKPARALYZE, MYACTION, ENEMYATTACK, DOTDAMAGE
};

class Dungeon
{
private:
    static Monster* monster[26];
public:
    Dungeon()
    {}

    static CRect rect;
    static int difficulty;
    static int current_Level;
    static int current_player_HP;
    static int current_player_MP;
    static int enemy_HP;
    static int current_enemy_HP;
    static int toolbar;
    static int mod;
    static int revive;
    static int duration;
    static int enemy_duration;
    static int tutorialFlag;
    static bool tutorialCleared;
    static bool tutorial;
    static bool start_tutorial;
    static bool cleared[5];
    static bool paralyze;
    static bool poison;
    static bool burning;
    static bool flag;
    static bool deathFlag;
    static int size;
    static vector<Object*> itemCounter;
    static vector<int> itemCounterIndex;
    static int inputIndex1;
    static int emptyIndex;
    static int bossItemIndex[5];
    static int enterDungeon;
    static int attackflag;
    static ACTION t;
    static TURN turn;
    static int canMove;
    static CWnd* pWnd;
    static int whatAttack;
    static int isEnemyDeath;

    static void set(CRect& in)
    {
        rect = in;
        size = in.Height() / 14 * 12 / 15; //세로 : 15 | 가로 : 25
    }


    static void dot_damage();
    static ACTION interact();
    static void cancel();

    static void draw(CDC* memdc);
    static void myAttack(ACTION in);
    static int useItem(ACTION in);
    static void enemyTurn();
    static void nextLevel();

    static ACTION keyDown(CWnd* pWnd, UINT nChar, UINT nRepCnt, UINT nFlags);

    static void initMonster()
    {
        monster[0] = new Monster_1_1;
        monster[1] = new Monster_1_2;
        monster[2] = new Monster_1_3;
        monster[3] = new Monster_1_4;
        monster[4] = new Monster_1_5;
        monster[5] = new Monster_2_1;
        monster[6] = new Monster_2_2;
        monster[7] = new Monster_2_3;
        monster[8] = new Monster_2_4;
        monster[9] = new Monster_2_5;
        monster[10] = new Monster_3_1;
        monster[11] = new Monster_3_2;
        monster[12] = new Monster_3_3;
        monster[13] = new Monster_3_4;
        monster[14] = new Monster_3_5;
        monster[15] = new Monster_4_1;
        monster[16] = new Monster_4_2;
        monster[17] = new Monster_4_3;
        monster[18] = new Monster_4_4;
        monster[19] = new Monster_4_5;
        monster[20] = new Monster_5_1;
        monster[21] = new Monster_5_2;
        monster[22] = new Monster_5_3;
        monster[23] = new Monster_5_4;
        monster[24] = new Monster_5_5;
        monster[25] = new Monster_5_6;
    }

    static void initStats();

    static void renderCurrentMonster(CDC* memdc, int current_Level)
    {
        if (current_Level >= 1 && current_Level <= 25)
        {
            monster[current_Level - 1]->render(memdc);
        }
    }

    static void turnProgress();
};