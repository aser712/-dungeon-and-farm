#pragma once

class AttackMotion
{
public:
	static CBitmap attackMotion1[7];
	static BITMAP attackMotionInfo1[7];

	static CBitmap attackMotion2[7];
	static BITMAP attackMotionInfo2[7];

	static CBitmap attackMotion3[7];
	static BITMAP attackMotionInfo3[7];

	static CBitmap attackMotion4[9];
	static BITMAP attackMotionInfo4[9];

	static CBitmap attackMotion5[16];
	static BITMAP attackMotionInfo5[16];

	static CBitmap deathMotion[25];
	static BITMAP deathMotionInfo[25];


	static void setAttackMotion1();
	static void setAttackMotion2();
	static void setAttackMotion3();
	static void setAttackMotion4();
	static void setAttackMotion5();
	static void setDeathMotion();

	static void setInit();
};