
// NotePadMFCView.cpp: CNotePadMFCView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include<wchar.h>
#include <afxdlgs.h>
#include <afxwin.h>
#include <afxcoll.h>
#include <fstream>
#include <string>
#include <locale>



// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
//#ifndef SHARED_HANDLERS
#include "NotePadMFC.h"
//#endif

#include "NotePadMFCDoc.h"
#include "NotePadMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNotePadMFCView

IMPLEMENT_DYNCREATE(CNotePadMFCView, CView)

BEGIN_MESSAGE_MAP(CNotePadMFCView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FILE_SAVE, &CNotePadMFCView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CNotePadMFCView::OnFileOpen)
END_MESSAGE_MAP()

// CNotePadMFCView 생성/소멸

CNotePadMFCView::CNotePadMFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CNotePadMFCView::~CNotePadMFCView()
{
}

BOOL CNotePadMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CNotePadMFCView 그리기

void CNotePadMFCView::OnDraw(CDC* pDC)
{
	CNotePadMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString str = theApp.text;
	HideCaret();
	
	int temp = -1;
	for (int i = 0; i < theApp.Return_Max; i++) {
		if (theApp.Return_space[i+1]>= theApp.Cursor) {
			temp = i;
			break;
		}
	}
	if (temp != -1) {
		CString substring = str.Mid(theApp.Return_space[temp], theApp.Cursor - theApp.Return_space[temp]);
		CSize size = pDC->GetTextExtent(substring);
		if(theApp.Return_space[temp +1] == theApp.Cursor && theApp.Return_space[temp + 2] == -1) SetCaretPos(CPoint(0, (temp+1) * 15));
		else SetCaretPos(CPoint(size.cx, (temp) * 15));
		
	}
	else {
		CSize size = pDC->GetTextExtent(theApp.text);
		SetCaretPos(CPoint(size.cx, 0));
	}
	
	
	ShowCaret();


	int x = 0;
	int y = 0;
		
		
		size_t num = wcslen(theApp.text);
		for (int i = 0; i < theApp.Return_Max; i++) {
			
				CString ch = str.Mid(theApp.Return_space[i], theApp.Return_space[i+1]- theApp.Return_space[i]);
				pDC->TextOut(x, y, CString(ch)); // 해당 문자를 출력
				
			
			
			y += 15;
		}
	

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


}


// CNotePadMFCView 인쇄

BOOL CNotePadMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CNotePadMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CNotePadMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CNotePadMFCView 진단

#ifdef _DEBUG
void CNotePadMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CNotePadMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNotePadMFCDoc* CNotePadMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNotePadMFCDoc)));
	return (CNotePadMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CNotePadMFCView 메시지 처리기


int CNotePadMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	CreateSolidCaret(1, 15);
	theApp.Caret.x = 0;
	theApp.Caret.y = 0;
	SetCaretPos(theApp.Caret);
	ShowCaret();
	theApp.text = new wchar_t[256];
	/*theApp.text[0] = '\0';*/


	theApp->text[theApp.Cursor++] = L' ';
	theApp->text[theApp.Cursor] = L'\0';
	theApp.Max_Count++;
	

	theApp.Return_space = new int[500];
	
	
	theApp.Return_space[theApp.Return_Max++] = 0;
	
	return 0;
}


void CNotePadMFCView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) {
	case VK_RETURN: {
		if ((theApp.Return_Max % 500) >= 490) {
			int* temp = new int[((theApp.Return_Max / 500) + 1) * 500];

			memcpy(temp, theApp.Return_space, theApp.Return_Max * sizeof(int));
			delete[] theApp.Return_space;
			theApp.Return_space = new int[((theApp.Return_Max / 500) + 1) * 500];
			memcpy(theApp.Return_space, temp, theApp.Return_Max * sizeof(int));
			delete[] temp;
		}
		if (theApp.Max_Count != theApp.Cursor) {
			int temp = -1;
			for (int i = 0; i < theApp.Return_Max; i++) {
				if (theApp.Return_space[i + 1] >= theApp.Cursor) {
					temp = i;
					break;
				}
			}
			
			for (int i = theApp.Return_Max; i >= temp+1; i--) {
				theApp.Return_space[i+1] = theApp.Return_space[i]+1;
			}

			


			for (int i = theApp.Max_Count+1; i >= theApp.Cursor; i--) {
				theApp.text[i + 1] = theApp.text[i];
			}

			theApp->text[theApp.Cursor++] = L' ';
			
			theApp.Max_Count++;
			theApp.Return_space[temp+1] = theApp.Cursor -1;
			theApp.Return_Max++;
			
			break;
		}


		size_t num = wcslen(theApp->text);
		if ((num % 256) > 254) {
			wchar_t* temp = new wchar_t[256 * ((num / 256) + 1)];
			wcsncpy(temp, theApp.text, num);
			delete[] theApp.text;
			theApp.text = temp;
		}

		

		theApp->text[theApp.Cursor++] = L' ';
		theApp->text[theApp.Cursor] = L'\0';
		theApp.Max_Count++;

		theApp.Return_space[theApp.Return_Max++] = theApp.Cursor-1;
		
		theApp.Return_space[theApp.Return_Max] = theApp.Cursor;
		
	}
		break;
	case VK_BACK:
	{

		
		if (theApp.Max_Count == 0) break;
		if (theApp.Cursor == 0) break;
		bool temp = false;
		int i_index = -1;
		for (int i = 1; i < theApp.Return_Max; i++) {
			if (theApp.Return_space[i] >= theApp.Cursor -1 && theApp.text[theApp.Cursor-1] == L' ') {
				i_index = i;
				temp = true;
				break;
			}
		}
		if (temp == true) {
			for (int i = i_index; i < theApp.Return_Max+1; i++) {
				theApp.Return_space[i] = theApp.Return_space[i + 1] -1 ;
			}
			for (int i = theApp.Cursor - 1; i < theApp.Max_Count+1; i++) {
				theApp.text[i] = theApp.text[i + 1];
			}
			theApp.Return_Max--;
			theApp.Max_Count--;
		}
		if (temp == true) break;

		if (theApp.Cursor != theApp.Max_Count) {
			for (int i = 1; i < theApp.Return_Max + 1; i++) {
				if (theApp.Return_space[i] > theApp.Cursor) {
					theApp.Return_space[i]--;
				}
			}
		}

		for (int i = theApp.Cursor; i < theApp.Max_Count+1; i++) {
			theApp->text[i-1] = theApp->text[i];
		}
		theApp.Max_Count--;
		theApp.Cursor--;
	}
		break;
	case VK_TAB:
	{
		wchar_t ch = (wchar_t)(nChar);
		size_t num = wcslen(theApp->text);
		if ((num % 256) > 254) {
			wchar_t* temp = new wchar_t[256 * ((num / 256) + 1)];
			wcsncpy(temp, theApp.text, num);
			delete[] theApp.text;
			theApp.text = temp;
		}
		theApp->text[theApp.Cursor++] = L' ';
		theApp->text[theApp.Cursor++] = L' ';
		theApp->text[theApp.Cursor++] = L' ';
		theApp->text[theApp.Cursor] = L'\0';
		theApp.Max_Count +=3;

		theApp.Return_space[theApp.Return_Max] = theApp.Cursor;

	}
	break;
	default:
		wchar_t ch = ( wchar_t) (nChar);
		size_t num = wcslen(theApp->text);
		if ((num % 256)>230) {
			wchar_t* temp = new wchar_t[256 * ((num % 256) + 1)];
			wcsncpy(temp, theApp.text, num);
			delete[] theApp.text;
			theApp.text = temp;
		}
		if (theApp.Cursor != theApp.Max_Count) {
			if (theApp.InsertFlag == true) {
				theApp->text[theApp.Cursor++] = ch;
				break;
			}
			
			int temp = -1;
			for (int i = 0; i < theApp.Return_Max; i++) {
				if (theApp.Return_space[i + 1] >= theApp.Cursor) {
					temp = i;
					break;
				}
			}
			for (int i = theApp.Max_Count; i >= theApp.Cursor; i--) {
				theApp.text[i + 1] = theApp.text[i];
			}
			
			
			theApp->text[theApp.Cursor++] = ch;
			theApp.Max_Count++;
			if (temp != -1) {
				for(int i = temp +1;i<=theApp.Return_Max;i++)
				theApp.Return_space[i] += 1;
				break;
			}
		}
		else {
			theApp->text[theApp.Cursor++] = ch;
			theApp->text[theApp.Cursor] = '\0';
			theApp.Max_Count++;
		}
		theApp.Return_space[theApp.Return_Max] = theApp.Cursor;
		break;
	}
	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CNotePadMFCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) {
	case VK_DELETE:
	{
		if (theApp.Cursor == theApp.Max_Count) break;
		theApp.Cursor++;


		bool temp = false;
		int i_index = -1;
		for (int i = 2; i < theApp.Return_Max; i++) {
			if (theApp.Return_space[i] == theApp.Cursor) {
				i_index = i;
				temp = true;
				break;
			}
		}
		if (temp == true) {
			for (int i = i_index; i < theApp.Return_Max + 1; i++) {
				theApp.Return_space[i] = theApp.Return_space[i + 1];
			}
		}
		if (temp == true) break;
		for (int i = theApp.Cursor; i < theApp.Max_Count + 1; i++) {
			theApp->text[i - 1] = theApp->text[i];
		}
		theApp.Max_Count--;
		theApp.Cursor--;
		break;
	}
	case VK_LEFT:
	{
		if (theApp.Cursor == 0) break;
		
		else {
			theApp.Cursor--;
		}
	}
	break;
	case VK_RIGHT:
	{
		if (theApp.Cursor == theApp.Max_Count) break;
		
		else {
			theApp.Cursor++;
		}
	}
	break;
	case VK_UP:
	{
		int temp = -1;
		for (int i = 0; i < theApp.Return_Max; i++) {
			if (theApp.Return_space[i + 1] >= theApp.Cursor) {
				temp = i;
				break;
			}
		}
		if (temp <= 0) break;
		int index = theApp.Cursor - theApp.Return_space[temp];
		if (index > theApp.Return_space[temp] - theApp.Return_space[temp - 1]) { 
			index = theApp.Return_space[temp]; 
			theApp.Cursor = index;
			break;
		}
		theApp.Cursor = theApp.Return_space[temp - 1] + index;
	}
	break;
	case VK_DOWN: {
		int temp = -1;
		for (int i = 0; i < theApp.Return_Max; i++) {
			if (theApp.Return_space[i + 1] >= theApp.Cursor) {
				temp = i;
				break;
			}
		}
		if (temp >= theApp.Return_Max-1) break;
		int index = theApp.Cursor - theApp.Return_space[temp];
		if (index > theApp.Return_space[temp+2] - theApp.Return_space[temp+1]) {
			index = theApp.Return_space[temp+2];
			theApp.Cursor = index;
			break;
		}
		theApp.Cursor = theApp.Return_space[temp+1] + index;
	}
	break;
	case VK_END: {
		bool flag = false;
		for (int i = 0; i < theApp.Return_Max; i++) {
			if (theApp.Return_space[i] >= theApp.Cursor) {
				theApp.Cursor = theApp.Return_space[i];
				flag = true;
				break;
			}
		}
		if (flag == false) theApp.Cursor = theApp.Max_Count;
	}
	break;
	case VK_HOME: {
		bool flag = false;
		for (int i = theApp.Return_Max; i >  0; i--) {
			if (theApp.Return_space[i] < theApp.Cursor) {
				theApp.Cursor = theApp.Return_space[i] + 1;
				flag = true;
				break;
			}
		}
		if (flag == false) theApp.Cursor = 1;
	}
	break;
	case VK_INSERT: {
		if (theApp.InsertFlag == true) {
			theApp.InsertFlag = false;
			break;
		}
		else theApp.InsertFlag = true;
	}
				  break;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CNotePadMFCView::OnFileSave()
{
	CFileDialog fileDlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), AfxGetMainWnd());

	if (fileDlg.DoModal() == IDOK) {
		CString pathName = fileDlg.GetPathName();

		std::wofstream file(pathName);
		file.imbue(std::locale(std::locale("kor")));

		if (file.is_open()) {
			file << theApp.Max_Count << std::endl;
			file << theApp.Return_Max << std::endl;
			for (int i = 0; i < theApp.Return_Max+1; i++) {
				file << theApp.Return_space[i] << std::endl;
			}
			file << theApp.text << std::endl;
			file.close();
			AfxMessageBox(_T("저장됐습니다."), MB_OK | MB_ICONINFORMATION);
		}
		else {
			AfxMessageBox(_T("저장 실패"), MB_OK | MB_ICONERROR);
		}
	}
}


void CNotePadMFCView::OnFileOpen()
{
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, OFN_HIDEREADONLY, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), AfxGetMainWnd());
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();
		std::wifstream file(pathName);
		file.imbue(std::locale(std::locale("kor")));
		if (file.is_open())
		{
			delete[] theApp.text;
			delete[] theApp.Return_space;
			std::wstring line;
			std::getline(file, line);
			theApp.Max_Count = _wtoi(line.c_str());
			theApp.text = new wchar_t[(((theApp.Max_Count) / 256) + 1) * 256];
			std::getline(file, line);
			theApp.Return_Max = _wtoi(line.c_str());
			theApp.Return_space = new int[500];
			for (int i = 0; i < theApp.Return_Max + 1; i++)
			{
				std::getline(file, line);
				theApp.Return_space[i] = _wtoi(line.c_str());
			}
			std::getline(file, line);
			wcscpy(theApp.text, line.c_str());
			file.close();
			AfxMessageBox(_T("열림"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox(_T("열기 실패"), MB_OK | MB_ICONERROR);
		}
	}
	Invalidate();
}