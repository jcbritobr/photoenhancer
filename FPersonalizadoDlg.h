#pragma once


// CFPersonalizadoDlg dialog

class CFPersonalizadoDlg : public CDialog
{
	DECLARE_DYNCREATE(CFPersonalizadoDlg)

public:
	CFPersonalizadoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFPersonalizadoDlg();
// Overrides
// Dialog Data
 enum {IDD = IDD_FPERDLG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	
public:
	float m_p1;
	float m_p2;
	float m_p3;
	float m_p4;
	float m_p5;
	float m_p6;
	float m_p7;
	float m_p8;
	float m_p9;
};
