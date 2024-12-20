// ChildView.h: CChildView 클래스의 인터페이스
//
#include <gdiplus.h>
using namespace Gdiplus;

#pragma once


// CChildView 창


class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();
// 특성입니다.
public:
	int inputlook;
	CBitmap Prologue[17];
	CBitmap Ending[4];  
	int isPrologue;
	int PNum;
	int isEnding;
	int ENum;
	int check;
	bool menuFlag;
// 작업입니다.
public:

	void setPrologue();
	void setEnding();
// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
// 구현입니다.
	ULONG_PTR gdiplusToken;

	void InitializeGDIPlus();
	void ShutdownGDIPlus();
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
