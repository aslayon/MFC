
// NotePadMFCView.h: CNotePadMFCView 클래스의 인터페이스
//

#pragma once



class CNotePadMFCView : public CView
{
protected: // serialization에서만 만들어집니다.
	CNotePadMFCView() noexcept;
	DECLARE_DYNCREATE(CNotePadMFCView)

// 특성입니다.
public:
	CNotePadMFCDoc* GetDocument() const;

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

// 구현입니다.
public:
	virtual ~CNotePadMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();

private:
	CScrollBar m_hScrollBar;
	CScrollBar m_vScrollBar;
public:

	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // NotePadMFCView.cpp의 디버그 버전
inline CNotePadMFCDoc* CNotePadMFCView::GetDocument() const
   { return reinterpret_cast<CNotePadMFCDoc*>(m_pDocument); }
#endif

