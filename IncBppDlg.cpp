// IncBppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "IncBppDlg.h"
#include ".\incbppdlg.h"


// CIncBppDlg dialog

IMPLEMENT_DYNAMIC(CIncBppDlg, CDialog)
CIncBppDlg::CIncBppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIncBppDlg::IDD, pParent)
{
}

CIncBppDlg::~CIncBppDlg()
{
}

void CIncBppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_r4);
	DDX_Control(pDX, IDC_RADIO2, m_r8);
	DDX_Control(pDX, IDC_RADIO3, m_r24);
}


BEGIN_MESSAGE_MAP(CIncBppDlg, CDialog)
END_MESSAGE_MAP()


// CIncBppDlg message handlers

BOOL CIncBppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_bit==4) m_r4.SetCheck(1);
	else if(m_bit==8) m_r8.SetCheck(1);
	else m_r24.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CIncBppDlg::OnOK()
{
	if(m_r4.GetCheck()) m_bit=4;
	else if(m_r8.GetCheck()) m_bit=8;
	else m_bit=24; 

	CDialog::OnOK();
}
