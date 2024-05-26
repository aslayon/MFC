
// PaintView.h: CPaintView 클래스의 인터페이스
//

#pragma once

struct vectLy
{
	short Mode;
	CPoint st;
	CPoint ed;
};

class CPaintView : public CView
{
protected: // serialization에서만 만들어집니다.
	CPaintView() noexcept;
	DECLARE_DYNCREATE(CPaintView)

// 특성입니다.
public:
	CPaintDoc* GetDocument() const;
	int iMode = -1;
	POINT stPos;
	POINT mvPos;
	BOOL isDrawing = FALSE;
	int R = 0;
	int B = 0;
	int G = 0;
	int thickness = 5;
	CDC memDC;
	CBitmap memBitmap;
	CBitmap* pOldMemBitmap;
	struct vectLy* SaveByVector;
	LONGLONG Count = 0;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual POINT draw(CDC* pDC);
// 구현입니다.
public:
	virtual ~CPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPen();
	afx_msg void OnEraser();
	
	afx_msg void OnRect();
	afx_msg void OnCircle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnSaveAsVector();
	afx_msg void OnOpenAsVec();
};

#ifndef _DEBUG  // PaintView.cpp의 디버그 버전
inline CPaintDoc* CPaintView::GetDocument() const
   { return reinterpret_cast<CPaintDoc*>(m_pDocument); }
#endif

