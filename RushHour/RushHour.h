
// RushHour.h : RushHour ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CRushHourApp:
// �� Ŭ������ ������ ���ؼ��� RushHour.cpp�� �����Ͻʽÿ�.
//

class CRushHourApp : public CWinAppEx
{
public:
	CRushHourApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRushHourApp theApp;
