// Win.h: interface for the CWin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIN_H__081FA238_C0D6_4EC2_B49C_6927C1DA1956__INCLUDED_)
#define AFX_WIN_H__081FA238_C0D6_4EC2_B49C_6927C1DA1956__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWin  
{
public:
	CWin();
	virtual ~CWin();
public:
	bool ShengFu(int row,int col,int m_board[][15],int iYanSe);

private:
	int iHeng;
	int iShu ;
	int iZuo ;
	int iYou ;

};

#endif // !defined(AFX_WIN_H__081FA238_C0D6_4EC2_B49C_6927C1DA1956__INCLUDED_)
