#pragma once


// CRuidoDlg dialog

class CRuidoDlg : public CDialog
{
	DECLARE_DYNAMIC(CRuidoDlg)

public:
	CRuidoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRuidoDlg();

// Dialog Data
	enum { IDD = IDD_RUIDODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int Quantidade;
};
