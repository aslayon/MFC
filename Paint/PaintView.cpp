
// PaintView.cpp: CPaintView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Paint.h"
#endif

#include "PaintDoc.h"
#include "PaintView.h"
#include <afxdlgs.h>
#include <afxwin.h>
#include <afxcoll.h>
#include <afxext.h>
#include <fstream>
#include <string>
#include <locale>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintView

IMPLEMENT_DYNCREATE(CPaintView, CView)

BEGIN_MESSAGE_MAP(CPaintView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_Pen, &CPaintView::OnPen)
	ON_COMMAND(ID_Eraser, &CPaintView::OnEraser)
	
	ON_COMMAND(ID_Rect, &CPaintView::OnRect)
	ON_COMMAND(ID_Circle, &CPaintView::OnCircle)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_SAVE_AS, &CPaintView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_NEW, &CPaintView::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CPaintView::OnFileOpen)
	ON_COMMAND(ID_SAVE_AS_VECTOR, &CPaintView::OnSaveAsVector)
	ON_COMMAND(ID_OPEN_AS_VEC, &CPaintView::OnOpenAsVec)
END_MESSAGE_MAP()

// CPaintView 생성/소멸

CPaintView::CPaintView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPaintView::~CPaintView()
{
}

BOOL CPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPaintView 그리기

void CPaintView::OnDraw(CDC* pDC)
{
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (iMode == 1 && isDrawing) {
		draw(pDC);
	}
	else if (iMode == 2) {
		draw(pDC);
	}
	else if (iMode == 3) {
		CRect rect;
		GetClientRect(&rect);
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		draw(pDC);
		
	}
	else if (iMode == 4) {
		CRect rect;
		GetClientRect(&rect);
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		draw(pDC);

	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPaintView 인쇄

BOOL CPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPaintView 진단

#ifdef _DEBUG
void CPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintDoc* CPaintView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintDoc)));
	return (CPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaintView 메시지 처리기


void CPaintView::OnPen()
{
	
	iMode = 1;
	Invalidate(false);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CPaintView::OnEraser()
{

	iMode = 2;
	Invalidate(false);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


 // 해당 문자를 출력



void CPaintView::OnRect()
{
	iMode = 3;
	Invalidate(false);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CPaintView::OnCircle()
{
	iMode = 4;
	Invalidate(false);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	stPos = point;
	isDrawing = TRUE;
	if (iMode >= 3) {
		CPaintDC dc(this);
		CDC* pDC = &dc;

		CRect rect;
		GetClientRect(&rect);


		memDC.CreateCompatibleDC(pDC);
		memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		pOldMemBitmap = (CBitmap*)memDC.SelectObject(&memBitmap);

		// memDC에 현재 화면 복사
		memDC.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);

		stPos = point;
		isDrawing = TRUE;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (isDrawing == TRUE) {
		mvPos = point;
		Invalidate(false);
	}
	CView::OnMouseMove(nFlags, point);
}

POINT CPaintView::draw(CDC* pDC) {
	CPen* pOldPen;
	if (iMode == 1) {
		CPen newPen(PS_SOLID, thickness, RGB(R, G, B));
		pOldPen = pDC->SelectObject(&newPen);

		pDC->MoveTo(stPos);
		pDC->LineTo(mvPos);

		SaveByVector[Count].Mode = 1;
		SaveByVector[Count].st = stPos;
		SaveByVector[Count].ed = mvPos;
		Count++;
		pDC->SelectObject(pOldPen);
		stPos = mvPos;
	}
	if (iMode == 2) {
		CPen newPen(PS_SOLID, thickness, RGB(255, 255, 255));
		pOldPen = pDC->SelectObject(&newPen);

		pDC->MoveTo(stPos);
		pDC->LineTo(mvPos);


		SaveByVector[Count].Mode = 2;
		SaveByVector[Count].st = stPos;
		SaveByVector[Count].ed = mvPos;
		Count++;
		pDC->SelectObject(pOldPen);



		stPos = mvPos;
	}
	if (iMode == 3) {
		CRect rect;
		GetClientRect(&rect);
		
		CPen newPen(PS_SOLID, thickness, RGB(R, G, B));
		pOldPen = pDC->SelectObject(&newPen);

		CBrush* pOldBrush = pDC->SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));

		CRect RectToDraw = CRect(stPos, mvPos); 
		pDC->Rectangle(RectToDraw);
		
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}
	if (iMode == 4) {
		CRect rect;
		GetClientRect(&rect);

		CPen newPen(PS_SOLID, thickness, RGB(R, G, B));
		pOldPen = pDC->SelectObject(&newPen);

		CBrush* pOldBrush = pDC->SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));

		CRect RectToDraw = CRect(stPos, mvPos);
		pDC->Ellipse(RectToDraw);

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}

	

	return stPos;
}



void CPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isDrawing = FALSE;
	
	if (iMode >= 3) {
		memDC.SelectObject(pOldMemBitmap);
		memBitmap.DeleteObject();
		memDC.DeleteDC();

		SaveByVector[Count].Mode = iMode;
		SaveByVector[Count].st.x = stPos.x;
		SaveByVector[Count].st.y = stPos.y;
		SaveByVector[Count].ed.x = point.x;
		SaveByVector[Count].ed.y = point.y;
		Count++;
	}
	stPos.x = -5;
	stPos.y = -5;
	mvPos.x = -5;
	mvPos.y = -5;
	CView::OnLButtonUp(nFlags, point);
	
}


int CPaintView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	SaveByVector = new struct vectLy[100000];
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void CPaintView::OnFileSaveAs()
{
	{
		CFileDialog dlg(FALSE, _T("bmp"), NULL, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
			_T("Bitmap File (*.bmp)|*.bmp|JPEG File (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG File (*.png)|*.png||"), this);
		if (dlg.DoModal() != IDOK)
		{
			return;
		}

		CString filePath = dlg.GetPathName();
		CClientDC deviceContext(this);

		CDC memDC;
		memDC.CreateCompatibleDC(&deviceContext);

		CRect windowRect;
		CWnd::GetClientRect(&windowRect);

		CBitmap windowBitmap;
		windowBitmap.CreateCompatibleBitmap(&deviceContext, windowRect.Width(), windowRect.Height());

		CBitmap* pOldBitmap = memDC.SelectObject(&windowBitmap);
		memDC.BitBlt(0, 0, windowRect.Width(), windowRect.Height(), &deviceContext, 0, 0, SRCCOPY);

		CImage currentImage;
		currentImage.Attach((HBITMAP)windowBitmap.Detach());
		currentImage.Save(filePath);

		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();
	}
}


void CPaintView::OnFileNew()
{
	Count = 0;
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CPaintView::OnFileOpen()
{
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("Bitmap File (*.bmp)|*.bmp|JPEG File (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG File (*.png)|*.png||"), this);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	CString filePath = dlg.GetPathName();
	CImage newImage;
	newImage.Load(filePath);

	CRect windowRect;
	CWnd::GetClientRect(&windowRect);

	CClientDC deviceContext(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&deviceContext);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&deviceContext, windowRect.Width(), windowRect.Height());

	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	newImage.Draw(memDC.m_hDC, 0, 0, windowRect.Width(), windowRect.Height());
	deviceContext.StretchBlt(0, 0, windowRect.Width(), windowRect.Height(), &memDC, 0, 0, windowRect.Width(), windowRect.Height(), SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
}


void CPaintView::OnSaveAsVector()
{
	CFileDialog fileDlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), AfxGetMainWnd());

	if (fileDlg.DoModal() == IDOK) {
		CString pathName = fileDlg.GetPathName();

		std::wofstream file(pathName);
		file.imbue(std::locale(std::locale("kor")));

		if (file.is_open()) {
			file << Count << std::endl;
			
			for (int i = 0; i < Count; i++) {
				
				file << SaveByVector[i].Mode << std::endl;
				file << SaveByVector[i].st.x << std::endl;
				file << SaveByVector[i].st.y << std::endl;
				file << SaveByVector[i].ed.x << std::endl;
				file << SaveByVector[i].ed.y << std::endl;
			}
			
			file.close();
			//AfxMessageBox(_T("저장됐습니다."), MB_OK | MB_ICONINFORMATION);
		}
		else {
			AfxMessageBox(_T("저장 실패"), MB_OK | MB_ICONERROR);
		}
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CPaintView::OnOpenAsVec()
{
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, OFN_HIDEREADONLY, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), AfxGetMainWnd());
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();
		std::wifstream file(pathName);
		file.imbue(std::locale(std::locale("kor")));
		if (file.is_open())
		{

			std::wstring line;
			std::getline(file, line);
			line.erase(std::remove(line.begin(), line.end(), ','), line.end());
			Count = std::stoll(line.c_str());

			

			for (int i = 0; i < Count; i++)
			{
				std::getline(file, line);
				line.erase(std::remove(line.begin(), line.end(), ','), line.end());
				SaveByVector[i].Mode = _wtoi(line.c_str());
				std::getline(file, line);
				line.erase(std::remove(line.begin(), line.end(), ','), line.end());
				SaveByVector[i].st.x = _wtoi(line.c_str());
				std::getline(file, line);
				line.erase(std::remove(line.begin(), line.end(), ','), line.end());
				SaveByVector[i].st.y = _wtoi(line.c_str());
				std::getline(file, line);
				line.erase(std::remove(line.begin(), line.end(), ','), line.end());
				SaveByVector[i].ed.x = _wtoi(line.c_str());
				std::getline(file, line);
				line.erase(std::remove(line.begin(), line.end(), ','), line.end());
				SaveByVector[i].ed.y = _wtoi(line.c_str());
			}
			for (int i = 0; i < Count; i++) {
				CPen* pOldPen;
				CDC* pDC = GetDC();
				if (SaveByVector[i].Mode == 1) {
					CPen newPen(PS_SOLID, thickness, RGB(R, G, B));
					pOldPen = pDC->SelectObject(&newPen);

					pDC->MoveTo(SaveByVector[i].st);
					pDC->LineTo(SaveByVector[i].ed);

					
					pDC->SelectObject(pOldPen);
					
				}
				if (SaveByVector[i].Mode == 2) {
					CPen newPen(PS_SOLID, thickness, RGB(255, 255, 255));
					pOldPen = pDC->SelectObject(&newPen);

					pDC->MoveTo(SaveByVector[i].st);
					pDC->LineTo(SaveByVector[i].ed);


					
					pDC->SelectObject(pOldPen);



					
				}
				if (SaveByVector[i].Mode == 3) {
					CRect rect;
					GetClientRect(&rect);

					CPen newPen(PS_SOLID, thickness, RGB(R, G, B));
					pOldPen = pDC->SelectObject(&newPen);

					CBrush* pOldBrush = pDC->SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));

					CRect RectToDraw = CRect(SaveByVector[i].st, SaveByVector[i].ed);
					pDC->Rectangle(RectToDraw);

					pDC->SelectObject(pOldPen);
					pDC->SelectObject(pOldBrush);
				}
				if (SaveByVector[i].Mode == 4) {
					CRect rect;
					GetClientRect(&rect);

					CPen newPen(PS_SOLID, thickness, RGB(R, G, B));
					pOldPen = pDC->SelectObject(&newPen);

					CBrush* pOldBrush = pDC->SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));

					CRect RectToDraw = CRect(SaveByVector[i].st, SaveByVector[i].ed);
					pDC->Ellipse(RectToDraw);

					pDC->SelectObject(pOldPen);
					pDC->SelectObject(pOldBrush);
				}


			}
			file.close();
			AfxMessageBox(_T("열림"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox(_T("열기 실패"), MB_OK | MB_ICONERROR);
		}
	}
	
}