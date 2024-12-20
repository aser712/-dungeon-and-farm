#include "pch.h"
#include "Monster.h"
#include "User.h"
#include "Dungeon.h"

CRect Monster::rect;
int Monster::size;
int Monster::size_W;
int Monster::size_H;

void Monster::render(CDC* memdc)
{
	CDC memDC;
	memDC.CreateCompatibleDC(memdc);
	memDC.SelectObject(&bitmap);

	if(Dungeon::current_Level >= 1 && Dungeon::current_Level <= 4);
	int x = (size_W - size * 5) / 2;
	int y = (size_H - size * 5) / 2;

	COLORREF color = RGB(255, 255, 255);
	memdc->TransparentBlt(x, y, 5 * size, 5 * size, &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, color);
}