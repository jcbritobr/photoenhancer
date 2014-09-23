// HistoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoEnhancer.h"
#include "HistoDlg.h"
#include ".\histodlg.h"
#include "PhotoEnhancerDoc.h"
#include "MainFrm.h"


// CHistoDlg dialog

IMPLEMENT_DYNAMIC(CHistoDlg, CDialog)
CHistoDlg::CHistoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistoDlg::IDD, pParent)
{
	m_initok = false;
}

CHistoDlg::~CHistoDlg()
{
}

void CHistoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECKRED, m_cred);
	DDX_Control(pDX, IDC_CHECKGREEN, m_cgreen);
	DDX_Control(pDX, IDC_CHECKBLUE, m_cblue);
	DDX_Control(pDX, IDC_CHECKCINZA, m_ccinza);
}


BEGIN_MESSAGE_MAP(CHistoDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECKRED, OnBnClickedCheckred)
	ON_BN_CLICKED(IDC_CHECKGREEN, OnBnClickedCheckgreen)
	ON_BN_CLICKED(IDC_CHECKBLUE, OnBnClickedCheckblue)
	ON_BN_CLICKED(IDC_CHECKCINZA, OnBnClickedCheckcinza)
END_MESSAGE_MAP()


// CHistoDlg message handlers

BOOL CHistoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ren=m_gen=m_ben=m_grayen=1;
	if(m_ren==1)m_cred.SetCheck(1);
	if(m_gen==1)m_cgreen.SetCheck(1);
	if(m_ben==1)m_cblue.SetCheck(1);
	if(m_grayen==1)m_ccinza.SetCheck(1);



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CHistoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CPhotoEnhancerDoc* pDoc = (CPhotoEnhancerDoc*)
		((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();


	RECT r;
	GetClientRect(&r);

	CPen gridPen(PS_DOT,1,::GetSysColor(COLOR_APPWORKSPACE));
	CPen* pOldPen = dc.SelectObject(&gridPen);
	for (int gx=9+32;gx<265;gx+=32){
		dc.MoveTo(gx,40);
		dc.LineTo(gx,r.bottom - 6);
	}
	for (int gy=0;gy<(r.bottom - 40);gy+=((r.bottom - 40)/10)){
		dc.MoveTo(8,r.bottom - 9 - gy);
		dc.LineTo(268,r.bottom - 9 - gy);
	}
	dc.SelectObject(pOldPen);

	CPen axisPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
	pOldPen = dc.SelectObject(&axisPen);
	dc.MoveTo(9, 38);
	dc.LineTo(9, r.bottom - 9);
	dc.LineTo(266, r.bottom - 9);
	dc.LineTo(266, 38);
	dc.SelectObject(pOldPen);

	if (pDoc && pDoc->RecImagem()) {
		pDoc->m_hmax=pDoc->RecImagem()->Histogram(pDoc->m_hr,pDoc->m_hg,pDoc->m_hb,pDoc->m_hgray);
		if (pDoc->m_hmax){
			int ybase = r.bottom-10;
			if (TRUE){
				float yratio = (r.bottom - r.top - 50)/(float)log10((float)(pDoc->m_hmax+1));
				if (m_ren){
					CPen redPen(PS_SOLID, 1, RGB(222, 0, 0));
					pOldPen = dc.SelectObject(&redPen);
					dc.MoveTo(10, (int)(ybase-log10((float)(1+pDoc->m_hr[0]))*yratio));
					for (int x=1; x<256; x++)
						dc.LineTo(x+10, (int)(ybase-log10((float)(1+pDoc->m_hr[x]))*yratio));
				}
				if (m_gen){
					CPen greenPen(PS_SOLID, 1, RGB(0, 222, 0));
					pOldPen = dc.SelectObject(&greenPen);
					dc.MoveTo(10, (int)(ybase-log10((float)(1+pDoc->m_hg[0]))*yratio));
					for (int x=1; x<256; x++)
						dc.LineTo(x+10, (int)(ybase-log10((float)(1+pDoc->m_hg[x]))*yratio));
				}
				if (m_ben){
					CPen bluePen(PS_SOLID, 1, RGB(0, 0, 222));
					pOldPen = dc.SelectObject(&bluePen);
					dc.MoveTo(10, (int)(ybase-log10((float)(1+pDoc->m_hb[0]))*yratio));
					for (int x=1; x<256; x++)
						dc.LineTo(x+10, (int)(ybase-log10((float)(1+pDoc->m_hb[x]))*yratio));
				}
				if (m_grayen){
					CPen grayPen(PS_SOLID, 1, RGB(64, 64, 64));
					pOldPen = dc.SelectObject(&grayPen);
					dc.MoveTo(10, (int)(ybase-log10((float)(1+pDoc->m_hgray[0]))*yratio));
					for (int x=1; x<256; x++)
						dc.LineTo(x+10, (int)(ybase-log10((float)(1+pDoc->m_hgray[x]))*yratio));
				}
				dc.SelectObject(pOldPen);
			} else {
				float yratio = (r.bottom - r.top - 50)/(float)pDoc->m_hmax;
				if (m_ren){
					CPen redPen(PS_SOLID, 1, RGB(222, 0, 0));
					pOldPen = dc.SelectObject(&redPen);
					dc.MoveTo(10, (int)(ybase-pDoc->m_hr[0]*yratio));
					for (int x=1; x<256; x++)
						dc.LineTo(x+10, (int)(ybase-pDoc->m_hr[x]*yratio));
				}
				if (m_gen){
					CPen greenPen(PS_SOLID, 1, RGB(0, 222, 0));
					pOldPen = dc.SelectObject(&greenPen);
					dc.MoveTo(10, (int)(ybase-pDoc->m_hg[0]*yratio));
					for (int x=1; x<256; x++)
						dc.LineTo(x+10, (int)(ybase-pDoc->m_hg[x]*yratio));
				}
				if (m_ben){
					CPen bluePen(PS_SOLID, 1, RGB(0, 0, 222));
					pOldPen = dc.SelectObject(&bluePen);
					dc.MoveTo(10, (int)(ybase-pDoc->m_hb[0]*yratio));
					for (int x=1; x<256; x++)
						dc.LineTo(x+10, (int)(ybase-pDoc->m_hb[x]*yratio));
				}
				if (m_grayen){
					CPen grayPen(PS_SOLID, 1, RGB(64, 64, 64));
					pOldPen = dc.SelectObject(&grayPen);
					dc.MoveTo(10, (int)(ybase-pDoc->m_hgray[0]*yratio));
					for (int x=1; x<256; x++)
						dc.LineTo(x+10, (int)(ybase-pDoc->m_hgray[x]*yratio));
				}
				dc.SelectObject(pOldPen);
			}
		}
		else
		{
			pDoc->m_hmax=pDoc->RecImagem()->Histogram(pDoc->m_hr,pDoc->m_hg,pDoc->m_hb,pDoc->m_hgray);
			if (pDoc->m_hmax) Invalidate();
		}
	}

}	





void CHistoDlg::OnBnClickedCheckred()
{
	if(m_cred.GetCheck()==1)m_ren=1;
	else m_ren=0;
	Invalidate();
}

void CHistoDlg::OnBnClickedCheckgreen()
{
	if(m_cgreen.GetCheck()==1)m_gen=1;
	else m_gen=0;
	Invalidate();
}

void CHistoDlg::OnBnClickedCheckblue()
{
	if(m_cblue.GetCheck()==1)m_ben=1;
	else m_ben=0;
	Invalidate();
}

void CHistoDlg::OnBnClickedCheckcinza()
{
	if(m_ccinza.GetCheck()==1)m_grayen=1;
	else m_grayen=0;
	Invalidate();
}
