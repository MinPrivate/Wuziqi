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

	LoadDlgBk(IDB_BITMAP_WELCOME);     //���ػ�ӭ����
	m_currentBK=IDB_BITMAP_WELCOME;
	m_inGame=0;                        //δ������Ϸ����
	GetMenu()->GetSubMenu(1)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	GetMenu()->GetSubMenu(2)->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	GetMenu()->GetSubMenu(2)->GetSubMenu(1)->CheckMenuItem(0, MF_BYPOSITION|MF_CHECKED);

	m_bkChange=1;

	InitData();                 //��ʼ������������Ϣ
	InitBoard();                //��ʼ��������Ϣ
	bushu = NULL;               //��������
	//m_moder=0;                  //Ĭ��Ϊ���˶�ս
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
		//��ȡ�ͻ������С
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
//���ر���ͼƬ
void CWuziqiDlg::LoadDlgBk(int iBmpID)
{
	m_dcMain.DeleteDC();
	m_dcBK.DeleteDC();
	m_bmpMain.DeleteObject();
	m_bmpBK.DeleteObject();

	//��ȡ�ͻ������С
	CRect rect;
	GetClientRect(rect);

	//���Ʊ���
	CClientDC dc(this);								// Get a dc for a CWnd object pointer.
	m_dcMain.CreateCompatibleDC(&dc);				//����ָ��DC������һ���ڴ��豸������
	m_bmpMain.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);	//����ָ��dc����ʼ��Bitmap���󣬲�ָ����С
	m_dcMain.SelectObject(&m_bmpMain);				//ѡ��һ��Bitmap����

	m_dcBK.CreateCompatibleDC(&m_dcMain);			//��ȡһ���ڴ��豸������
	m_bmpBK.LoadBitmap(iBmpID);						//����Bitmap�����ȡͼƬ
	m_dcBK.SelectObject(m_bmpBK);					//����ͼ���豸����ѡ��һ��Bitmap����

	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);	//ָ���豸����չģʽ
													//STRETCH_HALFTONE :��ͬCOLORONCOLOR
													//ɾ�����أ����ģʽɾ�����д�ɾ���������У������������ǵ���Ϣ��
	
	//������Դ�����и���һ��λͼ��Ŀ����Σ���Ҫʱ��ĿǰĿ���豸����ģʽ����ͼ��������ѹ��
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
	//�ͷ���Դ
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

	InitBoard();                               //��ʼ��������Ϣ
	InitData();                                //��ʼ������������Ϣ
	m_menAndComputer.InitMenAndComputer();     //��ʼ���˻���ս���ּ�¼ 

		if(m_color==HEI && m_ifwin==false)
		{
			ZUOBIAO *m_coord=new ZUOBIAO;
			//�õ�����Ӧ�µ������
			//WherePoint(point);
			row=7;
			col=7;
			X=50+row*40;
			Y=50+col*40;

			if(m_board[row][col]==NO)					           //�������������
			{
				//�º�����
				LoadChessHei(X,Y);
				m_board[row][col]=HEI;                              ///�������
				m_color=BAI;                                        //�����������
		
				m_coord->col = col;
				m_coord->row = row;
					//�������

				jiaRu(m_coord);  
				numHuiQi = 0;

				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 
				}
			}
		}
		// ��������Ϊ��Ч
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

////////////////��ʼ��������Ϣ
void CWuziqiDlg::InitBoard()
{
	m_color=HEI;                 //��������
	m_ifwin=false;               //û��ʤ��
	bushu=NULL;
	//��ʼ���������Ӵ�����Ϣ  �����������ʼ��Ϊ0
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
			m_board[i][j]=0;
	}

}
////////////////////////��ʼ��������Ϣ
void CWuziqiDlg::InitData()
{
	// ��ʼ�ڴ��豸��λͼ
	m_bmpChessHei.DeleteObject();                    //��ʼ��������
	m_dcChessHei.DeleteDC();
	
	m_bmpChessBai.DeleteObject();                    //��ʼ��������
	m_dcChessBai.DeleteDC();

	m_bmpMask.DeleteObject();                        //��ʼ������
	m_dcMask.DeleteDC();

	// ����λͼ��ѡ���ڴ��豸
	m_dcChessHei.CreateCompatibleDC(&m_dcMain);      //���غ����Ӳ�ѡ���ڴ�
	m_bmpChessHei.LoadBitmap(IDB_BITMAP_HEI);
	m_dcChessHei.SelectObject(m_bmpChessHei);

	m_dcChessBai.CreateCompatibleDC(&m_dcMain);      //���ذ����Ӳ�ѡ���ڴ�
	m_bmpChessBai.LoadBitmap(IDB_BITMAP_BAI);
	m_dcChessBai.SelectObject(m_bmpChessBai);

	m_dcMask.CreateCompatibleDC(&m_dcMain);          //�������벢ѡ���ڴ�
	m_bmpMask.LoadBitmap(IDB_BITMAP_MASK);
	m_dcMask.SelectObject(m_bmpMask);
}
///////////////////�º�����
void CWuziqiDlg::LoadChessHei(int X,int Y)
{
	PlaySound("res\\play.wav", AfxGetInstanceHandle(), SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	// ���λͼ��Ϣ
	BITMAP bmpInfoHei;
	m_bmpChessHei.GetBitmap(&bmpInfoHei);

	// ������ͼ

	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);
	//���������������
	m_dcChessHei.BitBlt(0,0,bmpInfoHei.bmWidth, bmpInfoHei.bmHeight,
						&m_dcMask,0,0,SRCPAINT);
	//���������������
	//�ӵ�
	m_dcMain.StretchBlt(X-17,Y-18,34, 34, 
						&m_dcMask, 0, 0,bmpInfoHei.bmWidth, bmpInfoHei.bmHeight, MERGEPAINT);
	//�ϳ�����͸��λͼ

	m_dcMain.StretchBlt(X-17,Y-18, 35, 37, 
						&m_dcChessHei, 0, 0, bmpInfoHei.bmWidth, bmpInfoHei.bmHeight, SRCAND);
}
//////////////////////�°�����
void CWuziqiDlg::LoadChessBai(int X,int Y)
{
PlaySound("res\\play.wav", AfxGetInstanceHandle(), SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	// ���λͼ��Ϣ
	BITMAP bmpInfoBai;
	m_bmpChessBai.GetBitmap(&bmpInfoBai);

	// ������ͼ

	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);
	//���������������
	m_dcChessBai.BitBlt(0,0,bmpInfoBai.bmWidth, bmpInfoBai.bmHeight,
						&m_dcMask,0,0,SRCPAINT);
	//���������������
	m_dcMain.BitBlt(X-17,Y-18,bmpInfoBai.bmWidth, 100,
						&m_dcMask,bmpInfoBai.bmWidth,0,MERGEPAINT);
	//�ϳ�����͸��λͼ
	//�ӵ�
	m_dcMain.StretchBlt(X-17,Y-18,34, 34, 
						&m_dcMask, 0, 0,bmpInfoBai.bmWidth, bmpInfoBai.bmHeight, MERGEPAINT);

	m_dcMain.StretchBlt(X-17,Y-18, 
						35, 37, &m_dcChessBai, 0, 0, bmpInfoBai.bmWidth, bmpInfoBai.bmHeight, SRCAND);
}
///////////////�ж��Ƿ������̷�Χ��
bool CWuziqiDlg::InGame(CPoint point)
{
	if(point.x<30 ||point.y<30 ||point.x>630 ||point.y>630)
		return false;
	else 
		return true;
}
///////////////ȷ�����ӵ������
void CWuziqiDlg::WherePoint(CPoint point)
{
	row=(point.x-30)/40;
	col=(point.y-30)/40;

	X=50+row*40;
	Y=50+col*40;
}
//////////////��������º��Ӳ��ж�ʤ��
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
			//�õ�����Ӧ�µ������
			WherePoint(point);
			if(m_board[row][col]==NO)					           //�������������
			{
				//�º�����
				LoadChessHei(X,Y);
				m_board[row][col]=HEI;                              ///�������
				m_color=BAI;                                        //�����������

				m_coord->col = col;
				m_coord->row = row;
					//�������

				jiaRu(m_coord);  
				numHuiQi = 0;

				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("�ڷ�ʤ��!");
					m_ifwin=true; 
				}
			}
		}
	}
	else if(m_moder==0)
	{
		//////////////////////////////////////////�˻���ս�㷨
		if(m_firstDo==0)
		{
			///////////////////////////////////////��������
			//�������
			if(m_color==BAI && m_ifwin==false && InGame(point)==true)
			{
				ZUOBIAO *m_coord=new ZUOBIAO;
				//�õ�����������
				WherePoint(point);
				if(m_board[row][col]==NO)                               //�������������
				{ 
					//�°�����
					LoadChessBai(X,Y);
					m_board[row][col]=BAI;                              ///�������
					m_color=HEI;                                        //�������ڰ���

					m_coord->col = col;
					m_coord->row = row;
						//�������

					jiaRu(m_coord); 
					numHuiQi = 0;
					///�ж�ʤ��
					if(win.ShengFu(row,col,m_board,BAI)==true)
					{
						// ��������Ϊ��Ч
						Invalidate(FALSE);
						::AfxMessageBox("��Ӯ��!");

						m_ifwin=true;                       
					}
				}
			
				//��������
				ComputerLoadChessHei();

				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 

					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("������! ����Ŭ����!");
				}
			}

		}
		else if(m_firstDo==1)
		{
			////////////////////////////////////////�������
			if(m_color==HEI && m_ifwin==false && InGame(point)==true)
			{
				ZUOBIAO *m_coord=new ZUOBIAO;
				//�õ�����Ӧ�µ������
					WherePoint(point);
				if(m_board[row][col]==NO)					           //�������������
				{
					//�º�����
					LoadChessHei(X,Y);
					m_board[row][col]=HEI;                              ///�������
					m_color=BAI;                                        //�����������
				
					m_coord->col = col;
					m_coord->row = row;
						//�������

					jiaRu(m_coord);  
					numHuiQi = 0;

					//�ж�ʤ��
					if(win.ShengFu(row,col,m_board,HEI)==true)
					{
						// ��������Ϊ��Ч
						Invalidate(FALSE);
						::AfxMessageBox("��Ӯ��!");
						m_ifwin=true; 
					}
				}
			
				//////�����������
				ComputerLoadChessBai();
				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					m_ifwin=true; 

					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("������! ����Ŭ����!");
				}
			}

		}
		else
			return;
	}
	else
		return;

	// ��������Ϊ��Ч
	Invalidate(FALSE);
	if(bushu->num==225)
	::AfxMessageBox("����!");
	}

	CDialog::OnLButtonUp(nFlags, point);
}
/////////////////////�Ҽ������°����Ӳ��ж�ʤ��
void CWuziqiDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_inGame!=0)
	{
	if(m_moder==1)
	{
		if(m_color==BAI && m_ifwin==false && InGame(point)==true)
		{ZUOBIAO *m_coord=new ZUOBIAO;
			//�õ�����������
			WherePoint(point);
			if(m_board[row][col]==NO)                              //�������������
			{ 
				//�°�����
				LoadChessBai(X,Y);
				m_board[row][col]=BAI;                              ///�������
				m_color=HEI;                                        //�����������

				m_coord->col = col;
				m_coord->row = row;
					//�������

				jiaRu(m_coord);  
				numHuiQi = 0;
				///�ж�ʤ��
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("�׷�ʤ��!");

					m_ifwin=true;                        ///�׷�ʤ��
				}

				// ��������Ϊ��Ч
				Invalidate(FALSE);
			}
		}
	}
	else
		return;
	}

	CDialog::OnRButtonUp(nFlags, point);
}
///////////////////////////////////////////////////////////////ִ�л������
void CWuziqiDlg::OnButtonTakeback() 
{
	if(m_ifwin==true)
		return;
	else
	{
		if(m_moder == 0 && numHuiQi == 3)
		{
			::AfxMessageBox("�Ѵﵽ��������");
		}
		else
		{
			if(isHuiQi()==true)
			{
				huiQi();
				numHuiQi += 1;
			}	
			else
				::AfxMessageBox("�޷����壡");
		}
	}
}
//���¿���
void CWuziqiDlg::OnButtonRestart() 
{
	// TODO: Add your control notification handler code here
	LoadDlgBk(m_currentBK);
	InitBoard();                                //��ʼ��������Ϣ
	InitData();                                 //��ʼ������������Ϣ
	m_menAndComputer.InitMenAndComputer();      //��ʼ���˻���ս���ּ�¼ 
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
		// ��������Ϊ��Ч
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
//ִ�л������
void CWuziqiDlg::huiQi()
{
	if(bushu==NULL)
		::AfxMessageBox("��ǰ���ӿɻ�!");
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

//�ж��Ƿ���Ի���
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
	// ���λͼ��Ϣ
	BITMAP bmpInfo1;
	m_bmpHuiQi.GetBitmap(&bmpInfo1);

	// ������ͼ

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
	m_bmpHuiQi.DeleteObject();                        //��ʼ������
	m_dcHuiQi.DeleteDC();

	m_dcHuiQi.CreateCompatibleDC(&m_dcMain);          //���ػ���λͼ��ѡ���ڴ�

	m_bmpHuiQi.LoadBitmap(m_currentBK);

	m_dcHuiQi.SelectObject(m_bmpHuiQi);
}
//���������
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
				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 

					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("�ڷ�ʤ��!");
				}
			}
			else if(m_color==BAI)
			{
				ComputerLoadChessBai();
				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					m_ifwin=true; 

					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("�׷�ʤ��!");
				}
			}
		}
		else if(m_moder==0)
		{
			if(m_firstDo==0)
			{
				ComputerLoadChessBai();	
				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					m_ifwin=true; 

					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("�׷�ʤ��!");
				}

				//�����������
				ComputerLoadChessHei();
				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 

					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("������! ����Ŭ����!");
				}
			}
			else if(m_firstDo==1)
			{
				ComputerLoadChessHei();
				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,HEI)==true)
				{
					m_ifwin=true; 

					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("�ڷ�ʤ��!");
				}

				//�����������
				ComputerLoadChessBai();
				//�ж�ʤ��
				if(win.ShengFu(row,col,m_board,BAI)==true)
				{
					m_ifwin=true; 

					// ��������Ϊ��Ч
					Invalidate(FALSE);
					::AfxMessageBox("������! ����Ŭ����!");
				}
			}
		}
		// ��������Ϊ��Ч
		Invalidate(FALSE);
		if(bushu->num==225)
		::AfxMessageBox("����!");
	}
	else
		return;
}
//�����º�����
void CWuziqiDlg::ComputerLoadChessHei()
{
	if(m_inGame!=0)
	{
	if(m_color==HEI && m_ifwin==false)
	{
		ZUOBIAO *m_coord=new ZUOBIAO;
		//�õ�����Ӧ�µ������
		//	WherePoint(point);
		m_menAndComputer.InitMenAndComputer();         //��ʼ���˻���ս���ּ�¼ 
		m_menAndComputer.ScoreComputer(m_board,BAI);   //����������
		m_menAndComputer.ScorePlayer(m_board,HEI);     //���������
		CPoint pt;
		pt=m_menAndComputer.MaxPoint();
		row=pt.x;
		col=pt.y;

		X=50+row*40;
		Y=50+col*40;

		if(m_board[row][col]==NO)					            //�������������
		{
			//�º�����
			LoadChessHei(X,Y);
			m_board[row][col]=HEI;                              ///�������
			m_color=BAI;                                        //�����������
		
			m_coord->col = col;
			m_coord->row = row;
			//�������

			jiaRu(m_coord);  
			numHuiQi = 0;
		}
	}
	}
}
//�����°�����
void CWuziqiDlg::ComputerLoadChessBai()
{
	if(m_inGame!=0)
	{
	if(m_color==BAI && m_ifwin==false)
	{
		ZUOBIAO *m_coord=new ZUOBIAO;
		//�õ�����������
		//WherePoint(point);
		m_menAndComputer.InitMenAndComputer();         //��ʼ���˻���ս���ּ�¼ 
		m_menAndComputer.ScoreComputer(m_board,BAI);   //����������
		m_menAndComputer.ScorePlayer(m_board,HEI);     //���������
		CPoint pt;
		pt=m_menAndComputer.MaxPoint();
		row=pt.x;
		col=pt.y;

		X=50+row*40;
		Y=50+col*40;

		if(m_board[row][col]==NO)                              //�������������
		{ 
			//�°�����
			LoadChessBai(X,Y); 
			m_board[row][col]=BAI;                              ///�������
			m_color=HEI;                                        //�����������

			m_coord->col = col;
			m_coord->row = row;

			jiaRu(m_coord);
			numHuiQi = 0;
		}
	}
	}
}
//����
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
				::AfxMessageBox("�������! ����Ŭ����!");
			}
			else if(m_firstDo==1)
			{
				m_ifwin=true;
				::AfxMessageBox("�������! ����Ŭ����!");
			}
		}
		else if(m_moder==1)
		{
			if(m_color==HEI)
			{
				m_ifwin=true;
				::AfxMessageBox("�ڷ�����! ����Ŭ����!");
			}
			else if(m_color==BAI)
			{
				m_ifwin=true;
				::AfxMessageBox("�׷�����! ����Ŭ����!");
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
	// ���ŵ�һ�����ֲ��رճ�ʼ���ֺ���������
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
	// ���ŵڶ������ֲ��رճ�ʼ���ֺ���������
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
	// ���ŵ��������ֲ��رճ�ʼ���ֺ���������
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
	//�ر���������
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
		m_firstDo=1;                  //��ʼ��ϷĬ���˻���ս ������
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
	CFileDialog m_store(false,NULL,"*.wuziqi",OFN_EXPLORER | OFN_NOCHANGEDIR,"�����ļ�(.wuziqi)|*.wuziqi||");
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
	CFileDialog m_store(true,NULL,"*.wuziqi",OFN_EXPLORER | OFN_NOCHANGEDIR,"�����ļ�(.wuziqi)|*.wuziqi||");
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
::AfxMessageBox("��Ϸ����\n\
1�������л�\n\
����Ϸ�ṩ�����Ų�ͬ���������̹����ѡ����ҿɰ�����������ѡ����л���\n\n\
2����սģʽѡ��\n\
��Ϸ��Ϊ���ֶ�սģʽ�����˶�ս���˻���ս��ѡ�����˶�ս�󣬵����������\n\
���壬�������Ҽ�����塣ѡ���˻���ս֮�󣬼���ѡ������������ӻ��ǵ���\n\
�����ӣ�Ȼ������Һ͵��Խ��ж�ս��\n\n\
3�����������л�\n\
������Ϸ�󣬻��Զ�����һ�ױ������֡���һ�������ѡ�������������ֻ��߹ر�\n\
���֡�\n\
��Ϸ����\n\n\n\
1������\n\
�������Ϸ�п���ȡ����һ�������ӽ����������ӣ����˻���ս��Ϸ�п��������\n\
������3�Σ������˶�ս�п��������ƻ���ֱ����������Ϊֹ��\n\n\
2�����¿���\n\
������¿��ߣ�ֱ�ӿ�ʼ�µ�һ����Ϸ��\n\n\
3������\n\
��������ʱ�̣�����������ɵ��԰���������Ŷ��\n\n\
4������\n\
������䣬����ʧ�ܰɣ��´μ���Ŭ���ɣ�",MB_OK);

}

void CWuziqiDlg::OnMenuAb() 
{
	// TODO: Add your command handler code here
::AfxMessageBox("�й�������\n\
����������Դ���й��Ŵ��Ĵ�ͳ�ڰ�����֮һ���ִ����������ĳ�֮Ϊ\n\
���� ,Ӣ��Ϊ Renju ,Ӣ�ĳ�֮Ϊ Gobang  �� FIR (Five in  a Row\n\
����д ) ,���� ������ , ������ , ���� , ��Ŀ, ��Ŀ�� , ��� ��\n\
���ֳ�ν.\n\n\n\
�����岻������ǿ˼ά������������������Ҹ��������������������ԡ�\n\
����������ִ����е���������   ��,ƽ,��   ,���йŵ���ѧ�ĸ���ѧ��\n\
�������� ;�����м���ѧ������,Ϊ����Ⱥ����ϲ���ּ�,������µļ�\n\
�ɺ͸�ˮƽ�Ĺ����Ա������������Ļ�ԴԨ���������ж��������غ�����\n\
��ֱ�ۣ�����   ��   �ĸ������   ��   �����ӡ����������Ļ��Ľ�\n\
����,�ǹŽ�����Ľᾧ. \n\n\n\
��������Դ�ڹŴ��й�,��չ���ձ�,������ŷ��.��������Χ��Ĺ�ϵ������\n\
˵��,һ˵����Χ��,����   Ң��Χ��   ֮ǰ,����������������Ϸ;һ˵\n\
Դ��Χ��,��Χ�巢չ��һ����֧.���й����Ļ���,�������ǵ�����.�Ŵ���\n\
������������Χ����ͬ,�ݺ��ʮ�ߵ�.�������Լ��Χ��һ�����ҹ��ϱ�\n\
��ʱ�Ⱥ��볯��,�ձ��ȵ�.�����ͳ������崫��ŷ�޲�Ѹ�ٷ���ȫŷ��ͨ\n\
��һϵ�еı仯,ʹ��������һ�򵥵���Ϸ���ӻ�,�淶��,�����ճ�Ϊ����\n\
��ְҵ����������,ͬʱҲ��Ϊһ�ֹ��ʱ�����. \n\n\n\
����ʱ.�ɳֺ����һ��������.�Ժ�˫����������.ÿ��ֻ����һ����,����\n\
�������̵ĵ���,�����¶��Ժ�,�������������ƶ�.��һ����������������5\n\
��,��һ����Ӯ.�����������Ĺ���.",MB_OK);
}
