// PhotoEnhancerDoc.cpp : implementation of the CPhotoEnhancerDoc class
//

#include <math.h>
#include "stdafx.h"

#include "PhotoEnhancer.h"
#include "DlgLinerizar.h"
#include "RuidoDlg.h"
#include "ImgMelhoramento.h"
#include "FPersonalizadoDlg.h"
#include "IPropriedadesDlg.h"
#include "GammaDlg.h"
#include "ReamostrarDlg.h"
#include "DecBppDlg.h"
#include "IncBppDlg.h"
#include "HistoDlg.h"
#include "MainFrm.h"


#include "PhotoEnhancerDoc.h"
#include ".\photoenhancerdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif
#define MAXD 8

// CPhotoEnhancerDoc

IMPLEMENT_DYNCREATE(CPhotoEnhancerDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhotoEnhancerDoc, CDocument)
	ON_COMMAND(ID_FILTROS_LINERIZAR, OnFiltrosLinerizar)
	ON_COMMAND(ID_FILTROS_CLAREAR, OnFiltrosClarear)
	ON_COMMAND(ID_FILTROS_ESCURECER, OnFiltrosEscurecer)
	ON_COMMAND(ID_FILTROS_MAISCONTRASTE, OnFiltrosMaiscontraste)
	ON_COMMAND(ID_FILTROS_MENOSCONTRASTE, OnFiltrosMenoscontraste)
	ON_COMMAND(ID_FILTROS_PASSAALTA, OnFiltrosPassaalta)
	ON_COMMAND(ID_FILTROS_PASSABAIXA, OnFiltrosPassabaixa)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_BTN_DESFAZER, OnEditUndo)
	ON_COMMAND(ID_BTN_REFAZER, Refazer)
	ON_COMMAND(ID_EDITAR_REFAZER, Refazer)
	ON_COMMAND(ID_FILTROS_LAPLACIANO, OnFiltrosLaplaciano)
	ON_COMMAND(ID_IMAGEM_YUV, OnImagemYUV)
	ON_COMMAND(ID_IMAGEM_NEGATIVO, OnImagemNegativo)
	ON_COMMAND(ID_BTNZOOMN, ResetaNivelZoom)
	ON_COMMAND(ID_BTNMENOSZOOM, MenosZoom)
	ON_COMMAND(ID_BTNMAISZOOM, MaisZoom)
	ON_COMMAND(ID_FILTROS_ADICIONARUIDO, OnFiltrosAdicionaruido)
	ON_COMMAND(ID_FILTROS_FILTROPERSONALIZADO, OnFiltrosFiltropersonalizado)
	ON_COMMAND(ID_IMAGEM_PROPRIEDADESDAIMAGEM, OnImagemPropriedadesdaimagem)
	ON_COMMAND(ID_FILTROS_GAMMA, OnFiltrosGamma)
	ON_COMMAND(ID_IMAGEM_ESPELHAMENTO, OnImagemEspelhamento)
	ON_COMMAND(ID_IMAGEM_ESPELHAMENTOVERTICAL, OnImagemEspelhamentovertical)
	ON_COMMAND(ID_IMAGEM_REAMOSTRAR, OnImagemReamostrar)
	ON_COMMAND(ID_IMAGEM_DECREMENTARBPP, OnImagemDecrementarbpp)
	ON_COMMAND(ID_IMAGEM_INCREMENTARBPP, OnImagemIncrementarbpp)
	ON_COMMAND(ID_BTN_SEL, SetaSel)	
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_IMAGEM_EQUALIZA, OnImagemEqualiza)
	ON_COMMAND(ID_HISTOGRAMA_ESTICAMENTO1, OnHistogramaEsticamento1)
	ON_COMMAND(ID_HISTOGRAMA_ESTICAMENTO2, OnHistogramaEsticamento2)
	ON_COMMAND(ID_HISTOGRAMA_ESTICAMENTO3, OnHistogramaEsticamento3)
	ON_COMMAND(ID_HISTOGRAMA_EXIBIRHISTOGRAMA, OnHistogramaExibirhistograma)
END_MESSAGE_MAP()


// CPhotoEnhancerDoc construction/destruction

CPhotoEnhancerDoc::CPhotoEnhancerDoc()
{
	Imagem = NULL;
	for(int i=0; i<MAXD;i++)
	{
		DImagem[i] = NULL;
	}
	RImagem = new CxImage();

	NumAlt = 0;
	NivelZoom = 0;
	Ferramenta = 0;
	X = 0;
	Y = 0;
	X1 = 0;
	Y1 = 0;
	m_hmax = 0;

}

CPhotoEnhancerDoc::~CPhotoEnhancerDoc()
{
	delete Imagem;
	Imagem = NULL;
	delete RImagem;
	RImagem = NULL;
	
	for(int i=0; i<MAXD;i++)
	 {
		delete DImagem[i];
		DImagem[i] = NULL;
	 }

}

int CPhotoEnhancerDoc::FindType(const CString& ext)
{
	int type = 0;
	if (ext == "bmp")					type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (ext=="jpg"||ext=="jpeg")	type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (ext == "gif")				type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (ext == "png")				type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (ext=="mng"||ext=="jng")	type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (ext == "ico")				type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (ext=="tiff"||ext=="tif")	type = CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (ext=="tga")				type = CXIMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
	else if (ext=="pcx")				type = CXIMAGE_FORMAT_PCX;
#endif
#if CXIMAGE_SUPPORT_WBMP
	else if (ext=="wbmp")				type = CXIMAGE_FORMAT_WBMP;
#endif
#if CXIMAGE_SUPPORT_WMF
	else if (ext=="wmf"||ext=="emf")	type = CXIMAGE_FORMAT_WMF;
#endif
#if CXIMAGE_SUPPORT_J2K
	else if (ext=="j2k"||ext=="jp2")	type = CXIMAGE_FORMAT_J2K;
#endif
#if CXIMAGE_SUPPORT_JBG
	else if (ext=="jbg")				type = CXIMAGE_FORMAT_JBG;
#endif
#if CXIMAGE_SUPPORT_JP2
	else if (ext=="jp2"||ext=="j2k")	type = CXIMAGE_FORMAT_JP2;
#endif
#if CXIMAGE_SUPPORT_JPC
	else if (ext=="jpc"||ext=="j2c")	type = CXIMAGE_FORMAT_JPC;
#endif
#if CXIMAGE_SUPPORT_PGX
	else if (ext=="pgx")				type = CXIMAGE_FORMAT_PGX;
#endif
#if CXIMAGE_SUPPORT_RAS
	else if (ext=="ras")				type = CXIMAGE_FORMAT_RAS;
#endif
#if CXIMAGE_SUPPORT_PNM
	else if (ext=="pnm"||ext=="pgm"||ext=="ppm") type = CXIMAGE_FORMAT_PNM;
#endif
	else type = CXIMAGE_FORMAT_UNKNOWN;

	return type;
}
//////////////////////////////////////////////////////////////////////////////


BOOL CPhotoEnhancerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPhotoEnhancerDoc serialization

void CPhotoEnhancerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CPhotoEnhancerDoc diagnostics

#ifdef _DEBUG
void CPhotoEnhancerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhotoEnhancerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPhotoEnhancerDoc commands

BOOL CPhotoEnhancerDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	
	CString nomeArquivo(lpszPathName);
	CString ext(PathFindExtension(nomeArquivo));
	
	ext.MakeLower();
	if(ext=="") return FALSE;
	int tipo = FindType(ext);

	Imagem = new CxImage(nomeArquivo,tipo);

	if(!Imagem->IsValid())
	{
		AfxMessageBox(Imagem->GetLastError());
		delete Imagem;
		Imagem = NULL;
		return FALSE;
	}

	return TRUE;
}

void CPhotoEnhancerDoc::OnFiltrosLinerizar()
{
	GuardaDesfazer();
	CDlgLinerizar dlg;	
	
  
 if(Imagem)
  {
	CxImage* tmp = new CxImage(*Imagem);
  
	if(dlg.DoModal()==IDOK) 
	{
		CImgMelhoramento *filtros = new CImgMelhoramento();
		int nivel = dlg.m_nivel;
		filtros->Limiarizar(Imagem,nivel);			
		
		delete filtros;
		filtros = NULL;
	}
  }
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}



void CPhotoEnhancerDoc::OnFiltrosClarear()
{
	GuardaDesfazer();
	CImgMelhoramento *filtros = new CImgMelhoramento();
	
	if(Imagem)
	{
	  CxImage *tmp = new CxImage(*Imagem,TRUE);
	  tmp->Copy(*Imagem);
	  filtros->Clarear(tmp,30);	
	  Imagem->Copy(*tmp);
	  delete tmp;
	  delete filtros;
	  tmp = NULL;
	  filtros = NULL;	
	  UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);

	}
}

void CPhotoEnhancerDoc::OnFiltrosEscurecer()
{
	GuardaDesfazer();


	if(Imagem)
	{
	  CxImage *tmp = new CxImage(*Imagem);
	  CImgMelhoramento *filtros = new CImgMelhoramento();
	  filtros->Escurecer(tmp,30);	
	  Imagem->Copy(*tmp);
	  delete tmp;
	  delete filtros;
	  tmp = NULL;
	  filtros = NULL;
	  UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
	
	}
}

void CPhotoEnhancerDoc::OnFiltrosMaiscontraste()
{
	GuardaDesfazer();
	
	if(Imagem)
	{
	  CxImage tmp(*Imagem);	
	  CImgMelhoramento filtros;
	  filtros.MaisContraste(&tmp,50);
	  Imagem->Copy(tmp);
	  UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
	}

}

void CPhotoEnhancerDoc::OnFiltrosMenoscontraste()
{
	GuardaDesfazer();
	
    if(Imagem)
	{
	  CxImage tmp(*Imagem);
	  CImgMelhoramento filtros;
	  tmp.Copy(*Imagem);

	  filtros.MenosContraste(&tmp,50);
	  Imagem->Copy(tmp);
	  UpdateAllViews(NULL, WM_USER_NOVAIMAGEM);
	}
}


void CPhotoEnhancerDoc::OnFiltrosPassaalta()
{
	GuardaDesfazer();
	float Mask[9] = {-1,-1,-1,
				    -1,9,-1,
					-1,-1,-1};
	
	CImgMelhoramento filtros;
	CxImage tmp(*Imagem);
	if(tmp.IsValid())
	{
		if(tmp.GetBpp()<24) tmp.IncreaseBpp(24);
		filtros.Convolui(&tmp,1,Mask);

	}
	
	Imagem->Copy(tmp);
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);	
}

void CPhotoEnhancerDoc::OnFiltrosPassabaixa()
{
	GuardaDesfazer();
	float Mask[9] = {1.0/10,1.0/10,1.0/10,
					 1.0/10,1.0/5.0,1.0/10,
					 1.0/10,1.0/10,1.0/10};
	
	CImgMelhoramento filtros;
	CxImage tmp(*Imagem);
	if(tmp.IsValid())
	{
		if(tmp.GetBpp()<24) tmp.IncreaseBpp(24);
		filtros.Convolui(&tmp,1,Mask);
	}
	
	Imagem->Copy(tmp);
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

void CPhotoEnhancerDoc::GuardaDesfazer(void)
{
	
	if(Imagem)
	{
	  if(NumAlt==8) NumAlt=0;
	
	  if(Imagem->IsValid())
	  {
		if (DImagem[NumAlt]==NULL)DImagem[NumAlt]=new CxImage();
		DImagem[NumAlt]->Copy(*Imagem);
	  }
	NumAlt++;
	}
}

void CPhotoEnhancerDoc::OnEditUndo()
{
	NumAlt--;
	if(NumAlt<0) NumAlt=0;

	if (DImagem[NumAlt]!=NULL)
	{
		RImagem->Copy(*Imagem);
		Imagem->Copy(*DImagem[NumAlt]);
		UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
	}
}

void CPhotoEnhancerDoc::OnFiltrosLaplaciano()
{
	GuardaDesfazer();
	float Mask[9] = {-1.0,-1.0,-1.0,
					 -1.0,8.0,-1.0,
					 -1.0,-1.0,-1.0};
	CImgMelhoramento filtros;
	CxImage tmp(*Imagem);
	
	if(tmp.IsValid())
	{
		if(tmp.GetBpp()<24) tmp.IncreaseBpp(24);
		
		filtros.Convolui(&tmp,1,Mask);
	}
	tmp.GrayScale();
	Imagem->Copy(tmp);

	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}


void CPhotoEnhancerDoc::OnImagemYUV()
{
 GuardaDesfazer();
 RGBTRIPLE *Linha;
 int Cinza;
 CxImage *tmp = new CxImage(*Imagem);
 if(tmp)
 {
	if(tmp->GetBpp()<24) tmp->IncreaseBpp(24);
	
	for(int j=0;j<tmp->GetHeight();j++)
	{
		Linha = (RGBTRIPLE*)tmp->GetBits(j);
		for(int i=0;i<tmp->GetWidth();i++)
		{
			Cinza = Linha[i].rgbtBlue * 0.3 + Linha[i].rgbtGreen * 0.59 + Linha[i].rgbtRed * 0.11;

			Linha[i].rgbtBlue = Cinza;
			Linha[i].rgbtGreen = Cinza;
			Linha[i].rgbtRed = Cinza;
		}
	}
	Imagem->Copy(*tmp);
}
 delete tmp;
 tmp = NULL;
 UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

void CPhotoEnhancerDoc::OnImagemNegativo()
{
 GuardaDesfazer();
 CImgMelhoramento filtros;
 CxImage tmp(*Imagem);
	 if(tmp.IsValid())
 {
	 if(tmp.GetBpp()<24) tmp.IncreaseBpp(24);
	 filtros.Negativo(&tmp); 
 }
 Imagem->Copy(tmp);	
 UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

void CPhotoEnhancerDoc::AtualizaBarraStatus(void)
{
	if(Imagem)
	{
		CString msg;
		CStatusBar& sb = ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->RecStatusBar();
		msg.Format("[%dx%dx%d]",Imagem->GetWidth(),Imagem->GetHeight(),Imagem->GetBpp());
		sb.SetPaneText(1,msg);
	}
}

void CPhotoEnhancerDoc::SetNivelZoom(int Nivel)
{
	NivelZoom = Nivel;
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

void CPhotoEnhancerDoc::MenosZoom(void)
{
	NivelZoom -=25;
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

void CPhotoEnhancerDoc::MaisZoom(void)
{
	NivelZoom +=25;
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

int CPhotoEnhancerDoc::RecNivelZoom(void)
{
	return NivelZoom;
}

void CPhotoEnhancerDoc::ResetaNivelZoom(void)
{
	NivelZoom = 0;
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

void CPhotoEnhancerDoc::Refazer(void)
{
	
	if(RImagem!=NULL)
	{
		Imagem->Copy(*RImagem);
		UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
	}
}

void CPhotoEnhancerDoc::OnFiltrosAdicionaruido()
{
	GuardaDesfazer();
	CRuidoDlg dlg;
	CxImage tmp;
	CImgMelhoramento utils;
	if(Imagem)
	{
		if(dlg.DoModal()==IDOK)
		{
		  tmp.Copy(*Imagem);
		  utils.AdicionaRuidoCor(&tmp,dlg.Quantidade);
		  Imagem->Copy(tmp);
		}
	}
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

void CPhotoEnhancerDoc::OnFiltrosFiltropersonalizado()
{
	GuardaDesfazer();
	CFPersonalizadoDlg dlg;
	float Mascara[9];

	CxImage tmp;
	CImgMelhoramento utils;
	if(Imagem)
	{
		if(dlg.DoModal()==IDOK)
		{
		  Mascara[0] = dlg.m_p1;
		  Mascara[1] = dlg.m_p2;
		  Mascara[2] = dlg.m_p3;
		  Mascara[3] = dlg.m_p4;
		  Mascara[4] = dlg.m_p5;
		  Mascara[5] = dlg.m_p6;
		  Mascara[6] = dlg.m_p7;
		  Mascara[7] = dlg.m_p8;
		  Mascara[8] = dlg.m_p9;
		  tmp.Copy(*Imagem);
		  utils.Convolui(&tmp,1,Mascara);
		  Imagem->Copy(tmp);
		}
	}
	UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
}

void CPhotoEnhancerDoc::OnImagemPropriedadesdaimagem()
{
	CIPropriedadesDlg dlg;
	CxImage tmp;

	if(Imagem)
	{
		tmp.Copy(*Imagem);
		dlg.m_qualidade = tmp.GetJpegQuality();
		dlg.m_xres = tmp.GetXDPI();
		dlg.m_yres = tmp.GetYDPI();
		if(dlg.DoModal()==IDOK)
		{
		  tmp.SetJpegQuality(dlg.m_qualidade);
		  tmp.SetXDPI(dlg.m_xres);
		  tmp.SetYDPI(dlg.m_yres);
		  Imagem->Copy(tmp);
		  UpdateAllViews(NULL);
		}
	}
}

BOOL CPhotoEnhancerDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CString nArquivo(lpszPathName);
	CString ext(FindExtension(nArquivo));
	ext.MakeLower();

	if(ext=="") return FALSE;
	int tipo = FindType(ext);
	if(tipo==CXIMAGE_FORMAT_UNKNOWN) return FALSE;

	bool retval;
	retval = Imagem->Save(nArquivo,tipo);
	
	if(retval) return TRUE;
	AfxMessageBox(Imagem->GetLastError());

	return CDocument::OnSaveDocument(lpszPathName);
}

CString CPhotoEnhancerDoc::FindExtension(const CString& nome)
{
	int len = nome.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (nome[i] == '.'){
			return nome.Mid(i+1);
		}
	}
	return CString("");
}
void CPhotoEnhancerDoc::OnFiltrosGamma()
{
    GuardaDesfazer();
	CGammaDlg dlg;
	CImgMelhoramento filtros;

	if(Imagem)
	{
		if(dlg.DoModal()==IDOK)
		{
			filtros.GammaCorrecao(Imagem,dlg.m_nivel);
		    UpdateAllViews(NULL);
		}
	}
}

void CPhotoEnhancerDoc::OnImagemEspelhamento()
{

	if(Imagem)
	{
		GuardaDesfazer();
	    CImgMelhoramento filtros;
		filtros.EHoritontal(Imagem);
        UpdateAllViews(NULL);
	}
}

void CPhotoEnhancerDoc::OnImagemEspelhamentovertical()
{
	if(Imagem)
	{
		GuardaDesfazer();
	    CImgMelhoramento filtros;
		filtros.EVertical(Imagem);
        UpdateAllViews(NULL);
	}
}

void CPhotoEnhancerDoc::OnImagemReamostrar()
{
	if(Imagem)
	{
		GuardaDesfazer();
		CReamostrarDlg dlg;
		CImgMelhoramento filtros;
		dlg.m_largura = Imagem->GetWidth();
		dlg.m_altura  = Imagem->GetHeight();
		if(dlg.DoModal()==IDOK)
		{
			filtros.Reamostrar(Imagem,dlg.m_largura,dlg.m_altura);
		    UpdateAllViews(NULL);
		}
	}
}

void CPhotoEnhancerDoc::OnImagemDecrementarbpp()
{
	if(Imagem)
	{
		GuardaDesfazer();
		CDecBppDlg dlg;
		dlg.m_bit = Imagem->GetBpp();
		if(dlg.DoModal() == IDOK)
		{
			Imagem->DecreaseBpp(dlg.m_bit,0,0,0);
			UpdateAllViews(NULL);
		}
	}
}

void CPhotoEnhancerDoc::OnImagemIncrementarbpp()
{
	if(Imagem)
	{
		GuardaDesfazer();
		CIncBppDlg dlg;
		dlg.m_bit = Imagem->GetBpp();
		if(dlg.DoModal() == IDOK)
		{
			Imagem->IncreaseBpp(dlg.m_bit);
			UpdateAllViews(NULL);
		}
	}
}

int CPhotoEnhancerDoc::RecFerramenta(void)
{
	return Ferramenta;
}

void CPhotoEnhancerDoc::SetaSel(void)
{
	if(Ferramenta ==0)Ferramenta = 1;
	else Ferramenta = 0;
}

// Seta Coordenadas para função de corte da imagem digital
HRESULT CPhotoEnhancerDoc::SetaCoordCorte(int x, int y, int x1, int y1)
{
   if(Imagem)
   {
	  X = x;
	  Y = y;
      X1 = x1;
	  Y1 = y1;
      return S_OK;
   }
	return E_NOTIMPL;
}

void CPhotoEnhancerDoc::OnEditCut()
{
	if(Imagem && X!=0 && Y!=0 && X1!=0 && Y1!=0)
	{
		GuardaDesfazer();
		Imagem->Crop(X,Y,X1,Y1,0);
		UpdateAllViews(NULL);
	}
}

void CPhotoEnhancerDoc::OnImagemEqualiza()
{
	if(Imagem)
	{
		GuardaDesfazer();
		CImgMelhoramento filtros;
		filtros.HEqualizar(Imagem);
		UpdateAllViews(NULL);
	}
}

void CPhotoEnhancerDoc::OnHistogramaEsticamento1()
{
	if(Imagem)
	{
		GuardaDesfazer();
		CImgMelhoramento filtros;
		filtros.HEsticamento(Imagem,1.2);
		UpdateAllViews(NULL);
	}
}

void CPhotoEnhancerDoc::OnHistogramaEsticamento2()
{
	if(Imagem)
	{
		GuardaDesfazer();
		CImgMelhoramento filtros;
		filtros.HEsticamento(Imagem,1.5);
		UpdateAllViews(NULL);
	}
}

void CPhotoEnhancerDoc::OnHistogramaEsticamento3()
{
	if(Imagem)
	{
		GuardaDesfazer();
		CImgMelhoramento filtros;
		filtros.HEsticamento(Imagem,2.5);
		UpdateAllViews(NULL);
	}
}
void CPhotoEnhancerDoc::OnHistogramaExibirhistograma()
{
	if(Imagem)
	{
		CHistoDlg dlg;
		dlg.DoModal();
	}
}
