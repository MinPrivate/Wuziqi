// WuziqiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Wuziqi.h"
#include "WuziqiDlg.h"
#include "Win.h"
#include "MenAndComputer.h"
#include "mmsystem.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWuziqiDlg dialog

CWuziqiDlg::CWuziqiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWuziqiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWuziqiDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWuziqiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWuziqiDlg)
	DDX_Control(pDX, IDC_BUTTON_TAKEBACK, m_takeback);
	DDX_Control(pDX, IDC_BUTTON_RESTART, m_restart);
	DDX_Control(pDX, IDC_BUTTON_COMPUTERHELP, m_computerhelp);
	DDX_Control(pDX, IDC_BUTTON_LOST, m_lost);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWuziqiDlg, CDialog)
	//{{AFX_MSG_MAP(CWuziqiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_COMMAND(ID_MENU_1, OnMenu1)
	ON_COMMAND(ID_MENU_2, OnMenu2)
	ON_COMMAND(ID_MENU_3, OnMenu3)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_TAKEBACK, OnButtonTakeback)
	ON_BN_CLICKED(IDC_BUTTON_RESTART, OnButtonRestart)
	ON_COMMAND(ID_MENU_PLAYER, OnMenuPlayer)
	ON_COMMAND(ID_MENU_COMPUTERFIRST, OnMenuComputerfirst)
	ON_COMMAND(ID_MENU_PLAYERFIRST, OnMenuPlayerfirst)
	ON_BN_CLICKED(IDC_BUTTON_COMPUTERHELP, OnButtonComputerhelp)
	ON_BN_CLICKED(IDC_BUTTON_LOST, OnButtonLost)
	ON_COMMAND(ID_MENU_BK4, OnMenuBk4)
	ON_COMMAND(IDC_MUSIC_1, OnMusic1)
	ON_COMMAND(IDC_MUSIC_2, OnMusic2)
	ON_COMMAND(IDC_MUSIC_3, OnMusic3)
	ON_COMMAND(IDC_MUSIC_CLOSE, OnMusicClose)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MENU_START, OnMenuStart)
	ON_COMMAND(ID_MENU_TAKEBACK, OnMenuTakeback)
	ON_COMMAND(ID_MENU_HELP, OnMenuHelp)
	ON_COMMAND(ID_MENU_LOST, OnMenuLost)
	ON_COMMAND(ID_MENU_SAVE, OnMenuSave)
	ON_COMMAND(ID_MENU_OPEN, OnMenuOpen)
	ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
	ON_WM_TIMER()
	ON_COMMAND(IDC_HELP, OnHelp)
	ON_COMMAND(ID_MENU_AB, OnMenuAb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWuziqiDlg message handlers

BOOL CWuziqiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	LoadDlgBk(IDB_BITMAP_WELCOME);     //加载欢迎界面
	m_currentBK=IDB_BITMAP_WELCOME;
	m_inGame=0;                        //未进入游戏界面
	GetMenu()->GetSubMenu(1)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	GetMenu()->GetSubMenu(2)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	GetMenu()->GetSubMenu(2)->GetSubMenu(1)->CheckMenuItem(0, MF_BYPOSITION|MF_CHECKED);

	m_bkChange=1;

	InitData();                 //初始化棋子掩码信息
	InitBoard();                //初始化棋盘信息
	bushu = NULL;               //悔棋链表
	//m_moder=0;                  //默认为人人对战
	//m_firstDo=0;
	r = 1    ;  
	playMusic = "music\\background.mp3";

	mciSendString("play "+playMusic+" repeat", NULL, 0, NULL);
	
	CBitmap Bitmap;

     Bitmap.LoadBitmap(IDB_BITMAP_XINKAIJU);

     HBITMAP hBitmap=(HBITMAP)Bitmap.Detach();

     CButton *pButton=(CButton*)GetDlgItem(IDC_BUTTON_RESTART);

      pButton->SetBitmap(hBitmap);


   CBitmap Bitmap1;

   Bitmap1.LoadBitmap(IDB_BITMAP_HUIQI);

    HBITMAP hBitmap1=(HBITMAP)Bitmap1.Detach();

   CButton *pButton1=(CButton*)GetDlgItem(IDC_BUTTON_TAKEBACK);

   pButton1->SetBitmap(hBitmap1);


   CBitmap Bitmap2;

   Bitmap2.LoadBitmap(IDB_BITMAP_QIUZHU);

   HBITMAP hBitmap2=(HBITMAP)Bitmap2.Detach();

   CButton *pButton2=(CButton*)GetDlgItem(IDC_BUTTON_COMPUTERHELP);
 
   pButton2->SetBitmap(hBitmap2);


CBitmap Bitmap3;

Bitmap3.LoadBitmap(IDB_BITMAP_RENSHU);

HBITMAP hBitmap3=(HBITMAP)Bitmap3.Detach();

CButton *pButton3=(CButton*)GetDlgItem(IDC_BUTTON_LOST);

pButton3->SetBitmap(hBitmap3);



	m_restart.ShowWindow(SW_HIDE);
	m_computerhelp.ShowWindow(SW_HIDE);
	m_lost.ShowWindow(SW_HIDE);
	m_takeback.ShowWindow(SW_HIDE);





	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWuziqiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWuziqiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//获取客户区域大小
		CRect rect;
		GetClientRect(rect);

		CPaintDC dc(this);
		dc.BitBlt(0, 0, rect.right, rect.bottom, &m_dcMain, 0, 0, SRCCOPY);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWuziqiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//加载背景图片
void CWuziqiDlg::LoadDlgBk(int iBmpID)
{
	m_dcMain.DeleteDC();
	m_dcBK.DeleteDC();
	m_bmpMain.DeleteObject();
	m_bmpBK.DeleteObject();

	//获取客户区域大小
	CRect rect;
	GetClientRect(rect);

	//绘制背景
	CClientDC dc(this);								// Get a dc for a CWnd object pointer.
	m_dcMain.CreateCompatibleDC(&dc);				//根据指定DC来创建一个内存设备上下文
	m_bmpMain.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);	//根据指定dc来初始化Bitmap对象，并指定大小
	m_dcMain.SelectObject(&m_bmpMain);				//选择一个Bitmap对象

	m_dcBK.CreateCompatibleDC(&m_dcMain);			//获取一个内存设备上下文
	m_bmpBK.LoadBitmap(iBmpID);						//背景Bitmap对象读取图片
	m_dcBK.SelectObject(m_bmpBK);					//背景图形设备对象选择一个Bitmap对象

	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);	//指定设备的伸展模式
													//STRETCH_HALFTONE :等同COLORONCOLOR
													//删除像素，这个模式删除所有待删除的像素行，而不保留他们的信息。
	
	//函数从源矩形中复制一个位图到目标矩形，必要时按目前目标设备设置模式进行图像的拉伸或压缩
	BITMAP bmpInfo;
	m_bmpBK.GetBitmap(&bmpInfo);
//	m_dcMain.StretchBlt(0, 0, rect.right, rect.bottom-50, &m_dcBK, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	m_dcMain.StretchBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &m_dcBK, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	Invalidate(FALSE);

}

void CWuziqiDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	//释放资源
	m_dcMain.DeleteDC();
	m_dcBK.DeleteDC();
	m_dcChessHei.DeleteDC();
	m_dcChessBai.DeleteDC();
	m_dcMask.DeleteDC();

	m_bmpMain.DeleteObject();
	m_bmpBK.DeleteObject();
	m_bmpChessHei.DeleteObject();
	m_bmpChessBai.DeleteObject();
	m_bmpMask.DeleteObject();

	m_dcHuiQi.DeleteDC();
	m_bmpHuiQi.DeleteObject();


}

void CWuziqiDlg::OnMenu1() 
{
	// TODO: Add your command handler code here
	if(m_inGame!=0)
	{
		LoadDlgBk(IDB_BITMAP2);
		m_currentBK=IDB_BITMAP2;
		RePaintChessBoard();

		GetMenu()->GetSubMenu(1)->CheckMenuItem(m_bkChange, MF_BYPOSITION|MF_UNCHECKED);
		GetMenu()->GetSubMenu(1)->CheckMenuItem(0, MF_BYPOSITION|MF_CHECKED);
		m_bkChange=0;
	}
}

void CWuziqiDlg::OnMenu2() 
{
	// TODO: Add your command handler code here
	if(m_inGame!=0)
	{
		LoadDlgBk(IDB_BITMAP3);
		m_currentBK=IDB_BITMAP3;
		RePaintChessBoard();

		GetMenu()->GetSubMenu(1)->CheckMenuItem(m_bkChange, MF_BYPOSITION|MF_UNCHECKED);
		GetMenu()->GetSubMenu(1)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
		m_bkChange=1;
	}
}

void CWuziqiDlg::OnMenu3() 
{
	// TODO: Add your command handler code here
	if(m_inGame!=0)
	{
		LoadDlgBk(IDB_BITMAP_BK);
		m_currentBK=IDB_BITMAP_BK;
		RePaintChessBoard();

		GetMenu()->GetSubMenu(1)->CheckMenuItem(m_bkChange, MF_BYPOSITION|MF_UNCHECKED);
		GetMenu()->GetSubMenu(1)->CheckMenuItem(2, MF_BYPOSITION|MF_CHECKED);
		m_bkChange=2;
	}
}
void CWuziqiDlg::OnMenuBk4() 
{
	// TODO: Add your command handler code here
	if(m_inGame!=0)
	{
		LoadDlgBk(IDB_BITMAP_BK4);
		m_currentBK=IDB_BITMAP_BK4;
		RePaintChessBoard();

		GetMenu()->GetSubMenu(1)->CheckMenuItem(m_bkChange, MF_BYPOSITION|MF_UNCHECKED);
		GetMenu()->GetSubMenu(1)->CheckMenuItem(3, MF_BYPOSITION|MF_CHECKED);
		m_bkChange=3;
	}	
}

void CWuziqiDlg::OnMenuPlayer() 
{
	// TODO: Add your command handler code here
	if(m_inGame!=0)
	{
	m_moder=1;
	OnButtonRestart();

	GetMenu()->GetSubMenu(2)->CheckMenuItem(0, MF_BYPOSITION|MF_CHECKED);
	GetMenu()->GetSubMenu(2)->GetSubMenu(1)->CheckMenuItem(1, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(2)->CheckMenuItem(1, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(2)->GetSubMenu(1)->CheckMenuItem(0, MF_BYPOSITION|MF_UNCHECKED);
	}
}

void CWuziqiDlg::OnMenuComputerfirst() 
{
	// TODO: Add your command handler code here
	if(m_inGame!=0)
	{
	m_moder=0;
	m_firstDo=0;
	LoadDlgBk(m_currentBK);

	InitBoard();                               //初始化棋盘信息
	InitData();                                //初始化棋子掩码信息
	m_menAndComputer.InitMenAndComputer();     //初始化人机对战评分记录 

		if(m_color==HEI && m_ifwin==false)
		{
			ZUOBIAO *m_coord=new ZUOBIAO;
			//得到棋子应下点的坐标
			//WherePoint(point);
			row=7;
			col=7;
			X=50+row*40;
			Y=50+col*40;

			if(m_board[row][col]==NO)					           //若无子则可下子
			{
				//下黑棋子
				LoadChessHei(X,Y);
				m_board[row][col]=HEI;                              ///已落黑子
				m_color=BAI;                                        //接下来落白子
		
				m_coord->col = col;
				m_coord->row = row;
					//已落黑子

				jiaRu(m_coord);  
				numHuiQi = 0;

				//判断胜负
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 
				}
			}
		}
		// 将界面设为无效
		Invalidate(FALSE);

	GetMenu()->GetSubMenu(2)->CheckMenuItem(0, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(2)->GetSubMenu(1)->CheckMenuItem(0, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(2)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	GetMenu()->GetSubMenu(2)->GetSubMenu(1)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	}
}

void CWuziqiDlg::OnMenuPlayerfirst() 
{
	// TODO: Add your command handler code here
	if(m_inGame!=0)
	{
	m_moder=0;
	m_firstDo=1;
	OnButtonRestart();
	GetMenu()->GetSubMenu(2)->CheckMenuItem(0, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(2)->GetSubMenu(1)->CheckMenuItem(1, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(2)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	GetMenu()->GetSubMenu(2)->GetSubMenu(1)->CheckMenuItem(0, MF_BYPOSITION|MF_CHECKED);
	}
}

////////////////初始化棋盘信息
void CWuziqiDlg::InitBoard()
{
	m_color=HEI;                 //黑棋先行
	m_ifwin=false;               //没有胜利
	bushu=NULL;
	//初始化棋盘棋子储存信息  将棋盘数组初始化为0
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
			m_board[i][j]=0;
	}

}
////////////////////////初始化棋子信息
void CWuziqiDlg::InitData()
{
	// 初始内存设备与位图
	m_bmpChessHei.DeleteObject();                    //初始化黑棋子
	m_dcChessHei.DeleteDC();
	
	m_bmpChessBai.DeleteObject();                    //初始化白棋子
	m_dcChessBai.DeleteDC();

	m_bmpMask.DeleteObject();                        //初始化掩码
	m_dcMask.DeleteDC();

	// 加载位图，选入内存设备
	m_dcChessHei.CreateCompatibleDC(&m_dcMain);      //加载黑棋子并选入内存
	m_bmpChessHei.LoadBitmap(IDB_BITMAP_HEI);
	m_dcChessHei.SelectObject(m_bmpChessHei);

	m_dcChessBai.CreateCompatibleDC(&m_dcMain);      //加载白棋子并选入内存
	m_bmpChessBai.LoadBitmap(IDB_BITMAP_BAI);
	m_dcChessBai.SelectObject(m_bmpChessBai);

	m_dcMask.CreateCompatibleDC(&m_dcMain);          //加载掩码并选入内存
	m_bmpMask.LoadBitmap(IDB_BITMAP_MASK);
	m_dcMask.SelectObject(m_bmpMask);
}
///////////////////下黑棋子
void CWuziqiDlg::LoadChessHei(int X,int Y)
{
	PlaySound("res\\play.wav", AfxGetInstanceHandle(), SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	// 获得位图信息
	BITMAP bmpInfoHei;
	m_bmpChessHei.GetBitmap(&bmpInfoHei);

	// 缩放贴图

	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);
	//将棋子与掩码相或
	m_dcChessHei.BitBlt(0,0,bmpInfoHei.bmWidth, bmpInfoHei.bmHeight,
						&m_dcMask,0,0,SRCPAINT);
	//将背景与掩码异或
	//加的
	m_dcMain.StretchBlt(X-17,Y-18,34, 34, 
						&m_dcMask, 0, 0,bmpInfoHei.bmWidth, bmpInfoHei.bmHeight, MERGEPAINT);
	//合成最终透明位图

	m_dcMain.StretchBlt(X-17,Y-18, 35, 37, 
						&m_dcChessHei, 0, 0, bmpInfoHei.bmWidth, bmpInfoHei.bmHeight, SRCAND);
}
//////////////////////下白棋子
void CWuziqiDlg::LoadChessBai(int X,int Y)
{
PlaySound("res\\play.wav", AfxGetInstanceHandle(), SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	// 获得位图信息
	BITMAP bmpInfoBai;
	m_bmpChessBai.GetBitmap(&bmpInfoBai);

	// 缩放贴图

	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);
	//将棋子与掩码相或
	m_dcChessBai.BitBlt(0,0,bmpInfoBai.bmWidth, bmpInfoBai.bmHeight,
						&m_dcMask,0,0,SRCPAINT);
	//将背景与掩码异或
	m_dcMain.BitBlt(X-17,Y-18,bmpInfoBai.bmWidth, 100,
						&m_dcMask,bmpInfoBai.bmWidth,0,MERGEPAINT);
	//合成最终透明位图
	//加的
	m_dcMain.StretchBlt(X-17,Y-18,34, 34, 
						&m_dcMask, 0, 0,bmpInfoBai.bmWidth, bmpInfoBai.bmHeight, MERGEPAINT);

	m_dcMain.StretchBlt(X-17,Y-18, 
						35, 37, &m_dcChessBai, 0, 0, bmpInfoBai.bmWidth, bmpInfoBai.bmHeight, SRCAND);
}
///////////////判断是否在棋盘范围内
bool CWuziqiDlg::InGame(CPoint point)
{
	if(point.x<30 ||point.y<30 ||point.x>630 ||point.y>630)
		return false;
	else 
		return true;
}
///////////////确定落子点的坐标
void CWuziqiDlg::WherePoint(CPoint point)
{
	row=(point.x-30)/40;
	col=(point.y-30)/40;

	X=50+row*40;
	Y=50+col*40;
}
//////////////左键单击下黑子并判断胜负
void CWuziqiDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_inGame!=0)
	{
	if(m_moder==1)
	{
		if(m_color==HEI && m_ifwin==false && InGame(point)==true)
		{
			ZUOBIAO *m_coord=new ZUOBIAO;
			//得到棋子应下点的坐标
			WherePoint(point);
			if(m_board[row][col]==NO)					           //若无子则可下子
			{
				//下黑棋子
				LoadChessHei(X,Y);
				m_board[row][col]=HEI;                              ///已落黑子
				m_color=BAI;                                        //接下来落白子

				m_coord->col = col;
				m_coord->row = row;
					//已落黑子

				jiaRu(m_coord);  
				numHuiQi = 0;

				//判断胜负
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("黑方胜利!");
					m_ifwin=true; 
				}
			}
		}
	}
	else if(m_moder==0)
	{
		//////////////////////////////////////////人机对战算法
		if(m_firstDo==0)
		{
			///////////////////////////////////////电脑先行
			//玩家行子
			if(m_color==BAI && m_ifwin==false && InGame(point)==true)
			{
				ZUOBIAO *m_coord=new ZUOBIAO;
				//得到下棋点的坐标
				WherePoint(point);
				if(m_board[row][col]==NO)                               //若无子则可下子
				{ 
					//下白棋子
					LoadChessBai(X,Y);
					m_board[row][col]=BAI;                              ///已落白子
					m_color=HEI;                                        //接下来黑白子

					m_coord->col = col;
					m_coord->row = row;
						//已落黑子

					jiaRu(m_coord); 
					numHuiQi = 0;
					///判断胜负
					if(win.ShengFu(row,col,m_board,BAI)==true)
					{
						// 将界面设为无效
						Invalidate(FALSE);
						::AfxMessageBox("您赢了!");

						m_ifwin=true;                       
					}
				}
			
				//电脑行子
				ComputerLoadChessHei();

				//判断胜负
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 

					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("您输了! 继续努力吧!");
				}
			}

		}
		else if(m_firstDo==1)
		{
			////////////////////////////////////////玩家先行
			if(m_color==HEI && m_ifwin==false && InGame(point)==true)
			{
				ZUOBIAO *m_coord=new ZUOBIAO;
				//得到棋子应下点的坐标
					WherePoint(point);
				if(m_board[row][col]==NO)					           //若无子则可下子
				{
					//下黑棋子
					LoadChessHei(X,Y);
					m_board[row][col]=HEI;                              ///已落黑子
					m_color=BAI;                                        //接下来落白子
				
					m_coord->col = col;
					m_coord->row = row;
						//已落黑子

					jiaRu(m_coord);  
					numHuiQi = 0;

					//判断胜负
					if(win.ShengFu(row,col,m_board,HEI)==true)
					{
						// 将界面设为无效
						Invalidate(FALSE);
						::AfxMessageBox("您赢了!");
						m_ifwin=true; 
					}
				}
			
				//////加入电脑行子
				ComputerLoadChessBai();
				//判断胜负
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					m_ifwin=true; 

					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("您输了! 继续努力吧!");
				}
			}

		}
		else
			return;
	}
	else
		return;

	// 将界面设为无效
	Invalidate(FALSE);
	if(bushu->num==225)
	::AfxMessageBox("和棋!");
	}

	CDialog::OnLButtonUp(nFlags, point);
}
/////////////////////右键单击下白棋子并判断胜负
void CWuziqiDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_inGame!=0)
	{
	if(m_moder==1)
	{
		if(m_color==BAI && m_ifwin==false && InGame(point)==true)
		{ZUOBIAO *m_coord=new ZUOBIAO;
			//得到下棋点的坐标
			WherePoint(point);
			if(m_board[row][col]==NO)                              //若无子则可下子
			{ 
				//下白棋子
				LoadChessBai(X,Y);
				m_board[row][col]=BAI;                              ///已落白子
				m_color=HEI;                                        //接下来落白子

				m_coord->col = col;
				m_coord->row = row;
					//已落黑子

				jiaRu(m_coord);  
				numHuiQi = 0;
				///判断胜负
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("白方胜利!");

					m_ifwin=true;                        ///白方胜利
				}

				// 将界面设为无效
				Invalidate(FALSE);
			}
		}
	}
	else
		return;
	}

	CDialog::OnRButtonUp(nFlags, point);
}
///////////////////////////////////////////////////////////////执行悔棋操作
void CWuziqiDlg::OnButtonTakeback() 
{
	if(m_ifwin==true)
		return;
	else
	{
		if(m_moder == 0 && numHuiQi == 3)
		{
			::AfxMessageBox("已达到最大悔棋数");
		}
		else
		{
			if(isHuiQi()==true)
			{
				huiQi();
				numHuiQi += 1;
			}	
			else
				::AfxMessageBox("无法悔棋！");
		}
	}
}
//重新开局
void CWuziqiDlg::OnButtonRestart() 
{
	// TODO: Add your control notification handler code here
	LoadDlgBk(m_currentBK);
	InitBoard();                                //初始化棋盘信息
	InitData();                                 //初始化棋子掩码信息
	m_menAndComputer.InitMenAndComputer();      //初始化人机对战评分记录 
	if(m_moder==0 && m_firstDo==0)
		OnMenuComputerfirst();
}

void CWuziqiDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//CString szTxt;
	//szTxt.Format("%d", point.x);
	//this->GetDlgItem(IDC_EDIT1)->SetWindowText(szTxt);
	//szTxt.Format("%d", point.y);
	//this->GetDlgItem(IDC_EDIT2)->SetWindowText(szTxt);
	if(InGame(point)==true && 	m_currentBK!=IDB_BITMAP_WELCOME)
	{
	WherePoint(point);
	int x1,y1,x2,y2;
	x1=X-18;
	y1=Y-18;
	x2=X+18;
	y2=Y+18;

	CClientDC dc(this);
	//CPen pen(PS_SOLID, 5, RGB(47, 79, 79));
	CPen pen(PS_SOLID, 5, RGB(200, 150, 79));
	CPen* pOldPen = dc.SelectObject(&pen);
	if(point.x>x1 && point.x<x2 && point.y>y1 && point.y<y2 )
	{
		dc.MoveTo(x1,y1);
		dc.LineTo(x1+10,y1);

		dc.MoveTo(x2-10,y1);
		dc.LineTo(x2,y1);

		dc.MoveTo(x1,y1);
		dc.LineTo(x1,y1+10);

		dc.MoveTo(x2,y1);
		dc.LineTo(x2,y1+10);

		dc.MoveTo(x1,y2);
		dc.LineTo(x1+10,y2);

		dc.MoveTo(x2-10,y2);
		dc.LineTo(x2,y2);

		dc.MoveTo(x1,y2);
		dc.LineTo(x1,y2-10);

		dc.MoveTo(x2,y2);
		dc.LineTo(x2,y2-10);
	}
	else
	{
		// 将界面设为无效
		Invalidate(FALSE);
		UpdateWindow();
	}
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CWuziqiDlg::jiaRu(ZUOBIAO *mes)
{
	if(bushu == 0)
	{
		mes -> num = 1;
		bushu = mes;
		mes -> next = NULL;
	}
	else
	{
		mes -> num = bushu -> num + 1;
		mes -> next = bushu;
		bushu = mes;
	}
		
}
//执行悔棋操作
void CWuziqiDlg::huiQi()
{
	if(bushu==NULL)
		::AfxMessageBox("当前无子可悔!");
	else
	{
		int k = 2;
		if(m_moder==1)
		{
			k = 1;
			if(m_color==HEI)
				m_color=BAI;
			else if(m_color==BAI)
				m_color=HEI;
		}
			for(int i = 0;i < k && bushu!=NULL;i ++)
			{
				X=22+bushu->row*35;
				Y=22+bushu->col*35;

				LoadTakeBack();
				Takeback(X,Y);
				m_board[bushu->row][bushu->col]=NO;

				bushu = bushu->next;
			}
		
	
		Invalidate(FALSE);
	}
}

//判断是否可以悔棋
bool CWuziqiDlg::isHuiQi()
{
	if(bushu==NULL)
		return false;
	else if(m_moder == 1)
	{
		return true;
	}
		
	else if(bushu -> num <= 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CWuziqiDlg::Takeback(int X,int Y)
{
	// 获得位图信息
	BITMAP bmpInfo1;
	m_bmpHuiQi.GetBitmap(&bmpInfo1);

	// 缩放贴图

	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);
	m_dcMain.StretchBlt(
					50 + bushu -> row * 40 - 20, 50 + bushu -> col * 40 - 20,
					39, 39,&m_dcHuiQi,
					50 + bushu -> row * 40 - 20, 50 + bushu -> col * 40 - 20,
					39, 39,SRCCOPY);
	//m_dcMain.StretchBlt(X-18.5,Y-18.5,45, 47, 
	//					&m_dcMask, 0, 0,bmpInfoBai.bmWidth, bmpInfoBai.bmHeight, MERGEPAINT);

}

void CWuziqiDlg::LoadTakeBack()
{
	m_bmpHuiQi.DeleteObject();                        //初始化棋子
	m_dcHuiQi.DeleteDC();

	m_dcHuiQi.CreateCompatibleDC(&m_dcMain);          //加载悔棋位图并选入内存

	m_bmpHuiQi.LoadBitmap(m_currentBK);

	m_dcHuiQi.SelectObject(m_bmpHuiQi);
}
//向电脑求助
void CWuziqiDlg::OnButtonComputerhelp() 
{
	// TODO: Add your control notification handler code here
	if(bushu!=NULL)
	{
		if(m_moder==1)
		{
			if(m_color==HEI)
			{
				ComputerLoadChessHei();
				//判断胜负
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 

					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("黑方胜利!");
				}
			}
			else if(m_color==BAI)
			{
				ComputerLoadChessBai();
				//判断胜负
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					m_ifwin=true; 

					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("白方胜利!");
				}
			}
		}
		else if(m_moder==0)
		{
			if(m_firstDo==0)
			{
				ComputerLoadChessBai();	
				//判断胜负
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					m_ifwin=true; 

					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("白方胜利!");
				}

				//加入电脑行子
				ComputerLoadChessHei();
				//判断胜负
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 

					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("您输了! 继续努力吧!");
				}
			}
			else if(m_firstDo==1)
			{
				ComputerLoadChessHei();
				//判断胜负
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 

					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("黑方胜利!");
				}

				//加入电脑行子
				ComputerLoadChessBai();
				//判断胜负
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					m_ifwin=true; 

					// 将界面设为无效
					Invalidate(FALSE);
					::AfxMessageBox("您输了! 继续努力吧!");
				}
			}
		}
		// 将界面设为无效
		Invalidate(FALSE);
		if(bushu->num==225)
		::AfxMessageBox("和棋!");
	}
	else
		return;
}
//电脑下黑棋子
void CWuziqiDlg::ComputerLoadChessHei()
{
	if(m_inGame!=0)
	{
	if(m_color==HEI && m_ifwin==false)
	{
		ZUOBIAO *m_coord=new ZUOBIAO;
		//得到棋子应下点的坐标
		//	WherePoint(point);
		m_menAndComputer.InitMenAndComputer();         //初始化人机对战评分记录 
		m_menAndComputer.ScoreComputer(m_board,BAI);   //给电脑评分
		m_menAndComputer.ScorePlayer(m_board,HEI);     //给玩家评分
		CPoint pt;
		pt=m_menAndComputer.MaxPoint();
		row=pt.x;
		col=pt.y;

		X=50+row*40;
		Y=50+col*40;

		if(m_board[row][col]==NO)					            //若无子则可下子
		{
			//下黑棋子
			LoadChessHei(X,Y);
			m_board[row][col]=HEI;                              ///已落黑子
			m_color=BAI;                                        //接下来落白子
		
			m_coord->col = col;
			m_coord->row = row;
			//已落黑子

			jiaRu(m_coord);  
			numHuiQi = 0;
		}
	}
	}
}
//电脑下白棋子
void CWuziqiDlg::ComputerLoadChessBai()
{
	if(m_inGame!=0)
	{
	if(m_color==BAI && m_ifwin==false)
	{
		ZUOBIAO *m_coord=new ZUOBIAO;
		//得到下棋点的坐标
		//WherePoint(point);
		m_menAndComputer.InitMenAndComputer();         //初始化人机对战评分记录 
		m_menAndComputer.ScoreComputer(m_board,BAI);   //给电脑评分
		m_menAndComputer.ScorePlayer(m_board,HEI);     //给玩家评分
		CPoint pt;
		pt=m_menAndComputer.MaxPoint();
		row=pt.x;
		col=pt.y;

		X=50+row*40;
		Y=50+col*40;

		if(m_board[row][col]==NO)                              //若无子则可下子
		{ 
			//下白棋子
			LoadChessBai(X,Y); 
			m_board[row][col]=BAI;                              ///已落白子
			m_color=HEI;                                        //接下来落黑子

			m_coord->col = col;
			m_coord->row = row;

			jiaRu(m_coord);
			numHuiQi = 0;
		}
	}
	}
}
//认输
void CWuziqiDlg::OnButtonLost() 
{
	// TODO: Add your control notification handler code here
	if(m_ifwin==false)
	{
		if(m_moder==0)
		{
			if(m_firstDo==0)
			{
				m_ifwin=true;
				::AfxMessageBox("玩家认输! 继续努力吧!");
			}
			else if(m_firstDo==1)
			{
				m_ifwin=true;
				::AfxMessageBox("玩家认输! 继续努力吧!");
			}
		}
		else if(m_moder==1)
		{
			if(m_color==HEI)
			{
				m_ifwin=true;
				::AfxMessageBox("黑方认输! 继续努力吧!");
			}
			else if(m_color==BAI)
			{
				m_ifwin=true;
				::AfxMessageBox("白方认输! 继续努力吧!");
			}
		}
	}
}


void CWuziqiDlg::RePaintChessBoard()
{
	int i,j;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
		{
			int x=50+i*40;
			int y=50+j*40;

			if(m_board[i][j]==BAI)
			{
				LoadChessBai(x,y);
			}
			else if(m_board[i][j]==HEI)
			{
				LoadChessHei(x,y);
			}
			else
				continue;
		}
}


void CWuziqiDlg::OnMusic1() 
{
	// 播放第一首音乐并关闭初始音乐和其他音乐
	mciSendString("close music\\background.mp3","",0,NULL);
	mciSendString("close music\\lanhua.mp3","",0,NULL);
	mciSendString("close music\\merrychristmas.mp3","",0,NULL);
	mciSendString("play music\\war1.mp3","",0,NULL);

	GetMenu()->GetSubMenu(3)->CheckMenuItem(m_musicChange, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(3)->CheckMenuItem(0, MF_BYPOSITION|MF_CHECKED);
	m_musicChange=0;
	
}

void CWuziqiDlg::OnMusic2() 
{
	// 播放第二首音乐并关闭初始音乐和其他音乐
	mciSendString("close music\\background.mp3","",0,NULL);
	mciSendString("close music\\war1.mp3","",0,NULL);
	mciSendString("close music\\merrychristmas.mp3","",0,NULL);
	mciSendString("play music\\lanhua.mp3","",0,NULL);

	GetMenu()->GetSubMenu(3)->CheckMenuItem(m_musicChange, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(3)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	m_musicChange=1;
	
}

void CWuziqiDlg::OnMusic3() 
{
	// 播放第三首音乐并关闭初始音乐和其他音乐
	mciSendString("close music\\background.mp3","",0,NULL);
	mciSendString("close music\\lanhua.mp3","",0,NULL);
	mciSendString("close music\\war1.mp3","",0,NULL);
	mciSendString("play music\\merrychristmas.mp3","",0,NULL);
	
	GetMenu()->GetSubMenu(3)->CheckMenuItem(m_musicChange, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(3)->CheckMenuItem(2, MF_BYPOSITION|MF_CHECKED);
	m_musicChange=2;

}

void CWuziqiDlg::OnMusicClose() 
{
	//关闭所有音乐
	mciSendString("close music\\background.mp3","",0,NULL);
	mciSendString("close music\\lanhua.mp3","",0,NULL);
	mciSendString("close music\\war1.mp3","",0,NULL);
	mciSendString("close music\\merrychristmas.mp3","",0,NULL);

	GetMenu()->GetSubMenu(3)->CheckMenuItem(m_musicChange, MF_BYPOSITION|MF_UNCHECKED);
	GetMenu()->GetSubMenu(3)->CheckMenuItem(3, MF_BYPOSITION|MF_CHECKED);
	m_musicChange=3;

}

void CWuziqiDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(point.x>730 && point.y>590 && m_inGame!=0)
	{
		OnOK();
	}
	CDialog::OnLButtonDown(nFlags, point);
}
/*
void CWuziqiDlg::TenX(int x,int y)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);

	dc.MoveTo(x-5,y);
	dc.LineTo(x+5,y);

	dc.MoveTo(x,y-5);
	dc.LineTo(x,y+5);
}
*/

void CWuziqiDlg::OnMenuStart() 
{
	// TODO: Add your command handler code here
	if(m_inGame==0)
	{
		LoadDlgBk(IDB_BITMAP3);
		m_currentBK=IDB_BITMAP3;
		m_moder=0;
		m_firstDo=1;                  //开始游戏默认人机对战 人先行
		m_inGame=1;
		OnButtonRestart();

		m_restart.ShowWindow(SW_SHOW);
		m_computerhelp.ShowWindow(SW_SHOW);
		m_lost.ShowWindow(SW_SHOW);
		m_takeback.ShowWindow(SW_SHOW);
	}
	else
		OnButtonRestart();
}

void CWuziqiDlg::OnMenuTakeback() 
{
	// TODO: Add your command handler code here
	OnButtonTakeback();
}

void CWuziqiDlg::OnMenuHelp() 
{
	// TODO: Add your command handler code here
	OnButtonComputerhelp();
}

void CWuziqiDlg::OnMenuLost() 
{
	// TODO: Add your command handler code here
	OnButtonLost();
}

void CWuziqiDlg::OnMenuSave() 
{
	CString file_path;
	CFileDialog m_store(false,NULL,"*.wuziqi",OFN_EXPLORER | OFN_NOCHANGEDIR,"棋盘文件(.wuziqi)|*.wuziqi||");
	if(m_store.DoModal()==IDOK) 
	{
		file_path=m_store.GetPathName();
		if(file_path.Right(7)!=".wuziqi")
		{
			file_path+=".wuziqi";
		}
		CString fileName = m_store.GetFileTitle();
		ofstream fileout;
    		fileout.open(file_path);
			fileout << bushu->num << ' ';
			ZUOBIAO *swap = bushu;
			int i = bushu->num;
			for(i = 1;i<=bushu->num;i++){
				ZUOBIAO *swap = bushu;
    			for(int j = 0; ;j++){
					if(swap->num == i){
						fileout << swap->row<<' '<<swap->col<<'\n';
						break;
					}
					swap=swap->next;
				}
			}

    	fileout  << flush; 
		fileout.close();
	}	
}

void CWuziqiDlg::OnMenuOpen() 
{
		CString file_path;
	CFileDialog m_store(true,NULL,"*.wuziqi",OFN_EXPLORER | OFN_NOCHANGEDIR,"棋盘文件(.wuziqi)|*.wuziqi||");
	if(m_store.DoModal()==IDOK) 
	{
		file_path=m_store.GetPathName();

		ifstream fileIn;
    	fileIn.open(file_path);
/////////////////////////////////////////////////////

		fileIn >> num;
		
		bushu = new ZUOBIAO;
		fileIn >> bushu->row >> bushu->col;
		bushu->num = 1;


		ZUOBIAO *a ;
		for(int i =1;i<num;i++){
			a = new ZUOBIAO;
			fileIn >> a->row >> a->col;
			jiaRu(a);
		}
		fileIn.close();
		SetTimer(9,1000,NULL);
////////////////////////////////////////////////////////////////////////////////////////
	
			LoadDlgBk(m_currentBK);
	}
}

void CWuziqiDlg::OnMenuExit() 
{
	// TODO: Add your command handler code here
	OnOK();
}

void CWuziqiDlg::OnTimer(UINT nIDEvent) 
{
		for(int i=0;i<15;i++)
		{
			for(int j=0;j<15;j++)
			m_board[i][j]=0;
		}
		InitData();

			ZUOBIAO *swap = bushu;
    		for(int j = 0; ;j++){
				if(swap->num == r){

					break;
				}
				swap=swap->next;
			}

			X=50+swap->row*40;
			Y=50+swap->col*40;
			if(r%2==1){
				LoadChessHei(X,Y);
			}
			else{
				LoadChessBai(X,Y);
			}
			if(num == swap->num){
					r = 1 ;
				KillTimer(9);
			}

			r++;
		

		Invalidate(FALSE);		
	CDialog::OnTimer(nIDEvent);
}


void CWuziqiDlg::OnHelp() 
{
	// TODO: Add your command handler code here
::AfxMessageBox("游戏控制\n\
1、背景切换\n\
本游戏提供了四张不同的星云棋盘供玩家选择，玩家可按自身爱好随意选择和切换。\n\n\
2、对战模式选择\n\
游戏分为两种对战模式，人人对战和人机对战。选择人人对战后，点击鼠标左键落\n\
黑棋，点击鼠标右键落白棋。选择人机对战之后，继续选择是玩家先落子还是电脑\n\
先落子，然后由玩家和电脑进行对战。\n\n\
3、背景音乐切换\n\
进入游戏后，会自动播放一首背景音乐。玩家还可自行选择其他背景音乐或者关闭\n\
音乐。\n\
游戏功能\n\n\n\
1、悔棋\n\
玩家在游戏中可以取消上一步的落子进行重新落子，在人机对战游戏中可以最多连\n\
续悔棋3次，在人人对战中可以无限制悔棋直至棋盘无子为止！\n\n\
2、重新开局\n\
点击重新开具，直接开始新的一局游戏！\n\n\
3、求助\n\
落子困难时刻，点击求助可由电脑帮助你落子哦！\n\n\
4、认输\n\
点击认输，承认失败吧！下次继续努力吧！",MB_OK);

}

void CWuziqiDlg::OnMenuAb() 
{
	// TODO: Add your command handler code here
::AfxMessageBox("有关五子棋\n\
五子棋是起源于中国古代的传统黑白棋种之一。现代五子棋日文称之为\n\
连珠 ,英译为 Renju ,英文称之为 Gobang  或 FIR (Five in  a Row\n\
的缩写 ) ,亦有 连五子 , 五子连 , 串珠 , 五目, 五目碰 , 五格 等\n\
多种称谓.\n\n\n\
五子棋不仅能增强思维能力，提高智力，而且富含哲理，有助于修身养性。\n\
五子棋既有现代休闲的明显特征   短,平,快   ,又有古典哲学的高深学问\n\
阴阳易理 ;它既有简单易学的特性,为人民群众所喜闻乐见,又有深奥的技\n\
巧和高水平的国际性比赛；它的棋文化源渊流长，具有东方的神秘和西方\n\
的直观；既有   场   的概念，亦有   点   的连接。它是中西文化的交\n\
流点,是古今哲理的结晶. \n\n\n\
五子棋起源于古代中国,发展于日本,风靡于欧洲.对于它与围棋的关系有两种\n\
说法,一说早于围棋,早在   尧造围棋   之前,民间就已有五子棋游戏;一说\n\
源于围棋,是围棋发展的一个分支.在中国的文化里,倍受人们的青睐.古代的\n\
五子棋的棋具与围棋相同,纵横各十七道.五子棋大约随围棋一起在我国南北\n\
朝时先后传入朝鲜,日本等地.本世纪初五子棋传入欧洲并迅速风靡全欧。通\n\
过一系列的变化,使五子棋这一简单的游戏复杂化,规范化,而最终成为今天\n\
的职业连珠五子棋,同时也成为一种国际比赛棋. \n\n\n\
下棋时.由持黑棋的一方先下子.以后双方轮流下子.每次只能下一个子,棋子\n\
落在棋盘的点上,棋子下定以后,不得向其他点移动.哪一方的棋子率先连成5\n\
个,哪一方便赢.这就是五子棋的规则.",MB_OK);
}
