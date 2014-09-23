// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "PhotoEnhancerDoc.h"
#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_STBBPP,AtualizaStatusBar)
	ON_WM_MEASUREITEM()
//	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,// status line indicator
	ID_STBBPP,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.SetWindowText(_T("Paleta de Ferramentas"));

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(1,ID_STBBPP,1,80);//aqui, adicionando mais um campo para a barra de status
	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

//BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
//{
//	if( !CMDIFrameWnd::PreCreateWindow(cs) )
//		return FALSE;
//
//
//	return TRUE;
//}

void CMainFrame::AtualizaStatusBar(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers


HMENU CMainFrame::NovoMenu(void)
{
	/*Uma maneira de se criar menus com bitmaps
	é carregá-los de uma toolbar*/
	
	m_menu.LoadMenu(IDR_PhotoEnhancerTYPE);
	m_menu.LoadToolbar(IDR_TOOL_MAINFRAME);
	
	
	return (m_menu.Detach());
}

HMENU CMainFrame::NovoPadrao(void)
{
	m_padrao.LoadMenu(IDR_MAINFRAME);
	m_padrao.LoadToolbar(IDR_TOOL_MAINFRAME);

    return (m_padrao.Detach());
}

void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	  BOOL setflag=FALSE;
  if(lpMeasureItemStruct->CtlType==ODT_MENU){
    if(IsMenu((HMENU)lpMeasureItemStruct->itemID)){
      CMenu* cmenu = 
       CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
	  if(m_menu.IsMenu(cmenu) || m_padrao.IsMenu(cmenu)){
        m_menu.MeasureItem(lpMeasureItemStruct);
		m_padrao.MeasureItem(lpMeasureItemStruct);
        setflag=TRUE;
      }
    }
  }

	CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}