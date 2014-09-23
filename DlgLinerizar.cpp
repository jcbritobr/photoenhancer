// DlgLinerizar.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "DlgLinerizar.h"
#include ".\dlglinerizar.h"



// CDlgLinerizar dialog

IMPLEMENT_DYNAMIC(CDlgLinerizar, CDialog)
CDlgLinerizar::CDlgLinerizar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLinerizar::IDD, pParent)
	, m_nivel(127)
{
	nivel = 127;
}

CDlgLinerizar::~CDlgLinerizar()
{

}

void CDlgLinerizar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_LINERIZAR, m_nivel);
	DDV_MinMaxByte(pDX, m_nivel, 0, 255);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDCANCEL, m_btcancela);
	//DDX_Control(pDX, IDC_SPIN1, m_spinbtn);
}


BEGIN_MESSAGE_MAP(CDlgLinerizar, CDialog)

	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgLinerizar message handlers

BOOL CDlgLinerizar::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgLinerizar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

