
// ChildView.cpp : CChildView Ŭ������ ����
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
		AfxMessageBox(_T("xml �б⿡ �����߽��ϴ�."));
	else
		AfxMessageBox(_T("�����߽��ϴ�."));

	xml.FindElem(_T("rss"));		// rss ������ ã�´�.
	xml.IntoElem();					// rss ���� ���� Ȯ��
	xml.FindElem(_T("channel")); // channel ������ ã�´�.
	xml.IntoElem();              // rss->channel ���� ���� Ȯ��
	xml.FindElem(_T("title"));
	str[0] = xml.GetData();
	xml.FindElem(_T("description"));
	str[1] = xml.GetData();
	xml.FindElem(_T("generator"));
	str[2] = xml.GetData();
	xml.FindElem(_T("item"));      // item ������ ã�´�.
	xml.IntoElem();               // rss -> channel -> item ���� ���� Ȯ��
	xml.FindElem(_T("category"));
	str[3] = xml.GetData();
	xml.FindElem(_T("title"));
	str[4] = xml.GetData();
	xml.FindElem(_T("description")); // description ������ ã�´�.
	xml.IntoElem();               // rss -> channel ->item -> description ���� ���� Ȯ��
	xml.FindElem(_T("header"));   //header �� ã�´�.
	xml.IntoElem();             // rss -> channel ->item -> header ���� ����
	xml.FindElem(_T("title"));
	str[5] = xml.GetData();
	xml.FindElem(_T("tm"));
	str[6] = xml.GetData();
	xml.OutOfElem();      // �Ѵܰ� ���ؿ��� ����
	xml.FindElem(_T("body"));   // body �� ã�´�.
	xml.IntoElem();            // rss-> channel ->item -> body ���� ����
	xml.FindElem(_T("location")); // location�� ã�´�.
	xml.IntoElem();              // rss->channel ->item -> body -> location ���� ����
	xml.FindElem(_T("province"));
	str[7] = xml.GetData();
	xml.FindElem(_T("city"));
	str[8] = xml.GetData();
}

//------------------------------------------------------������
void CChildView::TestCMarkupSave()
{
	CMarkup xml;

	xml.AddElem(_T("Machine"));             // ���� Level ���ؿ��� Element�� �߰��մϴ�.
	xml.AddChildElem(_T("MachineSize"));    // ���� Level ���� Element�� Child�� �߰��մϴ�.

	xml.IntoElem();                         // �Ѵܰ� ������ ���ϴ�.
	xml.AddAttrib(_T("XSIZE"), _T("200"));   // ���� Element�� Attribute �� �߰��մϴ�.
	xml.AddAttrib(_T("YSIZE"), _T("200"));   //IntoElem �� AddAttrib �� AddChildAttrib �� �Ȱ��� ȿ���� ���ϴ�.
	xml.OutOfElem();                        // ���� Level����(Machine) ���ɴϴ�.

	xml.AddElem(_T("X"));
	xml.AddChildElem(_T("COL"));
	xml.IntoElem();
	xml.AddAttrib(_T("Count"), _T("3"));
	xml.AddChildElem(_T("Data"), _T("4")); // IntoElem �� AddElem �� �Ȱ��� ȿ���� ���ϴ�.
	xml.AddChildElem(_T("Data"), _T("7"));
	xml.AddChildElem(_T("Data"), _T("2"));
	xml.OutOfElem();

	CString strXML = xml.GetDoc();	//GetDoc() : xml �������� ��� ���ϳ��� �о���δ�.
	AfxMessageBox(strXML);

	xml.Save(_T("TestXml.XML"));
}
void CChildView::TestCMarkupLoad()
{
	CMarkup xml;
	CString strFileName1 = _T("TestXml.XML");

	if (xml.Load(strFileName1) == true)
		AfxMessageBox(_T("xml �б⿡ �����߽��ϴ�."));
	else
		AfxMessageBox(_T("�����߽��ϴ�."));

	xml.FindElem(_T("Machine"));  //Element �� ã���ϴ�.
	xml.IntoElem();
	xml.FindElem(_T("MachineSize"));
	CString strSizeX = xml.GetAttrib(_T("XSIZE")); // ���� Element���� Attribute �� ���� �����ɴϴ�.
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
//------------------------------------------------------������

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView �޽��� ó����

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
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	//TestCMarkupToLoad();
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.weather.go.kr/weather/forecast/mid-term-rss3.jsp?stnId=108"), _T("Weather.XML"), 0, NULL);
	CString str[10];		//�����⺻����	
	CString Seoulstr[6];	//����������

	CString strFileName = _T("Weather.XML");

	if (xml.Load(strFileName) == true)
		AfxMessageBox(_T("xml �б⿡ �����߽��ϴ�."));
	else
		AfxMessageBox(_T("�����߽��ϴ�."));

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
	
	//------------------------------------��������
	xml.FindElem(_T("city"));
	Seoulstr[0] = xml.GetData();
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmEf"));
	Seoulstr[1] = xml.GetData();	//2���� �ϱ⿹�� ��¥ �ð�
	xml.FindElem(_T("wf"));
	Seoulstr[2] = xml.GetData();	//2���� �ϱ⿹�� �ϴ� ����
	xml.FindElem(_T("tmn"));
	Seoulstr[3] = xml.GetData();	//2���� �ϱ⿹�� ���� �µ�
	xml.FindElem(_T("tmx"));
	Seoulstr[4] = xml.GetData();	//2���� �ϱ⿹�� �ְ� �µ�
	xml.FindElem(_T("reliability"));
	Seoulstr[5] = xml.GetData();	//2���� �ϱ⿹�� �ŷڵ�

	//--------------------------------------------------�⺻����
	for (int i = 0; i < 10; i++)
	{
		dc.TextOutW(100, 100 + i * 30, str[i]);
	}
	//----------------------------------------------------------


	//----------------------------------------------���� 2�� �� ����
	for (int i = 0; i < 5; i++)
	{
		dc.TextOutW(1000, 100 + i * 30, Seoulstr[i]);
	}
	//---------------------------------------------------------------




	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}

