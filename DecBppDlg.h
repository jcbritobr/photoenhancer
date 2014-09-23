#pragma once


// CDecBppDlg dialog

class CDecBppDlg : public CDialog
{
	DECLARE_DYNAMIC(CDecBppDlg)

public:
	CDecBppDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDecBppDlg();
	long m_bit;
	CButton	m_r8;
	CButton	m_r4;
	CButton	m_r1;
// Dialog Data
	enum { IDD = IDD_DECBPPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
