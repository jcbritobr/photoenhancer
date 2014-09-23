// FPersonalizadoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "FPersonalizadoDlg.h"


// CFPersonalizadoDlg dialog

IMPLEMENT_DYNCREATE(CFPersonalizadoDlg, CDialog)

CFPersonalizadoDlg::CFPersonalizadoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFPersonalizadoDlg::IDD,pParent)
	, m_p1(0)
	, m_p2(0)
	, m_p3(0)
	, m_p4(0)
	, m_p5(0)
	, m_p6(0)
	, m_p7(0)
	, m_p8(0)
	, m_p9(0)
{
}

CFPersonalizadoDlg::~CFPersonalizadoDlg()
{
}

void CFPersonalizadoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_p1);
	DDX_Text(pDX, IDC_EDIT2, m_p2);
	DDX_Text(pDX, IDC_EDIT3, m_p3);
	DDX_Text(pDX, IDC_EDIT4, m_p4);
	DDX_Text(pDX, IDC_EDIT5, m_p5);
	DDX_Text(pDX, IDC_EDIT6, m_p6);
	DDX_Text(pDX, IDC_EDIT7, m_p7);
	DDX_Text(pDX, IDC_EDIT8, m_p8);
	DDX_Text(pDX, IDC_EDIT9, m_p9);
}

BOOL CFPersonalizadoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CFPersonalizadoDlg, CDialog)
END_MESSAGE_MAP()





// CFPersonalizadoDlg message handlers
