// TakeBack.h: interface for the CTakeBack class.
//
//////////////////////////////////////////////////////////////////////
//   在主类中加上 huiqi 类成员		

//   加上 悔棋位图     CDC		m_dchuiqi;  CBitmap		 m_bmphuiqi;

//   用bushu(){}记录下棋次数huiQiCiShu(也是总的次数)  我暂定为3次

//使用悔棋huiQi()前请先用判断是否可以isHuiQi()

//用display()返回可以悔棋的次数

//	悔棋就是用悔棋出的棋盘的小部分覆盖上  记录其棋盘 行row 列col 替换	
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAKEBACK_H__8839E90C_BEA0_4D50_8A0F_E7C370082697__INCLUDED_)
#define AFX_TAKEBACK_H__8839E90C_BEA0_4D50_8A0F_E7C370082697__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXHUIQI 3     /////////////悔棋的次数
#define BAI 1	                   //白子     1
#define HEI 2	                   //黑子     2

////////////////////////////对于已下棋子的棋盘坐标（row,col）横列
struct ZUOBIAO{
	int row;
	int col;
	ZUOBIAO *next;
};

class CTakeBack  
{
public:
	CTakeBack();                       //构造函数
	virtual ~CTakeBack();


/////////////////////////////////////////加入悔棋信息
	void jiaRu(ZUOBIAO *mes);

/////////////////////////////////////////悔棋
	void huiQi(int);

//////////////////////////////////////////是否可以悔棋  可以则返回1 
	bool isHuiQi(int color);

////////////////////////////////////////////显示可以悔棋次数
	int display(int color);


private:

	// 主内存设备与位图 
	CDC		m_dcHuiQi;
	CBitmap m_bmpHuiQi;

//////////////////////////////////悔棋链表
	ZUOBIAO * bushu;

/////////////////////////////////记录悔棋次数
	int baiCiShu;
	int heiCiShu;

////////////////////////////////悔棋链表的长度
	int numZUOBIAO;

	int m_X;                     //悔棋点坐标
	int m_Y;
};	

#endif // !defined(AFX_TAKEBACK_H__8839E90C_BEA0_4D50_8A0F_E7C370082697__INCLUDED_)
