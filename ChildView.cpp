// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include "Markup.h"			//CMarkup xml parser �̿�
#include <Urlmon.h>			//RSS ���� �޾ƿ���
#pragma comment(lib, "urlmon.lib")

//----------------------------------------------------------
#define STR_SWITCH(x) {CString switchval(x); if(false){;}
#define CASE(y) else if(switchval == y) {
#define DEFAULT else if(true) {
#define BREAK }
#define END_SWITCH }
//--------------------------------��������� switch�� ��� -


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CButton m_pushButton1;		//���ü��� ��ư ��Ʈ�ѷ� ����
CButton m_pushButton2;		//�ְ��� ��ư ��Ʈ�ѷ� ����
CButton m_pushButton3;		//������� ��ư ��Ʈ�ѷ� ����
CButton m_pushButton4;		//�����ϴ� ��ư ��Ʈ�ѷ� ����
CButton m_pushButton5;		//�ְ����� ��ư ��Ʈ�ѷ� ����

BOOL   choose = FALSE;		//���ü��� ���ú���
BOOL   choose1 = FALSE;		//�ְ��� ���ú���
BOOL   choose2 = FALSE;		//������� ���ú���
BOOL   choose3 = FALSE;		//�����ϴ� ���ú���
BOOL   choose4 = FALSE;		//�ְ����� ���ú���
BOOL   choose5 = TRUE;	    //ù ȭ�� ���ú���
BOOL   stop = FALSE;  		//���ü��� �̺�Ʈ����
BOOL   stop1 = FALSE;		//�ְ��� �̺�Ʈ����
BOOL   stop2 = FALSE;		//������� �̺�Ʈ����
BOOL   stop3 = FALSE;		//�����ϴ� �̺�Ʈ����
BOOL   stop4 = FALSE;		//�ְ����� �̺�Ʈ����


BOOL   seoul = FALSE;
BOOL   seoul1 = FALSE;     // �������� ���� �̺�Ʈ ����
BOOL   gyeonggi = FALSE;
BOOL   gyeonggi1 = FALSE;  // ��⵵ ���� ���� �̺�Ʈ ����
BOOL   gangwon = FALSE;
BOOL   gangwon1 = FALSE;   // ������ ���� ���� �̺�Ʈ ���� 
BOOL   chungnam = FALSE;
BOOL   chungnam1 = FALSE;  // ��û���� ���� ���� �̺�Ʈ ����
BOOL   chungbuk = FALSE;
BOOL   chungbuk1 = FALSE;  // ��û�ϵ� ���� ���� �̺�Ʈ ����
BOOL   jeonnam = FALSE;
BOOL   jeonnam1 = FALSE;   // ���󳲵� ���� ���� �̺�Ʈ ����
BOOL   jeonbuk = FALSE;
BOOL   jeonbuk1 = FALSE;   // ����ϵ� ���� ���� �̺�Ʈ ����
BOOL   gyeongnam = FALSE;
BOOL   gyeongnam1 = FALSE; // ��󳲵� ���� ���� �̺�Ʈ ����
BOOL   gyeongbuk = FALSE;
BOOL   gyeongbuk1 = FALSE; // ���ϵ� ���� ���� �̺�Ʈ ����


CString Daejeonstr[10];		//���������� ����� ��ȭ�� ��󿹺�
CString Jejustr[10];		//����Ư����ġ�� ���ֽ� ������ �������
CString Yeosustr[10];		//���󳲵� ������ ������ �������
CString Incheonstr[10];		//��õ������ �߱� ������ �������
CString Ulsanstr[10];		//��걤���� ���� �޵� �������
CString Seoulstr[10];		//����Ư���� ������ ����1�� �������
CString Busanstr[10];		//�λ걤���� ������ ������9�� �������
CString Daegustr[10];		//�뱸������ ���� ���̵� �������
CString Gwangjustr[10];		//���ֱ����� ���� ���嵿 �������
CString Chuncheonstr[10];        //������ ��õ�� ���� �������
CString Gangneungstr[10];	//������ ������ ������ �������
CString Cheongjustr[10];	         //��û�ϵ� û�ֽ�û���� ����1�� �������
CString Changwonstr[10];	         //��󳲵� â���� ���ر� ��ȭ�� �������
CString Jeonjustr[10];	         //����ϵ� ���ֽ� ��ģ�� �ݾ�1�� �������

CString Hanul[14];		//�����ϴ�����
CString Weekstr[6];		//�߱⿹������
CString WeekHanul[6];		//�ְ��ϴ�����
CString WeekHigh[6];		//�ְ��ְ���
CString WeekLow[6];		//�ְ��������
CString Weekday[6];		//�ְ�����
CString Weekdate[6];		//�ְ���¥


CChildView::CChildView()	//�����ڷ� RSS���� ����
{
	Daejeon();
	Cheongju();
	Jeonju();
	Jeju();
	Yeosu();
	Incheon();
	Ulsan();
	Seoul();
	Busan();
	Daegu();
	Gwangju();
	Changwon();
	Gangneung();
	Chuncheon();
	Week();

}

UINT one_minute_thread(LPVOID arg)	//1�и��� ���� �۾��ڽ�����
{
	while (1)
	{
		CChildView();
		Sleep(60000);		//msec����, 1�и���
	}
	return 0;
}

CChildView::~CChildView()
{
}

void CChildView::Daejeon()
{

	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=3023052000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);

	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Daejeonstr[0] = xml.GetData();   //���û ���׿��� ������ - ���������� ����� ��ȭ�� ��ǥ����
	xml.FindElem(_T("generator"));
	Daejeonstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Daejeonstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();
	
	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Daejeonstr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Daejeonstr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Daejeonstr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Daejeonstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Daejeonstr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[0] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Daejeonstr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��
	
	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Daejeonstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Daejeonstr[7] = xml.GetData();   //�����µ�

	Daejeonstr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Daejeonstr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�

}
void CChildView::Seoul()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=1168066000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);

	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Seoulstr[0] = xml.GetData();   //���û ���׿��� ������ - ����Ư���� ������ ����1�� ��ǥ����
	xml.FindElem(_T("generator"));
	Seoulstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Seoulstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();

	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Seoulstr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Seoulstr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Seoulstr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Seoulstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Seoulstr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[1] = xml.GetData();      //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Seoulstr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��
	xml.OutOfElem();
	//-------------------------------------���� 1����(����)
	for (int i = 0; i < 8; i++)
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	WeekHigh[0] = xml.GetData();	//�ְ�µ�
	Seoulstr[6] = xml.GetData();	//�ְ�µ�
	xml.FindElem(_T("tmn"));
	WeekLow[0] = xml.GetData();		//�����µ�
	Seoulstr[7] = xml.GetData();	//�����µ�
	xml.FindElem(_T("wfKor"));
	WeekHanul[0] = xml.GetData();   //�ϴû�Ȳ
	xml.OutOfElem();
	//-------------------------------------���� 2����(��)
	for (int i = 0; i < 4; i++)
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	WeekHigh[1] = xml.GetData();	//�ְ�µ�
	xml.FindElem(_T("tmn"));
	WeekLow[1] = xml.GetData();		//�����µ�
	xml.FindElem(_T("wfKor"));
	WeekHanul[1] = xml.GetData();   //�ϴû�Ȳ

	Seoulstr[6].Replace(_T(".0"), _T(""));   //.0 �����ڵ�
	Seoulstr[7].Replace(_T(".0"), _T(""));   //.0 �����ڵ�
	WeekHigh[0].Replace(_T(".0"), _T(""));   //.0 �����ڵ�
	WeekLow[0].Replace(_T(".0"), _T(""));   //.0 �����ڵ�
	WeekHigh[1].Replace(_T(".0"), _T(""));   //.0 �����ڵ�
	WeekLow[1].Replace(_T(".0"), _T(""));   //.0 �����ڵ�

}
void CChildView::Incheon()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2811056000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);

	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Incheonstr[0] = xml.GetData();   //���û ���׿��� ������ - ��õ������ �߱� ������ ��ǥ����
	xml.FindElem(_T("generator"));
	Incheonstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Incheonstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Incheonstr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Incheonstr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Incheonstr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Incheonstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Incheonstr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[2] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Incheonstr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Incheonstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Incheonstr[7] = xml.GetData();   //�����µ�

	Incheonstr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Incheonstr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�

}
void CChildView::Chuncheon()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4211052000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);

	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Chuncheonstr[0] = xml.GetData();   //���û ���׿��� ������ - ������ ��õ�� ���� ��ǥ����
	xml.FindElem(_T("generator"));
	Chuncheonstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Chuncheonstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Chuncheonstr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Chuncheonstr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Chuncheonstr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Chuncheonstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Chuncheonstr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[3] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Chuncheonstr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Chuncheonstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Chuncheonstr[7] = xml.GetData();   //�����µ�

	Chuncheonstr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Chuncheonstr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Cheongju()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4311452000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Daejeonstr[0] = xml.GetData();   //���û ���׿��� ������ - ��û�ϵ� û�ֽ�û���� ����1�� ��ǥ����
	xml.FindElem(_T("generator"));
	Daejeonstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Daejeonstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Cheongjustr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Cheongjustr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Cheongjustr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Cheongjustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Cheongjustr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[4] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Cheongjustr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Cheongjustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Cheongjustr[7] = xml.GetData();   //�����µ�

	Cheongjustr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Cheongjustr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Jeonju()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4511358000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);

	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Jeonjustr[0] = xml.GetData();   //���û ���׿��� ������ - ����ϵ� ���ֽô����� �ݾ�1�� ��ǥ����
	xml.FindElem(_T("generator"));
	Jeonjustr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Jeonjustr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Jeonjustr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Jeonjustr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Jeonjustr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Jeonjustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Jeonjustr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[5] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Jeonjustr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Jeonjustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Jeonjustr[7] = xml.GetData();   //�����µ�

	Jeonjustr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Jeonjustr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Gwangju()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2911052500"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Gwangjustr[0] = xml.GetData();   //���û ���׿��� ������ - ���ֱ����� ���� ���嵿 ��ǥ����
	xml.FindElem(_T("generator"));
	Gwangjustr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Gwangjustr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Gwangjustr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Gwangjustr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Gwangjustr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Gwangjustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Gwangjustr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[6] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Gwangjustr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Gwangjustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Gwangjustr[7] = xml.GetData();   //�����µ�

	Gwangjustr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Gwangjustr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Yeosu()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4613062500"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Yeosustr[0] = xml.GetData();   //���û ���׿��� ������ - ���󳲵� ������ ������ ��ǥ����
	xml.FindElem(_T("generator"));
	Yeosustr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Yeosustr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Yeosustr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Yeosustr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Yeosustr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Yeosustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Yeosustr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[7] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Yeosustr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Yeosustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Yeosustr[7] = xml.GetData();   //�����µ�

	Yeosustr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Yeosustr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Jeju()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=5011066000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Jejustr[0] = xml.GetData();   //���û ���׿��� ������ - ����Ư����ġ�� ���ֽ� ������ ��ǥ����
	xml.FindElem(_T("generator"));
	Jejustr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Jejustr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Jejustr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Jejustr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Jejustr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Jejustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Jejustr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[8] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Jejustr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Jejustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Jejustr[7] = xml.GetData();   //�����µ�

	Jejustr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Jejustr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Gangneung()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4215061500"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);

	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Gangneungstr[0] = xml.GetData();   //���û ���׿��� ������ - ������ ������ ������ ��ǥ����
	xml.FindElem(_T("generator"));
	Gangneungstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Gangneungstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Gangneungstr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Gangneungstr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Gangneungstr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Gangneungstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Gangneungstr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[9] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Gangneungstr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Gangneungstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Gangneungstr[7] = xml.GetData();   //�����µ�

	Gangneungstr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Gangneungstr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Daegu()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2714067000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Daegustr[0] = xml.GetData();   //���û ���׿��� ������ - �뱸������ ���� ���̵� ��ǥ����
	xml.FindElem(_T("generator"));
	Daegustr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Daegustr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Daegustr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Daegustr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Daegustr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Daegustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Daegustr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[10] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Daegustr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Daegustr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Daegustr[7] = xml.GetData();   //�����µ�

	Daegustr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Daegustr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Ulsan()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=3114056000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Ulsanstr[0] = xml.GetData();   //���û ���׿��� ������ - ��걤���� ���� �޵� ��ǥ����
	xml.FindElem(_T("generator"));
	Ulsanstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Ulsanstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Ulsanstr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Ulsanstr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Ulsanstr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Ulsanstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Ulsanstr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[11] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Ulsanstr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Ulsanstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Ulsanstr[7] = xml.GetData();   //�����µ�

	Ulsanstr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Ulsanstr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Changwon()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=48129560000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Changwonstr[0] = xml.GetData();   //���û ���׿��� ������ - ��󳲵� â���� ���ر� ��ȭ�� ��ǥ����
	xml.FindElem(_T("generator"));
	Changwonstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Changwonstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Changwonstr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Changwonstr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Changwonstr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Changwonstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Changwonstr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[12] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Changwonstr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Changwonstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Changwonstr[7] = xml.GetData();   //�����µ�

	Changwonstr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Changwonstr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
}
void CChildView::Busan()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2647073000"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("title"));
	Busanstr[0] = xml.GetData();   //���û ���׿��� ������ - �λ걤���� ������ ������9�� ��ǥ����
	xml.FindElem(_T("generator"));
	Busanstr[1] = xml.GetData();   //���׿���
	xml.FindElem(_T("pubDate"));
	Busanstr[2] = xml.GetData();   //2018�� 12�� 07�� (��)���� 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------//---------------------------------�ش� ���� ���� ��������
	xml.FindElem(_T("hour"));
	Busanstr[3] = xml.GetData();   //18 ���׿��� 3�ð�����(15��~18�ñ���)
	xml.FindElem(_T("day"));
	Busanstr[4] = xml.GetData();   //1��°��(����/����/�� �� ����)
	xml.FindElem(_T("temp"));
	Busanstr[5] = xml.GetData();   //����ð��µ�(15��~18��)
	xml.FindElem(_T("tmx"));
	//Busanstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	//Busanstr[7] = xml.GetData();   //�����µ�
	xml.FindElem(_T("sky"));
	Hanul[13] = xml.GetData();        //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
	xml.FindElem(_T("pty"));
	Busanstr[9] = xml.GetData();   //���������ڵ� 0 : ���� 1 : �� 2 : ��/�� 3 : ��/�� 4 : ��

	//---------------------------------���� ����
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//�������� �޾ƿ���
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Busanstr[6] = xml.GetData();   //�ְ�µ�
	xml.FindElem(_T("tmn"));
	Busanstr[7] = xml.GetData();   //�����µ�

	Busanstr[6].Replace(_T(".0"), _T(""));	//.0 �����ڵ�
	Busanstr[7].Replace(_T(".0"), _T(""));	//.0 �����ڵ�

}
void CChildView::Week()
{
	CMarkup xml;
	HRESULT res = URLDownloadToFile(NULL, _T("http://www.weather.go.kr/weather/forecast/mid-term-rss3.jsp?stnId=109"), _T("Weather.XML"), 0, NULL);
	CString strFileName = _T("Weather.XML");
	xml.Load(strFileName);


	xml.FindElem(_T("rss"));
	xml.IntoElem();
	xml.FindElem(_T("channel"));
	xml.IntoElem();
	xml.FindElem(_T("pubDate"));	
	Weekstr[0] = xml.GetData();		//2018�� 12�� 12�� (��)���� 18:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("category"));
	xml.FindElem(_T("title"));
	Weekstr[1] = xml.GetData();   //����,��⵵ ���� �߱⿹�� - 2018�� 12�� 12�� (��)���� 18:00 ��ǥ
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("header"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	Weekstr[2] = xml.GetData();   //��а��� ����~~
	xml.OutOfElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("location"));
	xml.IntoElem();
	xml.FindElem(_T("province"));
	Weekstr[3] = xml.GetData();   //�������õ����⵵
	xml.FindElem(_T("city"));
	Weekstr[4] = xml.GetData();   //����
	//-------------------------------------3����
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	WeekHanul[2] = xml.GetData();   //�ϴû�Ȳ
	xml.FindElem(_T("tmn"));
	WeekLow[2] = xml.GetData();   //�������
	xml.FindElem(_T("tmx"));
	WeekHigh[2] = xml.GetData();   //�ְ���
	xml.OutOfElem();
	//-------------------------------------4����
	xml.FindElem(_T("data"));
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	WeekHanul[3] = xml.GetData();   //�ϴû�Ȳ
	xml.FindElem(_T("tmn"));
	WeekLow[3] = xml.GetData();   //�������
	xml.FindElem(_T("tmx"));
	WeekHigh[3] = xml.GetData();   //�ְ���
	xml.OutOfElem();
	//-------------------------------------5����
	xml.FindElem(_T("data"));
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	WeekHanul[4] = xml.GetData();   //�ϴû�Ȳ
	xml.FindElem(_T("tmn"));
	WeekLow[4] = xml.GetData();   //�������
	xml.FindElem(_T("tmx"));
	WeekHigh[4] = xml.GetData();   //�ְ���
	xml.OutOfElem();
	//-------------------------------------6����
	xml.FindElem(_T("data"));
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	WeekHanul[5] = xml.GetData();   //�ϴû�Ȳ
	xml.FindElem(_T("tmn"));
	WeekLow[5] = xml.GetData();   //�������
	xml.FindElem(_T("tmx"));
	WeekHigh[5] = xml.GetData();   //�ְ���
	xml.OutOfElem();
	
	Weekstr[0].Delete(0, 12);
	Weekstr[0].Delete(2, 17);
	Weekstr[1].Delete(0, 45);
	Weekstr[1].Delete(4, 14);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(101, OnButton1Clicked)
	ON_BN_CLICKED(102, OnButton2Clicked)
	ON_BN_CLICKED(103, OnButton3Clicked)
	ON_BN_CLICKED(104, OnButton4Clicked)
	ON_BN_CLICKED(105, OnButton5Clicked)
//	ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDBLCLK()
//ON_WM_DRAWITEM()
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
	AfxBeginThread(one_minute_thread, (LPVOID)arg);

	//ó��ȭ��
	if (choose5) {
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		dc.SetBkMode(TRANSPARENT);	//����� ����
		CFont font;
		// ��Ʈ�� ���ҽ��� �ε��� �� ũ�� ������ ��´�.
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP12);
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);
		// �޸� DC�� ���� �� ��Ʈ���� ������ �ִ´�.
		CDC dcmem;
		dcmem.CreateCompatibleDC(&dc);
		dcmem.SelectObject(&bitmap);

		// ��Ʈ���� ȭ�鿡 ����Ѵ�.
		dc.StretchBlt(0, 0, bmpinfo.bmWidth*0.75, bmpinfo.bmHeight*0.75,
			&dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
		//------------------------------���׸���-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		//-------------------------------��ǳ�� �ֱ�---
		CString Malstr = _T("�ȳ��ϼ���. ");
		Malstr = Malstr + Daejeonstr[1] + _T(" ������ �Դϴ�.  ���� ") + Daejeonstr[2] + _T("            ��󿹺��� �ǽ��ϰڽ��ϴ�.");
	    m_static->SetWindowTextA(Malstr);
		//---------------------------------------------
		return;
	}
	//����ȭ��
    else if (choose) {
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		dc.SetBkMode(TRANSPARENT);	//����� ����
		CFont font;
		
		CBitmap bitmap4;					//��������
		bitmap4.LoadBitmap(IDB_BITMAP11);
		BITMAP bmpinfo4;
		bitmap4.GetBitmap(&bmpinfo4);

		CDC dcmem4;
		dcmem4.CreateCompatibleDC(&dc);
		dcmem4.SelectObject(&bitmap4);

		CBitmap bitmap4_1;					//���1
		bitmap4_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_1;
		bitmap4_1.GetBitmap(&bmpinfo4_1);

		CDC dcmem4_1;
		dcmem4_1.CreateCompatibleDC(&dc);
		dcmem4_1.SelectObject(&bitmap4_1);
		//--------------------���1��ǳ������ֱ�----------
		CBrush brush1(RGB(120, 120, 120));
		dcmem4_1.SelectObject(&brush1);
		dcmem4_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_2;					//���2
		bitmap4_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_2;
		bitmap4_2.GetBitmap(&bmpinfo4_2);

		CDC dcmem4_2;
		dcmem4_2.CreateCompatibleDC(&dc);
		dcmem4_2.SelectObject(&bitmap4_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_2.SelectObject(&brush1);
		dcmem4_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_1.StretchBlt(0, 0, bmpinfo4.bmWidth, bmpinfo4.bmHeight,	//���� ���׸���
			&dcmem4, 0, 0, bmpinfo4.bmWidth, bmpinfo4.bmHeight, SRCCOPY);
		dcmem4_2.StretchBlt(0, 0, bmpinfo4.bmWidth, bmpinfo4.bmHeight,	//���� ���׸���
			&dcmem4, 0, 0, bmpinfo4.bmWidth, bmpinfo4.bmHeight, SRCCOPY);

		
		//------------------------------���׸���-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		//-------------------------------��ǳ�� �ֱ�---
		CString Malstr = _T("���ϴ� ������ �������ּ���.");
		m_static->SetWindowTextA(Malstr);
		//---------------------------------------------

		CBitmap bitmap4_3;					//���2
		bitmap4_3.LoadBitmap(IDB_BITMAP17);
		BITMAP bmpinfo4_3;
		bitmap4_3.GetBitmap(&bmpinfo4_3);

		CDC dcmem4_3;
		dcmem4_3.CreateCompatibleDC(&dc);
		dcmem4_3.SelectObject(&bitmap4_3);

		CBitmap bitmap4_3_1;					//���1
		bitmap4_3_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_3_1;
		bitmap4_3_1.GetBitmap(&bmpinfo4_3_1);

		CDC dcmem4_3_1;
		dcmem4_3_1.CreateCompatibleDC(&dc);
		dcmem4_3_1.SelectObject(&bitmap4_3_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_3_1.SelectObject(&brush1);
		dcmem4_3_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_3_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_3_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_3_2;					//���2
		bitmap4_3_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_3_2;
		bitmap4_3_2.GetBitmap(&bmpinfo4_3_2);

		CDC dcmem4_3_2;
		dcmem4_3_2.CreateCompatibleDC(&dc);
		dcmem4_3_2.SelectObject(&bitmap4_3_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_3_2.SelectObject(&brush1);
		dcmem4_3_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_3_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_3_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_3_1.StretchBlt(0, 0, bmpinfo4_3.bmWidth*0.8, bmpinfo4_3.bmHeight*0.87,	//���� ���׸���
			&dcmem4_3, 0, 0, bmpinfo4_3.bmWidth, bmpinfo4_3.bmHeight, SRCCOPY);
		dcmem4_3_2.StretchBlt(0, 0, bmpinfo4_3.bmWidth*0.8, bmpinfo4_3.bmHeight*0.87,	//���� ���׸���
			&dcmem4_3, 0, 0, bmpinfo4_3.bmWidth, bmpinfo4_3.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_4;					//���2
		bitmap4_4.LoadBitmap(IDB_BITMAP18);
		BITMAP bmpinfo4_4;
		bitmap4_4.GetBitmap(&bmpinfo4_4);

		CDC dcmem4_4;
		dcmem4_4.CreateCompatibleDC(&dc);
		dcmem4_4.SelectObject(&bitmap4_4);

		CBitmap bitmap4_4_1;					//���1
		bitmap4_4_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_4_1;
		bitmap4_4_1.GetBitmap(&bmpinfo4_4_1);

		CDC dcmem4_4_1;
		dcmem4_4_1.CreateCompatibleDC(&dc);
		dcmem4_4_1.SelectObject(&bitmap4_4_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_4_1.SelectObject(&brush1);
		dcmem4_4_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_4_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_4_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_4_2;					//���2
		bitmap4_4_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_4_2;
		bitmap4_4_2.GetBitmap(&bmpinfo4_4_2);

		CDC dcmem4_4_2;
		dcmem4_4_2.CreateCompatibleDC(&dc);
		dcmem4_4_2.SelectObject(&bitmap4_4_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_4_2.SelectObject(&brush1);
		dcmem4_4_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_4_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_4_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_4_1.StretchBlt(0, 0, bmpinfo4_4.bmWidth*0.8, bmpinfo4_4.bmHeight*0.87,	//��� ���׸���
			&dcmem4_4, 0, 0, bmpinfo4_4.bmWidth, bmpinfo4_4.bmHeight, SRCCOPY);
		dcmem4_4_2.StretchBlt(0, 0, bmpinfo4_4.bmWidth*0.8, bmpinfo4_4.bmHeight*0.87,	//��� ���׸���
			&dcmem4_4, 0, 0, bmpinfo4_4.bmWidth, bmpinfo4_4.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_5;					//���2
		bitmap4_5.LoadBitmap(IDB_BITMAP19);
		BITMAP bmpinfo4_5;
		bitmap4_5.GetBitmap(&bmpinfo4_5);

		CDC dcmem4_5;
		dcmem4_5.CreateCompatibleDC(&dc);
		dcmem4_5.SelectObject(&bitmap4_5);

		CBitmap bitmap4_5_1;					//���1
		bitmap4_5_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_5_1;
		bitmap4_5_1.GetBitmap(&bmpinfo4_5_1);

		CDC dcmem4_5_1;
		dcmem4_5_1.CreateCompatibleDC(&dc);
		dcmem4_5_1.SelectObject(&bitmap4_5_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_5_1.SelectObject(&brush1);
		dcmem4_5_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_5_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_5_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_5_2;					//���2
		bitmap4_5_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_5_2;
		bitmap4_5_2.GetBitmap(&bmpinfo4_5_2);

		CDC dcmem4_5_2;
		dcmem4_5_2.CreateCompatibleDC(&dc);
		dcmem4_5_2.SelectObject(&bitmap4_5_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_5_2.SelectObject(&brush1);
		dcmem4_5_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_5_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_5_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_5_1.StretchBlt(0, 0, bmpinfo4_5.bmWidth*0.8, bmpinfo4_5.bmHeight*0.87,	//���� ���׸���
			&dcmem4_5, 0, 0, bmpinfo4_5.bmWidth, bmpinfo4_5.bmHeight, SRCCOPY);
		dcmem4_5_2.StretchBlt(0, 0, bmpinfo4_4.bmWidth*0.8, bmpinfo4_4.bmHeight*0.87,	//���� ���׸���
			&dcmem4_5, 0, 0, bmpinfo4_5.bmWidth, bmpinfo4_5.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_6;					//���2
		bitmap4_6.LoadBitmap(IDB_BITMAP20);
		BITMAP bmpinfo4_6;
		bitmap4_6.GetBitmap(&bmpinfo4_6);

		CDC dcmem4_6;
		dcmem4_6.CreateCompatibleDC(&dc);
		dcmem4_6.SelectObject(&bitmap4_6);

		CBitmap bitmap4_6_1;					//���1
		bitmap4_6_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_6_1;
		bitmap4_6_1.GetBitmap(&bmpinfo4_6_1);

		CDC dcmem4_6_1;
		dcmem4_6_1.CreateCompatibleDC(&dc);
		dcmem4_6_1.SelectObject(&bitmap4_6_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_6_1.SelectObject(&brush1);
		dcmem4_6_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_6_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_6_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_6_2;					//���2
		bitmap4_6_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_6_2;
		bitmap4_6_2.GetBitmap(&bmpinfo4_6_2);

		CDC dcmem4_6_2;
		dcmem4_6_2.CreateCompatibleDC(&dc);
		dcmem4_6_2.SelectObject(&bitmap4_6_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_6_2.SelectObject(&brush1);
		dcmem4_6_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_6_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_6_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_6_1.StretchBlt(0, 0, bmpinfo4_6.bmWidth*0.8, bmpinfo4_6.bmHeight*0.87,	//�泲 ���׸���
			&dcmem4_6, 0, 0, bmpinfo4_6.bmWidth, bmpinfo4_6.bmHeight, SRCCOPY);
		dcmem4_6_2.StretchBlt(0, 0, bmpinfo4_6.bmWidth*0.8, bmpinfo4_6.bmHeight*0.87,	//�泲 ���׸���
			&dcmem4_6, 0, 0, bmpinfo4_6.bmWidth, bmpinfo4_6.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_7;					//���2
		bitmap4_7.LoadBitmap(IDB_BITMAP21);
		BITMAP bmpinfo4_7;
		bitmap4_7.GetBitmap(&bmpinfo4_7);

		CDC dcmem4_7;
		dcmem4_7.CreateCompatibleDC(&dc);
		dcmem4_7.SelectObject(&bitmap4_7);

		CBitmap bitmap4_7_1;					//���1
		bitmap4_7_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_7_1;
		bitmap4_7_1.GetBitmap(&bmpinfo4_7_1);

		CDC dcmem4_7_1;
		dcmem4_7_1.CreateCompatibleDC(&dc);
		dcmem4_7_1.SelectObject(&bitmap4_7_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_7_1.SelectObject(&brush1);
		dcmem4_7_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_7_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_7_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_7_2;					//���2
		bitmap4_7_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_7_2;
		bitmap4_7_2.GetBitmap(&bmpinfo4_7_2);

		CDC dcmem4_7_2;
		dcmem4_7_2.CreateCompatibleDC(&dc);
		dcmem4_7_2.SelectObject(&bitmap4_7_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_7_2.SelectObject(&brush1);
		dcmem4_7_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_7_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_7_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_7_1.StretchBlt(0, 0, bmpinfo4_7.bmWidth*0.8, bmpinfo4_7.bmHeight*0.87,	//��� ���׸���
			&dcmem4_7, 0, 0, bmpinfo4_7.bmWidth, bmpinfo4_7.bmHeight, SRCCOPY);
		dcmem4_7_2.StretchBlt(0, 0, bmpinfo4_7.bmWidth*0.8, bmpinfo4_7.bmHeight*0.87,	//��� ���׸���
			&dcmem4_7, 0, 0, bmpinfo4_7.bmWidth, bmpinfo4_7.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_8;					//���2
		bitmap4_8.LoadBitmap(IDB_BITMAP22);
		BITMAP bmpinfo4_8;
		bitmap4_8.GetBitmap(&bmpinfo4_8);

		CDC dcmem4_8;
		dcmem4_8.CreateCompatibleDC(&dc);
		dcmem4_8.SelectObject(&bitmap4_8);

		CBitmap bitmap4_8_1;					//���1
		bitmap4_8_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_8_1;
		bitmap4_8_1.GetBitmap(&bmpinfo4_8_1);

		CDC dcmem4_8_1;
		dcmem4_8_1.CreateCompatibleDC(&dc);
		dcmem4_8_1.SelectObject(&bitmap4_8_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_8_1.SelectObject(&brush1);
		dcmem4_8_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_8_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_8_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_8_2;					//���2
		bitmap4_8_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_8_2;
		bitmap4_8_2.GetBitmap(&bmpinfo4_8_2);

		CDC dcmem4_8_2;
		dcmem4_8_2.CreateCompatibleDC(&dc);
		dcmem4_8_2.SelectObject(&bitmap4_8_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_8_2.SelectObject(&brush1);
		dcmem4_8_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_8_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_8_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_8_1.StretchBlt(0, 0, bmpinfo4_8.bmWidth*0.8, bmpinfo4_8.bmHeight*0.87,	//���� ���׸���
			&dcmem4_8, 0, 0, bmpinfo4_8.bmWidth, bmpinfo4_8.bmHeight, SRCCOPY);
		dcmem4_8_2.StretchBlt(0, 0, bmpinfo4_8.bmWidth*0.8, bmpinfo4_8.bmHeight*0.87,	//���� ���׸���
			&dcmem4_8, 0, 0, bmpinfo4_8.bmWidth, bmpinfo4_8.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_9;					//���2
		bitmap4_9.LoadBitmap(IDB_BITMAP23);
		BITMAP bmpinfo4_9;
		bitmap4_9.GetBitmap(&bmpinfo4_9);

		CDC dcmem4_9;
		dcmem4_9.CreateCompatibleDC(&dc);
		dcmem4_9.SelectObject(&bitmap4_9);

		CBitmap bitmap4_9_1;					//���1
		bitmap4_9_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_9_1;
		bitmap4_9_1.GetBitmap(&bmpinfo4_9_1);

		CDC dcmem4_9_1;
		dcmem4_9_1.CreateCompatibleDC(&dc);
		dcmem4_9_1.SelectObject(&bitmap4_9_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_9_1.SelectObject(&brush1);
		dcmem4_9_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_9_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_9_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_9_2;					//���2
		bitmap4_9_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_9_2;
		bitmap4_9_2.GetBitmap(&bmpinfo4_9_2);

		CDC dcmem4_9_2;
		dcmem4_9_2.CreateCompatibleDC(&dc);
		dcmem4_9_2.SelectObject(&bitmap4_9_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_9_2.SelectObject(&brush1);
		dcmem4_9_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_9_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_9_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_9_1.StretchBlt(0, 0, bmpinfo4_9.bmWidth*0.8, bmpinfo4_9.bmHeight*0.87,	//���� ���׸���
			&dcmem4_9, 0, 0, bmpinfo4_9.bmWidth, bmpinfo4_9.bmHeight, SRCCOPY);
		dcmem4_9_2.StretchBlt(0, 0, bmpinfo4_9.bmWidth*0.8, bmpinfo4_9.bmHeight*0.87,	//���� ���׸���
			&dcmem4_9, 0, 0, bmpinfo4_9.bmWidth, bmpinfo4_9.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_10;					//���2
		bitmap4_10.LoadBitmap(IDB_BITMAP24);
		BITMAP bmpinfo4_10;
		bitmap4_10.GetBitmap(&bmpinfo4_10);

		CDC dcmem4_10;
		dcmem4_10.CreateCompatibleDC(&dc);
		dcmem4_10.SelectObject(&bitmap4_10);

		CBitmap bitmap4_10_1;					//���1
		bitmap4_10_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_10_1;
		bitmap4_10_1.GetBitmap(&bmpinfo4_10_1);

		CDC dcmem4_10_1;
		dcmem4_10_1.CreateCompatibleDC(&dc);
		dcmem4_10_1.SelectObject(&bitmap4_10_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_10_1.SelectObject(&brush1);
		dcmem4_10_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_10_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_10_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_10_2;					//���2
		bitmap4_10_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_10_2;
		bitmap4_10_2.GetBitmap(&bmpinfo4_10_2);

		CDC dcmem4_10_2;
		dcmem4_10_2.CreateCompatibleDC(&dc);
		dcmem4_10_2.SelectObject(&bitmap4_10_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_10_2.SelectObject(&brush1);
		dcmem4_10_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_10_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_10_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_10_1.StretchBlt(0, 0, bmpinfo4_10.bmWidth*0.8, bmpinfo4_10.bmHeight*0.87,	//�泲 ���׸���
			&dcmem4_10, 0, 0, bmpinfo4_10.bmWidth, bmpinfo4_10.bmHeight, SRCCOPY);
		dcmem4_10_2.StretchBlt(0, 0, bmpinfo4_10.bmWidth*0.8, bmpinfo4_10.bmHeight*0.87,	//�泲 ���׸���
			&dcmem4_10, 0, 0, bmpinfo4_10.bmWidth, bmpinfo4_10.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_11;					//���2
		bitmap4_11.LoadBitmap(IDB_BITMAP25);
		BITMAP bmpinfo4_11;
		bitmap4_11.GetBitmap(&bmpinfo4_11);

		CDC dcmem4_11;
		dcmem4_11.CreateCompatibleDC(&dc);
		dcmem4_11.SelectObject(&bitmap4_11);

		CBitmap bitmap4_11_1;					//���1
		bitmap4_11_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_11_1;
		bitmap4_11_1.GetBitmap(&bmpinfo4_11_1);

		CDC dcmem4_11_1;
		dcmem4_11_1.CreateCompatibleDC(&dc);
		dcmem4_11_1.SelectObject(&bitmap4_11_1);
		//--------------------���1��ǳ������ֱ�----------
		dcmem4_11_1.SelectObject(&brush1);
		dcmem4_11_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_11_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_11_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_11_2;					//���2
		bitmap4_11_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_11_2;
		bitmap4_11_2.GetBitmap(&bmpinfo4_11_2);

		CDC dcmem4_11_2;
		dcmem4_11_2.CreateCompatibleDC(&dc);
		dcmem4_11_2.SelectObject(&bitmap4_11_2);
		//--------------------���2��ǳ������ֱ�-----------
		dcmem4_11_2.SelectObject(&brush1);
		dcmem4_11_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_11_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_11_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_11_1.StretchBlt(0, 0, bmpinfo4_11.bmWidth*0.8, bmpinfo4_11.bmHeight*0.87,	//��� ���׸���
			&dcmem4_11, 0, 0, bmpinfo4_11.bmWidth, bmpinfo4_11.bmHeight, SRCCOPY);
		dcmem4_11_2.StretchBlt(0, 0, bmpinfo4_11.bmWidth*0.8, bmpinfo4_11.bmHeight*0.87,	//��� ���׸���
			&dcmem4_11, 0, 0, bmpinfo4_11.bmWidth, bmpinfo4_11.bmHeight, SRCCOPY);


		//------------------------------���׸���-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		int sel_hanul[14] = { 0 };      //�̸�Ƽ�� ���� ����   
		for (int i = 0; i < 14; i++)   //�̸�Ƽ�� ���� ����� ���� ����ġ��
		{
			STR_SWITCH(Hanul[i])      //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
				CASE(_T("1"))
				sel_hanul[i] = 367;
			BREAK
				CASE(_T("2"))
				sel_hanul[i] = 365;
			BREAK
				CASE(_T("3"))
				sel_hanul[i] = 366;
			BREAK
				CASE(_T("4"))
				sel_hanul[i] = 368;
			BREAK
				END_SWITCH;
		}
		CBitmap Hanul_Bitmap[14];   //�̸�Ƽ�� ǥ�� ��Ʈ�� ��������
		BITMAP Hanul_Bmpinfo[14];   //�̸�Ƽ�� ǥ�� ��Ʈ�� ��������
		CDC dcmem[14];
		//---------------------------------------���� ���� ���-----------------------------
		CString se_hanul[14] = { 0 };      //�̸�Ƽ�� ���� ����   
		for (int i = 0; i < 14; i++)   //�̸�Ƽ�� ���� ����� ���� ����ġ��
		{
			STR_SWITCH(Hanul[i])      //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
				CASE(_T("1"))
				se_hanul[i] = "����";
			BREAK
				CASE(_T("2"))
				se_hanul[i] = "���� ����";
			BREAK
				CASE(_T("3"))
				se_hanul[i] = "���� ����";
			BREAK
				CASE(_T("4"))
				se_hanul[i] = "�帲";
			BREAK
				END_SWITCH;
		}
	//-------------------------------------------------------------------

		font.CreateFont(35,     // ���ڳ���
			15,                     // ���ڳʺ�
			0,                      // ��°���
			0,                      // ���� �������ǰ���
			FW_HEAVY,               // ���ڱ���
			FALSE,                  // Italic ���뿩��
			FALSE,                  // �������뿩��
			FALSE,                  // ��Ҽ����뿩��
			DEFAULT_CHARSET,        // ���ڼ�����
			OUT_DEFAULT_PRECIS,     // ������е�
			CLIP_DEFAULT_PRECIS,    // Ŭ�������е�
			DEFAULT_QUALITY,        // ��¹���ǰ��
			DEFAULT_PITCH,          // �۲�Pitch
			_T("���� ���")         // �۲�
		);
		//------------------------------------------------------------
		for (int i = 0; i < 14; i++)
		{
			Hanul_Bitmap[i].LoadBitmap(sel_hanul[i]);
			Hanul_Bitmap[i].GetBitmap(&Hanul_Bmpinfo[i]);
			dcmem[i].CreateCompatibleDC(&dc);			//�޸𸮵���̽����ؽ�Ʈ ����
			dcmem[i].SelectObject(&Hanul_Bitmap[i]);   //��Ʈ���� �޸� ����̽� ���ؽ�Ʈ�� ����
		}
		//------------------------------------------------------------

		for (int i = 0; ; i++)
		{
			if (stop)
			{
				break;
			}

			m_r1.SetRect(200, 150, 250, 200);
			m_r2.SetRect(270, 100, 320, 250);
			m_r3.SetRect(350, 100, 450, 250);
			m_r4.SetRect(150, 300, 250, 400);
			m_r5.SetRect(300, 300, 400, 400);
			m_r6.SetRect(150, 650, 300, 750);
			m_r7.SetRect(150, 450, 300, 600);
			m_r8.SetRect(300,550, 400, 700);
			m_r9.SetRect(450, 200, 600, 450);
			//������ ����1��
			if (seoul1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_3_1.bmWidth*0.75, bmpinfo4_3_1.bmHeight*0.75,
					&dcmem4_3_1, 0, 0, bmpinfo4_3_1.bmWidth, bmpinfo4_3_1.bmHeight, SRCCOPY);
				dc.TextOut(300, 300, _T("������ ����1��"));
				dc.TextOut(300, 400, Seoulstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[1].bmWidth*0.4, Hanul_Bmpinfo[1].bmHeight*0.4,
					&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
				CString Malstr = _T(" ����Ư���� ������ ����1�� - ");
				Malstr = Malstr +  _T(" ���� �µ�: ") + Seoulstr[5] + _T(" ���糯��: ") + se_hanul[1];
				m_static->SetWindowTextA(Malstr);
			}
			//��õ �߱� ������
			else if (gyeonggi1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_4_1.bmWidth*0.75, bmpinfo4_4_1.bmHeight*0.75,
					&dcmem4_4_1, 0, 0, bmpinfo4_4_1.bmWidth, bmpinfo4_4_1.bmHeight, SRCCOPY);
				dc.TextOut(300, 300, _T("��õ �߱� ������"));
				dc.TextOut(300, 400, Incheonstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[2].bmWidth*0.4, Hanul_Bmpinfo[2].bmHeight*0.4,
					&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
				CString Malstr = _T(" ��õ �߱� ������ - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Incheonstr[5] + _T(" ���糯��: ") + se_hanul[2];
				m_static->SetWindowTextA(Malstr);
			}
			//��õ ����
			else if (gangwon1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_5_1.bmWidth*0.75, bmpinfo4_5_1.bmHeight*0.75,
					&dcmem4_5_1, 0, 0, bmpinfo4_5_1.bmWidth, bmpinfo4_5_1.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("��õ�� ����"));
				dc.TextOut(250, 400, Chuncheonstr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[3].bmWidth*0.4, Hanul_Bmpinfo[3].bmHeight*0.4,
					&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("������ ������"));
				dc.TextOut(250, 550, Gangneungstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[9].bmWidth*0.4, Hanul_Bmpinfo[9].bmHeight*0.4,
					&dcmem[9], 0, 0, Hanul_Bmpinfo[9].bmWidth, Hanul_Bmpinfo[9].bmHeight, SRCCOPY); //���� ������
				CString Malstr = _T(" ��õ�� ���� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Chuncheonstr[5] + _T(" ���糯��: ") + se_hanul[3] + _T(" ������ ������ - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Gangneungstr[5] + _T(" ���糯��: ") + se_hanul[9] ;
				m_static->SetWindowTextA(Malstr);
			}
			//���� ����� ��ȭ��
			else if (chungnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_6_1.bmWidth*0.75, bmpinfo4_6_1.bmHeight*0.75,
					&dcmem4_6_1, 0, 0, bmpinfo4_6_1.bmWidth, bmpinfo4_6_1.bmHeight, SRCCOPY);
				dc.TextOut(250, 300, _T("���� ����� ��ȭ��"));
				dc.TextOut(300, 400, Daejeonstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[0].bmWidth*0.4, Hanul_Bmpinfo[0].bmHeight*0.4,
					&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY); 
				CString Malstr = _T(" ���� ����� ��ȭ�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Daejeonstr[5] + _T(" ���糯��: ") + se_hanul[0];
				m_static->SetWindowTextA(Malstr);

			}
			// û�ֽ� û���� ����1��
			else if (chungbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_7_1.bmWidth*0.75, bmpinfo4_7_1.bmHeight*0.75,
					&dcmem4_7_1, 0, 0, bmpinfo4_7_1.bmWidth, bmpinfo4_7_1.bmHeight, SRCCOPY);
				dc.TextOut(150, 300, _T("û�ֽ� û���� ����1��"));
				dc.TextOut(200, 400, Cheongjustr[5]);
				dc.StretchBlt(200, 350, Hanul_Bmpinfo[4].bmWidth*0.4, Hanul_Bmpinfo[4].bmHeight*0.4,
					&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
				CString Malstr = _T(" û�ֽ� û���� ����1�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Cheongjustr[5] + _T(" ���糯��: ") + se_hanul[4];
				m_static->SetWindowTextA(Malstr);
			}
			//������ ������
			else if (jeonnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_8_1.bmWidth*0.75, bmpinfo4_8_1.bmHeight*0.75,
					&dcmem4_8_1, 0, 0, bmpinfo4_8_1.bmWidth, bmpinfo4_8_1.bmHeight, SRCCOPY);
				dc.TextOut(250, 300, _T("������ ������"));
				dc.TextOut(300, 400, Yeosustr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[7].bmWidth*0.4, Hanul_Bmpinfo[7].bmHeight*0.4,
					&dcmem[7], 0, 0, Hanul_Bmpinfo[7].bmWidth, Hanul_Bmpinfo[7].bmHeight, SRCCOPY);
				CString Malstr = _T(" ������ ������ - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Yeosustr[5] + _T(" ���糯��: ") + se_hanul[7];
				m_static->SetWindowTextA(Malstr);

			}
			//������ �ݾ�1��
			else if (jeonbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_9_1.bmWidth*0.75, bmpinfo4_9_1.bmHeight*0.75,
					&dcmem4_9_1, 0, 0, bmpinfo4_9_1.bmWidth, bmpinfo4_9_1.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("���ֽ� ������ �ݾ�1��"));
				dc.TextOut(250, 400, Jeonjustr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[5].bmWidth*0.4, Hanul_Bmpinfo[5].bmHeight*0.4,
					&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("���ֱ����� ���� ���嵿"));
				dc.TextOut(250, 550, Gwangjustr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[6].bmWidth*0.4, Hanul_Bmpinfo[6].bmHeight*0.4,
					&dcmem[6], 0, 0, Hanul_Bmpinfo[6].bmWidth, Hanul_Bmpinfo[6].bmHeight, SRCCOPY); //����
				CString Malstr = _T(" ���ֽ� ������ �ݾ�1�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Jeonjustr[5] + _T(" ���糯��: ") + se_hanul[5] + _T(" ���ֱ����� ���� ���嵿 - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Gwangjustr[5] + _T(" ���糯��: ") + se_hanul[6];
				m_static->SetWindowTextA(Malstr);
			}
			//â���� ���ر� ��ȭ��
			else if (gyeongnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_10_1.bmWidth*0.75, bmpinfo4_10_1.bmHeight*0.75,
					&dcmem4_10_1, 0, 0, bmpinfo4_10_1.bmWidth, bmpinfo4_10_1.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("â���� ���ر� ��ȭ��"));
				dc.TextOut(250, 400, Changwonstr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[12].bmWidth*0.4, Hanul_Bmpinfo[12].bmHeight*0.4,
					&dcmem[12], 0, 0, Hanul_Bmpinfo[12].bmWidth, Hanul_Bmpinfo[12].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("�λ� ������ ���� ��9��"));
				dc.TextOut(250, 550, Busanstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[13].bmWidth*0.4, Hanul_Bmpinfo[13].bmHeight*0.4,
					&dcmem[13], 0, 0, Hanul_Bmpinfo[13].bmWidth, Hanul_Bmpinfo[13].bmHeight, SRCCOPY); // �λ�
				CString Malstr = _T(" â���� ���ر� ��ȭ�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Changwonstr[5] + _T(" ���糯��: ") + se_hanul[12] + _T(" �λ� ������ ���� ��9�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Busanstr[5] + _T(" ���糯��: ") + se_hanul[13];
				m_static->SetWindowTextA(Malstr);
			}
			//�뱸 ���� ���̵�
			else if (gyeongbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_11_1.bmWidth*0.75, bmpinfo4_11_1.bmHeight*0.75,
					&dcmem4_11_1, 0, 0, bmpinfo4_11_1.bmWidth, bmpinfo4_11_1.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("�뱸 ���� ���̵�"));
				dc.TextOut(250, 400, Daegustr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[10].bmWidth*0.4, Hanul_Bmpinfo[10].bmHeight*0.4,
					&dcmem[10], 0, 0, Hanul_Bmpinfo[10].bmWidth, Hanul_Bmpinfo[10].bmHeight, SRCCOPY); 
				dc.TextOut(200, 450, _T("��� ���� �޵�"));
				dc.TextOut(250, 550, Ulsanstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[11].bmWidth*0.4, Hanul_Bmpinfo[11].bmHeight*0.4,
					&dcmem[11], 0, 0, Hanul_Bmpinfo[11].bmWidth, Hanul_Bmpinfo[11].bmHeight, SRCCOPY);
				CString Malstr = _T(" �뱸 ���� ���̵� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Daegustr[5] + _T(" ���糯��: ") + se_hanul[10] + _T(" ��� ���� �޵� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Ulsanstr[5] + _T(" ���糯��: ") + se_hanul[11];
				m_static->SetWindowTextA(Malstr);
			}
			else
			{ 
				dc.StretchBlt(0, 0, bmpinfo4_1.bmWidth*0.75, bmpinfo4_1.bmHeight*0.75,
					&dcmem4_1, 0, 0, bmpinfo4_1.bmWidth, bmpinfo4_1.bmHeight, SRCCOPY);

			}

			wait(500);

			if (stop)
			{
				break;
			}
			//������ ����1��
			if (seoul1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_3_2.bmWidth*0.75, bmpinfo4_3_2.bmHeight*0.75,
					&dcmem4_3_2, 0, 0, bmpinfo4_3_2.bmWidth, bmpinfo4_3_2.bmHeight, SRCCOPY);
				dc.TextOut(300, 300, _T("������ ����1��"));
				dc.TextOut(300, 400, Seoulstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[1].bmWidth*0.4, Hanul_Bmpinfo[1].bmHeight*0.4,
					&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
				CString Malstr = _T(" ����Ư���� ������ ����1�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Seoulstr[5] + _T(" ���糯��: ") + se_hanul[1];
				m_static->SetWindowTextA(Malstr);
			}
			//��õ �߱� ������
			else if (gyeonggi1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_4_2.bmWidth*0.75, bmpinfo4_4_2.bmHeight*0.75,
					&dcmem4_4_2, 0, 0, bmpinfo4_4_2.bmWidth, bmpinfo4_4_2.bmHeight, SRCCOPY);
				dc.TextOut(300, 300, _T("��õ �߱� ������"));
				dc.TextOut(300, 400, Incheonstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[2].bmWidth*0.4, Hanul_Bmpinfo[2].bmHeight*0.4,
					&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
				CString Malstr = _T(" ��õ �߱� ������ - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Incheonstr[5] + _T(" ���糯��: ") + se_hanul[2];
				m_static->SetWindowTextA(Malstr);
			}
			//��õ ����
			else if (gangwon1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_5_2.bmWidth*0.75, bmpinfo4_5_2.bmHeight*0.75,
					&dcmem4_5_2, 0, 0, bmpinfo4_5_2.bmWidth, bmpinfo4_5_2.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("��õ�� ����"));
				dc.TextOut(250, 400, Chuncheonstr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[3].bmWidth*0.4, Hanul_Bmpinfo[3].bmHeight*0.4,
					&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("������ ������"));
				dc.TextOut(250, 550, Gangneungstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[9].bmWidth*0.4, Hanul_Bmpinfo[9].bmHeight*0.4,
					&dcmem[9], 0, 0, Hanul_Bmpinfo[9].bmWidth, Hanul_Bmpinfo[9].bmHeight, SRCCOPY); //���� ������
				CString Malstr = _T(" ��õ�� ���� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Chuncheonstr[5] + _T(" ���糯��: ") + se_hanul[3] + _T(" ������ ������ - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Gangneungstr[5] + _T(" ���糯��: ") + se_hanul[9];
				m_static->SetWindowTextA(Malstr);
			}
			//���� ����� ��ȭ��
			else if (chungnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_6_2.bmWidth*0.75, bmpinfo4_6_2.bmHeight*0.75,
					&dcmem4_6_2, 0, 0, bmpinfo4_6_2.bmWidth, bmpinfo4_6_2.bmHeight, SRCCOPY);
				dc.TextOut(250, 300, _T("���� ����� ��ȭ��"));
				dc.TextOut(300, 400, Daejeonstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[0].bmWidth*0.4, Hanul_Bmpinfo[0].bmHeight*0.4,
					&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY);
				CString Malstr = _T(" ���� ����� ��ȭ�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Daejeonstr[5] + _T(" ���糯��: ") + se_hanul[0];
				m_static->SetWindowTextA(Malstr);
			}
			// û�ֽ� û���� ����1��
			else if (chungbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_7_2.bmWidth*0.75, bmpinfo4_7_2.bmHeight*0.75,
					&dcmem4_7_2, 0, 0, bmpinfo4_7_2.bmWidth, bmpinfo4_7_2.bmHeight, SRCCOPY);
				dc.TextOut(150, 300, _T("û�ֽ� û���� ����1��"));
				dc.TextOut(200, 400, Cheongjustr[5]);
				dc.StretchBlt(200, 350, Hanul_Bmpinfo[4].bmWidth*0.4, Hanul_Bmpinfo[4].bmHeight*0.4,
					&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
				CString Malstr = _T(" û�ֽ� û���� ����1�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Cheongjustr[5] + _T(" ���糯��: ") + se_hanul[4];
				m_static->SetWindowTextA(Malstr);
			}
			//������ ������
			else if (jeonnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_8_2.bmWidth*0.75, bmpinfo4_8_2.bmHeight*0.75,
					&dcmem4_8_2, 0, 0, bmpinfo4_8_2.bmWidth, bmpinfo4_8_2.bmHeight, SRCCOPY);
				dc.TextOut(250, 300, _T("������ ������"));
				dc.TextOut(300, 400, Yeosustr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[7].bmWidth*0.4, Hanul_Bmpinfo[7].bmHeight*0.4,
					&dcmem[7], 0, 0, Hanul_Bmpinfo[7].bmWidth, Hanul_Bmpinfo[7].bmHeight, SRCCOPY);
				CString Malstr = _T(" ������ ������ - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Yeosustr[5] + _T(" ���糯��: ") + se_hanul[7];
				m_static->SetWindowTextA(Malstr);
			}
			//������ �ݾ�1��
			else if (jeonbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_9_2.bmWidth*0.75, bmpinfo4_9_2.bmHeight*0.75,
					&dcmem4_9_2, 0, 0, bmpinfo4_9_2.bmWidth, bmpinfo4_9_2.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("���ֽ� ������ �ݾ�1��"));
				dc.TextOut(250, 400, Jeonjustr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[5].bmWidth*0.4, Hanul_Bmpinfo[5].bmHeight*0.4,
					&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("���ֱ����� ���� ���嵿"));
				dc.TextOut(250, 550, Gwangjustr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[6].bmWidth*0.4, Hanul_Bmpinfo[6].bmHeight*0.4,
					&dcmem[6], 0, 0, Hanul_Bmpinfo[6].bmWidth, Hanul_Bmpinfo[6].bmHeight, SRCCOPY); //����
				CString Malstr = _T(" ���ֽ� ������ �ݾ�1�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Jeonjustr[5] + _T(" ���糯��: ") + se_hanul[5] + _T(" ���ֱ����� ���� ���嵿 - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Gwangjustr[5] + _T(" ���糯��: ") + se_hanul[6];
				m_static->SetWindowTextA(Malstr);
			}
			//â���� ���ر� ��ȭ��
			else if (gyeongnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_10_2.bmWidth*0.75, bmpinfo4_10_2.bmHeight*0.75,
					&dcmem4_10_2, 0, 0, bmpinfo4_10_2.bmWidth, bmpinfo4_10_2.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("â���� ���ر� ��ȭ��"));
				dc.TextOut(250, 400, Changwonstr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[12].bmWidth*0.4, Hanul_Bmpinfo[12].bmHeight*0.4,
					&dcmem[12], 0, 0, Hanul_Bmpinfo[12].bmWidth, Hanul_Bmpinfo[12].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("�λ� ������ ���� ��9��"));
				dc.TextOut(250, 550, Busanstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[13].bmWidth*0.4, Hanul_Bmpinfo[13].bmHeight*0.4,
					&dcmem[13], 0, 0, Hanul_Bmpinfo[13].bmWidth, Hanul_Bmpinfo[13].bmHeight, SRCCOPY); // �λ�
				CString Malstr = _T(" â���� ���ر� ��ȭ�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Changwonstr[5] + _T(" ���糯��: ") + se_hanul[12] + _T(" �λ� ������ ���� ��9�� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Busanstr[5] + _T(" ���糯��: ") + se_hanul[13];
				m_static->SetWindowTextA(Malstr);
			}
			//�뱸 ���� ���̵�
			else if (gyeongbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_11_2.bmWidth*0.75, bmpinfo4_11_2.bmHeight*0.75,
					&dcmem4_11_2, 0, 0, bmpinfo4_11_2.bmWidth, bmpinfo4_11_2.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("�뱸 ���� ���̵�"));
				dc.TextOut(250, 400, Daegustr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[10].bmWidth*0.4, Hanul_Bmpinfo[10].bmHeight*0.4,
					&dcmem[10], 0, 0, Hanul_Bmpinfo[10].bmWidth, Hanul_Bmpinfo[10].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("��� ���� �޵�"));
				dc.TextOut(250, 550, Ulsanstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[11].bmWidth*0.4, Hanul_Bmpinfo[11].bmHeight*0.4,
					&dcmem[11], 0, 0, Hanul_Bmpinfo[11].bmWidth, Hanul_Bmpinfo[11].bmHeight, SRCCOPY);
				CString Malstr = _T(" �뱸 ���� ���̵� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Daegustr[5] + _T(" ���糯��: ") + se_hanul[10] + _T(" ��� ���� �޵� - ");
				Malstr = Malstr + _T(" ���� �µ�: ") + Ulsanstr[5] + _T(" ���糯��: ") + se_hanul[11];
				m_static->SetWindowTextA(Malstr);
			}
			else
			{
			
				dc.StretchBlt(0, 0, bmpinfo4_2.bmWidth*0.75, bmpinfo4_2.bmHeight*0.75,
					&dcmem4_2, 0, 0, bmpinfo4_2.bmWidth, bmpinfo4_2.bmHeight, SRCCOPY);
			}

			wait(500);

		}
		return;
	}
	//�ְ���
	else if (choose1) {

		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		dc.SetBkMode(TRANSPARENT);   //����� ����

		// ��Ʈ�� ���ҽ��� �ε��� �� ũ�� ������ ��´�.
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP2);
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);

		// �޸� DC�� ���� �� ��Ʈ���� ������ �ִ´�.
		CDC dcmem;
		dcmem.CreateCompatibleDC(&dc);
		dcmem.SelectObject(&bitmap);

		CBitmap bitmap_0;
		bitmap_0.LoadBitmap(IDB_BITMAP1);
		BITMAP bmpinfo_0;
		bitmap_0.GetBitmap(&bmpinfo_0);

		// �޸� DC�� ���� �� ��Ʈ���� ������ �ִ´�.
		CDC dcmem_0;
		dcmem_0.CreateCompatibleDC(&dc);
		dcmem_0.SelectObject(&bitmap_0);
		//------------------------------���׸���-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CFont font;
		font.CreateFont(35,     // ���ڳ���
			15,                     // ���ڳʺ�
			0,                      // ��°���
			0,                      // ���� �������ǰ���
			FW_HEAVY,               // ���ڱ���
			FALSE,                  // Italic ���뿩��
			FALSE,                  // �������뿩��
			FALSE,                  // ��Ҽ����뿩��
			DEFAULT_CHARSET,        // ���ڼ�����
			OUT_DEFAULT_PRECIS,     // ������е�
			CLIP_DEFAULT_PRECIS,    // Ŭ�������е�
			DEFAULT_QUALITY,        // ��¹���ǰ��
			DEFAULT_PITCH,          // �۲�Pitch
			_T("���� ���")         // �۲�
		);

		dc.SelectObject(&font);
		dc.SetTextColor(RGB(255, 255, 255));
		//-------------------------------��ǳ�� �ֱ�---
		CString Malstr = _T("���� �ְ� ����� �˷��帮�ڽ��ϴ�.");
		m_static->SetWindowTextA(Malstr);
		//---------------------------------------------
		for (int i = 0; ; i++)
		{
			if (stop1)
			{
				break;
			}

			dc.StretchBlt(0, 0, bmpinfo.bmWidth*0.75, bmpinfo.bmHeight*0.75,
				&dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			//15/20
			//����
			dc.TextOut(520, 350, Daejeonstr[6]);
			//����
			dc.TextOut(553, 237, Seoulstr[6]);
			//��õ
			dc.TextOut(400, 255, Incheonstr[6]);
			//��õ
			dc.TextOut(540, 175, Chuncheonstr[6]);
			//û��
			dc.TextOut(570, 295, Cheongjustr[6]);
			//����
			dc.TextOut(480, 415, Jeonjustr[6]);
			//����
			dc.TextOut(430, 475, Gwangjustr[6]);
			//����
			dc.TextOut(510, 540, Yeosustr[6]);
			//����
			dc.TextOut(390, 660, Jejustr[6]);
			//����
			dc.TextOut(705, 215, Gangneungstr[6]);
			//�뱸
			dc.TextOut(690, 347, Daegustr[6]);
			//���
			dc.TextOut(805, 400, Ulsanstr[6]);
			//â��
			dc.TextOut(645, 450, Changwonstr[6]);
			//�λ�
			dc.TextOut(740, 500, Busanstr[6]);

			dc.TextOut(73500, 50000, Busanstr[6]);

			wait(500);

			if (stop1)
			{
				break;
			}

			dc.StretchBlt(0, 0, bmpinfo_0.bmWidth*0.75, bmpinfo_0.bmHeight*0.75,
				&dcmem_0, 0, 0, bmpinfo_0.bmWidth, bmpinfo_0.bmHeight, SRCCOPY);

			//����
			dc.TextOut(520, 350, Daejeonstr[6]);
			//����
			dc.TextOut(553, 237, Seoulstr[6]);
			//��õ
			dc.TextOut(400, 255, Incheonstr[6]);
			//��õ
			dc.TextOut(540, 175, Chuncheonstr[6]);
			//û��
			dc.TextOut(570, 295, Cheongjustr[6]);
			//����
			dc.TextOut(480, 415, Jeonjustr[6]);
			//����
			dc.TextOut(430, 475, Gwangjustr[6]);
			//����
			dc.TextOut(510, 540, Yeosustr[6]);
			//����
			dc.TextOut(390, 660, Jejustr[6]);
			//����
			dc.TextOut(705, 215, Gangneungstr[6]);
			//�뱸
			dc.TextOut(690, 347, Daegustr[6]);
			//���
			dc.TextOut(805, 400, Ulsanstr[6]);
			//â��
			dc.TextOut(645, 450, Changwonstr[6]);
			//�λ�
			dc.TextOut(740, 500, Busanstr[6]);

			dc.TextOut(73500, 50000, Busanstr[6]);

			wait(500);
		}
		return;
	}	//�������
	//�������
	else if (choose2) {
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		dc.SetBkMode(TRANSPARENT);   //����� ����
		CFont font;

		CBitmap bitmap3;
		bitmap3.LoadBitmap(IDB_BITMAP4);
		BITMAP bmpinfo3;
		bitmap3.GetBitmap(&bmpinfo3);

		CDC dcmem3;
		dcmem3.CreateCompatibleDC(&dc);
		dcmem3.SelectObject(&bitmap3);
		CBitmap bitmap3_0;
		bitmap3_0.LoadBitmap(IDB_BITMAP3);
		BITMAP bmpinfo3_0;
		bitmap3_0.GetBitmap(&bmpinfo3_0);

		CDC dcmem3_0;
		dcmem3_0.CreateCompatibleDC(&dc);
		dcmem3_0.SelectObject(&bitmap3_0);
		
		//------------------------------���׸���-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		font.CreateFont(35,     // ���ڳ���
			15,                     // ���ڳʺ�
			0,                      // ��°���
			0,                      // ���� �������ǰ���
			FW_HEAVY,               // ���ڱ���
			FALSE,                  // Italic ���뿩��
			FALSE,                  // �������뿩��
			FALSE,                  // ��Ҽ����뿩��
			DEFAULT_CHARSET,        // ���ڼ�����
			OUT_DEFAULT_PRECIS,     // ������е�
			CLIP_DEFAULT_PRECIS,    // Ŭ�������е�
			DEFAULT_QUALITY,        // ��¹���ǰ��
			DEFAULT_PITCH,          // �۲�Pitch
			_T("���� ���")         // �۲�
		);
		dc.SelectObject(&font);
		dc.SetTextColor(RGB(255, 255, 255));
		//-------------------------------��ǳ�� �ֱ�---
		CString Malstr = _T("���� ���� ����� �˷��帮�ڽ��ϴ�.");
		m_static->SetWindowTextA(Malstr);
		//---------------------------------------------
		for (int i = 0; ; i++)
		{
			if (stop2)
			{
				break;
			}

			dc.StretchBlt(0, 0, bmpinfo3.bmWidth*0.75, bmpinfo3.bmHeight*0.75,
				&dcmem3, 0, 0, bmpinfo3.bmWidth, bmpinfo3.bmHeight, SRCCOPY);

			//����
			dc.TextOut(510, 350, Daejeonstr[7]);
			//����
			dc.TextOut(548, 237, Seoulstr[7]);
			//��õ
			dc.TextOut(390, 265, Incheonstr[7]);
			//��õ
			dc.TextOut(535, 175, Chuncheonstr[7]);
			//û��
			dc.TextOut(565, 295, Cheongjustr[7]);
			//����
			dc.TextOut(475, 415, Jeonjustr[7]);
			//����
			dc.TextOut(425, 475, Gwangjustr[7]);
			//����
			dc.TextOut(510, 540, Yeosustr[7]);
			//����
			dc.TextOut(395, 650, Jejustr[7]);
			//����
			dc.TextOut(700, 218, Gangneungstr[7]);
			//�뱸
			dc.TextOut(675, 347, Daegustr[7]);
			//���
			dc.TextOut(800, 400, Ulsanstr[7]);
			//â��
			dc.TextOut(640, 447, Changwonstr[7]);
			//�λ�
			dc.TextOut(730, 500, Busanstr[7]);

			dc.TextOut(73500, 50000, Busanstr[6]);

			wait(500);

			if (stop2)
			{
				break;
			}

			dc.StretchBlt(0, 0, bmpinfo3_0.bmWidth*0.75, bmpinfo3_0.bmHeight*0.75,
				&dcmem3_0, 0, 0, bmpinfo3_0.bmWidth, bmpinfo3_0.bmHeight, SRCCOPY);

			//����
			dc.TextOut(510, 350, Daejeonstr[7]);
			//����
			dc.TextOut(548, 237, Seoulstr[7]);
			//��õ
			dc.TextOut(390, 265, Incheonstr[7]);
			//��õ
			dc.TextOut(535, 175, Chuncheonstr[7]);
			//û��
			dc.TextOut(565, 295, Cheongjustr[7]);
			//����
			dc.TextOut(475, 415, Jeonjustr[7]);
			//����
			dc.TextOut(425, 475, Gwangjustr[7]);
			//����
			dc.TextOut(510, 540, Yeosustr[7]);
			//����
			dc.TextOut(395, 650, Jejustr[7]);
			//����
			dc.TextOut(700, 218, Gangneungstr[7]);
			//�뱸
			dc.TextOut(675, 347, Daegustr[7]);
			//���
			dc.TextOut(800, 400, Ulsanstr[7]);
			//â��
			dc.TextOut(640, 447, Changwonstr[7]);
			//�λ�
			dc.TextOut(730, 500, Busanstr[7]);

			dc.TextOut(73500, 50000, Busanstr[6]);

			wait(500);
		}
		return;
	}	//�����ϴ�
	//���ϳ���
	else if (choose3) {

		int sel_hanul[14] = { 0 };      //�̸�Ƽ�� ���� ����   
		for (int i = 0; i < 14; i++)   //�̸�Ƽ�� ���� ����� ���� ����ġ��
		{
			STR_SWITCH(Hanul[i])      //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
				CASE(_T("1"))
				sel_hanul[i] = 367;
			BREAK
				CASE(_T("2"))
				sel_hanul[i] = 365;
			BREAK
				CASE(_T("3"))
				sel_hanul[i] = 366;
			BREAK
				CASE(_T("4"))
				sel_hanul[i] = 368;
			BREAK
				END_SWITCH;
		}

		//-------------------------------��ǳ�� �ֱ�---
		CString Malstr = _T("���� �ϴû��¸� �˷��帮�ڽ��ϴ�.");
		m_static->SetWindowTextA(Malstr);
		//---------------------------------------------

		CPaintDC dc(this);
		dc.SetBkMode(TRANSPARENT);   //����� ����

		//------------------------------���׸���-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		CFont font;
		CBitmap Hanul_Bitmap[14];   //�̸�Ƽ�� ǥ�� ��Ʈ�� ��������
		BITMAP Hanul_Bmpinfo[14];   //�̸�Ƽ�� ǥ�� ��Ʈ�� ��������
		CDC dcmem[14];            
		//------------------------------------------------------------
		for (int i = 0; i < 14; i++)
		{
			Hanul_Bitmap[i].LoadBitmap(sel_hanul[i]);
			Hanul_Bitmap[i].GetBitmap(&Hanul_Bmpinfo[i]);
			dcmem[i].CreateCompatibleDC(&dc);			//�޸𸮵���̽����ؽ�Ʈ ����
			dcmem[i].SelectObject(&Hanul_Bitmap[i]);   //��Ʈ���� �޸� ����̽� ���ؽ�Ʈ�� ����
		}
		//------------------------------------------------------------


		CBitmap bitmap1_0;
		bitmap1_0.LoadBitmap(IDB_BITMAP5);
		BITMAP bmpinfo1_0;
		bitmap1_0.GetBitmap(&bmpinfo1_0);

		CDC dcmem1_0;
		dcmem1_0.CreateCompatibleDC(&dc);
		dcmem1_0.SelectObject(&bitmap1_0);
		//--------------------��ǳ������ֱ�---------------
		CBrush brush1(RGB(120, 120, 120));
		dcmem1_0.SelectObject(&brush1);
		dcmem1_0.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem1_0.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem1_0.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		CBitmap bitmap_1;
		bitmap_1.LoadBitmap(IDB_BITMAP6);
		BITMAP bmpinfo_1;
		bitmap_1.GetBitmap(&bmpinfo_1);

		CDC dcmem_1;
		dcmem_1.CreateCompatibleDC(&dc);
		dcmem_1.SelectObject(&bitmap_1);

		//--------------------��ǳ������ֱ�---------------
		dcmem_1.SelectObject(&brush1);
		dcmem_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		for (int i = 0; ; i++)
		{
			if (stop3)
				break;
		
			dc.StretchBlt(0, 0, bmpinfo_1.bmWidth*0.75, bmpinfo_1.bmHeight*0.75,
				&dcmem_1, 0, 0, bmpinfo_1.bmWidth, bmpinfo_1.bmHeight, SRCCOPY);

			//����
			dc.StretchBlt(467, 355, Hanul_Bmpinfo[0].bmWidth*0.4, Hanul_Bmpinfo[0].bmHeight*0.4,
				&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(475, 220, Hanul_Bmpinfo[1].bmWidth*0.4, Hanul_Bmpinfo[1].bmHeight*0.4,
				&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
			//��õ
			dc.StretchBlt(375, 230, Hanul_Bmpinfo[2].bmWidth*0.4, Hanul_Bmpinfo[2].bmHeight*0.4,
				&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
			//��õ
			dc.StretchBlt(529, 132, Hanul_Bmpinfo[3].bmWidth*0.4, Hanul_Bmpinfo[3].bmHeight*0.4,
				&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
			//û��
			dc.StretchBlt(566, 325, Hanul_Bmpinfo[4].bmWidth*0.4, Hanul_Bmpinfo[4].bmHeight*0.4,
				&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(447, 455, Hanul_Bmpinfo[5].bmWidth*0.4, Hanul_Bmpinfo[5].bmHeight*0.4,
				&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(345, 505, Hanul_Bmpinfo[6].bmWidth*0.4, Hanul_Bmpinfo[6].bmHeight*0.4,
				&dcmem[6], 0, 0, Hanul_Bmpinfo[6].bmWidth, Hanul_Bmpinfo[6].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(483, 560, Hanul_Bmpinfo[7].bmWidth*0.4, Hanul_Bmpinfo[7].bmHeight*0.4,
				&dcmem[7], 0, 0, Hanul_Bmpinfo[7].bmWidth, Hanul_Bmpinfo[7].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(300, 643, Hanul_Bmpinfo[8].bmWidth*0.4, Hanul_Bmpinfo[8].bmHeight*0.4,
				&dcmem[8], 0, 0, Hanul_Bmpinfo[8].bmWidth, Hanul_Bmpinfo[8].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(635, 195, Hanul_Bmpinfo[9].bmWidth*0.4, Hanul_Bmpinfo[9].bmHeight*0.4,
				&dcmem[9], 0, 0, Hanul_Bmpinfo[9].bmWidth, Hanul_Bmpinfo[9].bmHeight, SRCCOPY);
			//�뱸
			dc.StretchBlt(668, 325, Hanul_Bmpinfo[10].bmWidth*0.4, Hanul_Bmpinfo[10].bmHeight*0.4,
				&dcmem[10], 0, 0, Hanul_Bmpinfo[10].bmWidth, Hanul_Bmpinfo[10].bmHeight, SRCCOPY);
			//���
			dc.StretchBlt(690, 424, Hanul_Bmpinfo[11].bmWidth*0.4, Hanul_Bmpinfo[11].bmHeight*0.4,
				&dcmem[11], 0, 0, Hanul_Bmpinfo[11].bmWidth, Hanul_Bmpinfo[11].bmHeight, SRCCOPY);
			//â��
			dc.StretchBlt(566, 447, Hanul_Bmpinfo[12].bmWidth*0.4, Hanul_Bmpinfo[12].bmHeight*0.4,
				&dcmem[12], 0, 0, Hanul_Bmpinfo[12].bmWidth, Hanul_Bmpinfo[12].bmHeight, SRCCOPY);
			//�λ�
			dc.StretchBlt(670, 533, Hanul_Bmpinfo[13].bmWidth*0.4, Hanul_Bmpinfo[13].bmHeight*0.4,
				&dcmem[13], 0, 0, Hanul_Bmpinfo[13].bmWidth, Hanul_Bmpinfo[13].bmHeight, SRCCOPY);

			wait(500);
			if (stop3)
			{
				break;
			}
			dc.StretchBlt(0, 0, bmpinfo1_0.bmWidth*0.75, bmpinfo1_0.bmHeight*0.75,
				&dcmem1_0, 0, 0, bmpinfo1_0.bmWidth, bmpinfo1_0.bmHeight, SRCCOPY);

			//����
			dc.StretchBlt(467, 355, Hanul_Bmpinfo[0].bmWidth*0.4, Hanul_Bmpinfo[0].bmHeight*0.4,
				&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(475, 220, Hanul_Bmpinfo[1].bmWidth*0.4, Hanul_Bmpinfo[1].bmHeight*0.4,
				&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
			//��õ
			dc.StretchBlt(375, 230, Hanul_Bmpinfo[2].bmWidth*0.4, Hanul_Bmpinfo[2].bmHeight*0.4,
				&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
			//��õ
			dc.StretchBlt(529, 132, Hanul_Bmpinfo[3].bmWidth*0.4, Hanul_Bmpinfo[3].bmHeight*0.4,
				&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
			//û��
			dc.StretchBlt(566, 325, Hanul_Bmpinfo[4].bmWidth*0.4, Hanul_Bmpinfo[4].bmHeight*0.4,
				&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(447, 455, Hanul_Bmpinfo[5].bmWidth*0.4, Hanul_Bmpinfo[5].bmHeight*0.4,
				&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(345, 505, Hanul_Bmpinfo[6].bmWidth*0.4, Hanul_Bmpinfo[6].bmHeight*0.4,
				&dcmem[6], 0, 0, Hanul_Bmpinfo[6].bmWidth, Hanul_Bmpinfo[6].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(483, 560, Hanul_Bmpinfo[7].bmWidth*0.4, Hanul_Bmpinfo[7].bmHeight*0.4,
				&dcmem[7], 0, 0, Hanul_Bmpinfo[7].bmWidth, Hanul_Bmpinfo[7].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(300, 643, Hanul_Bmpinfo[8].bmWidth*0.4, Hanul_Bmpinfo[8].bmHeight*0.4,
				&dcmem[8], 0, 0, Hanul_Bmpinfo[8].bmWidth, Hanul_Bmpinfo[8].bmHeight, SRCCOPY);
			//����
			dc.StretchBlt(635, 195, Hanul_Bmpinfo[9].bmWidth*0.4, Hanul_Bmpinfo[9].bmHeight*0.4,
				&dcmem[9], 0, 0, Hanul_Bmpinfo[9].bmWidth, Hanul_Bmpinfo[9].bmHeight, SRCCOPY);
			//�뱸
			dc.StretchBlt(668, 325, Hanul_Bmpinfo[10].bmWidth*0.4, Hanul_Bmpinfo[10].bmHeight*0.4,
				&dcmem[10], 0, 0, Hanul_Bmpinfo[10].bmWidth, Hanul_Bmpinfo[10].bmHeight, SRCCOPY);
			//���
			dc.StretchBlt(690, 424, Hanul_Bmpinfo[11].bmWidth*0.4, Hanul_Bmpinfo[11].bmHeight*0.4,
				&dcmem[11], 0, 0, Hanul_Bmpinfo[11].bmWidth, Hanul_Bmpinfo[11].bmHeight, SRCCOPY);
			//â��
			dc.StretchBlt(566, 447, Hanul_Bmpinfo[12].bmWidth*0.4, Hanul_Bmpinfo[12].bmHeight*0.4,
				&dcmem[12], 0, 0, Hanul_Bmpinfo[12].bmWidth, Hanul_Bmpinfo[12].bmHeight, SRCCOPY);
			//�λ�
			dc.StretchBlt(670, 533, Hanul_Bmpinfo[13].bmWidth*0.4, Hanul_Bmpinfo[13].bmHeight*0.4,
				&dcmem[13], 0, 0, Hanul_Bmpinfo[13].bmWidth, Hanul_Bmpinfo[13].bmHeight, SRCCOPY);
			wait(500);
		}
		return;
	}	//�ְ�����
	//�ְ����
	else if (choose4){

		int sel_hanul[6] = { 0 };      //�̸�Ƽ�� ���� ����   
		for (int i = 0; i < 6; i++)   //�̸�Ƽ�� ���� ����� ���� ����ġ��
		{
			STR_SWITCH(WeekHanul[i])      //�ϴû����ڵ� 1 : ���� 2 : �������� 3 : �������� 4 : �帲
				CASE(_T("����"))
				sel_hanul[i] = 367;
			BREAK
				CASE(_T("��������"))
				sel_hanul[i] = 365;
			BREAK
				CASE(_T("��������"))
				sel_hanul[i] = 366;
			BREAK
				CASE(_T("�帲"))
				sel_hanul[i] = 368;
			BREAK
				DEFAULT
				sel_hanul[i] = 368;
			BREAK
				END_SWITCH;
		}
		//---------------------------------------------------------------------------���� ã�Ƴ���

		CString select_day[14] = { _T("��"),_T("ȭ"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),
			_T("��"),_T("ȭ"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��") };


		for (int i = 0; i < 14; i++)   //���ϰ��� ����� ���� ����ġ��
		{
			STR_SWITCH(Weekstr[1])       //����,��⵵ ���� �߱⿹�� - 2018�� 12�� 12�� (��)���� 18:00 ��ǥ
				CASE(_T("(��)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 1];
			BREAK
				CASE(_T("(ȭ)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 2];
			BREAK
				CASE(_T("(��)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 3];
			BREAK
				CASE(_T("(��)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 4];
			BREAK
				CASE(_T("(��)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 5];
			BREAK
				CASE(_T("(��)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 6];
			BREAK
				CASE(_T("(��)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 7];
			BREAK
				END_SWITCH;
		}
		//----------------------------------------------------------------------------------------
		//----------------------------------------------------------------��¥ ���ϱ�-------------
		int select_date = _ttoi(Weekstr[0]);
		for (int i = 0; i < 6; i++)
			Weekdate[i].Format(_T("%d"), select_date + i);
		//----------------------------------------------------------------------------------------
		

		//-------------------------------��ǳ�� �ֱ�---
		CString Malstr = _T("�ְ� ����Ȳ�� �˷��帮�ڽ��ϴ�.");
		m_static->SetWindowTextA(Malstr);
		//---------------------------------------------

		CPaintDC dc(this);
		dc.SetBkMode(TRANSPARENT);   //����� ����

		//------------------------------���׸���-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		CBitmap Hanul_Bitmap[6];   //�̸�Ƽ�� ǥ�� ��Ʈ�� ��������
		BITMAP Hanul_Bmpinfo[6];   //�̸�Ƽ�� ǥ�� ��Ʈ�� ��������
		CDC dcmem[6];
		//------------------------------------------------------------
		for (int i = 0; i < 6; i++)
		{
			Hanul_Bitmap[i].LoadBitmap(sel_hanul[i]);
			Hanul_Bitmap[i].GetBitmap(&Hanul_Bmpinfo[i]);
			dcmem[i].CreateCompatibleDC(&dc);			//�޸𸮵���̽����ؽ�Ʈ ����
			dcmem[i].SelectObject(&Hanul_Bitmap[i]);   //��Ʈ���� �޸� ����̽� ���ؽ�Ʈ�� ����
		}
		//------------------------------------------------------------


		CBitmap bitmap1_0;
		bitmap1_0.LoadBitmap(IDB_BITMAP13);
		BITMAP bmpinfo1_0;
		bitmap1_0.GetBitmap(&bmpinfo1_0);

		CDC dcmem1_0;
		dcmem1_0.CreateCompatibleDC(&dc);
		dcmem1_0.SelectObject(&bitmap1_0);
		//--------------------��ǳ������ֱ�---------------
		CBrush brush1(RGB(120, 120, 120));
		dcmem1_0.SelectObject(&brush1);
		dcmem1_0.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem1_0.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem1_0.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		CBitmap bitmap_1;
		bitmap_1.LoadBitmap(IDB_BITMAP14);
		BITMAP bmpinfo_1;
		bitmap_1.GetBitmap(&bmpinfo_1);

		CDC dcmem_1;
		dcmem_1.CreateCompatibleDC(&dc);
		dcmem_1.SelectObject(&bitmap_1);

		//--------------------��ǳ������ֱ�---------------
		dcmem_1.SelectObject(&brush1);
		dcmem_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------


		CFont font;
		font.CreateFont(50,     // ���ڳ���
			20,                     // ���ڳʺ�
			0,                      // ��°���
			0,                      // ���� �������ǰ���
			FW_HEAVY,               // ���ڱ���
			FALSE,                  // Italic ���뿩��
			FALSE,                  // �������뿩��
			FALSE,                  // ��Ҽ����뿩��
			DEFAULT_CHARSET,        // ���ڼ�����
			OUT_DEFAULT_PRECIS,     // ������е�
			CLIP_DEFAULT_PRECIS,    // Ŭ�������е�
			DEFAULT_QUALITY,        // ��¹���ǰ��
			DEFAULT_PITCH,          // �۲�Pitch
			_T("���� ���")         // �۲�

		);

		dc.SelectObject(&font);
		dc.SetTextColor(RGB(255, 255, 255));


		//--------------------------------------------------------------------------------------------
		for (int i = 0; ; i++)
		{
			if (stop4)
				break;

			dc.StretchBlt(0, 0, bmpinfo_1.bmWidth*0.75, bmpinfo_1.bmHeight*0.75,
				&dcmem_1, 0, 0, bmpinfo_1.bmWidth, bmpinfo_1.bmHeight, SRCCOPY);

			//-------------------------------------------------------------����ǥ��
			
		 //012345 ������� �ְ���� ĭ ���ʺ��� ������ �ȴ�.

			dc.StretchBlt(131, 350, Hanul_Bmpinfo[0].bmWidth*0.75, Hanul_Bmpinfo[0].bmHeight*0.75,
				&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY);
			dc.StretchBlt(259, 350, Hanul_Bmpinfo[1].bmWidth*0.75, Hanul_Bmpinfo[1].bmHeight*0.75,
				&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
			dc.StretchBlt(391, 350, Hanul_Bmpinfo[2].bmWidth*0.75, Hanul_Bmpinfo[2].bmHeight*0.75,
				&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
			dc.StretchBlt(523, 350, Hanul_Bmpinfo[3].bmWidth*0.75, Hanul_Bmpinfo[3].bmHeight*0.75,
				&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
			dc.StretchBlt(654, 350, Hanul_Bmpinfo[4].bmWidth*0.75, Hanul_Bmpinfo[4].bmHeight*0.75,
				&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
			dc.StretchBlt(783, 350, Hanul_Bmpinfo[5].bmWidth*0.75, Hanul_Bmpinfo[5].bmHeight*0.75,
				&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);

			dc.TextOut(120, 177, Weekday[0]);
			dc.TextOut(245, 177, Weekday[1]);
			dc.TextOut(380, 177, Weekday[2]);
			dc.TextOut(515, 177, Weekday[3]);
			dc.TextOut(647, 177, Weekday[4]);
			dc.TextOut(770, 177, Weekday[5]);

			dc.TextOut(175, 205, Weekdate[0]);
			dc.TextOut(300, 205, Weekdate[1]);
			dc.TextOut(435, 205, Weekdate[2]);
			dc.TextOut(570, 205, Weekdate[3]);
			dc.TextOut(702, 205, Weekdate[4]);
			dc.TextOut(825, 205, Weekdate[5]);

			dc.TextOut(153, 510, WeekHigh[0]);
			dc.TextOut(283, 510, WeekHigh[1]);
			dc.TextOut(415, 510, WeekHigh[2]);
			dc.TextOut(548, 510, WeekHigh[3]);
			dc.TextOut(680, 510, WeekHigh[4]);
			dc.TextOut(809, 510, WeekHigh[5]);

			dc.TextOut(147, 560, WeekLow[0]);
			dc.TextOut(276, 560, WeekLow[1]);
			dc.TextOut(407, 560, WeekLow[2]);
			dc.TextOut(542, 560, WeekLow[3]);
			dc.TextOut(674, 560, WeekLow[4]);
			dc.TextOut(802, 560, WeekLow[5]);

			dc.TextOut(10000, 10000, WeekLow[5]);

			wait(500);

			if (stop4)
			{
				break;
			}

			dc.StretchBlt(0, 0, bmpinfo1_0.bmWidth*0.75, bmpinfo1_0.bmHeight*0.75,
				&dcmem1_0, 0, 0, bmpinfo1_0.bmWidth, bmpinfo1_0.bmHeight, SRCCOPY);

			//012345 ������� �ְ���� ĭ ���ʺ��� ������ �ȴ�.

			dc.StretchBlt(131, 350, Hanul_Bmpinfo[0].bmWidth*0.75, Hanul_Bmpinfo[0].bmHeight*0.75,
				&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY);
			dc.StretchBlt(259, 350, Hanul_Bmpinfo[1].bmWidth*0.75, Hanul_Bmpinfo[1].bmHeight*0.75,
				&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
			dc.StretchBlt(391, 350, Hanul_Bmpinfo[2].bmWidth*0.75, Hanul_Bmpinfo[2].bmHeight*0.75,
				&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
			dc.StretchBlt(523, 350, Hanul_Bmpinfo[3].bmWidth*0.75, Hanul_Bmpinfo[3].bmHeight*0.75,
				&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
			dc.StretchBlt(654, 350, Hanul_Bmpinfo[4].bmWidth*0.75, Hanul_Bmpinfo[4].bmHeight*0.75,
				&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
			dc.StretchBlt(783, 350, Hanul_Bmpinfo[5].bmWidth*0.75, Hanul_Bmpinfo[5].bmHeight*0.75,
				&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);

			dc.TextOut(120, 177, Weekday[0]);
			dc.TextOut(245, 177, Weekday[1]);
			dc.TextOut(380, 177, Weekday[2]);
			dc.TextOut(515, 177, Weekday[3]);
			dc.TextOut(647, 177, Weekday[4]);
			dc.TextOut(770, 177, Weekday[5]);

			dc.TextOut(175, 205, Weekdate[0]);
			dc.TextOut(300, 205, Weekdate[1]);
			dc.TextOut(435, 205, Weekdate[2]);
			dc.TextOut(570, 205, Weekdate[3]);
			dc.TextOut(702, 205, Weekdate[4]);
			dc.TextOut(825, 205, Weekdate[5]);

			dc.TextOut(153, 510, WeekHigh[0]);
			dc.TextOut(283, 510, WeekHigh[1]);
			dc.TextOut(415, 510, WeekHigh[2]);
			dc.TextOut(548, 510, WeekHigh[3]);
			dc.TextOut(680, 510, WeekHigh[4]);
			dc.TextOut(809, 510, WeekHigh[5]);

			dc.TextOut(147, 560, WeekLow[0]);
			dc.TextOut(276, 560, WeekLow[1]);
			dc.TextOut(407, 560, WeekLow[2]);
			dc.TextOut(542, 560, WeekLow[3]);
			dc.TextOut(674, 560, WeekLow[4]);
			dc.TextOut(802, 560, WeekLow[5]);

			dc.TextOut(10000, 10000, WeekLow[5]);

			wait(500);

		}
		return;
	}//�ְ�����


}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_pushButton1.Create(_T("���ü���"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 460, 1800, 530), this, 101);
	m_pushButton2.Create(_T("�ְ���"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 530, 1800, 600), this, 102);
	m_pushButton3.Create(_T("�������"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 600, 1800, 670), this, 103);
	m_pushButton4.Create(_T("���ϳ���"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 670, 1800, 740), this, 104);
	m_pushButton5.Create(_T("�ְ�����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 740, 1800, 810), this, 105); 
	
	m_static = new CStatic;	//���� �ؽ�Ʈ ��Ʈ�� ����
	m_static->Create(_T("Click a button to change my color"), WS_CHILD | WS_VISIBLE | SS_LEFT | WS_DLGFRAME,
		CRect(1438, 0, 1800, 150), this);

	return 0;
}

void CChildView::OnButton1Clicked(void)
{
	choose = TRUE;	//�޴�����
	choose1 = FALSE;
	choose2 = FALSE;
	choose3 = FALSE;
	choose4 = FALSE;
	choose5 = FALSE;
	stop = FALSE;	//�̺�Ʈ�߻�
	stop1 = TRUE;
	stop2 = TRUE;
	stop3 = TRUE;
	stop4 = TRUE;
	Invalidate();
}

void CChildView::OnButton2Clicked()
{	
	choose = FALSE;
	choose1 = TRUE;
	choose2 = FALSE;
	choose3 = FALSE;
	choose4 = FALSE;
	choose5 = FALSE;
	stop = TRUE;
	stop1 = FALSE;
	stop2 = TRUE;
	stop3 = TRUE;
	stop4 = TRUE;
	Invalidate();
}

void CChildView::OnButton3Clicked()
{
	choose = FALSE;
	choose1 = FALSE;
	choose2 = TRUE;
	choose3 = FALSE;
	choose4 = FALSE;
	choose5 = FALSE;
	stop = TRUE;
	stop1 = TRUE;
	stop2 = FALSE;
	stop3 = TRUE;
	stop4 = TRUE;
	Invalidate();
}

void CChildView::OnButton4Clicked()
{
	choose = FALSE;
	choose1 = FALSE;
	choose2 = FALSE;
	choose3 = TRUE;
	choose4 = FALSE;
	choose5 = FALSE;
	stop = TRUE;
	stop1 = TRUE;
	stop2 = TRUE;
	stop3 = FALSE;
	stop4 = TRUE;
	Invalidate();
}

void CChildView::OnButton5Clicked()
{
	choose = FALSE;
	choose1 = FALSE;
	choose2 = FALSE;
	choose3 = FALSE;
	choose4 = TRUE;
	choose5 = FALSE;
	stop = TRUE;
	stop1 = TRUE;
	stop2 = TRUE;
	stop3 = TRUE;
	stop4 = FALSE;
	Invalidate();
}

void CChildView::wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (choose) {
		GetCursorPos(&m_pt);
		ScreenToClient(&m_pt);
		if (m_r1.PtInRect(m_pt)) { // PtlnRect() �� ������ ��ġȮ�� 
			seoul = TRUE;

		}
		else if (m_r2.PtInRect(m_pt)) {
			gyeonggi = TRUE;
		}
		else if (m_r3.PtInRect(m_pt)) {
			gangwon = TRUE;
		}

		else if (m_r4.PtInRect(m_pt)) {
			chungnam = TRUE;
		}
		else if (m_r5.PtInRect(m_pt)) {
			chungbuk = TRUE;
		}
		else if (m_r6.PtInRect(m_pt)) {
			jeonnam = TRUE;
		}
		else if (m_r7.PtInRect(m_pt)) {
			jeonbuk = TRUE;
		}
		else if (m_r8.PtInRect(m_pt)) {
			gyeongnam = TRUE;
		}
		else if (m_r9.PtInRect(m_pt)) {
			gyeongbuk = TRUE;
		}
		else {
			seoul = 0;
			gyeonggi = 0;
			gangwon = 0;
			chungnam = 0;
			chungbuk = 0;
			jeonnam = 0;
			jeonbuk = 0;
			gyeongnam = 0;
			gyeongbuk = 0;
		}
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (seoul) {
		seoul1 = TRUE;
		Invalidate();
	}
	else if (gyeonggi)
	{
		gyeonggi1 = TRUE;
		Invalidate();
	}
	else if (gangwon)
	{
		gangwon1 = TRUE;
		Invalidate();
	}
	else if (chungnam)
	{
		chungnam1 = TRUE;
		Invalidate();
	}
	else if (chungbuk)
	{
		chungbuk1 = TRUE;
		Invalidate();
	}
	else if (jeonnam)
	{
		jeonnam1 = TRUE;
		Invalidate();
	}
	else if (jeonbuk)
	{
		jeonbuk1 = TRUE;
		Invalidate();
	}
	else if (gyeongnam)
	{
		gyeongnam1 = TRUE;
		Invalidate();
	}
	else if (gyeongbuk)
	{
		gyeongbuk1 = TRUE;
		Invalidate();
	}
	else {
		seoul1 = false;
		gyeonggi1 = FALSE;
		gangwon1 = FALSE;
		chungnam1 = FALSE;
		chungbuk1 = FALSE;
		jeonnam1 = FALSE;
		jeonbuk1 = FALSE;
		gyeongnam1 = FALSE;
		gyeongbuk1 = FALSE;
		Invalidate();
	}
	CWnd::OnLButtonDblClk(nFlags, point);

}



