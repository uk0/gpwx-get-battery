


#pragma once

#ifndef __AFXWIN_H__
	#error "include befor include¡°stdafx.h¡±make PCH file"
#endif

#include "resource.h"		




class fmMain1 : public CWinApp
{
public:
	fmMain1();


public:
	virtual BOOL InitInstance();



	DECLARE_MESSAGE_MAP()
};

extern fmMain1 theApp;