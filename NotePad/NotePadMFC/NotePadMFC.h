
// NotePadMFC.h: NotePadMFC 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CNotePadMFCApp:
// 이 클래스의 구현에 대해서는 NotePadMFC.cpp을(를) 참조하세요.
//

class CNotePadMFCApp : public CWinApp
{
public:
	CNotePadMFCApp() noexcept;
	wchar_t* text;
	int* Return_space;
	int iRC = 0;
	int Cursor = 0;
	int Max_Count = 0;
	int Return_Max = 0;
	bool InsertFlag = false;
	POINT Caret;
// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	CNotePadMFCApp* operator-> () {
		return this;
	}
// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int Run();
	
};

extern CNotePadMFCApp theApp;
