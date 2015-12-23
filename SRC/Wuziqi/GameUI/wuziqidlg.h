// WuziqiDlg.h : header file
//

#if !defined(AFX_WUZIQIDLG_H__32E4352A_9731_4534_84D1_2C0D896B6FAF__INCLUDED_)
#define AFX_WUZIQIDLG_H__32E4352A_9731_4534_84D1_2C0D896B6FAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Win.h"
#include "MenAndComputer.h"

#define NO  0         //0 表示无棋子
#define BAI 1         //1 表示白棋子
#define HEI 2         //2 表示黑棋子

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
	//void TenX(int,int);                        //给上一步下子表示
	void RePaintChessBoard();                    //重绘棋盘上的棋子
	void ComputerLoadChessBai();                 //电脑下白棋子
	void ComputerLoadChessHei();                 //电脑下黑棋子

	void LoadDlgBk(int iBmpID);                  //背景位图
	void InitData();                             //初始化棋子信息
	void InitBoard();                            //初始化棋盘
	void LoadChessHei(int,int);                  //下黑棋子
	void LoadChessBai(int,int);                  //下白棋子
	void WherePoint(CPoint point);               //确定下棋的坐标
	bool InGame(CPoint point);                   //判断是否在棋盘内
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

/////////////////////////////////////////加入悔棋信息
	void jiaRu(ZUOBIAO *mes);

/////////////////////////////////////////悔棋
	void huiQi();

//////////////////////////////////////////是否可以悔棋  可以则返回1 
	bool isHuiQi();
	int num;	 //记录录像的部数
	int r;		//记录录像的悔棋颜色   奇数 黑
private:

	// 主内存设备与位图 
	CDC		m_dcHuiQi;
	CBitmap m_bmpHuiQi;

//////////////////////////////////悔棋链表
	ZUOBIAO * bushu;
protected:
	// 主内存设备与位图 
	CDC		m_dcMain;
	CBitmap m_bmpMain;

	// 背景内存设备与位图
	CDC		m_dcBK;
	CBitmap m_bmpBK;

	// 游戏棋子内存设备与位图
	CDC		m_dcChessHei;          //黑棋
	CBitmap	m_bmpChessHei;

	CDC		m_dcChessBai;
	CBitmap m_bmpChessBai;

	//掩码位图
	CDC		m_dcMask;
	CBitmap m_bmpMask;

protected:
	CWin win;                          //建立判断胜负对象
	CMenAndComputer m_menAndComputer;  //建立人机对弈对象

	int     m_moder;                   //记录下棋模式 0 代表人机对战 1 人人
	int     m_firstDo;                 //人机对战时记录先行一方  0 代表 电脑先行 1 代表人先行

protected:

	int		m_board[15][15];           //0 代表无子 1 代表白子 2 代表黑子 
	
	int     m_color;                   //使黑白棋子个行一下 2 下黑子 1 下白子

	bool	m_ifwin;                   //判断是否有胜利 false 代表无 true 代表有

	int     row;                       ////////////////////记录棋盘逻辑位置
	int     col;

	int     X;                        //棋子落点的位置
	int     Y;

	int     m_currentBK;               //记录背景
	int     numHuiQi;
	
	int     m_bkChange;                //转换背景记录
	int     m_musicChange;             //菜单转换记录
	int     m_inGame;                  //判断是否进入游戏0代表未进入1代表进入
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
