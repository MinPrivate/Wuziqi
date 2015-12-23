// WuziqiDlg.h : header file
//

#if !defined(AFX_WUZIQIDLG_H__32E4352A_9731_4534_84D1_2C0D896B6FAF__INCLUDED_)
#define AFX_WUZIQIDLG_H__32E4352A_9731_4534_84D1_2C0D896B6FAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Win.h"
#include "MenAndComputer.h"

#define NO  0         //0 ��ʾ������
#define BAI 1         //1 ��ʾ������
#define HEI 2         //2 ��ʾ������

struct ZUOBIAO{
	int row;
	int col;
	int num;
	ZUOBIAO *next;
};

/////////////////////////////////////////////////////////////////////////////
// CWuziqiDlg dialog

class CWuziqiDlg : public CDialog
{
// Construction
public:
	//void TenX(int,int);                        //����һ�����ӱ�ʾ
	void RePaintChessBoard();                    //�ػ������ϵ�����
	void ComputerLoadChessBai();                 //�����°�����
	void ComputerLoadChessHei();                 //�����º�����

	void LoadDlgBk(int iBmpID);                  //����λͼ
	void InitData();                             //��ʼ��������Ϣ
	void InitBoard();                            //��ʼ������
	void LoadChessHei(int,int);                  //�º�����
	void LoadChessBai(int,int);                  //�°�����
	void WherePoint(CPoint point);               //ȷ�����������
	bool InGame(CPoint point);                   //�ж��Ƿ���������
	CWuziqiDlg(CWnd* pParent = NULL);	         // standard constructor

// Dialog Data
	//{{AFX_DATA(CWuziqiDlg)
	enum { IDD = IDD_WUZIQI_DIALOG };
	CButton	m_takeback;
	CButton	m_restart;
	CButton	m_computerhelp;
	CButton	m_lost;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWuziqiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void LoadTakeBack();
	void Takeback(int,int);
	void reStart();

/////////////////////////////////////////���������Ϣ
	void jiaRu(ZUOBIAO *mes);

/////////////////////////////////////////����
	void huiQi();

//////////////////////////////////////////�Ƿ���Ի���  �����򷵻�1 
	bool isHuiQi();
	int num;	 //��¼¼��Ĳ���
	int r;		//��¼¼��Ļ�����ɫ   ���� ��
private:

	// ���ڴ��豸��λͼ 
	CDC		m_dcHuiQi;
	CBitmap m_bmpHuiQi;

//////////////////////////////////��������
	ZUOBIAO * bushu;
protected:
	// ���ڴ��豸��λͼ 
	CDC		m_dcMain;
	CBitmap m_bmpMain;

	// �����ڴ��豸��λͼ
	CDC		m_dcBK;
	CBitmap m_bmpBK;

	// ��Ϸ�����ڴ��豸��λͼ
	CDC		m_dcChessHei;          //����
	CBitmap	m_bmpChessHei;

	CDC		m_dcChessBai;
	CBitmap m_bmpChessBai;

	//����λͼ
	CDC		m_dcMask;
	CBitmap m_bmpMask;

protected:
	CWin win;                          //�����ж�ʤ������
	CMenAndComputer m_menAndComputer;  //�����˻����Ķ���

	int     m_moder;                   //��¼����ģʽ 0 �����˻���ս 1 ����
	int     m_firstDo;                 //�˻���սʱ��¼����һ��  0 ���� �������� 1 ����������

protected:

	int		m_board[15][15];           //0 �������� 1 ������� 2 ������� 
	
	int     m_color;                   //ʹ�ڰ����Ӹ���һ�� 2 �º��� 1 �°���

	bool	m_ifwin;                   //�ж��Ƿ���ʤ�� false ������ true ������

	int     row;                       ////////////////////��¼�����߼�λ��
	int     col;

	int     X;                        //��������λ��
	int     Y;

	int     m_currentBK;               //��¼����
	int     numHuiQi;
	
	int     m_bkChange;                //ת��������¼
	int     m_musicChange;             //�˵�ת����¼
	int     m_inGame;                  //�ж��Ƿ������Ϸ0����δ����1�������
protected:
	HICON m_hIcon;

	CString playMusic;

	// Generated message map functions
	//{{AFX_MSG(CWuziqiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnMenu1();
	afx_msg void OnMenu2();
	afx_msg void OnMenu3();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonTakeback();
	afx_msg void OnButtonRestart();
	afx_msg void OnMenuPlayer();
	afx_msg void OnMenuComputerfirst();
	afx_msg void OnMenuPlayerfirst();
	afx_msg void OnButtonComputerhelp();
	afx_msg void OnButtonLost();
	afx_msg void OnMenuBk4();
	afx_msg void OnMusic1();
	afx_msg void OnMusic2();
	afx_msg void OnMusic3();
	afx_msg void OnMusicClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuStart();
	afx_msg void OnMenuTakeback();
	afx_msg void OnMenuHelp();
	afx_msg void OnMenuLost();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMusicAbout();
	afx_msg void OnHelp();
	afx_msg void OnMenuAb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WUZIQIDLG_H__32E4352A_9731_4534_84D1_2C0D896B6FAF__INCLUDED_)
