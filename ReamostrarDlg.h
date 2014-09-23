#pragma once


// CReamostrarDlg dialog

class CReamostrarDlg : public CDialog
{
	DECLARE_DYNAMIC(CReamostrarDlg)

public:
	CReamostrarDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReamostrarDlg();

// Dialog Data
	enum { IDD = IDD_REAMOSTRARDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// guarda o novo valor da largura da imagem
	int m_largura;
	// guarda o novo valor da altura da imagem
	int m_altura;
};
