#pragma once
#include "afxwin.h"


// CHistoDlg dialog

class CHistoDlg : public CDialog
{
	DECLARE_DYNAMIC(CHistoDlg)

public:
	CHistoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHistoDlg();

// Dialog Data
	enum { IDD = IDD_HISTODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int	m_ren;
	int	m_gen;
	int	m_ben;
	int m_grayen;
	bool m_initok;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CButton m_cred;
	CButton m_cgreen;
	CButton m_cblue;
	afx_msg void OnBnClickedCheckred();
	afx_msg void OnBnClickedCheckgreen();
	afx_msg void OnBnClickedCheckblue();
	CButton m_ccinza;
	afx_msg void OnBnClickedCheckcinza();
};
