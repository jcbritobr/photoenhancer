// PhotoEnhancerView.h : interface of the CPhotoEnhancerView class
//


#pragma once


class CPhotoEnhancerView : public CScrollView
{
protected: // create from serialization only
	CPhotoEnhancerView();
	DECLARE_DYNCREATE(CPhotoEnhancerView)

// Attributes
public:
	CPhotoEnhancerDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPhotoEnhancerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int      X,Y;
	int      X1,Y1;
	RECT VelhaCoord;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in PhotoEnhancerView.cpp
inline CPhotoEnhancerDoc* CPhotoEnhancerView::GetDocument() const
   { return reinterpret_cast<CPhotoEnhancerDoc*>(m_pDocument); }
#endif

