
// ChildView.h : CChildView Ŭ������ �������̽�
//


#pragma once


// CChildView â

class CChildView : public CWnd
{
// �����Դϴ�.
public:
	CChildView();

// Ư���Դϴ�.
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

	CPoint m_pt;	//���콺 ��ġ Ȯ�κ���
	CRect m_r1, m_r2, m_r3, m_r4, m_r5, m_r6, m_r7, m_r8, m_r9;	//�� ���� ���� ���к���
	CStatic* m_static;	//static text ��������
	int arg = 0;		//�۾��� ������


// �۾��Դϴ�.
public:

// �������Դϴ�.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CChildView();

	// ������ �޽��� �� �Լ�
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

