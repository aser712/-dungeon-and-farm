#include "pch.h"
#include "UI.h"
#include "resource.h"

SEASON UI::season;
int UI::day;
int UI::money;
int UI::size;
CBitmap UI::UIImage;
BITMAP UI::UIImageInfo;
CBitmap UI::boardImage;
BITMAP UI::boardImageInfo;


void UI::setInit()
{
	UIImage.LoadBitmap(IDB_UI);
	UIImage.GetBitmap(&UIImageInfo);
	boardImage.LoadBitmap(IDB_Board);
	boardImage.GetBitmap(&boardImageInfo);
	season = SPRING;
	day = 1;
	money = 0;
}

void UI::setsize(CRect in)
{
	size = in.Height() / 14 * 12 / 15;
}

void UI::printUI(CDC* memdc)
{
	CDC imageDC;
	imageDC.CreateCompatibleDC(memdc);
	imageDC.SelectObject(&UIImage);

	COLORREF transparentColor = RGB(255, 255, 255);
	int x = size * 25;
	int y = 0;
	memdc->SelectStockObject(WHITE_BRUSH);
	//memdc->Rectangle(x, y, x + size * 3, y + size*2);
	memdc->TransparentBlt(x, y, size * 4, size * 2, &imageDC, 0, 0, UIImageInfo.bmWidth, UIImageInfo.bmHeight, transparentColor);

	CString temp;
	switch (season)
	{
	case SPRING:
		temp.Format(_T("봄 : %d일째"),day);
		break;
	case SUMMER:
		temp.Format(_T("여름: %d일째"), day);
		break;
	case FALL:
		temp.Format(_T("가을 : %d일째"), day);
		break;
	case WINTER:
		temp.Format(_T("겨울 : %d일째\n"), day);
		break;
	default:
		break;
	}
	CString str;
	str.Format(_T("돈 : %d"), money);
	
	LOGFONT logFont = { 0 };
	lstrcpy(logFont.lfFaceName, _T("굴림"));
	logFont.lfHeight = -size * 0.48;
	logFont.lfWidth = 0;
	logFont.lfWeight = FW_BOLD;
	logFont.lfItalic = FALSE;

	CFont font;
	font.CreateFontIndirect(&logFont);

	memdc->SelectObject(&font);  // 폰트 적용

	// 배경을 투명하게 설정
	memdc->SetBkMode(TRANSPARENT);

	memdc->SetTextColor(RGB(0,0,0));

	memdc->TextOutW(x + size * 0.2 + 1, y + size * 0.3 - 1, temp);
	memdc->TextOutW(x + size * 0.2 + 1, y + size * 0.3 + 1, temp);
	memdc->TextOutW(x + size * 0.2 - 1, y + size * 0.3 - 1, temp);
	memdc->TextOutW(x + size * 0.2 - 1, y + size * 0.3 + 1, temp);
	
	memdc->TextOutW(x + size * 0.2 + 1, y + size - 1, str);
	memdc->TextOutW(x + size * 0.2 + 1, y + size + 1, str);
	memdc->TextOutW(x + size * 0.2 - 1, y + size - 1, str);
	memdc->TextOutW(x + size * 0.2 - 1, y + size + 1, str);


	memdc->SetTextColor(RGB(255, 255, 255));
	memdc->TextOutW(x + size*0.2, y + size*0.3, temp);
	memdc->TextOutW(x + size*0.2, y + size*1, str);

	//->StretchBlt(x, y, size * 3, size * 2, &imageDC, 0, 0, UIImageInfo.bmWidth, UIImageInfo.bmHeight, SRCCOPY);
}
