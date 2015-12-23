// TakeBack.cpp: implementation of the CTakeBack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wuziqi.h"
#include "TakeBack.h"
#include "WuziqiDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//   在主类中加上 huiqi 类成员		

//   加上 悔棋位图     CDC		m_dchuiqi;  CBitmap		 m_bmphuiqi;

//   用bushu()记录下棋次数huiQiCiShu(也是总的次数)  我暂定为3次

//使用悔棋huiQi()前请先用判断是否可以isHuiQi()

//用display()返回可以悔棋的次数

//	悔棋就是用悔棋出的棋盘的小部分覆盖上  记录其棋盘 行row 列col 替换	
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//构造函数  初始化函数
CTakeBack::CTakeBack()
{
	bushu = 0;                      //还未下棋子

	heiCiShu = 0;                 //黑棋悔棋次数为0
	baiCiShu = 0;                 //白棋悔棋次数为0

	numZUOBIAO = 0;
	
	m_bmpHuiQi.DeleteObject();                    //初始化棋子
	m_dcHuiQi.DeleteDC();
}

/////////////////////////////////////////加入悔棋链表
void CTakeBack::jiaRu(ZUOBIAO *mes)
{
	if(bushu == 0)
	{
		bushu = mes;
		mes->next = 0;
		numZUOBIAO +=1;
	}
	else if(numZUOBIAO < (2*MAXHUIQI - heiCiShu - baiCiShu)*2)
	{
		mes->next=bushu;
		bushu=mes; 
		numZUOBIAO+=1;
	}
	else 
	{
		mes->next = bushu;
		bushu = mes; 

///////////////////////////////////////////消除超过悔棋步数
		ZUOBIAO *swap;
		swap = bushu;
		for(int i = 0;i < (2*MAXHUIQI - heiCiShu - baiCiShu)*2;i++)
		{
			swap = swap->next;
		}
		swap = 0;
	}
}
//执行悔棋操作
void CTakeBack::huiQi(int color)
{
	if(bushu==NULL)
		::AfxMessageBox("当前无子可悔!");
	else
	{
		for(int i = 0;i <= 2 && bushu!=NULL;i ++)
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//贴图  忘了
			//已知坐标bushu.row  bushu.col
			CWuziqiDlg Wuziqi;
			if(color==BAI)
			{
				m_X=95+bushu->row*37;
				m_Y=50+bushu->col*37;

				Wuziqi.LoadChessBai(m_X,m_Y);
			}
			else if(color==HEI)
			{
				m_X=95+bushu->row*37;
				m_Y=50+bushu->col*37;

				Wuziqi.LoadChessHei(m_X,m_Y);
			}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
			bushu = bushu->next;
		}
		numZUOBIAO -= 2;
	
	//////////////////////////////////记录一次对应颜色的下棋次数
		if(color == BAI)
			baiCiShu += 1;
		else
			heiCiShu += 1;
	}
}

//判断是否可以悔棋
bool CTakeBack::isHuiQi(int color)
{
	if(color == BAI )
	{
		if( (baiCiShu != MAXHUIQI) && (numZUOBIAO >= 2)	)
			return true;
		else
			return false;
	}
	else if(color == HEI )
	{
		if((heiCiShu!=MAXHUIQI) && (numZUOBIAO>= 1))
			return true;
		else
			return false;
	}
}
/////////////////////////////显示可悔棋次数
int CTakeBack::display(int color)
{
	int a,b;
	a=MAXHUIQI - baiCiShu;
	b=MAXHUIQI - heiCiShu;
	if(color == BAI)
		return a;
	else if(color == HEI)
		return b;
}
CTakeBack::~CTakeBack()
{
	m_dcHuiQi.DeleteDC();

	m_bmpHuiQi.DeleteObject();

}
