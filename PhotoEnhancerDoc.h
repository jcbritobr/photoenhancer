// PhotoEnhancerDoc.h : interface of the CPhotoEnhancerDoc class
//

#define WM_USER_NOVAIMAGEM WM_USER+1
#pragma once

class CPhotoEnhancerDoc : public CDocument
{
private:
	CxImage* Imagem;
	CxImage* DImagem[8];
	CxImage* RImagem;
	int      NumAlt;
	int      NivelZoom;
	int      Ferramenta;


protected: // create from serialization only
	CPhotoEnhancerDoc();
	DECLARE_DYNCREATE(CPhotoEnhancerDoc)

// Attributes
public:
int FindType(const CString& ext);
CxImage* RecImagem(void){return Imagem;}
// Operations
public:

	long m_hr[256]; //histogram
	long m_hg[256];
	long m_hb[256];
	long m_hgray[256];
	long m_hmax;
// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CPhotoEnhancerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int X,Y;
	int X1,Y1;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnFiltrosLinerizar();
	afx_msg void OnFiltrosClarear();
	afx_msg void OnFiltrosEscurecer();
	afx_msg void OnFiltrosMaiscontraste();
	afx_msg void OnFiltrosMenoscontraste();

	void GuardaDesfazer(void);
	afx_msg void OnFiltrosPassaalta();
	afx_msg void OnFiltrosPassabaixa();
	afx_msg void OnEditUndo();
	afx_msg void OnFiltrosLaplaciano();
	afx_msg void OnImagemYUV();
	afx_msg void OnImagemNegativo();
	afx_msg void SetNivelZoom(int Nivel);
	void AtualizaBarraStatus(void);
	
	void MenosZoom(void);
	void MaisZoom(void);
	int RecNivelZoom(void);
	void ResetaNivelZoom(void);
	void Refazer(void);
	afx_msg void OnFiltrosAdicionaruido();
	afx_msg void OnFiltrosFiltropersonalizado();
	afx_msg void OnImagemPropriedadesdaimagem();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	CString FindExtension(const CString& nome);
	afx_msg void OnFiltrosGamma();
	afx_msg void OnImagemEspelhamento();
	afx_msg void OnImagemEspelhamentovertical();
	afx_msg void OnImagemReamostrar();
	afx_msg void OnImagemDecrementarbpp();
	afx_msg void OnImagemIncrementarbpp();
	afx_msg void SetaSel(void);
	int RecFerramenta(void);

	// Seta Coordenadas para função de corte da imagem digital
	HRESULT SetaCoordCorte(int x, int y, int x1, int y1);
	afx_msg void OnEditCut();
	afx_msg void OnImagemEqualiza();
	afx_msg void OnHistogramaEsticamento1();
	afx_msg void OnHistogramaEsticamento2();
	afx_msg void OnHistogramaEsticamento3();
	afx_msg void OnHistogramaExibirhistograma();
};


