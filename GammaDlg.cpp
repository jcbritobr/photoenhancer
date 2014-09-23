// GammaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "GammaDlg.h"


// CGammaDlg dialog

IMPLEMENT_DYNAMIC(CGammaDlg, CDialog)
CGammaDlg::CGammaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGammaDlg::IDD, pParent)
	, m_nivel(0)
{
}

CGammaDlg::~CGammaDlg()
{
}

void CGammaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nivel);
}


BEGIN_MESSAGE_MAP(CGammaDlg, CDialog)
END_MESSAGE_MAP()


// CGammaDlg message handlers
