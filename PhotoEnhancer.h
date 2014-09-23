// PhotoEnhancer.h : main header file for the PhotoEnhancer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CPhotoEnhancerApp:
// See PhotoEnhancer.cpp for the implementation of this class
//

class CPhotoEnhancerApp : public CWinApp
{
public:
	CPhotoEnhancerApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPhotoEnhancerApp theApp;