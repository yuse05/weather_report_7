
// ChildView.h : CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	void Daejeon();
	void Jeonju();
	void Changwon();
	void Gangneung();
	void Cheongju();
	void Jeju();
	void Yeosu();
	void Incheon();
	void Ulsan();
	void Seoul();
	void Busan();
	void Daegu();
	void Gwangju();
	void Chuncheon();
	void Week();

	CPoint m_pt;	//마우스 위치 확인변수
	CRect m_r1, m_r2, m_r3, m_r4, m_r5, m_r6, m_r7, m_r8, m_r9;	//각 도별 지역 구분변수
	CStatic* m_static;	//static text 생성변수
	int arg = 0;		//작업자 스레드


// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnButton1Clicked();
	void OnButton2Clicked();
	void OnButton3Clicked();
	void OnButton4Clicked();
	void OnButton5Clicked();
	void wait(DWORD dwMillisecond);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

};

