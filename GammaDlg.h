#pragma once


// CGammaDlg dialog

class CGammaDlg : public CDialog
{
	DECLARE_DYNAMIC(CGammaDlg)

public:
	CGammaDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGammaDlg();

// Dialog Data
	enum { IDD = IDD_GAMMADLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_nivel;
};
