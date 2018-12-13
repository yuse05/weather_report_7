// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include "Markup.h"			//CMarkup xml parser 이용
#include <Urlmon.h>			//RSS 파일 받아오기
#pragma comment(lib, "urlmon.lib")

//----------------------------------------------------------
#define STR_SWITCH(x) {CString switchval(x); if(false){;}
#define CASE(y) else if(switchval == y) {
#define DEFAULT else if(true) {
#define BREAK }
#define END_SWITCH }
//--------------------------------사용자지정 switch문 사용 -


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CButton m_pushButton1;		//도시선택 버튼 컨트롤러 생성
CButton m_pushButton2;		//최고기온 버튼 컨트롤러 생성
CButton m_pushButton3;		//최저기온 버튼 컨트롤러 생성
CButton m_pushButton4;		//내일하늘 버튼 컨트롤러 생성
CButton m_pushButton5;		//주간날씨 버튼 컨트롤러 생성

BOOL   choose = FALSE;		//도시선택 선택변수
BOOL   choose1 = FALSE;		//최고기온 선택변수
BOOL   choose2 = FALSE;		//최저기온 선택변수
BOOL   choose3 = FALSE;		//내일하늘 선택변수
BOOL   choose4 = FALSE;		//주간날씨 선택변수
BOOL   choose5 = TRUE;	    //첫 화면 선택변수
BOOL   stop = FALSE;  		//도시선택 이벤트변수
BOOL   stop1 = FALSE;		//최고기온 이벤트변수
BOOL   stop2 = FALSE;		//최저기온 이벤트변수
BOOL   stop3 = FALSE;		//내일하늘 이벤트변수
BOOL   stop4 = FALSE;		//주간날씨 이벤트변수


BOOL   seoul = FALSE;
BOOL   seoul1 = FALSE;     // 서울지역 정보 이벤트 변수
BOOL   gyeonggi = FALSE;
BOOL   gyeonggi1 = FALSE;  // 경기도 지역 정보 이벤트 변수
BOOL   gangwon = FALSE;
BOOL   gangwon1 = FALSE;   // 강원도 지역 정보 이벤트 변수 
BOOL   chungnam = FALSE;
BOOL   chungnam1 = FALSE;  // 충청남도 지역 정보 이벤트 변수
BOOL   chungbuk = FALSE;
BOOL   chungbuk1 = FALSE;  // 충청북도 지역 정보 이벤트 변수
BOOL   jeonnam = FALSE;
BOOL   jeonnam1 = FALSE;   // 전라남도 지역 정보 이벤트 변수
BOOL   jeonbuk = FALSE;
BOOL   jeonbuk1 = FALSE;   // 전라북도 지역 정보 이벤트 변수
BOOL   gyeongnam = FALSE;
BOOL   gyeongnam1 = FALSE; // 경상남도 지역 정보 이벤트 변수
BOOL   gyeongbuk = FALSE;
BOOL   gyeongbuk1 = FALSE; // 경상북도 지역 정보 이벤트 변수


CString Daejeonstr[10];		//대전광역시 대덕구 대화동 기상예보
CString Jejustr[10];		//제주특별자치도 제주시 노형동 기상정보
CString Yeosustr[10];		//전라남도 여수시 광림동 기상정보
CString Incheonstr[10];		//인천광역시 중구 도원동 기상정보
CString Ulsanstr[10];		//울산광역시 남구 달동 기상정보
CString Seoulstr[10];		//서울특별시 강남구 개포1동 기상정보
CString Busanstr[10];		//부산광역시 연제구 연산제9동 기상정보
CString Daegustr[10];		//대구광역시 동구 방촌동 기상정보
CString Gwangjustr[10];		//광주광역시 동구 충장동 기상정보
CString Chuncheonstr[10];        //강원도 춘천시 교동 기상정보
CString Gangneungstr[10];	//강원도 강릉시 강남동 기상정보
CString Cheongjustr[10];	         //충청북도 청주시청원구 내덕1동 기상정보
CString Changwonstr[10];	         //경상남도 창원시 진해구 경화동 기상정보
CString Jeonjustr[10];	         //전라북도 전주시 덕친구 금암1동 기상정보

CString Hanul[14];		//내일하늘정보
CString Weekstr[6];		//중기예보정보
CString WeekHanul[6];		//주간하늘정보
CString WeekHigh[6];		//주간최고기온
CString WeekLow[6];		//주간최저기온
CString Weekday[6];		//주간요일
CString Weekdate[6];		//주간날짜


CChildView::CChildView()	//생성자로 RSS정보 갱신
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

UINT one_minute_thread(LPVOID arg)	//1분마다 갱신 작업자스레드
{
	while (1)
	{
		CChildView();
		Sleep(60000);		//msec단위, 1분마다
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
	Daejeonstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 대전광역시 대덕구 대화동 도표예보
	xml.FindElem(_T("generator"));
	Daejeonstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Daejeonstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();
	
	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Daejeonstr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Daejeonstr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Daejeonstr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Daejeonstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Daejeonstr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[0] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Daejeonstr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈
	
	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Daejeonstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Daejeonstr[7] = xml.GetData();   //최저온도

	Daejeonstr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Daejeonstr[7].Replace(_T(".0"), _T(""));	//.0 제거코드

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
	Seoulstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 서울특별시 강남구 개포1동 도표예보
	xml.FindElem(_T("generator"));
	Seoulstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Seoulstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();

	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Seoulstr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Seoulstr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Seoulstr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Seoulstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Seoulstr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[1] = xml.GetData();      //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Seoulstr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈
	xml.OutOfElem();
	//-------------------------------------서울 1일차(내일)
	for (int i = 0; i < 8; i++)
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	WeekHigh[0] = xml.GetData();	//최고온도
	Seoulstr[6] = xml.GetData();	//최고온도
	xml.FindElem(_T("tmn"));
	WeekLow[0] = xml.GetData();		//최저온도
	Seoulstr[7] = xml.GetData();	//최저온도
	xml.FindElem(_T("wfKor"));
	WeekHanul[0] = xml.GetData();   //하늘상황
	xml.OutOfElem();
	//-------------------------------------서울 2일차(모레)
	for (int i = 0; i < 4; i++)
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	WeekHigh[1] = xml.GetData();	//최고온도
	xml.FindElem(_T("tmn"));
	WeekLow[1] = xml.GetData();		//최저온도
	xml.FindElem(_T("wfKor"));
	WeekHanul[1] = xml.GetData();   //하늘상황

	Seoulstr[6].Replace(_T(".0"), _T(""));   //.0 제거코드
	Seoulstr[7].Replace(_T(".0"), _T(""));   //.0 제거코드
	WeekHigh[0].Replace(_T(".0"), _T(""));   //.0 제거코드
	WeekLow[0].Replace(_T(".0"), _T(""));   //.0 제거코드
	WeekHigh[1].Replace(_T(".0"), _T(""));   //.0 제거코드
	WeekLow[1].Replace(_T(".0"), _T(""));   //.0 제거코드

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
	Incheonstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 인천광역시 중구 도원동 도표예보
	xml.FindElem(_T("generator"));
	Incheonstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Incheonstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Incheonstr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Incheonstr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Incheonstr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Incheonstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Incheonstr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[2] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Incheonstr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Incheonstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Incheonstr[7] = xml.GetData();   //최저온도

	Incheonstr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Incheonstr[7].Replace(_T(".0"), _T(""));	//.0 제거코드

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
	Chuncheonstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 강원도 춘천시 교동 도표예보
	xml.FindElem(_T("generator"));
	Chuncheonstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Chuncheonstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Chuncheonstr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Chuncheonstr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Chuncheonstr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Chuncheonstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Chuncheonstr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[3] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Chuncheonstr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Chuncheonstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Chuncheonstr[7] = xml.GetData();   //최저온도

	Chuncheonstr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Chuncheonstr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Daejeonstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 충청북도 청주시청원구 내덕1동 도표예보
	xml.FindElem(_T("generator"));
	Daejeonstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Daejeonstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Cheongjustr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Cheongjustr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Cheongjustr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Cheongjustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Cheongjustr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[4] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Cheongjustr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Cheongjustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Cheongjustr[7] = xml.GetData();   //최저온도

	Cheongjustr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Cheongjustr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Jeonjustr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 전라북도 전주시덕진구 금암1동 도표예보
	xml.FindElem(_T("generator"));
	Jeonjustr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Jeonjustr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Jeonjustr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Jeonjustr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Jeonjustr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Jeonjustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Jeonjustr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[5] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Jeonjustr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Jeonjustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Jeonjustr[7] = xml.GetData();   //최저온도

	Jeonjustr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Jeonjustr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Gwangjustr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 광주광역시 동구 충장동 도표예보
	xml.FindElem(_T("generator"));
	Gwangjustr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Gwangjustr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Gwangjustr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Gwangjustr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Gwangjustr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Gwangjustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Gwangjustr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[6] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Gwangjustr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Gwangjustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Gwangjustr[7] = xml.GetData();   //최저온도

	Gwangjustr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Gwangjustr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Yeosustr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 전라남도 여수시 광림동 도표예보
	xml.FindElem(_T("generator"));
	Yeosustr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Yeosustr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Yeosustr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Yeosustr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Yeosustr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Yeosustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Yeosustr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[7] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Yeosustr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Yeosustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Yeosustr[7] = xml.GetData();   //최저온도

	Yeosustr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Yeosustr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Jejustr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 제주특별자치도 제주시 노형동 도표예보
	xml.FindElem(_T("generator"));
	Jejustr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Jejustr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Jejustr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Jejustr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Jejustr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Jejustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Jejustr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[8] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Jejustr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Jejustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Jejustr[7] = xml.GetData();   //최저온도

	Jejustr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Jejustr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Gangneungstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 강원도 강릉시 강남동 도표예보
	xml.FindElem(_T("generator"));
	Gangneungstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Gangneungstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Gangneungstr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Gangneungstr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Gangneungstr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Gangneungstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Gangneungstr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[9] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Gangneungstr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Gangneungstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Gangneungstr[7] = xml.GetData();   //최저온도

	Gangneungstr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Gangneungstr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Daegustr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 대구광역시 동구 방촌동 도표예보
	xml.FindElem(_T("generator"));
	Daegustr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Daegustr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Daegustr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Daegustr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Daegustr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Daegustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Daegustr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[10] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Daegustr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Daegustr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Daegustr[7] = xml.GetData();   //최저온도

	Daegustr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Daegustr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Ulsanstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 울산광역시 남구 달동 도표예보
	xml.FindElem(_T("generator"));
	Ulsanstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Ulsanstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Ulsanstr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Ulsanstr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Ulsanstr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Ulsanstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Ulsanstr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[11] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Ulsanstr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Ulsanstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Ulsanstr[7] = xml.GetData();   //최저온도

	Ulsanstr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Ulsanstr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Changwonstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 경상남도 창원시 진해구 경화동 도표예보
	xml.FindElem(_T("generator"));
	Changwonstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Changwonstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Changwonstr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Changwonstr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Changwonstr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Changwonstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Changwonstr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[12] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Changwonstr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Changwonstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Changwonstr[7] = xml.GetData();   //최저온도

	Changwonstr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Changwonstr[7].Replace(_T(".0"), _T(""));	//.0 제거코드
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
	Busanstr[0] = xml.GetData();   //기상청 동네예보 웹서비스 - 부산광역시 연제구 연산제9동 도표예보
	xml.FindElem(_T("generator"));
	Busanstr[1] = xml.GetData();   //동네예보
	xml.FindElem(_T("pubDate"));
	Busanstr[2] = xml.GetData();   //2018년 12월 07일 (금)요일 08:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("data"));
	xml.IntoElem();

	//---------------------------------//---------------------------------해당 도시 날씨 세부정보
	xml.FindElem(_T("hour"));
	Busanstr[3] = xml.GetData();   //18 동네예보 3시간단위(15시~18시까지)
	xml.FindElem(_T("day"));
	Busanstr[4] = xml.GetData();   //1번째날(오늘/내일/모레 중 오늘)
	xml.FindElem(_T("temp"));
	Busanstr[5] = xml.GetData();   //현재시간온도(15시~18시)
	xml.FindElem(_T("tmx"));
	//Busanstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	//Busanstr[7] = xml.GetData();   //최저온도
	xml.FindElem(_T("sky"));
	Hanul[13] = xml.GetData();        //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
	xml.FindElem(_T("pty"));
	Busanstr[9] = xml.GetData();   //강수상태코드 0 : 없음 1 : 비 2 : 비/눈 3 : 눈/비 4 : 눈

	//---------------------------------내일 날씨
	xml.OutOfElem();
	for (int i = 0; i < 8; i++)		//내일정보 받아오기
		xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("tmx"));
	Busanstr[6] = xml.GetData();   //최고온도
	xml.FindElem(_T("tmn"));
	Busanstr[7] = xml.GetData();   //최저온도

	Busanstr[6].Replace(_T(".0"), _T(""));	//.0 제거코드
	Busanstr[7].Replace(_T(".0"), _T(""));	//.0 제거코드

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
	Weekstr[0] = xml.GetData();		//2018년 12월 12일 (수)요일 18:00
	xml.FindElem(_T("item"));
	xml.IntoElem();
	xml.FindElem(_T("category"));
	xml.FindElem(_T("title"));
	Weekstr[1] = xml.GetData();   //서울,경기도 육상 중기예보 - 2018년 12월 12일 (수)요일 18:00 발표
	xml.FindElem(_T("description"));
	xml.IntoElem();
	xml.FindElem(_T("header"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	Weekstr[2] = xml.GetData();   //기압골의 영향~~
	xml.OutOfElem();
	xml.FindElem(_T("body"));
	xml.IntoElem();
	xml.FindElem(_T("location"));
	xml.IntoElem();
	xml.FindElem(_T("province"));
	Weekstr[3] = xml.GetData();   //서울ㆍ인천ㆍ경기도
	xml.FindElem(_T("city"));
	Weekstr[4] = xml.GetData();   //서울
	//-------------------------------------3일차
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	WeekHanul[2] = xml.GetData();   //하늘상황
	xml.FindElem(_T("tmn"));
	WeekLow[2] = xml.GetData();   //최저기온
	xml.FindElem(_T("tmx"));
	WeekHigh[2] = xml.GetData();   //최고기온
	xml.OutOfElem();
	//-------------------------------------4일차
	xml.FindElem(_T("data"));
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	WeekHanul[3] = xml.GetData();   //하늘상황
	xml.FindElem(_T("tmn"));
	WeekLow[3] = xml.GetData();   //최저기온
	xml.FindElem(_T("tmx"));
	WeekHigh[3] = xml.GetData();   //최고기온
	xml.OutOfElem();
	//-------------------------------------5일차
	xml.FindElem(_T("data"));
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	WeekHanul[4] = xml.GetData();   //하늘상황
	xml.FindElem(_T("tmn"));
	WeekLow[4] = xml.GetData();   //최저기온
	xml.FindElem(_T("tmx"));
	WeekHigh[4] = xml.GetData();   //최고기온
	xml.OutOfElem();
	//-------------------------------------6일차
	xml.FindElem(_T("data"));
	xml.FindElem(_T("data"));
	xml.IntoElem();
	xml.FindElem(_T("wf"));
	WeekHanul[5] = xml.GetData();   //하늘상황
	xml.FindElem(_T("tmn"));
	WeekLow[5] = xml.GetData();   //최저기온
	xml.FindElem(_T("tmx"));
	WeekHigh[5] = xml.GetData();   //최고기온
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
	AfxBeginThread(one_minute_thread, (LPVOID)arg);

	//처음화면
	if (choose5) {
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		dc.SetBkMode(TRANSPARENT);	//배경모드 설정
		CFont font;
		// 비트맵 리소스를 로드한 후 크기 정보를 얻는다.
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP12);
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);
		// 메모리 DC를 만든 후 비트맵을 선택해 넣는다.
		CDC dcmem;
		dcmem.CreateCompatibleDC(&dc);
		dcmem.SelectObject(&bitmap);

		// 비트맵을 화면에 출력한다.
		dc.StretchBlt(0, 0, bmpinfo.bmWidth*0.75, bmpinfo.bmHeight*0.75,
			&dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
		//------------------------------배경그리기-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		//-------------------------------말풍선 넣기---
		CString Malstr = _T("안녕하세요. ");
		Malstr = Malstr + Daejeonstr[1] + _T(" 웹서비스 입니다.  현재 ") + Daejeonstr[2] + _T("            기상예보를 실시하겠습니다.");
	    m_static->SetWindowTextA(Malstr);
		//---------------------------------------------
		return;
	}
	//메인화면
    else if (choose) {
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		dc.SetBkMode(TRANSPARENT);	//배경모드 설정
		CFont font;
		
		CBitmap bitmap4;					//전국지도
		bitmap4.LoadBitmap(IDB_BITMAP11);
		BITMAP bmpinfo4;
		bitmap4.GetBitmap(&bmpinfo4);

		CDC dcmem4;
		dcmem4.CreateCompatibleDC(&dc);
		dcmem4.SelectObject(&bitmap4);

		CBitmap bitmap4_1;					//배경1
		bitmap4_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_1;
		bitmap4_1.GetBitmap(&bmpinfo4_1);

		CDC dcmem4_1;
		dcmem4_1.CreateCompatibleDC(&dc);
		dcmem4_1.SelectObject(&bitmap4_1);
		//--------------------배경1말풍선집어넣기----------
		CBrush brush1(RGB(120, 120, 120));
		dcmem4_1.SelectObject(&brush1);
		dcmem4_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_2;					//배경2
		bitmap4_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_2;
		bitmap4_2.GetBitmap(&bmpinfo4_2);

		CDC dcmem4_2;
		dcmem4_2.CreateCompatibleDC(&dc);
		dcmem4_2.SelectObject(&bitmap4_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_2.SelectObject(&brush1);
		dcmem4_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_1.StretchBlt(0, 0, bmpinfo4.bmWidth, bmpinfo4.bmHeight,	//전국 덧그리기
			&dcmem4, 0, 0, bmpinfo4.bmWidth, bmpinfo4.bmHeight, SRCCOPY);
		dcmem4_2.StretchBlt(0, 0, bmpinfo4.bmWidth, bmpinfo4.bmHeight,	//전국 덧그리기
			&dcmem4, 0, 0, bmpinfo4.bmWidth, bmpinfo4.bmHeight, SRCCOPY);

		
		//------------------------------배경그리기-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		//-------------------------------말풍선 넣기---
		CString Malstr = _T("원하는 지역을 선택해주세요.");
		m_static->SetWindowTextA(Malstr);
		//---------------------------------------------

		CBitmap bitmap4_3;					//배경2
		bitmap4_3.LoadBitmap(IDB_BITMAP17);
		BITMAP bmpinfo4_3;
		bitmap4_3.GetBitmap(&bmpinfo4_3);

		CDC dcmem4_3;
		dcmem4_3.CreateCompatibleDC(&dc);
		dcmem4_3.SelectObject(&bitmap4_3);

		CBitmap bitmap4_3_1;					//배경1
		bitmap4_3_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_3_1;
		bitmap4_3_1.GetBitmap(&bmpinfo4_3_1);

		CDC dcmem4_3_1;
		dcmem4_3_1.CreateCompatibleDC(&dc);
		dcmem4_3_1.SelectObject(&bitmap4_3_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_3_1.SelectObject(&brush1);
		dcmem4_3_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_3_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_3_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_3_2;					//배경2
		bitmap4_3_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_3_2;
		bitmap4_3_2.GetBitmap(&bmpinfo4_3_2);

		CDC dcmem4_3_2;
		dcmem4_3_2.CreateCompatibleDC(&dc);
		dcmem4_3_2.SelectObject(&bitmap4_3_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_3_2.SelectObject(&brush1);
		dcmem4_3_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_3_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_3_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_3_1.StretchBlt(0, 0, bmpinfo4_3.bmWidth*0.8, bmpinfo4_3.bmHeight*0.87,	//서울 덧그리기
			&dcmem4_3, 0, 0, bmpinfo4_3.bmWidth, bmpinfo4_3.bmHeight, SRCCOPY);
		dcmem4_3_2.StretchBlt(0, 0, bmpinfo4_3.bmWidth*0.8, bmpinfo4_3.bmHeight*0.87,	//서울 덧그리기
			&dcmem4_3, 0, 0, bmpinfo4_3.bmWidth, bmpinfo4_3.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_4;					//배경2
		bitmap4_4.LoadBitmap(IDB_BITMAP18);
		BITMAP bmpinfo4_4;
		bitmap4_4.GetBitmap(&bmpinfo4_4);

		CDC dcmem4_4;
		dcmem4_4.CreateCompatibleDC(&dc);
		dcmem4_4.SelectObject(&bitmap4_4);

		CBitmap bitmap4_4_1;					//배경1
		bitmap4_4_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_4_1;
		bitmap4_4_1.GetBitmap(&bmpinfo4_4_1);

		CDC dcmem4_4_1;
		dcmem4_4_1.CreateCompatibleDC(&dc);
		dcmem4_4_1.SelectObject(&bitmap4_4_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_4_1.SelectObject(&brush1);
		dcmem4_4_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_4_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_4_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_4_2;					//배경2
		bitmap4_4_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_4_2;
		bitmap4_4_2.GetBitmap(&bmpinfo4_4_2);

		CDC dcmem4_4_2;
		dcmem4_4_2.CreateCompatibleDC(&dc);
		dcmem4_4_2.SelectObject(&bitmap4_4_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_4_2.SelectObject(&brush1);
		dcmem4_4_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_4_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_4_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_4_1.StretchBlt(0, 0, bmpinfo4_4.bmWidth*0.8, bmpinfo4_4.bmHeight*0.87,	//경기 덧그리기
			&dcmem4_4, 0, 0, bmpinfo4_4.bmWidth, bmpinfo4_4.bmHeight, SRCCOPY);
		dcmem4_4_2.StretchBlt(0, 0, bmpinfo4_4.bmWidth*0.8, bmpinfo4_4.bmHeight*0.87,	//경기 덧그리기
			&dcmem4_4, 0, 0, bmpinfo4_4.bmWidth, bmpinfo4_4.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_5;					//배경2
		bitmap4_5.LoadBitmap(IDB_BITMAP19);
		BITMAP bmpinfo4_5;
		bitmap4_5.GetBitmap(&bmpinfo4_5);

		CDC dcmem4_5;
		dcmem4_5.CreateCompatibleDC(&dc);
		dcmem4_5.SelectObject(&bitmap4_5);

		CBitmap bitmap4_5_1;					//배경1
		bitmap4_5_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_5_1;
		bitmap4_5_1.GetBitmap(&bmpinfo4_5_1);

		CDC dcmem4_5_1;
		dcmem4_5_1.CreateCompatibleDC(&dc);
		dcmem4_5_1.SelectObject(&bitmap4_5_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_5_1.SelectObject(&brush1);
		dcmem4_5_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_5_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_5_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_5_2;					//배경2
		bitmap4_5_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_5_2;
		bitmap4_5_2.GetBitmap(&bmpinfo4_5_2);

		CDC dcmem4_5_2;
		dcmem4_5_2.CreateCompatibleDC(&dc);
		dcmem4_5_2.SelectObject(&bitmap4_5_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_5_2.SelectObject(&brush1);
		dcmem4_5_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_5_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_5_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_5_1.StretchBlt(0, 0, bmpinfo4_5.bmWidth*0.8, bmpinfo4_5.bmHeight*0.87,	//강원 덧그리기
			&dcmem4_5, 0, 0, bmpinfo4_5.bmWidth, bmpinfo4_5.bmHeight, SRCCOPY);
		dcmem4_5_2.StretchBlt(0, 0, bmpinfo4_4.bmWidth*0.8, bmpinfo4_4.bmHeight*0.87,	//강원 덧그리기
			&dcmem4_5, 0, 0, bmpinfo4_5.bmWidth, bmpinfo4_5.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_6;					//배경2
		bitmap4_6.LoadBitmap(IDB_BITMAP20);
		BITMAP bmpinfo4_6;
		bitmap4_6.GetBitmap(&bmpinfo4_6);

		CDC dcmem4_6;
		dcmem4_6.CreateCompatibleDC(&dc);
		dcmem4_6.SelectObject(&bitmap4_6);

		CBitmap bitmap4_6_1;					//배경1
		bitmap4_6_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_6_1;
		bitmap4_6_1.GetBitmap(&bmpinfo4_6_1);

		CDC dcmem4_6_1;
		dcmem4_6_1.CreateCompatibleDC(&dc);
		dcmem4_6_1.SelectObject(&bitmap4_6_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_6_1.SelectObject(&brush1);
		dcmem4_6_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_6_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_6_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_6_2;					//배경2
		bitmap4_6_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_6_2;
		bitmap4_6_2.GetBitmap(&bmpinfo4_6_2);

		CDC dcmem4_6_2;
		dcmem4_6_2.CreateCompatibleDC(&dc);
		dcmem4_6_2.SelectObject(&bitmap4_6_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_6_2.SelectObject(&brush1);
		dcmem4_6_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_6_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_6_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_6_1.StretchBlt(0, 0, bmpinfo4_6.bmWidth*0.8, bmpinfo4_6.bmHeight*0.87,	//충남 덧그리기
			&dcmem4_6, 0, 0, bmpinfo4_6.bmWidth, bmpinfo4_6.bmHeight, SRCCOPY);
		dcmem4_6_2.StretchBlt(0, 0, bmpinfo4_6.bmWidth*0.8, bmpinfo4_6.bmHeight*0.87,	//충남 덧그리기
			&dcmem4_6, 0, 0, bmpinfo4_6.bmWidth, bmpinfo4_6.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_7;					//배경2
		bitmap4_7.LoadBitmap(IDB_BITMAP21);
		BITMAP bmpinfo4_7;
		bitmap4_7.GetBitmap(&bmpinfo4_7);

		CDC dcmem4_7;
		dcmem4_7.CreateCompatibleDC(&dc);
		dcmem4_7.SelectObject(&bitmap4_7);

		CBitmap bitmap4_7_1;					//배경1
		bitmap4_7_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_7_1;
		bitmap4_7_1.GetBitmap(&bmpinfo4_7_1);

		CDC dcmem4_7_1;
		dcmem4_7_1.CreateCompatibleDC(&dc);
		dcmem4_7_1.SelectObject(&bitmap4_7_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_7_1.SelectObject(&brush1);
		dcmem4_7_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_7_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_7_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_7_2;					//배경2
		bitmap4_7_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_7_2;
		bitmap4_7_2.GetBitmap(&bmpinfo4_7_2);

		CDC dcmem4_7_2;
		dcmem4_7_2.CreateCompatibleDC(&dc);
		dcmem4_7_2.SelectObject(&bitmap4_7_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_7_2.SelectObject(&brush1);
		dcmem4_7_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_7_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_7_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_7_1.StretchBlt(0, 0, bmpinfo4_7.bmWidth*0.8, bmpinfo4_7.bmHeight*0.87,	//충북 덧그리기
			&dcmem4_7, 0, 0, bmpinfo4_7.bmWidth, bmpinfo4_7.bmHeight, SRCCOPY);
		dcmem4_7_2.StretchBlt(0, 0, bmpinfo4_7.bmWidth*0.8, bmpinfo4_7.bmHeight*0.87,	//충북 덧그리기
			&dcmem4_7, 0, 0, bmpinfo4_7.bmWidth, bmpinfo4_7.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_8;					//배경2
		bitmap4_8.LoadBitmap(IDB_BITMAP22);
		BITMAP bmpinfo4_8;
		bitmap4_8.GetBitmap(&bmpinfo4_8);

		CDC dcmem4_8;
		dcmem4_8.CreateCompatibleDC(&dc);
		dcmem4_8.SelectObject(&bitmap4_8);

		CBitmap bitmap4_8_1;					//배경1
		bitmap4_8_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_8_1;
		bitmap4_8_1.GetBitmap(&bmpinfo4_8_1);

		CDC dcmem4_8_1;
		dcmem4_8_1.CreateCompatibleDC(&dc);
		dcmem4_8_1.SelectObject(&bitmap4_8_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_8_1.SelectObject(&brush1);
		dcmem4_8_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_8_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_8_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_8_2;					//배경2
		bitmap4_8_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_8_2;
		bitmap4_8_2.GetBitmap(&bmpinfo4_8_2);

		CDC dcmem4_8_2;
		dcmem4_8_2.CreateCompatibleDC(&dc);
		dcmem4_8_2.SelectObject(&bitmap4_8_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_8_2.SelectObject(&brush1);
		dcmem4_8_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_8_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_8_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_8_1.StretchBlt(0, 0, bmpinfo4_8.bmWidth*0.8, bmpinfo4_8.bmHeight*0.87,	//전남 덧그리기
			&dcmem4_8, 0, 0, bmpinfo4_8.bmWidth, bmpinfo4_8.bmHeight, SRCCOPY);
		dcmem4_8_2.StretchBlt(0, 0, bmpinfo4_8.bmWidth*0.8, bmpinfo4_8.bmHeight*0.87,	//전남 덧그리기
			&dcmem4_8, 0, 0, bmpinfo4_8.bmWidth, bmpinfo4_8.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_9;					//배경2
		bitmap4_9.LoadBitmap(IDB_BITMAP23);
		BITMAP bmpinfo4_9;
		bitmap4_9.GetBitmap(&bmpinfo4_9);

		CDC dcmem4_9;
		dcmem4_9.CreateCompatibleDC(&dc);
		dcmem4_9.SelectObject(&bitmap4_9);

		CBitmap bitmap4_9_1;					//배경1
		bitmap4_9_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_9_1;
		bitmap4_9_1.GetBitmap(&bmpinfo4_9_1);

		CDC dcmem4_9_1;
		dcmem4_9_1.CreateCompatibleDC(&dc);
		dcmem4_9_1.SelectObject(&bitmap4_9_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_9_1.SelectObject(&brush1);
		dcmem4_9_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_9_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_9_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_9_2;					//배경2
		bitmap4_9_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_9_2;
		bitmap4_9_2.GetBitmap(&bmpinfo4_9_2);

		CDC dcmem4_9_2;
		dcmem4_9_2.CreateCompatibleDC(&dc);
		dcmem4_9_2.SelectObject(&bitmap4_9_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_9_2.SelectObject(&brush1);
		dcmem4_9_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_9_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_9_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_9_1.StretchBlt(0, 0, bmpinfo4_9.bmWidth*0.8, bmpinfo4_9.bmHeight*0.87,	//전북 덧그리기
			&dcmem4_9, 0, 0, bmpinfo4_9.bmWidth, bmpinfo4_9.bmHeight, SRCCOPY);
		dcmem4_9_2.StretchBlt(0, 0, bmpinfo4_9.bmWidth*0.8, bmpinfo4_9.bmHeight*0.87,	//전북 덧그리기
			&dcmem4_9, 0, 0, bmpinfo4_9.bmWidth, bmpinfo4_9.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_10;					//배경2
		bitmap4_10.LoadBitmap(IDB_BITMAP24);
		BITMAP bmpinfo4_10;
		bitmap4_10.GetBitmap(&bmpinfo4_10);

		CDC dcmem4_10;
		dcmem4_10.CreateCompatibleDC(&dc);
		dcmem4_10.SelectObject(&bitmap4_10);

		CBitmap bitmap4_10_1;					//배경1
		bitmap4_10_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_10_1;
		bitmap4_10_1.GetBitmap(&bmpinfo4_10_1);

		CDC dcmem4_10_1;
		dcmem4_10_1.CreateCompatibleDC(&dc);
		dcmem4_10_1.SelectObject(&bitmap4_10_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_10_1.SelectObject(&brush1);
		dcmem4_10_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_10_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_10_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_10_2;					//배경2
		bitmap4_10_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_10_2;
		bitmap4_10_2.GetBitmap(&bmpinfo4_10_2);

		CDC dcmem4_10_2;
		dcmem4_10_2.CreateCompatibleDC(&dc);
		dcmem4_10_2.SelectObject(&bitmap4_10_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_10_2.SelectObject(&brush1);
		dcmem4_10_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_10_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_10_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_10_1.StretchBlt(0, 0, bmpinfo4_10.bmWidth*0.8, bmpinfo4_10.bmHeight*0.87,	//경남 덧그리기
			&dcmem4_10, 0, 0, bmpinfo4_10.bmWidth, bmpinfo4_10.bmHeight, SRCCOPY);
		dcmem4_10_2.StretchBlt(0, 0, bmpinfo4_10.bmWidth*0.8, bmpinfo4_10.bmHeight*0.87,	//경남 덧그리기
			&dcmem4_10, 0, 0, bmpinfo4_10.bmWidth, bmpinfo4_10.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CBitmap bitmap4_11;					//배경2
		bitmap4_11.LoadBitmap(IDB_BITMAP25);
		BITMAP bmpinfo4_11;
		bitmap4_11.GetBitmap(&bmpinfo4_11);

		CDC dcmem4_11;
		dcmem4_11.CreateCompatibleDC(&dc);
		dcmem4_11.SelectObject(&bitmap4_11);

		CBitmap bitmap4_11_1;					//배경1
		bitmap4_11_1.LoadBitmap(IDB_BITMAP16);
		BITMAP bmpinfo4_11_1;
		bitmap4_11_1.GetBitmap(&bmpinfo4_11_1);

		CDC dcmem4_11_1;
		dcmem4_11_1.CreateCompatibleDC(&dc);
		dcmem4_11_1.SelectObject(&bitmap4_11_1);
		//--------------------배경1말풍선집어넣기----------
		dcmem4_11_1.SelectObject(&brush1);
		dcmem4_11_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_11_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_11_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------
		CBitmap bitmap4_11_2;					//배경2
		bitmap4_11_2.LoadBitmap(IDB_BITMAP15);
		BITMAP bmpinfo4_11_2;
		bitmap4_11_2.GetBitmap(&bmpinfo4_11_2);

		CDC dcmem4_11_2;
		dcmem4_11_2.CreateCompatibleDC(&dc);
		dcmem4_11_2.SelectObject(&bitmap4_11_2);
		//--------------------배경2말풍선집어넣기-----------
		dcmem4_11_2.SelectObject(&brush1);
		dcmem4_11_2.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem4_11_2.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem4_11_2.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------

		//-------------------------------------------
		dcmem4_11_1.StretchBlt(0, 0, bmpinfo4_11.bmWidth*0.8, bmpinfo4_11.bmHeight*0.87,	//경북 덧그리기
			&dcmem4_11, 0, 0, bmpinfo4_11.bmWidth, bmpinfo4_11.bmHeight, SRCCOPY);
		dcmem4_11_2.StretchBlt(0, 0, bmpinfo4_11.bmWidth*0.8, bmpinfo4_11.bmHeight*0.87,	//경북 덧그리기
			&dcmem4_11, 0, 0, bmpinfo4_11.bmWidth, bmpinfo4_11.bmHeight, SRCCOPY);


		//------------------------------배경그리기-----
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		int sel_hanul[14] = { 0 };      //이모티콘 결정 변수   
		for (int i = 0; i < 14; i++)   //이모티콘 결정 사용자 정의 스위치문
		{
			STR_SWITCH(Hanul[i])      //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
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
		CBitmap Hanul_Bitmap[14];   //이모티콘 표시 비트맵 파일저장
		BITMAP Hanul_Bmpinfo[14];   //이모티콘 표시 비트맵 정보저장
		CDC dcmem[14];
		//---------------------------------------날씨 문자 출력-----------------------------
		CString se_hanul[14] = { 0 };      //이모티콘 결정 변수   
		for (int i = 0; i < 14; i++)   //이모티콘 결정 사용자 정의 스위치문
		{
			STR_SWITCH(Hanul[i])      //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
				CASE(_T("1"))
				se_hanul[i] = "맑음";
			BREAK
				CASE(_T("2"))
				se_hanul[i] = "구름 조금";
			BREAK
				CASE(_T("3"))
				se_hanul[i] = "구름 많음";
			BREAK
				CASE(_T("4"))
				se_hanul[i] = "흐림";
			BREAK
				END_SWITCH;
		}
	//-------------------------------------------------------------------

		font.CreateFont(35,     // 글자높이
			15,                     // 글자너비
			0,                      // 출력각도
			0,                      // 기준 선에서의각도
			FW_HEAVY,               // 글자굵기
			FALSE,                  // Italic 적용여부
			FALSE,                  // 밑줄적용여부
			FALSE,                  // 취소선적용여부
			DEFAULT_CHARSET,        // 문자셋종류
			OUT_DEFAULT_PRECIS,     // 출력정밀도
			CLIP_DEFAULT_PRECIS,    // 클리핑정밀도
			DEFAULT_QUALITY,        // 출력문자품질
			DEFAULT_PITCH,          // 글꼴Pitch
			_T("맑은 고딕")         // 글꼴
		);
		//------------------------------------------------------------
		for (int i = 0; i < 14; i++)
		{
			Hanul_Bitmap[i].LoadBitmap(sel_hanul[i]);
			Hanul_Bitmap[i].GetBitmap(&Hanul_Bmpinfo[i]);
			dcmem[i].CreateCompatibleDC(&dc);			//메모리디바이스컨텍스트 생성
			dcmem[i].SelectObject(&Hanul_Bitmap[i]);   //비트맵을 메모리 디바이스 컨텍스트에 선택
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
			//강남구 개포1동
			if (seoul1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_3_1.bmWidth*0.75, bmpinfo4_3_1.bmHeight*0.75,
					&dcmem4_3_1, 0, 0, bmpinfo4_3_1.bmWidth, bmpinfo4_3_1.bmHeight, SRCCOPY);
				dc.TextOut(300, 300, _T("강남구 개포1동"));
				dc.TextOut(300, 400, Seoulstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[1].bmWidth*0.4, Hanul_Bmpinfo[1].bmHeight*0.4,
					&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
				CString Malstr = _T(" 서울특별시 강남구 개포1동 - ");
				Malstr = Malstr +  _T(" 현재 온도: ") + Seoulstr[5] + _T(" 현재날씨: ") + se_hanul[1];
				m_static->SetWindowTextA(Malstr);
			}
			//인천 중구 도원구
			else if (gyeonggi1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_4_1.bmWidth*0.75, bmpinfo4_4_1.bmHeight*0.75,
					&dcmem4_4_1, 0, 0, bmpinfo4_4_1.bmWidth, bmpinfo4_4_1.bmHeight, SRCCOPY);
				dc.TextOut(300, 300, _T("인천 중구 도원구"));
				dc.TextOut(300, 400, Incheonstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[2].bmWidth*0.4, Hanul_Bmpinfo[2].bmHeight*0.4,
					&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
				CString Malstr = _T(" 인천 중구 도원구 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Incheonstr[5] + _T(" 현재날씨: ") + se_hanul[2];
				m_static->SetWindowTextA(Malstr);
			}
			//춘천 교동
			else if (gangwon1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_5_1.bmWidth*0.75, bmpinfo4_5_1.bmHeight*0.75,
					&dcmem4_5_1, 0, 0, bmpinfo4_5_1.bmWidth, bmpinfo4_5_1.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("춘천시 교동"));
				dc.TextOut(250, 400, Chuncheonstr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[3].bmWidth*0.4, Hanul_Bmpinfo[3].bmHeight*0.4,
					&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("강릉시 강남동"));
				dc.TextOut(250, 550, Gangneungstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[9].bmWidth*0.4, Hanul_Bmpinfo[9].bmHeight*0.4,
					&dcmem[9], 0, 0, Hanul_Bmpinfo[9].bmWidth, Hanul_Bmpinfo[9].bmHeight, SRCCOPY); //강릉 강남동
				CString Malstr = _T(" 춘천시 교동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Chuncheonstr[5] + _T(" 현재날씨: ") + se_hanul[3] + _T(" 강릉시 강남동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Gangneungstr[5] + _T(" 현재날씨: ") + se_hanul[9] ;
				m_static->SetWindowTextA(Malstr);
			}
			//대전 대덕구 대화동
			else if (chungnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_6_1.bmWidth*0.75, bmpinfo4_6_1.bmHeight*0.75,
					&dcmem4_6_1, 0, 0, bmpinfo4_6_1.bmWidth, bmpinfo4_6_1.bmHeight, SRCCOPY);
				dc.TextOut(250, 300, _T("대전 대덕구 대화동"));
				dc.TextOut(300, 400, Daejeonstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[0].bmWidth*0.4, Hanul_Bmpinfo[0].bmHeight*0.4,
					&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY); 
				CString Malstr = _T(" 대전 대덕구 대화동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Daejeonstr[5] + _T(" 현재날씨: ") + se_hanul[0];
				m_static->SetWindowTextA(Malstr);

			}
			// 청주시 청원구 내덕1동
			else if (chungbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_7_1.bmWidth*0.75, bmpinfo4_7_1.bmHeight*0.75,
					&dcmem4_7_1, 0, 0, bmpinfo4_7_1.bmWidth, bmpinfo4_7_1.bmHeight, SRCCOPY);
				dc.TextOut(150, 300, _T("청주시 청원구 내덕1동"));
				dc.TextOut(200, 400, Cheongjustr[5]);
				dc.StretchBlt(200, 350, Hanul_Bmpinfo[4].bmWidth*0.4, Hanul_Bmpinfo[4].bmHeight*0.4,
					&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
				CString Malstr = _T(" 청주시 청원구 내덕1동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Cheongjustr[5] + _T(" 현재날씨: ") + se_hanul[4];
				m_static->SetWindowTextA(Malstr);
			}
			//여수시 광림동
			else if (jeonnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_8_1.bmWidth*0.75, bmpinfo4_8_1.bmHeight*0.75,
					&dcmem4_8_1, 0, 0, bmpinfo4_8_1.bmWidth, bmpinfo4_8_1.bmHeight, SRCCOPY);
				dc.TextOut(250, 300, _T("여수시 광림동"));
				dc.TextOut(300, 400, Yeosustr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[7].bmWidth*0.4, Hanul_Bmpinfo[7].bmHeight*0.4,
					&dcmem[7], 0, 0, Hanul_Bmpinfo[7].bmWidth, Hanul_Bmpinfo[7].bmHeight, SRCCOPY);
				CString Malstr = _T(" 여수시 광림동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Yeosustr[5] + _T(" 현재날씨: ") + se_hanul[7];
				m_static->SetWindowTextA(Malstr);

			}
			//덕진구 금암1동
			else if (jeonbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_9_1.bmWidth*0.75, bmpinfo4_9_1.bmHeight*0.75,
					&dcmem4_9_1, 0, 0, bmpinfo4_9_1.bmWidth, bmpinfo4_9_1.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("전주시 덕진구 금암1동"));
				dc.TextOut(250, 400, Jeonjustr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[5].bmWidth*0.4, Hanul_Bmpinfo[5].bmHeight*0.4,
					&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("광주광역시 동구 충장동"));
				dc.TextOut(250, 550, Gwangjustr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[6].bmWidth*0.4, Hanul_Bmpinfo[6].bmHeight*0.4,
					&dcmem[6], 0, 0, Hanul_Bmpinfo[6].bmWidth, Hanul_Bmpinfo[6].bmHeight, SRCCOPY); //광주
				CString Malstr = _T(" 전주시 덕진구 금암1동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Jeonjustr[5] + _T(" 현재날씨: ") + se_hanul[5] + _T(" 광주광역시 동구 충장동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Gwangjustr[5] + _T(" 현재날씨: ") + se_hanul[6];
				m_static->SetWindowTextA(Malstr);
			}
			//창원시 진해구 경화동
			else if (gyeongnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_10_1.bmWidth*0.75, bmpinfo4_10_1.bmHeight*0.75,
					&dcmem4_10_1, 0, 0, bmpinfo4_10_1.bmWidth, bmpinfo4_10_1.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("창원시 진해구 경화동"));
				dc.TextOut(250, 400, Changwonstr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[12].bmWidth*0.4, Hanul_Bmpinfo[12].bmHeight*0.4,
					&dcmem[12], 0, 0, Hanul_Bmpinfo[12].bmWidth, Hanul_Bmpinfo[12].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("부산 연제구 연산 제9동"));
				dc.TextOut(250, 550, Busanstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[13].bmWidth*0.4, Hanul_Bmpinfo[13].bmHeight*0.4,
					&dcmem[13], 0, 0, Hanul_Bmpinfo[13].bmWidth, Hanul_Bmpinfo[13].bmHeight, SRCCOPY); // 부산
				CString Malstr = _T(" 창원시 진해구 경화동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Changwonstr[5] + _T(" 현재날씨: ") + se_hanul[12] + _T(" 부산 연제구 연산 제9동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Busanstr[5] + _T(" 현재날씨: ") + se_hanul[13];
				m_static->SetWindowTextA(Malstr);
			}
			//대구 동구 방촌동
			else if (gyeongbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_11_1.bmWidth*0.75, bmpinfo4_11_1.bmHeight*0.75,
					&dcmem4_11_1, 0, 0, bmpinfo4_11_1.bmWidth, bmpinfo4_11_1.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("대구 동구 방촌동"));
				dc.TextOut(250, 400, Daegustr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[10].bmWidth*0.4, Hanul_Bmpinfo[10].bmHeight*0.4,
					&dcmem[10], 0, 0, Hanul_Bmpinfo[10].bmWidth, Hanul_Bmpinfo[10].bmHeight, SRCCOPY); 
				dc.TextOut(200, 450, _T("울산 남구 달동"));
				dc.TextOut(250, 550, Ulsanstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[11].bmWidth*0.4, Hanul_Bmpinfo[11].bmHeight*0.4,
					&dcmem[11], 0, 0, Hanul_Bmpinfo[11].bmWidth, Hanul_Bmpinfo[11].bmHeight, SRCCOPY);
				CString Malstr = _T(" 대구 동구 방촌동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Daegustr[5] + _T(" 현재날씨: ") + se_hanul[10] + _T(" 울산 남구 달동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Ulsanstr[5] + _T(" 현재날씨: ") + se_hanul[11];
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
			//강남구 개포1동
			if (seoul1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_3_2.bmWidth*0.75, bmpinfo4_3_2.bmHeight*0.75,
					&dcmem4_3_2, 0, 0, bmpinfo4_3_2.bmWidth, bmpinfo4_3_2.bmHeight, SRCCOPY);
				dc.TextOut(300, 300, _T("강남구 개포1동"));
				dc.TextOut(300, 400, Seoulstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[1].bmWidth*0.4, Hanul_Bmpinfo[1].bmHeight*0.4,
					&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
				CString Malstr = _T(" 서울특별시 강남구 개포1동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Seoulstr[5] + _T(" 현재날씨: ") + se_hanul[1];
				m_static->SetWindowTextA(Malstr);
			}
			//인천 중구 도원구
			else if (gyeonggi1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_4_2.bmWidth*0.75, bmpinfo4_4_2.bmHeight*0.75,
					&dcmem4_4_2, 0, 0, bmpinfo4_4_2.bmWidth, bmpinfo4_4_2.bmHeight, SRCCOPY);
				dc.TextOut(300, 300, _T("인천 중구 도원구"));
				dc.TextOut(300, 400, Incheonstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[2].bmWidth*0.4, Hanul_Bmpinfo[2].bmHeight*0.4,
					&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
				CString Malstr = _T(" 인천 중구 도원구 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Incheonstr[5] + _T(" 현재날씨: ") + se_hanul[2];
				m_static->SetWindowTextA(Malstr);
			}
			//춘천 교동
			else if (gangwon1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_5_2.bmWidth*0.75, bmpinfo4_5_2.bmHeight*0.75,
					&dcmem4_5_2, 0, 0, bmpinfo4_5_2.bmWidth, bmpinfo4_5_2.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("춘천시 교동"));
				dc.TextOut(250, 400, Chuncheonstr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[3].bmWidth*0.4, Hanul_Bmpinfo[3].bmHeight*0.4,
					&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("강릉시 강남동"));
				dc.TextOut(250, 550, Gangneungstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[9].bmWidth*0.4, Hanul_Bmpinfo[9].bmHeight*0.4,
					&dcmem[9], 0, 0, Hanul_Bmpinfo[9].bmWidth, Hanul_Bmpinfo[9].bmHeight, SRCCOPY); //강릉 강남동
				CString Malstr = _T(" 춘천시 교동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Chuncheonstr[5] + _T(" 현재날씨: ") + se_hanul[3] + _T(" 강릉시 강남동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Gangneungstr[5] + _T(" 현재날씨: ") + se_hanul[9];
				m_static->SetWindowTextA(Malstr);
			}
			//대전 대덕구 대화동
			else if (chungnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_6_2.bmWidth*0.75, bmpinfo4_6_2.bmHeight*0.75,
					&dcmem4_6_2, 0, 0, bmpinfo4_6_2.bmWidth, bmpinfo4_6_2.bmHeight, SRCCOPY);
				dc.TextOut(250, 300, _T("대전 대덕구 대화동"));
				dc.TextOut(300, 400, Daejeonstr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[0].bmWidth*0.4, Hanul_Bmpinfo[0].bmHeight*0.4,
					&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY);
				CString Malstr = _T(" 대전 대덕구 대화동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Daejeonstr[5] + _T(" 현재날씨: ") + se_hanul[0];
				m_static->SetWindowTextA(Malstr);
			}
			// 청주시 청원구 내덕1동
			else if (chungbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_7_2.bmWidth*0.75, bmpinfo4_7_2.bmHeight*0.75,
					&dcmem4_7_2, 0, 0, bmpinfo4_7_2.bmWidth, bmpinfo4_7_2.bmHeight, SRCCOPY);
				dc.TextOut(150, 300, _T("청주시 청원구 내덕1동"));
				dc.TextOut(200, 400, Cheongjustr[5]);
				dc.StretchBlt(200, 350, Hanul_Bmpinfo[4].bmWidth*0.4, Hanul_Bmpinfo[4].bmHeight*0.4,
					&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
				CString Malstr = _T(" 청주시 청원구 내덕1동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Cheongjustr[5] + _T(" 현재날씨: ") + se_hanul[4];
				m_static->SetWindowTextA(Malstr);
			}
			//여수시 광림동
			else if (jeonnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_8_2.bmWidth*0.75, bmpinfo4_8_2.bmHeight*0.75,
					&dcmem4_8_2, 0, 0, bmpinfo4_8_2.bmWidth, bmpinfo4_8_2.bmHeight, SRCCOPY);
				dc.TextOut(250, 300, _T("여수시 광림동"));
				dc.TextOut(300, 400, Yeosustr[5]);
				dc.StretchBlt(300, 350, Hanul_Bmpinfo[7].bmWidth*0.4, Hanul_Bmpinfo[7].bmHeight*0.4,
					&dcmem[7], 0, 0, Hanul_Bmpinfo[7].bmWidth, Hanul_Bmpinfo[7].bmHeight, SRCCOPY);
				CString Malstr = _T(" 여수시 광림동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Yeosustr[5] + _T(" 현재날씨: ") + se_hanul[7];
				m_static->SetWindowTextA(Malstr);
			}
			//덕진구 금암1동
			else if (jeonbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_9_2.bmWidth*0.75, bmpinfo4_9_2.bmHeight*0.75,
					&dcmem4_9_2, 0, 0, bmpinfo4_9_2.bmWidth, bmpinfo4_9_2.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("전주시 덕진구 금암1동"));
				dc.TextOut(250, 400, Jeonjustr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[5].bmWidth*0.4, Hanul_Bmpinfo[5].bmHeight*0.4,
					&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("광주광역시 동구 충장동"));
				dc.TextOut(250, 550, Gwangjustr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[6].bmWidth*0.4, Hanul_Bmpinfo[6].bmHeight*0.4,
					&dcmem[6], 0, 0, Hanul_Bmpinfo[6].bmWidth, Hanul_Bmpinfo[6].bmHeight, SRCCOPY); //광주
				CString Malstr = _T(" 전주시 덕진구 금암1동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Jeonjustr[5] + _T(" 현재날씨: ") + se_hanul[5] + _T(" 광주광역시 동구 충장동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Gwangjustr[5] + _T(" 현재날씨: ") + se_hanul[6];
				m_static->SetWindowTextA(Malstr);
			}
			//창원시 진해구 경화동
			else if (gyeongnam1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_10_2.bmWidth*0.75, bmpinfo4_10_2.bmHeight*0.75,
					&dcmem4_10_2, 0, 0, bmpinfo4_10_2.bmWidth, bmpinfo4_10_2.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("창원시 진해구 경화동"));
				dc.TextOut(250, 400, Changwonstr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[12].bmWidth*0.4, Hanul_Bmpinfo[12].bmHeight*0.4,
					&dcmem[12], 0, 0, Hanul_Bmpinfo[12].bmWidth, Hanul_Bmpinfo[12].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("부산 연제구 연산 제9동"));
				dc.TextOut(250, 550, Busanstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[13].bmWidth*0.4, Hanul_Bmpinfo[13].bmHeight*0.4,
					&dcmem[13], 0, 0, Hanul_Bmpinfo[13].bmWidth, Hanul_Bmpinfo[13].bmHeight, SRCCOPY); // 부산
				CString Malstr = _T(" 창원시 진해구 경화동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Changwonstr[5] + _T(" 현재날씨: ") + se_hanul[12] + _T(" 부산 연제구 연산 제9동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Busanstr[5] + _T(" 현재날씨: ") + se_hanul[13];
				m_static->SetWindowTextA(Malstr);
			}
			//대구 동구 방촌동
			else if (gyeongbuk1)
			{
				dc.StretchBlt(0, 0, bmpinfo4_11_2.bmWidth*0.75, bmpinfo4_11_2.bmHeight*0.75,
					&dcmem4_11_2, 0, 0, bmpinfo4_11_2.bmWidth, bmpinfo4_11_2.bmHeight, SRCCOPY);
				dc.TextOut(200, 300, _T("대구 동구 방촌동"));
				dc.TextOut(250, 400, Daegustr[5]);
				dc.StretchBlt(250, 350, Hanul_Bmpinfo[10].bmWidth*0.4, Hanul_Bmpinfo[10].bmHeight*0.4,
					&dcmem[10], 0, 0, Hanul_Bmpinfo[10].bmWidth, Hanul_Bmpinfo[10].bmHeight, SRCCOPY);
				dc.TextOut(200, 450, _T("울산 남구 달동"));
				dc.TextOut(250, 550, Ulsanstr[5]);
				dc.StretchBlt(250, 500, Hanul_Bmpinfo[11].bmWidth*0.4, Hanul_Bmpinfo[11].bmHeight*0.4,
					&dcmem[11], 0, 0, Hanul_Bmpinfo[11].bmWidth, Hanul_Bmpinfo[11].bmHeight, SRCCOPY);
				CString Malstr = _T(" 대구 동구 방촌동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Daegustr[5] + _T(" 현재날씨: ") + se_hanul[10] + _T(" 울산 남구 달동 - ");
				Malstr = Malstr + _T(" 현재 온도: ") + Ulsanstr[5] + _T(" 현재날씨: ") + se_hanul[11];
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
	//최고기온
	else if (choose1) {

		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		dc.SetBkMode(TRANSPARENT);   //배경모드 설정

		// 비트맵 리소스를 로드한 후 크기 정보를 얻는다.
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP2);
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);

		// 메모리 DC를 만든 후 비트맵을 선택해 넣는다.
		CDC dcmem;
		dcmem.CreateCompatibleDC(&dc);
		dcmem.SelectObject(&bitmap);

		CBitmap bitmap_0;
		bitmap_0.LoadBitmap(IDB_BITMAP1);
		BITMAP bmpinfo_0;
		bitmap_0.GetBitmap(&bmpinfo_0);

		// 메모리 DC를 만든 후 비트맵을 선택해 넣는다.
		CDC dcmem_0;
		dcmem_0.CreateCompatibleDC(&dc);
		dcmem_0.SelectObject(&bitmap_0);
		//------------------------------배경그리기-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------
		CFont font;
		font.CreateFont(35,     // 글자높이
			15,                     // 글자너비
			0,                      // 출력각도
			0,                      // 기준 선에서의각도
			FW_HEAVY,               // 글자굵기
			FALSE,                  // Italic 적용여부
			FALSE,                  // 밑줄적용여부
			FALSE,                  // 취소선적용여부
			DEFAULT_CHARSET,        // 문자셋종류
			OUT_DEFAULT_PRECIS,     // 출력정밀도
			CLIP_DEFAULT_PRECIS,    // 클리핑정밀도
			DEFAULT_QUALITY,        // 출력문자품질
			DEFAULT_PITCH,          // 글꼴Pitch
			_T("맑은 고딕")         // 글꼴
		);

		dc.SelectObject(&font);
		dc.SetTextColor(RGB(255, 255, 255));
		//-------------------------------말풍선 넣기---
		CString Malstr = _T("내일 최고 기온을 알려드리겠습니다.");
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
			//대전
			dc.TextOut(520, 350, Daejeonstr[6]);
			//서울
			dc.TextOut(553, 237, Seoulstr[6]);
			//인천
			dc.TextOut(400, 255, Incheonstr[6]);
			//춘천
			dc.TextOut(540, 175, Chuncheonstr[6]);
			//청주
			dc.TextOut(570, 295, Cheongjustr[6]);
			//전주
			dc.TextOut(480, 415, Jeonjustr[6]);
			//광주
			dc.TextOut(430, 475, Gwangjustr[6]);
			//여수
			dc.TextOut(510, 540, Yeosustr[6]);
			//제주
			dc.TextOut(390, 660, Jejustr[6]);
			//강릉
			dc.TextOut(705, 215, Gangneungstr[6]);
			//대구
			dc.TextOut(690, 347, Daegustr[6]);
			//울산
			dc.TextOut(805, 400, Ulsanstr[6]);
			//창원
			dc.TextOut(645, 450, Changwonstr[6]);
			//부산
			dc.TextOut(740, 500, Busanstr[6]);

			dc.TextOut(73500, 50000, Busanstr[6]);

			wait(500);

			if (stop1)
			{
				break;
			}

			dc.StretchBlt(0, 0, bmpinfo_0.bmWidth*0.75, bmpinfo_0.bmHeight*0.75,
				&dcmem_0, 0, 0, bmpinfo_0.bmWidth, bmpinfo_0.bmHeight, SRCCOPY);

			//대전
			dc.TextOut(520, 350, Daejeonstr[6]);
			//서울
			dc.TextOut(553, 237, Seoulstr[6]);
			//인천
			dc.TextOut(400, 255, Incheonstr[6]);
			//춘천
			dc.TextOut(540, 175, Chuncheonstr[6]);
			//청주
			dc.TextOut(570, 295, Cheongjustr[6]);
			//전주
			dc.TextOut(480, 415, Jeonjustr[6]);
			//광주
			dc.TextOut(430, 475, Gwangjustr[6]);
			//여수
			dc.TextOut(510, 540, Yeosustr[6]);
			//제주
			dc.TextOut(390, 660, Jejustr[6]);
			//강릉
			dc.TextOut(705, 215, Gangneungstr[6]);
			//대구
			dc.TextOut(690, 347, Daegustr[6]);
			//울산
			dc.TextOut(805, 400, Ulsanstr[6]);
			//창원
			dc.TextOut(645, 450, Changwonstr[6]);
			//부산
			dc.TextOut(740, 500, Busanstr[6]);

			dc.TextOut(73500, 50000, Busanstr[6]);

			wait(500);
		}
		return;
	}	//최저기온
	//최저기온
	else if (choose2) {
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		dc.SetBkMode(TRANSPARENT);   //배경모드 설정
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
		
		//------------------------------배경그리기-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		font.CreateFont(35,     // 글자높이
			15,                     // 글자너비
			0,                      // 출력각도
			0,                      // 기준 선에서의각도
			FW_HEAVY,               // 글자굵기
			FALSE,                  // Italic 적용여부
			FALSE,                  // 밑줄적용여부
			FALSE,                  // 취소선적용여부
			DEFAULT_CHARSET,        // 문자셋종류
			OUT_DEFAULT_PRECIS,     // 출력정밀도
			CLIP_DEFAULT_PRECIS,    // 클리핑정밀도
			DEFAULT_QUALITY,        // 출력문자품질
			DEFAULT_PITCH,          // 글꼴Pitch
			_T("맑은 고딕")         // 글꼴
		);
		dc.SelectObject(&font);
		dc.SetTextColor(RGB(255, 255, 255));
		//-------------------------------말풍선 넣기---
		CString Malstr = _T("내일 최저 기온을 알려드리겠습니다.");
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

			//대전
			dc.TextOut(510, 350, Daejeonstr[7]);
			//서울
			dc.TextOut(548, 237, Seoulstr[7]);
			//인천
			dc.TextOut(390, 265, Incheonstr[7]);
			//춘천
			dc.TextOut(535, 175, Chuncheonstr[7]);
			//청주
			dc.TextOut(565, 295, Cheongjustr[7]);
			//전주
			dc.TextOut(475, 415, Jeonjustr[7]);
			//광주
			dc.TextOut(425, 475, Gwangjustr[7]);
			//여수
			dc.TextOut(510, 540, Yeosustr[7]);
			//제주
			dc.TextOut(395, 650, Jejustr[7]);
			//강릉
			dc.TextOut(700, 218, Gangneungstr[7]);
			//대구
			dc.TextOut(675, 347, Daegustr[7]);
			//울산
			dc.TextOut(800, 400, Ulsanstr[7]);
			//창원
			dc.TextOut(640, 447, Changwonstr[7]);
			//부산
			dc.TextOut(730, 500, Busanstr[7]);

			dc.TextOut(73500, 50000, Busanstr[6]);

			wait(500);

			if (stop2)
			{
				break;
			}

			dc.StretchBlt(0, 0, bmpinfo3_0.bmWidth*0.75, bmpinfo3_0.bmHeight*0.75,
				&dcmem3_0, 0, 0, bmpinfo3_0.bmWidth, bmpinfo3_0.bmHeight, SRCCOPY);

			//대전
			dc.TextOut(510, 350, Daejeonstr[7]);
			//서울
			dc.TextOut(548, 237, Seoulstr[7]);
			//인천
			dc.TextOut(390, 265, Incheonstr[7]);
			//춘천
			dc.TextOut(535, 175, Chuncheonstr[7]);
			//청주
			dc.TextOut(565, 295, Cheongjustr[7]);
			//전주
			dc.TextOut(475, 415, Jeonjustr[7]);
			//광주
			dc.TextOut(425, 475, Gwangjustr[7]);
			//여수
			dc.TextOut(510, 540, Yeosustr[7]);
			//제주
			dc.TextOut(395, 650, Jejustr[7]);
			//강릉
			dc.TextOut(700, 218, Gangneungstr[7]);
			//대구
			dc.TextOut(675, 347, Daegustr[7]);
			//울산
			dc.TextOut(800, 400, Ulsanstr[7]);
			//창원
			dc.TextOut(640, 447, Changwonstr[7]);
			//부산
			dc.TextOut(730, 500, Busanstr[7]);

			dc.TextOut(73500, 50000, Busanstr[6]);

			wait(500);
		}
		return;
	}	//오늘하늘
	//내일날씨
	else if (choose3) {

		int sel_hanul[14] = { 0 };      //이모티콘 결정 변수   
		for (int i = 0; i < 14; i++)   //이모티콘 결정 사용자 정의 스위치문
		{
			STR_SWITCH(Hanul[i])      //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
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

		//-------------------------------말풍선 넣기---
		CString Malstr = _T("내일 하늘상태를 알려드리겠습니다.");
		m_static->SetWindowTextA(Malstr);
		//---------------------------------------------

		CPaintDC dc(this);
		dc.SetBkMode(TRANSPARENT);   //배경모드 설정

		//------------------------------배경그리기-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		CFont font;
		CBitmap Hanul_Bitmap[14];   //이모티콘 표시 비트맵 파일저장
		BITMAP Hanul_Bmpinfo[14];   //이모티콘 표시 비트맵 정보저장
		CDC dcmem[14];            
		//------------------------------------------------------------
		for (int i = 0; i < 14; i++)
		{
			Hanul_Bitmap[i].LoadBitmap(sel_hanul[i]);
			Hanul_Bitmap[i].GetBitmap(&Hanul_Bmpinfo[i]);
			dcmem[i].CreateCompatibleDC(&dc);			//메모리디바이스컨텍스트 생성
			dcmem[i].SelectObject(&Hanul_Bitmap[i]);   //비트맵을 메모리 디바이스 컨텍스트에 선택
		}
		//------------------------------------------------------------


		CBitmap bitmap1_0;
		bitmap1_0.LoadBitmap(IDB_BITMAP5);
		BITMAP bmpinfo1_0;
		bitmap1_0.GetBitmap(&bmpinfo1_0);

		CDC dcmem1_0;
		dcmem1_0.CreateCompatibleDC(&dc);
		dcmem1_0.SelectObject(&bitmap1_0);
		//--------------------말풍선집어넣기---------------
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

		//--------------------말풍선집어넣기---------------
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

			//대전
			dc.StretchBlt(467, 355, Hanul_Bmpinfo[0].bmWidth*0.4, Hanul_Bmpinfo[0].bmHeight*0.4,
				&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY);
			//서울
			dc.StretchBlt(475, 220, Hanul_Bmpinfo[1].bmWidth*0.4, Hanul_Bmpinfo[1].bmHeight*0.4,
				&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
			//인천
			dc.StretchBlt(375, 230, Hanul_Bmpinfo[2].bmWidth*0.4, Hanul_Bmpinfo[2].bmHeight*0.4,
				&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
			//춘천
			dc.StretchBlt(529, 132, Hanul_Bmpinfo[3].bmWidth*0.4, Hanul_Bmpinfo[3].bmHeight*0.4,
				&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
			//청주
			dc.StretchBlt(566, 325, Hanul_Bmpinfo[4].bmWidth*0.4, Hanul_Bmpinfo[4].bmHeight*0.4,
				&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
			//전주
			dc.StretchBlt(447, 455, Hanul_Bmpinfo[5].bmWidth*0.4, Hanul_Bmpinfo[5].bmHeight*0.4,
				&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);
			//광주
			dc.StretchBlt(345, 505, Hanul_Bmpinfo[6].bmWidth*0.4, Hanul_Bmpinfo[6].bmHeight*0.4,
				&dcmem[6], 0, 0, Hanul_Bmpinfo[6].bmWidth, Hanul_Bmpinfo[6].bmHeight, SRCCOPY);
			//여수
			dc.StretchBlt(483, 560, Hanul_Bmpinfo[7].bmWidth*0.4, Hanul_Bmpinfo[7].bmHeight*0.4,
				&dcmem[7], 0, 0, Hanul_Bmpinfo[7].bmWidth, Hanul_Bmpinfo[7].bmHeight, SRCCOPY);
			//제주
			dc.StretchBlt(300, 643, Hanul_Bmpinfo[8].bmWidth*0.4, Hanul_Bmpinfo[8].bmHeight*0.4,
				&dcmem[8], 0, 0, Hanul_Bmpinfo[8].bmWidth, Hanul_Bmpinfo[8].bmHeight, SRCCOPY);
			//강릉
			dc.StretchBlt(635, 195, Hanul_Bmpinfo[9].bmWidth*0.4, Hanul_Bmpinfo[9].bmHeight*0.4,
				&dcmem[9], 0, 0, Hanul_Bmpinfo[9].bmWidth, Hanul_Bmpinfo[9].bmHeight, SRCCOPY);
			//대구
			dc.StretchBlt(668, 325, Hanul_Bmpinfo[10].bmWidth*0.4, Hanul_Bmpinfo[10].bmHeight*0.4,
				&dcmem[10], 0, 0, Hanul_Bmpinfo[10].bmWidth, Hanul_Bmpinfo[10].bmHeight, SRCCOPY);
			//울산
			dc.StretchBlt(690, 424, Hanul_Bmpinfo[11].bmWidth*0.4, Hanul_Bmpinfo[11].bmHeight*0.4,
				&dcmem[11], 0, 0, Hanul_Bmpinfo[11].bmWidth, Hanul_Bmpinfo[11].bmHeight, SRCCOPY);
			//창원
			dc.StretchBlt(566, 447, Hanul_Bmpinfo[12].bmWidth*0.4, Hanul_Bmpinfo[12].bmHeight*0.4,
				&dcmem[12], 0, 0, Hanul_Bmpinfo[12].bmWidth, Hanul_Bmpinfo[12].bmHeight, SRCCOPY);
			//부산
			dc.StretchBlt(670, 533, Hanul_Bmpinfo[13].bmWidth*0.4, Hanul_Bmpinfo[13].bmHeight*0.4,
				&dcmem[13], 0, 0, Hanul_Bmpinfo[13].bmWidth, Hanul_Bmpinfo[13].bmHeight, SRCCOPY);

			wait(500);
			if (stop3)
			{
				break;
			}
			dc.StretchBlt(0, 0, bmpinfo1_0.bmWidth*0.75, bmpinfo1_0.bmHeight*0.75,
				&dcmem1_0, 0, 0, bmpinfo1_0.bmWidth, bmpinfo1_0.bmHeight, SRCCOPY);

			//대전
			dc.StretchBlt(467, 355, Hanul_Bmpinfo[0].bmWidth*0.4, Hanul_Bmpinfo[0].bmHeight*0.4,
				&dcmem[0], 0, 0, Hanul_Bmpinfo[0].bmWidth, Hanul_Bmpinfo[0].bmHeight, SRCCOPY);
			//서울
			dc.StretchBlt(475, 220, Hanul_Bmpinfo[1].bmWidth*0.4, Hanul_Bmpinfo[1].bmHeight*0.4,
				&dcmem[1], 0, 0, Hanul_Bmpinfo[1].bmWidth, Hanul_Bmpinfo[1].bmHeight, SRCCOPY);
			//인천
			dc.StretchBlt(375, 230, Hanul_Bmpinfo[2].bmWidth*0.4, Hanul_Bmpinfo[2].bmHeight*0.4,
				&dcmem[2], 0, 0, Hanul_Bmpinfo[2].bmWidth, Hanul_Bmpinfo[2].bmHeight, SRCCOPY);
			//춘천
			dc.StretchBlt(529, 132, Hanul_Bmpinfo[3].bmWidth*0.4, Hanul_Bmpinfo[3].bmHeight*0.4,
				&dcmem[3], 0, 0, Hanul_Bmpinfo[3].bmWidth, Hanul_Bmpinfo[3].bmHeight, SRCCOPY);
			//청주
			dc.StretchBlt(566, 325, Hanul_Bmpinfo[4].bmWidth*0.4, Hanul_Bmpinfo[4].bmHeight*0.4,
				&dcmem[4], 0, 0, Hanul_Bmpinfo[4].bmWidth, Hanul_Bmpinfo[4].bmHeight, SRCCOPY);
			//전주
			dc.StretchBlt(447, 455, Hanul_Bmpinfo[5].bmWidth*0.4, Hanul_Bmpinfo[5].bmHeight*0.4,
				&dcmem[5], 0, 0, Hanul_Bmpinfo[5].bmWidth, Hanul_Bmpinfo[5].bmHeight, SRCCOPY);
			//광주
			dc.StretchBlt(345, 505, Hanul_Bmpinfo[6].bmWidth*0.4, Hanul_Bmpinfo[6].bmHeight*0.4,
				&dcmem[6], 0, 0, Hanul_Bmpinfo[6].bmWidth, Hanul_Bmpinfo[6].bmHeight, SRCCOPY);
			//여수
			dc.StretchBlt(483, 560, Hanul_Bmpinfo[7].bmWidth*0.4, Hanul_Bmpinfo[7].bmHeight*0.4,
				&dcmem[7], 0, 0, Hanul_Bmpinfo[7].bmWidth, Hanul_Bmpinfo[7].bmHeight, SRCCOPY);
			//제주
			dc.StretchBlt(300, 643, Hanul_Bmpinfo[8].bmWidth*0.4, Hanul_Bmpinfo[8].bmHeight*0.4,
				&dcmem[8], 0, 0, Hanul_Bmpinfo[8].bmWidth, Hanul_Bmpinfo[8].bmHeight, SRCCOPY);
			//강릉
			dc.StretchBlt(635, 195, Hanul_Bmpinfo[9].bmWidth*0.4, Hanul_Bmpinfo[9].bmHeight*0.4,
				&dcmem[9], 0, 0, Hanul_Bmpinfo[9].bmWidth, Hanul_Bmpinfo[9].bmHeight, SRCCOPY);
			//대구
			dc.StretchBlt(668, 325, Hanul_Bmpinfo[10].bmWidth*0.4, Hanul_Bmpinfo[10].bmHeight*0.4,
				&dcmem[10], 0, 0, Hanul_Bmpinfo[10].bmWidth, Hanul_Bmpinfo[10].bmHeight, SRCCOPY);
			//울산
			dc.StretchBlt(690, 424, Hanul_Bmpinfo[11].bmWidth*0.4, Hanul_Bmpinfo[11].bmHeight*0.4,
				&dcmem[11], 0, 0, Hanul_Bmpinfo[11].bmWidth, Hanul_Bmpinfo[11].bmHeight, SRCCOPY);
			//창원
			dc.StretchBlt(566, 447, Hanul_Bmpinfo[12].bmWidth*0.4, Hanul_Bmpinfo[12].bmHeight*0.4,
				&dcmem[12], 0, 0, Hanul_Bmpinfo[12].bmWidth, Hanul_Bmpinfo[12].bmHeight, SRCCOPY);
			//부산
			dc.StretchBlt(670, 533, Hanul_Bmpinfo[13].bmWidth*0.4, Hanul_Bmpinfo[13].bmHeight*0.4,
				&dcmem[13], 0, 0, Hanul_Bmpinfo[13].bmWidth, Hanul_Bmpinfo[13].bmHeight, SRCCOPY);
			wait(500);
		}
		return;
	}	//주간날씨
	//주간기온
	else if (choose4){

		int sel_hanul[6] = { 0 };      //이모티콘 결정 변수   
		for (int i = 0; i < 6; i++)   //이모티콘 결정 사용자 정의 스위치문
		{
			STR_SWITCH(WeekHanul[i])      //하늘상태코드 1 : 맑음 2 : 구름조금 3 : 구름많음 4 : 흐림
				CASE(_T("맑음"))
				sel_hanul[i] = 367;
			BREAK
				CASE(_T("구름조금"))
				sel_hanul[i] = 365;
			BREAK
				CASE(_T("구름많음"))
				sel_hanul[i] = 366;
			BREAK
				CASE(_T("흐림"))
				sel_hanul[i] = 368;
			BREAK
				DEFAULT
				sel_hanul[i] = 368;
			BREAK
				END_SWITCH;
		}
		//---------------------------------------------------------------------------요일 찾아내기

		CString select_day[14] = { _T("월"),_T("화"),_T("수"),_T("목"),_T("금"),_T("토"),_T("일"),
			_T("월"),_T("화"),_T("수"),_T("목"),_T("금"),_T("토"),_T("일") };


		for (int i = 0; i < 14; i++)   //요일결정 사용자 정의 스위치문
		{
			STR_SWITCH(Weekstr[1])       //서울,경기도 육상 중기예보 - 2018년 12월 12일 (수)요일 18:00 발표
				CASE(_T("(월)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 1];
			BREAK
				CASE(_T("(화)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 2];
			BREAK
				CASE(_T("(수)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 3];
			BREAK
				CASE(_T("(목)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 4];
			BREAK
				CASE(_T("(금)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 5];
			BREAK
				CASE(_T("(토)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 6];
			BREAK
				CASE(_T("(일)"))
				for (int i = 0; i < 6; i++)
					Weekday[i] = select_day[i + 7];
			BREAK
				END_SWITCH;
		}
		//----------------------------------------------------------------------------------------
		//----------------------------------------------------------------날짜 정하기-------------
		int select_date = _ttoi(Weekstr[0]);
		for (int i = 0; i < 6; i++)
			Weekdate[i].Format(_T("%d"), select_date + i);
		//----------------------------------------------------------------------------------------
		

		//-------------------------------말풍선 넣기---
		CString Malstr = _T("주간 기상상황을 알려드리겠습니다.");
		m_static->SetWindowTextA(Malstr);
		//---------------------------------------------

		CPaintDC dc(this);
		dc.SetBkMode(TRANSPARENT);   //배경모드 설정

		//------------------------------배경그리기-----
		CBrush Bbrush(RGB(200, 201, 203));
		dc.SelectObject(&Bbrush);
		dc.Rectangle(1438, 150, 1800, 460);
		//---------------------------------------------

		CBitmap Hanul_Bitmap[6];   //이모티콘 표시 비트맵 파일저장
		BITMAP Hanul_Bmpinfo[6];   //이모티콘 표시 비트맵 정보저장
		CDC dcmem[6];
		//------------------------------------------------------------
		for (int i = 0; i < 6; i++)
		{
			Hanul_Bitmap[i].LoadBitmap(sel_hanul[i]);
			Hanul_Bitmap[i].GetBitmap(&Hanul_Bmpinfo[i]);
			dcmem[i].CreateCompatibleDC(&dc);			//메모리디바이스컨텍스트 생성
			dcmem[i].SelectObject(&Hanul_Bitmap[i]);   //비트맵을 메모리 디바이스 컨텍스트에 선택
		}
		//------------------------------------------------------------


		CBitmap bitmap1_0;
		bitmap1_0.LoadBitmap(IDB_BITMAP13);
		BITMAP bmpinfo1_0;
		bitmap1_0.GetBitmap(&bmpinfo1_0);

		CDC dcmem1_0;
		dcmem1_0.CreateCompatibleDC(&dc);
		dcmem1_0.SelectObject(&bitmap1_0);
		//--------------------말풍선집어넣기---------------
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

		//--------------------말풍선집어넣기---------------
		dcmem_1.SelectObject(&brush1);
		dcmem_1.Ellipse(1850, 180, 1850 + 50, 180 + 50);
		dcmem_1.Ellipse(1785, 230, 1785 + 50, 230 + 50);
		dcmem_1.Ellipse(1700, 250, 1700 + 50, 250 + 50);
		//--------------------------------------------------


		CFont font;
		font.CreateFont(50,     // 글자높이
			20,                     // 글자너비
			0,                      // 출력각도
			0,                      // 기준 선에서의각도
			FW_HEAVY,               // 글자굵기
			FALSE,                  // Italic 적용여부
			FALSE,                  // 밑줄적용여부
			FALSE,                  // 취소선적용여부
			DEFAULT_CHARSET,        // 문자셋종류
			OUT_DEFAULT_PRECIS,     // 출력정밀도
			CLIP_DEFAULT_PRECIS,    // 클리핑정밀도
			DEFAULT_QUALITY,        // 출력문자품질
			DEFAULT_PITCH,          // 글꼴Pitch
			_T("맑은 고딕")         // 글꼴

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

			//-------------------------------------------------------------세부표시
			
		 //012345 순서대로 주간기온 칸 왼쪽부터 넣으면 된다.

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

			//012345 순서대로 주간기온 칸 왼쪽부터 넣으면 된다.

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
	}//주간날씨


}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_pushButton1.Create(_T("도시선택"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 460, 1800, 530), this, 101);
	m_pushButton2.Create(_T("최고기온"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 530, 1800, 600), this, 102);
	m_pushButton3.Create(_T("최저기온"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 600, 1800, 670), this, 103);
	m_pushButton4.Create(_T("내일날씨"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 670, 1800, 740), this, 104);
	m_pushButton5.Create(_T("주간날씨"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(1438, 740, 1800, 810), this, 105); 
	
	m_static = new CStatic;	//정적 텍스트 컨트롤 생성
	m_static->Create(_T("Click a button to change my color"), WS_CHILD | WS_VISIBLE | SS_LEFT | WS_DLGFRAME,
		CRect(1438, 0, 1800, 150), this);

	return 0;
}

void CChildView::OnButton1Clicked(void)
{
	choose = TRUE;	//메뉴선택
	choose1 = FALSE;
	choose2 = FALSE;
	choose3 = FALSE;
	choose4 = FALSE;
	choose5 = FALSE;
	stop = FALSE;	//이벤트발생
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (choose) {
		GetCursorPos(&m_pt);
		ScreenToClient(&m_pt);
		if (m_r1.PtInRect(m_pt)) { // PtlnRect() 로 포인터 위치확인 
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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



