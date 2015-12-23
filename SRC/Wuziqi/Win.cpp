// Win.cpp: implementation of the CWin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wuziqi.h"
#include "Win.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWin::CWin()
{
	iHeng =1;
	iShu = 1;
	iZuo = 1;
	iYou = 1;
}

CWin::~CWin()
{

}
bool CWin::ShengFu(int row,int col,int m_board[][15],int iYanSe)
{
//////////////

	if(row > 0)
	{
		for(int i = row - 1;i != -1 && m_board[i][col] == iYanSe;i --)
			iHeng += 1;
	}
	if(row < 14)
	{
		for(int i = row + 1;i != 15 && m_board[i][col] == iYanSe;i ++)
			iHeng += 1;
	}


//////////////


	if(col > 0)
	{
		for(int i = col - 1;i != -1 && m_board[row][i] == iYanSe;i --)
			iShu += 1;
	}
	if(col < 14)
	{
		for(int i = col + 1;i != 15 && m_board[row][i] == iYanSe;i ++)
			iShu += 1;
	}


/////////////


	if(row > 0 && col > 0)
	{
		for(int i = row - 1,int j = col - 1;i != -1 && j != -1 && m_board[i][j] == iYanSe;i --,j --)
			iZuo += 1;
	}
	if(row < 14 && col < 14)
	{
		for(int i = row + 1,int j = col + 1;i != 15 && j != 15 && m_board[i][j] == iYanSe;i ++,j ++)
			iZuo += 1;
	}


/////////////


	if(row > 0 && col < 14)
	{
		for(int i = row - 1,int j = col + 1;i != -1 && j != 15 && m_board[i][j] == iYanSe;i --,j ++)
			iYou += 1;
	}
	if(row < 14 && col > 0)
	{
		for(int i = row + 1,int j = col - 1;i != 15 && j != 15 && m_board[i][j] == iYanSe;i ++,j --)
			iYou += 1;
	}
//////////////////////
	if(iHeng > 4||iShu > 4||iZuo > 4||iYou > 4)
	{
		iHeng = 1;iShu = 1;iZuo = 1;iYou = 1;
		return TRUE;
	}
	else 
	{
		iHeng = 1;iShu = 1;iZuo = 1;iYou = 1;
		return FALSE;
	}
}
