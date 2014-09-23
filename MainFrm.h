// MainFrm.h : interface of the CMainFrame class
//
#include "BCMenu.h"


#pragma once
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	inline CStatusBar& RecStatusBar(){return m_wndStatusBar;}
	void AtualizaStatusBar(CCmdUI *pCmdUI);
		// Attributes
public:
// Operations
public:

// Overrides
public:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	BCMenu      m_menu;
	BCMenu      m_padrao;
protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;


// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	HMENU NovoMenu(void);
	HMENU NovoPadrao(void);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};


