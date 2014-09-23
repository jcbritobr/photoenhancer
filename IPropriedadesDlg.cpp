// IPropriedadesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "IPropriedadesDlg.h"
#include ".\ipropriedadesdlg.h"


// CIPropriedadesDlg dialog

IMPLEMENT_DYNAMIC(CIPropriedadesDlg, CDialog)
CIPropriedadesDlg::CIPropriedadesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPropriedadesDlg::IDD, pParent)
	, m_qualidade(0)
	, m_xres(0)
	, m_yres(0)
{
}

CIPropriedadesDlg::~CIPropriedadesDlg()
{
}

void CIPropriedadesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_qualidade);
	DDV_MinMaxByte(pDX, m_qualidade, 1, 255);
	DDX_Text(pDX, IDC_EDIT2, m_xres);
	DDV_MinMaxLong(pDX, m_xres, 0, 10000);
	DDX_Text(pDX, IDC_EDIT3, m_yres);
	DDV_MinMaxUInt(pDX, m_yres, 0, 10000);
}


BEGIN_MESSAGE_MAP(CIPropriedadesDlg, CDialog)
END_MESSAGE_MAP()


// CIPropriedadesDlg message handlers
