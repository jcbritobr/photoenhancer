#pragma once


// CIPropriedadesDlg dialog

class CIPropriedadesDlg : public CDialog
{
	DECLARE_DYNAMIC(CIPropriedadesDlg)
public:
	CIPropriedadesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIPropriedadesDlg();

// Dialog Data
	enum { IDD = IDD_PROPRIEDADESDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:

public:

	BYTE m_qualidade;
	long m_xres;
	DWORD m_yres;
};
