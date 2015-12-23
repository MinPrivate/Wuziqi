// MenAndComputer.h: interface for the CMenAndComputer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENANDCOMPUTER_H__059F39FC_B205_4D0E_A4BF_ECCD893013F1__INCLUDED_)
#define AFX_MENANDCOMPUTER_H__059F39FC_B205_4D0E_A4BF_ECCD893013F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMenAndComputer  
{
public:
	void InitMenAndComputer();
	CPoint MaxPoint();
	void ScorePlayer(int m_board[][15],int color);
	void ScoreComputer(int m_board[][15],int color);
	int  Scan(int x,int y,int m_board[][15],int color);
	CMenAndComputer();
	virtual ~CMenAndComputer();

private:
	//记录打分情况数组
	int Computer[15][15];
	int Player[15][15];

	/*/活4
	bool bXh4 ,bYh4 ,bXYh4,bYXh4;
	//死4
	bool bXs4 ,bYs4 ,bXYs4, bYXs4;
	//活3
	bool bXh3 ,bYh3 ,bXYh3,bYXh3;
	//死3
	bool bXs3 , bYs3 ,bXYs3,bYXs3;
	//活2
	bool bXh2 , bYh2 ,bXYh2,bYXh2;
	//死2
	bool bXs2 ,bYs2 ,bXYs2,bYXs2;
	//活1
	bool bXh1 , bYh1 ,bXYh1, bYXh1;

	///////////判断间隔棋子棋型
	//间隔成活4
	bool bjXh4  ,bjYh4  ,bjXYh4 ,bjYXh4 ;
	//间隔成死4
	bool bjXs4  ,bjYs4  ,bjXYs4 ,bjYXs4 ;
	//间隔成活3
	bool bjXh3  ,bjYh3  ,bjXYh3 ,bjYXh3 ;
	*/

};

#endif // !defined(AFX_MENANDCOMPUTER_H__059F39FC_B205_4D0E_A4BF_ECCD893013F1__INCLUDED_)
