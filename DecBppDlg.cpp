// DecBppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "DecBppDlg.h"
#include ".\decbppdlg.h"


// CDecBppDlg dialog

IMPLEMENT_DYNAMIC(CDecBppDlg, CDialog)
CDecBppDlg::CDecBppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDecBppDlg::IDD, pParent)
{
}

CDecBppDlg::~CDecBppDlg()
{
}

void CDecBppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_r1);
	DDX_Control(pDX, IDC_RADIO2, m_r4);
	DDX_Control(pDX, IDC_RADIO3, m_r8);
}


BEGIN_MESSAGE_MAP(CDecBppDlg, CDialog)
END_MESSAGE_MAP()


// CDecBppDlg message handlers

BOOL CDecBppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_bit==8)m_r8.SetCheck(1);
	else if(m_bit==4)m_r4.SetCheck(1);
	else m_r1.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDecBppDlg::OnOK()
{
	if (m_r8.GetCheck()) m_bit=8;
	else if (m_r4.GetCheck()) m_bit=4;
	else m_bit=1;

	CDialog::OnOK();
}
