
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include "Markup.h"
#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


void CChildView::TestCMarkupToLoad()
{

	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.weather.go.kr/weather/forecast/mid-term-rss3.jsp?stnId=108"), _T("Weather.XML"), 0, NULL);
	CString str[10];
	CString strFileName = _T("Weather.XML");

	if (xml.Load(strFileName) == true)
		AfxMessageBox(_T("xml 읽기에 성공했습니다."));
	else
		AfxMessageBox(_T("실패했습니다."));

	xml.FindElem(_T("rss"));		// rss 정보를 찾는다.
	xml.IntoElem();					// rss 안의 내용 확인
	xml.FindElem(_T("channel")); // channel 정보를 찾는다.
	xml.IntoElem();              // rss->channel 안의 내용 확인
	xml.FindElem(_T("title"));
	str[0] = xml.GetData();
	xml.FindElem(_T("description"));
	str[1] = xml.GetData();
	xml.FindElem(_T("generator"));
	str[2] = xml.GetData();
	xml.FindElem(_T("item"));      // item 정보를 찾는다.
	xml.IntoElem();               // rss -> channel -> item 안의 내용 확인
	xml.FindElem(_T("category"));
	str[3] = xml.GetData();
	xml.FindElem(_T("title"));
	str[4] = xml.GetData();
	xml.FindElem(_T("description")); // description 정보를 찾는다.
	xml.IntoElem();               // rss -> channel ->item -> description 안의 내용 확인
	xml.FindElem(_T("header"));   //header 를 찾는다.
	xml.IntoElem();             // rss -> channel ->item -> header 안의 내용
	xml.FindElem(_T("title"));
	str[5] = xml.GetData();
	xml.FindElem(_T("tm"));
	str[6] = xml.GetData();
	xml.OutOfElem();      // 한단계 수준에서 나옴
	xml.FindElem(_T("body"));   // body 를 찾는다.
	xml.IntoElem();            // rss-> channel ->item -> body 안의 내용
	xml.FindElem(_T("location")); // location을 찾는다.
	xml.IntoElem();              // rss->channel ->item -> body -> location 안의 내용
	xml.FindElem(_T("province"));
	str[7] = xml.GetData();
	xml.FindElem(_T("city"));
	str[8] = xml.GetData();
}

//------------------------------------------------------연습용
void CChildView::TestCMarkupSave()
{
	CMarkup xml;

	xml.AddElem(_T("Machine"));             // 현재 Level 수준에서 Element를 추가합니다.
	xml.AddChildElem(_T("MachineSize"));    // 현재 Level 에서 Element를 Child로 추가합니다.

	xml.IntoElem();                         // 한단계 안으로 들어갑니다.
	xml.AddAttrib(_T("XSIZE"), _T("200"));   // 현재 Element에 Attribute 를 추가합니다.
	xml.AddAttrib(_T("YSIZE"), _T("200"));   //IntoElem 후 AddAttrib 는 AddChildAttrib 와 똑같은 효과를 냅니다.
	xml.OutOfElem();                        // 현재 Level에서(Machine) 나옵니다.

	xml.AddElem(_T("X"));
	xml.AddChildElem(_T("COL"));
	xml.IntoElem();
	xml.AddAttrib(_T("Count"), _T("3"));
	xml.AddChildElem(_T("Data"), _T("4")); // IntoElem 후 AddElem 와 똑같은 효과를 냅니다.
	xml.AddChildElem(_T("Data"), _T("7"));
	xml.AddChildElem(_T("Data"), _T("2"));
	xml.OutOfElem();

	CString strXML = xml.GetDoc();	//GetDoc() : xml 형식으로 모든 파일내용 읽어들인다.
	AfxMessageBox(strXML);

	xml.Save(_T("TestXml.XML"));
}
void CChildView::TestCMarkupLoad()
{
	CMarkup xml;
	CString strFileName1 = _T("TestXml.XML");

	if (xml.Load(strFileName1) == true)
		AfxMessageBox(_T("xml 읽기에 성공했습니다."));
	else
		AfxMessageBox(_T("실패했습니다."));

	xml.FindElem(_T("Machine"));  //Element 를 찾습니다.
	xml.IntoElem();
	xml.FindElem(_T("MachineSize"));
	CString strSizeX = xml.GetAttrib(_T("XSIZE")); // 현재 Element에서 Attribute 의 값을 가져옵니다.
	CString strSizeY = xml.GetAttrib(_T("YSIZE"));

	CString strMsg;
	strMsg.Format(_T("SIZEX : %s, SIZEY: %s"), strSizeX, strSizeY);
	AfxMessageBox(strMsg);

	xml.OutOfElem();
	xml.FindElem(_T("X"));
	xml.IntoElem();
	xml.FindElem(_T("COL"	));
	int nCountX = _wtoi(xml.GetAttrib(_T("Count")));
	CString strCountX = xml.GetAttrib(_T("Count"));

	strMsg.Format(_T("nCOuntX : %d, strCountX: %s"), nCountX, strCountX);
	AfxMessageBox(strMsg);

	xml.IntoElem();
	while (xml.FindElem(_T("Data")))
	{
		AfxMessageBox(xml.GetData());
	}
	xml.OutOfElem();
	xml.OutOfElem();

}
//------------------------------------------------------연습용

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	//TestCMarkupToLoad();
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.weather.go.kr/weather/forecast/mid-term-rss3.jsp?stnId=108"), _T("Weather.XML"), 0, NULL);
	CString str[10];		//전국기본정보	
	CString Seoulstr[6];	//서울기상정보

	CString strFileName = _T("Weather.XML");

	if (xml.Load(strFileName) == true)
		AfxMessageBox(_T("xml 읽기에 성공했습니다."));
	else
		AfxMessageBox(_T("실패했습니다."));

	xml.FindElem(_T("rss"));		
	xml.IntoElem();					
	xml.FindElem(_T("channel")); 
	xml.IntoElem();
	xml.FindElem(_T("title"));
	str[0] = xml.GetData();
	xml.FindElem(_T("description"));
	str[1] = xml.GetData();
	xml.FindElem(_T("generator"));
	str[2] = xml.GetData();
	xml.FindElem(_T("item"));      
	xml.IntoElem();              
	xml.FindElem(_T("category"));
	str[3] = xml.GetData();
	xml.FindElem(_T("title"));
	str[4] = xml.GetData();
	xml.FindElem(_T("description")); 
	xml.IntoElem();               
	xml.FindElem(_T("header"));   
	xml.IntoElem();					
	xml.FindElem(_T("title"));
	str[5] = xml.GetData();
	xml.FindElem(_T("tm"));
	str[6] = xml.GetData();
	xml.FindElem(_T("wf"));		
	str[7] = xml.GetData();
	xml.OutOfElem();			
	xml.FindElem(_T("body"));   
	xml.IntoElem();            
	xml.FindElem(_T("location")); 
	xml.IntoElem();             
	xml.FindElem(_T("province"));
	str[8] = xml.GetData();
	
	//------------------------------------서울정보
	xml.FindElem(_T("city"));
	Seoulstr[0] = xml.GetData();
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmEf"));
	Seoulstr[1] = xml.GetData();	//2일후 일기예보 날짜 시간
	xml.FindElem(_T("wf"));
	Seoulstr[2] = xml.GetData();	//2일후 일기예보 하늘 상태
	xml.FindElem(_T("tmn"));
	Seoulstr[3] = xml.GetData();	//2일후 일기예보 최저 온도
	xml.FindElem(_T("tmx"));
	Seoulstr[4] = xml.GetData();	//2일후 일기예보 최고 온도
	xml.FindElem(_T("reliability"));
	Seoulstr[5] = xml.GetData();	//2일후 일기예보 신뢰도

	//--------------------------------------------------기본정보
	for (int i = 0; i < 10; i++)
	{
		dc.TextOutW(100, 100 + i * 30, str[i]);
	}
	//----------------------------------------------------------


	//----------------------------------------------서울 2일 후 정보
	for (int i = 0; i < 5; i++)
	{
		dc.TextOutW(1000, 100 + i * 30, Seoulstr[i]);
	}
	//---------------------------------------------------------------




	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

