// RuidoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "RuidoDlg.h"


// CRuidoDlg dialog

IMPLEMENT_DYNAMIC(CRuidoDlg, CDialog)
CRuidoDlg::CRuidoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRuidoDlg::IDD, pParent)
	, Quantidade(0)
{
}

CRuidoDlg::~CRuidoDlg()
{
}

void CRuidoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Quantidade);
}


BEGIN_MESSAGE_MAP(CRuidoDlg, CDialog)
END_MESSAGE_MAP()


// CRuidoDlg message handlers
