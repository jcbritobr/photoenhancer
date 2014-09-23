// PhotoEnhancerView.cpp : implementation of the CPhotoEnhancerView class
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "MainFrm.h"

#include "PhotoEnhancerDoc.h"
#include "PhotoEnhancerView.h"
#include ".\photoenhancerview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhotoEnhancerView

IMPLEMENT_DYNCREATE(CPhotoEnhancerView, CScrollView)

BEGIN_MESSAGE_MAP(CPhotoEnhancerView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
//	ON_WM_ACTIVATE()
ON_WM_VSCROLL()
ON_WM_HSCROLL()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CPhotoEnhancerView construction/destruction

CPhotoEnhancerView::CPhotoEnhancerView()
{
	// TODO: add construction code here

}

CPhotoEnhancerView::~CPhotoEnhancerView()
{
}

BOOL CPhotoEnhancerView::PreCreateWindow(CREATESTRUCT& cs)
{
	//CBrush background;
	//background.CreateSolidBrush(RGB(150,150,150));
	cs.lpszClass = ::AfxRegisterWndClass(NULL,NULL,(HBRUSH)GetSysColorBrush(COLOR_BTNFACE+4),NULL);


	return CScrollView::PreCreateWindow(cs);
}

// CPhotoEnhancerView drawing

void CPhotoEnhancerView::OnDraw(CDC* pDC)
{
	CPhotoEnhancerDoc* pDoc = GetDocument();// ponteiro para o doc ativo
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int zoom = pDoc->RecNivelZoom();//recupera o nivel de zoom
	CxImage*Buffer = pDoc->RecImagem();//recupera o jpeg


	if(Buffer)
	{
		if(zoom == 0)
		{
		  Buffer->Draw2(pDC->GetSafeHdc(),0,0,Buffer->GetWidth(),Buffer->GetHeight());
		  pDoc->AtualizaBarraStatus();
		}
		else
		{
		 	//LarguraCliente = Area.right / 2;
			//AlturaCliente  = Area.bottom /2;

			int LarguraImagem = (Buffer->GetWidth());
			int AlturaImagem  = (Buffer->GetHeight());

			int zoomlarg=(zoom*LarguraImagem)/100;
			int zoomalt=(zoom*AlturaImagem)/100;

			if((zoomlarg<0) || (zoomalt<0))
			{
				if(abs(zoomlarg)>LarguraImagem){ pDoc->SetNivelZoom(zoom+25); pDoc->UpdateAllViews(NULL); return;}
				if(abs(zoomalt)>AlturaImagem) {pDoc->SetNivelZoom(zoom+25); pDoc->UpdateAllViews(NULL); return;}
			}
			Buffer->Draw2(pDC->GetSafeHdc(),0,0,Buffer->GetWidth()+zoomlarg,Buffer->GetHeight()+zoomalt);
		    pDoc->AtualizaBarraStatus();	
		}
	}
	

	// TODO: add draw code for native data here
}


// CPhotoEnhancerView printing

BOOL CPhotoEnhancerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPhotoEnhancerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPhotoEnhancerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPhotoEnhancerView diagnostics

#ifdef _DEBUG
void CPhotoEnhancerView::AssertValid() const
{
	CView::AssertValid();
}

void CPhotoEnhancerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPhotoEnhancerDoc* CPhotoEnhancerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhotoEnhancerDoc)));
	return (CPhotoEnhancerDoc*)m_pDocument;
}
#endif //_DEBUG


// CPhotoEnhancerView message handlers

void CPhotoEnhancerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	
	CPhotoEnhancerDoc* pDoc = GetDocument();
	int zoom = pDoc->RecNivelZoom(); 
	if(zoom<0)
	{
	  if(abs(zoom*10) > pDoc->RecImagem()->GetWidth() || abs(zoom*10) > pDoc->RecImagem()->GetHeight())
	  {
		  pDoc->SetNivelZoom(zoom+25);
		  return;
	  }
	}

	SetScrollSizes(MM_TEXT,CSize(pDoc->RecImagem()->GetWidth()+(zoom*10),pDoc->RecImagem()->GetHeight()+(zoom*10)));

	switch(lHint)
	{
	case WM_USER_NOVAIMAGEM:
		{
			CPhotoEnhancerDoc* pDoc = GetDocument();
			CxImage *Buffer = pDoc->RecImagem();
			CWnd *pFrame = GetParentFrame();
	
			if(Buffer)
			{
				pFrame->SetWindowPos(0,0,0,Buffer->GetWidth(),Buffer->GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
			}
			break;
		}
	default:{
			
			  CPhotoEnhancerDoc* pDoc = GetDocument();
			  CxImage *Buffer = pDoc->RecImagem();
			  CWnd *pFrame = GetParentFrame();
	
			  if(Buffer)
			  {
				pFrame->SetWindowPos(0,0,0,Buffer->GetWidth(),Buffer->GetHeight(),SWP_NOMOVE|SWP_NOZORDER);
			  }
			  break;
			
			
			}
	}
			//CPhotoEnhancerDoc* pDoc = GetDocument();
	        pDoc->AtualizaBarraStatus();
			Invalidate();
			//CScrollView::OnUpdate(pSender,lHint,pHint);
}

void CPhotoEnhancerView::OnMouseMove(UINT nFlags, CPoint point)
{
	
	CPhotoEnhancerDoc* pDoc = GetDocument();
	int zoom = pDoc->RecNivelZoom();
	CxImage* tmp = pDoc->RecImagem();
	CStatusBar& sb = ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->RecStatusBar();
	if(!tmp) return;

	long x = point.x;
	long y = point.y;
	char msg[80];

	if(zoom == 0)
	{
	  if(tmp->IsInside(x,y))
	  {
		  long yInverso = tmp->GetHeight() -y -1;
		  RGBQUAD RGB = tmp->GetPixelColor(x,yInverso);
		  sprintf(msg,"PIXEL(XCoord:%d YCoord:%d)==(R:%d G:%d B:%d)",x,y,RGB.rgbRed,RGB.rgbGreen,RGB.rgbBlue);
		  sb.SetPaneText(0,msg);
	  }
	  else sb.SetPaneText(0,"");
	}
	else
	{
		sb.SetPaneText(0,"");
	}

	if(tmp->IsInside(x,y))
	{
	
		if(pDoc->RecFerramenta()==1 && (nFlags & MK_LBUTTON))
	    {
		  	CClientDC dc(this);
			
			DrawFocusRect(dc.GetSafeHdc(),&VelhaCoord);//desenha um retangulo na posição antiga, para apagar o primeiro
			RECT rect;
			rect.top  = Y;
			rect.left = X;
			X1 = point.x;
			Y1 = point.y;
			rect.bottom = Y1;
			rect.right = X1;
			DrawFocusRect(dc.GetSafeHdc(),&rect);// O retangulo da seleção é desenhado
			VelhaCoord.top = rect.top;
			VelhaCoord.left = rect.left;
			VelhaCoord.bottom = rect.bottom;
			VelhaCoord.right = rect.right;
		}
	}

	CScrollView::OnMouseMove(nFlags, point);
}
void CPhotoEnhancerView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	Invalidate(FALSE);
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CPhotoEnhancerView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	Invalidate(FALSE);
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPhotoEnhancerView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CPhotoEnhancerDoc* pDoc = GetDocument();
	int zoom = pDoc->RecNivelZoom();
	ASSERT(GetDocument()!=NULL);
	SetScrollSizes(MM_TEXT,CSize(pDoc->RecImagem()->GetWidth()+(zoom*10),pDoc->RecImagem()->GetHeight()+(zoom*10)));
	// TODO: Add your specialized code here and/or call the base class
}

void CPhotoEnhancerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPhotoEnhancerDoc* pDoc =GetDocument(); 
	if(pDoc->RecImagem()->IsInside(point.x,point.y))
	{
	 pDoc->UpdateAllViews(NULL,WM_USER_NOVAIMAGEM);
	 X = point.x;
	 Y = point.y;
	 VelhaCoord.top = X;
	 VelhaCoord.left = Y;
	 VelhaCoord.bottom = 0;
	 VelhaCoord.right = 0;
	}
   CScrollView::OnLButtonDown(nFlags, point);
}

void CPhotoEnhancerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	HRESULT hr;
	CPhotoEnhancerDoc* pDoc =GetDocument();//recupera o ponteiro para o doc ativo 
	CClientDC dc(this);//ponteiro para o dispositivo de pintura, no caso, referente a esta classe

	if(pDoc->RecFerramenta()==1 && pDoc->RecImagem()->IsInside(point.x,point.y))
	{
	  RECT rect;
	  rect.top  = Y;//guarda todas as coordfenadas atuais
	  rect.left = X;
	  X1 = point.x;
	  Y1 = point.y;	 
	  rect.bottom = Y1;
	  rect.right = X1;
	  hr = pDoc->SetaCoordCorte(X,Y,X1,Y1);
	  if(FAILED(hr)) AfxMessageBox("Doc falhou ao recuperar coordenadas");
	}
	CScrollView::OnLButtonUp(nFlags, point);
}
