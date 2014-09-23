#pragma once
#include "afxwin.h"


// CIncBppDlg dialog

class CIncBppDlg : public CDialog
{
	DECLARE_DYNAMIC(CIncBppDlg)

public:
	CIncBppDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIncBppDlg();

// Dialog Data
	enum { IDD = IDD_INCBPPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_r4;
	CButton m_r8;
	CButton m_r24;
	long m_bit;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
