#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Photoenhancerdoc.h"
#include "stdafx.h"
#include "ImgMelhoramento.h"


// CDlgLinerizar dialog

class CDlgLinerizar : public CDialog
{
	DECLARE_DYNAMIC(CDlgLinerizar)

public:
	CDlgLinerizar(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLinerizar();

// Dialog Data
	enum { IDD = IDD_DLGLINERIZAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int nivel;

	DECLARE_MESSAGE_MAP()

public:
	BYTE m_nivel;
	CButton m_btok;
	CButton m_btcancela;
	
protected:
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

};
