// ReamostrarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "ReamostrarDlg.h"


// CReamostrarDlg dialog

IMPLEMENT_DYNAMIC(CReamostrarDlg, CDialog)
CReamostrarDlg::CReamostrarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReamostrarDlg::IDD, pParent)
	, m_largura(0)
	, m_altura(0)
{
}

CReamostrarDlg::~CReamostrarDlg()
{
}

void CReamostrarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITLARGURA, m_largura);
	DDX_Text(pDX, IDC_EDITALTURA, m_altura);
}


BEGIN_MESSAGE_MAP(CReamostrarDlg, CDialog)
END_MESSAGE_MAP()


// CReamostrarDlg message handlers
