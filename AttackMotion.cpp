#include "pch.h"
#include "AttackMotion.h"


CBitmap AttackMotion::attackMotion1[7];
BITMAP AttackMotion::attackMotionInfo1[7];
CBitmap AttackMotion::attackMotion2[7];
BITMAP AttackMotion::attackMotionInfo2[7];
CBitmap AttackMotion::attackMotion3[7];
BITMAP AttackMotion::attackMotionInfo3[7];
CBitmap AttackMotion::attackMotion4[9];
BITMAP AttackMotion::attackMotionInfo4[9];
CBitmap AttackMotion::attackMotion5[16];
BITMAP AttackMotion::attackMotionInfo5[16];

CBitmap AttackMotion::deathMotion[25];
BITMAP AttackMotion::deathMotionInfo[25];

void AttackMotion::setAttackMotion1()
{
	int num = 486;
	for(int i = 0; i < 7; i++)
	{
		attackMotion1[i].LoadBitmap(num);
		attackMotion1[i].GetBitmap(&attackMotionInfo1[i]);
		num++;
	}
}

void AttackMotion::setAttackMotion2()
{
	int num = 493;
	for(int i = 0; i < 7; i++)
	{
		attackMotion2[i].LoadBitmap(num);
		attackMotion2[i].GetBitmap(&attackMotionInfo2[i]);
		num++;
	}
}

void AttackMotion::setAttackMotion3()
{
	int num = 500;
	for(int i = 0; i < 7; i++)
	{
		attackMotion3[i].LoadBitmap(num);
		attackMotion3[i].GetBitmap(&attackMotionInfo3[i]);
		num++;
	}
}

void AttackMotion::setAttackMotion4()
{
	int num = 507;
	for(int i = 0; i < 9; i++)
	{
		attackMotion4[i].LoadBitmap(num);
		attackMotion4[i].GetBitmap(&attackMotionInfo4[i]);
		num++;
	}
}

void AttackMotion::setAttackMotion5()
{
	int num = 516;
	for(int i = 0; i < 16; i++)
	{
		attackMotion5[i].LoadBitmap(num);
		attackMotion5[i].GetBitmap(&attackMotionInfo5[i]);
		num++;
	}
}

void AttackMotion::setDeathMotion()
{
	int num = 532;
	for(int i = 0; i < 25; i++)
	{
		deathMotion[i].LoadBitmap(num);
		deathMotion[i].GetBitmap(&deathMotionInfo[i]);
		num++;
	}
}

void AttackMotion::setInit()
{
	setAttackMotion1();
	setAttackMotion2();
	setAttackMotion3();
	setAttackMotion4();
	setAttackMotion5();
	setDeathMotion();
}
