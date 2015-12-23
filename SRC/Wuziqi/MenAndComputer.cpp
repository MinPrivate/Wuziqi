// MenAndComputer.cpp: implementation of the CMenAndComputer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wuziqi.h"
#include "MenAndComputer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenAndComputer::CMenAndComputer()
{

}

CMenAndComputer::~CMenAndComputer()
{

}
void CMenAndComputer::InitMenAndComputer()
{
	int i,j,k,l;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			Computer[i][j]=0;
	for(k=0;k<15;k++)
		for(l=0;l<15;l++)
			Player[k][l]=0;
}

int CMenAndComputer::Scan(int x,int y,int m_board[][15],int color)
{
	int i,j,k,l;                                                 //辅助变量
	int nOrder;                                                  //记录落棋子点的重要新
	int nXStart,nXEnd;                                           //X轴起始
	int nYStart,nYEnd;                                           //Y轴起始
	int nXYStart,nXYEnd;                                         //斜上
	int nYXStart,nYXEnd;                                         //斜下

	int nXStartAdd,nYStartAdd,nXYStartAdd,nYXStartAdd;           //起额外棋子数
	int nXEndAdd,nYEndAdd,nXYEndAdd,nYXEndAdd;                   //始额外棋子数

	bool bXStartEmpty,bXEndEmpty,bXStartEmpty1,bXEndEmpty1;      //记录棋子左右空位
	bool bYStartEmpty,bYEndEmpty,bYStartEmpty1,bYEndEmpty1;      //记录棋子左右空位
	bool bXYStartEmpty,bXYEndEmpty,bXYStartEmpty1,bXYEndEmpty1;  //记录棋子左右空位
	bool bYXStartEmpty,bYXEndEmpty,bYXStartEmpty1,bYXEndEmpty1;  //记录棋子左右空位

	////棋子最初放置位置
	nXStart=nXEnd=x;
	nYStart=nYEnd=y;
	nXYStart=nXYEnd=x;
	nYXStart=nYXEnd=x;

	///////初始化
	nXStartAdd=nYStartAdd=nXYStartAdd=nYXStartAdd=0;
	nXEndAdd=nYEndAdd=nXYEndAdd=nYXEndAdd=0;

	bXStartEmpty=bXEndEmpty=bXStartEmpty1=bXEndEmpty1=false;
	bYStartEmpty=bYEndEmpty=bYStartEmpty1=bYEndEmpty1=false;
	bXYStartEmpty=bXYEndEmpty=bXYStartEmpty1=bXYEndEmpty1=false;
	bYXStartEmpty=bYXEndEmpty=bYXStartEmpty1=bYXEndEmpty1=false;
	//从下棋位置向左扫描
	for(i=x-1;i>=0;i--)
	{
		//<---------<---------
		if(m_board[i][y]==color)                  //有棋子
			nXStart=i;
		else if(m_board[i][y]==0)
		{
			bXStartEmpty=true;
			for(j=i-1;j>=0;j--)
			{
				//<-----<------
				if(m_board[j][y]==color)
					nXStartAdd=i-j;
				else if(m_board[j][y]==0)
				{
					bXStartEmpty1=true;
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}
	///////////从下棋位置向右扫描
	for(i=x+1;i<15;i++)
	{
		/////---->----->
		if(m_board[i][y]==color)
			nXEnd=i;
		else if(m_board[i][y]==0)
		{
			bXEndEmpty=true;
			for(j=i+1;j<15;j++)
			{
				//------>----->
				if(m_board[j][y]==color)
					nXEndAdd=j-i;
				else if(m_board[j][y]==0)
				{
					bXEndEmpty1=true;
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}
	/////从下棋位置向上扫描
	for(i=y-1;i>=0;i--)
	{
		/// ^|^
		if(m_board[x][i]==color)
			nYStart=i;
		else if(m_board[x][i]==0)
		{
			bYStartEmpty=true;
			for(j=i-1;j>=0;j--)
			{
				////  ^|^
				if(m_board[x][j]==color)
					nYStartAdd=i-j;
				else if(m_board[x][j]==0)
				{
					bYStartEmpty1=true;
					break;
				}
				else 
					break;
			}
			break;
		}
		else
			break;
	}
	////////////从下棋位置向下扫描
	for(i=y+1;i<15;i++)
	{
		////  v|v
		if(m_board[x][i]==color)
			nYEnd=i;
		else if(m_board[x][i]==0)
		{
			bYEndEmpty=true;
			for(j=i+1;j<15;j++)
			{
				////  v|v
				if(m_board[x][j]==color)
					nYEndAdd=j-i;
				else if(m_board[x][j]==0)
				{
					bYEndEmpty1=true;
					break;
				}
				else 
					break;
			}
			break;
		}
		else
			break;
	}
	//////从下棋位置向左下扫描
	//            ---
	//		---
	//	-<--
	for(i=x-1,j=y+1;i>=0 && j<15;i--,j++)
	{
		if(m_board[i][j]==color)
			nXYStart=i;
		else if(m_board[i][j]==0)
		{
			bXYStartEmpty=true;
			for(k=i-1,l=j+1;k>=0  && l<15;k--,l++)
			{
				if(m_board[k][l]==color)
					nXYStartAdd=i-k;
				else if(m_board[k][l]==0)
				{
					bXYStartEmpty1=true;
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}
	////从下棋位置向右上扫描
	// /          ----->-
	//		---
	//-------
	for(i=x+1,j=y-1;i<15 && j>=0;i++,j--)
	{
		if(m_board[i][j]==color)
			nXYEnd=i;
		else if(m_board[i][j]==0)
		{
			bXYEndEmpty=true;
			for(k=i+1,l=j-1;k<15 && l>=0;k++,l--)
			{
				if(m_board[k][l]==color)
					nXYEndAdd=k-i;
				else if(m_board[k][l]==0)
				{
					bXYEndEmpty1=true;
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}
	///////////从下棋位置向左上扫描
	//-<---
	//	---
	//	   ---
	for(i=x-1,j=y-1;i>=0 && j>=0;i--,j--)
	{
		if(m_board[i][j]==color)
			nYXStart=i;
		else if(m_board[i][j]==0)
		{
			bYXStartEmpty=true;
			for(k=i-1,l=j-1;k>=0 && l>=0;k--,l--)
			{
				if(m_board[k][l]==color)
					nYXStartAdd=i-k;
				else if(m_board[k][l]==0)
				{
					bYXStartEmpty1=true;
					break;
				}
				else 
					break;
			}
			break;
		}
		else
			break;
	}
	//////////从下棋位置向右下扫描
	///-----
	//	----
	//		---->-
	for(i=x+1,j=y+1;i<15 && j<15;i++,j++)
	{
		if(m_board[i][j]==color)
			nYXEnd=i;
		else if(m_board[i][j]==0)
		{
			bYXEndEmpty=true;
			for(k=i+1,l=j+1;k<15 && l<15;k++,l++)
			{
				if(m_board[k][l]==color)
					nYXEndAdd=k-i;
				else if(m_board[k][l]==0)
				{
					bYXEndEmpty1=true;
					break;
				}
				else
					break;
			}
			break;
		}
		else
			break;
	}

	///////连珠个数
	int nXnum = nXEnd-nXStart+1;
	int nYnum = nYEnd-nYStart+1;
	int nXYnum = nXYEnd-nXYStart+1;
	int nYXnum = nYXEnd-nYXStart+1;

	////////////判断相连棋子类型
	//活4
	bool bXh4 =((nXnum==4)  && (bXStartEmpty && bXEndEmpty));
	bool bYh4 =((nYnum==4)  && (bYStartEmpty && bYEndEmpty));
	bool bXYh4=((nXYnum==4) && (bXYStartEmpty && bXYEndEmpty));
	bool bYXh4=((nYXnum==4) && (bYXStartEmpty && bYXEndEmpty));
	//死4
	bool bXs4 =((nXnum==4)  && (bXStartEmpty || bXEndEmpty));
	bool bYs4 =((nYnum==4)  && (bYStartEmpty || bYEndEmpty));
	bool bXYs4=((nXYnum==4) && (bXYStartEmpty || bXYEndEmpty));
	bool bYXs4=((nYXnum==4) && (bYXStartEmpty || bYXEndEmpty));
	//活3
	bool bXh3 =((nXnum==3)  && (bXStartEmpty && bXEndEmpty));
	bool bYh3 =((nYnum==3)  && (bYStartEmpty && bYEndEmpty));
	bool bXYh3=((nXYnum==3) && (bXYStartEmpty && bXYEndEmpty));
	bool bYXh3=((nYXnum==3) && (bYXStartEmpty && bYXEndEmpty));
	//死3
	bool bXs3 =((nXnum==3)  && (bXStartEmpty || bXEndEmpty));
	bool bYs3 =((nYnum==3)  && (bYStartEmpty || bYEndEmpty));
	bool bXYs3=((nXYnum==3) && (bXYStartEmpty || bXYEndEmpty));
	bool bYXs3=((nYXnum==3) && (bYXStartEmpty || bYXEndEmpty));
	//活2
	bool bXh2 =((nXnum==2)  && (bXStartEmpty && bXEndEmpty));
	bool bYh2 =((nYnum==2)  && (bYStartEmpty && bYEndEmpty));
	bool bXYh2=((nXYnum==2) && (bXYStartEmpty && bXYEndEmpty));
	bool bYXh2=((nYXnum==2) && (bYXStartEmpty && bYXEndEmpty));
	//死2
	bool bXs2 =((nXnum==2)  && (bXStartEmpty || bXEndEmpty));
	bool bYs2 =((nYnum==2)  && (bYStartEmpty || bYEndEmpty));
	bool bXYs2=((nXYnum==2) && (bXYStartEmpty || bXYEndEmpty));
	bool bYXs2=((nYXnum==2) && (bYXStartEmpty || bYXEndEmpty));
	//活1
	bool bXh1 =((nXnum==1)  && (bXStartEmpty && bXEndEmpty));
	bool bYh1 =((nYnum==1)  && (bYStartEmpty && bYEndEmpty));
	bool bXYh1=((nXYnum==1) && (bXYStartEmpty && bXYEndEmpty));
	bool bYXh1=((nYXnum==1) && (bYXStartEmpty && bYXEndEmpty));

	int nXAdd,nYAdd,nXYAdd,nYXAdd;   //记录已计算外的最多一侧连珠数
	//初始为0
	nXAdd=nYAdd=nXYAdd=nYXAdd=0;

	if(nXEndAdd>=nXStartAdd)
	{
		nXAdd     = nXEndAdd;
		bXEndEmpty= bXEndEmpty1;
	}
	else
	{
		nXAdd        = nXStartAdd;
		bXStartEmpty = bXStartEmpty1;
	}
	if(nYEndAdd>=nYStartAdd)
	{
		nYAdd     = nYEndAdd;
		bYEndEmpty= bYEndEmpty1;
	}
	else
	{
		nYAdd        = nYStartAdd;
		bYStartEmpty = bYStartEmpty1;
	}
	if(nXYEndAdd>=nXYStartAdd)
	{
		nXYAdd     = nXYEndAdd;
		bXYEndEmpty= bXYEndEmpty1;
	}
	else
	{
		nXYAdd        = nXYStartAdd;
		bXYStartEmpty = bXYStartEmpty1;
	}
	if(nYXEndAdd>=nYXStartAdd)
	{
		nYXAdd     = nYXEndAdd;
		bYXEndEmpty= bYXEndEmpty1;
	}
	else
	{
		nYXAdd        = nYXStartAdd;
		bYXStartEmpty = bYXStartEmpty1;
	}
	///////////判断间隔棋子棋型
	//间隔成活4
	bool bjXh4  = ((nXnum+nXAdd>=4)   && (bXStartEmpty  && bXEndEmpty));
	bool bjYh4  = ((nYnum+nYAdd>=4)   && (bYStartEmpty  && bYEndEmpty));
	bool bjXYh4 = ((nXYnum+nXYAdd>=4) && (bXYStartEmpty && bXYEndEmpty));
	bool bjYXh4 = ((nYXnum+nYXAdd>=4) && (bYXStartEmpty && bYXEndEmpty));
	//间隔成死4
	bool bjXs4  = ((nXnum+nXAdd>=4)   && (bXStartEmpty  || bXEndEmpty));
	bool bjYs4  = ((nYnum+nYAdd>=4)   && (bYStartEmpty  || bYEndEmpty));
	bool bjXYs4 = ((nXYnum+nXYAdd>=4) && (bXYStartEmpty || bXYEndEmpty));
	bool bjYXs4 = ((nYXnum+nYXAdd>=4) && (bYXStartEmpty || bYXEndEmpty));
	//间隔成活3
	bool bjXh3  = ((nXnum+nXAdd==3)   && (bXStartEmpty  && bXEndEmpty));
	bool bjYh3  = ((nYnum+nYAdd==3)   && (bYStartEmpty  && bYEndEmpty));
	bool bjXYh3 = ((nXYnum+nXYAdd==3) && (bXYStartEmpty && bXYEndEmpty));
	bool bjYXh3 = ((nYXnum+nYXAdd==3) && (bYXStartEmpty && bYXEndEmpty));


//////为各种棋型 分类

	//成 5
	if(nXnum>=5 || nYnum>=5 || nXYnum>=5 || nYXnum>=5)
	{
		nOrder=0;
	}
	//活 4
	else if(bXh4 || bYh4 || bXYh4 ||bYXh4)
	{
		nOrder=1;
	}
	//成双死 4
	else if((bXs4 && (bYs4 || bXYs4 || bYXs4 || bjYs4 || bjXYs4 || bjYXs4)) ||
			(bYs4 && (bXs4 || bXYs4 || bYXs4 || bjXs4 || bjXYs4 || bjYXs4)) ||
			(bXYs4 && (bYs4 || bXs4 || bYXs4 || bjYs4 || bjXs4 || bjYXs4))  ||
			(bYXs4 && (bXs4 || bYs4 || bXYs4 || bjXs4 || bjYs4 || bjXYs4))  ||
			(bjXs4 && (bYs4 || bXYs4 || bYXs4 || bjYs4 || bjXYs4 || bjYXs4)) ||
			(bjYs4 && (bXs4 || bXYs4 || bYXs4 || bjXs4 || bjXYs4 || bjYXs4)) ||
			(bjXYs4 && (bXs4 || bYs4 || bYXs4 || bjXs4 || bjYs4 || bjYXs4))  ||
			(bjYXs4 && (bXs4 || bYs4 || bXYs4 || bjXs4 || bjYs4 || bjXYs4) ))
	{
		nOrder=2;
	}
	//死 4 活 3
	else if((bXs4 && (bYh3 || bXYh3 || bYXh3 || bjYh3 || bjXYh3 || bjYXh3)) ||
			(bYs4 && (bXh3 || bXYh3 || bYXh3 || bjXh3 || bjXYh3 || bjYXh3)) ||
			(bXYs4 && (bYh3 || bXh3 || bYXh3 || bjYh3 || bjXh3 || bjYXh3)) ||
			(bYXs4 && (bYh3 || bXYh3 || bXh3 || bjYh3 || bjXYh3 || bjXh3)) ||

			(bjXs4 && (bYh3 || bXYh3 || bYXh3 || bjYh3 || bjXYh3 || bjYXh3)) ||
			(bjYs4 && (bXh3 || bXYh3 || bYXh3 || bjXh3 || bjXYh3 || bjYXh3)) ||
			(bjXYs4 && (bYh3 || bXh3 || bYXh3 || bjYh3 || bjXh3 || bjYXh3)) ||
			(bjYXs4 && (bYh3 || bXYh3 || bXh3 || bjYh3 || bjXYh3 || bjXh3)))
	{
		nOrder=3;
	}
	//成双活 3
	else if((bXh3 && (bYh3|| bXYh3 || bYXh3 || bjYh3 || bjXYh3 || bjYXh3)) ||
			(bYh3 && (bXh3 || bXYh3 || bYXh3 || bjXh3 || bjXYh3 || bjYXh3)) ||
			(bXYh3 && (bYh3 || bXh3 || bYXh3 || bjYh3 || bjXh3 || bjYXh3))  ||
			(bYXh3 && (bXh3 || bYh3 || bXYh3 || bjXh3 || bjYh3 || bjXYh3))  ||
			(bjXh3 && (bYh3 || bXYh3 || bYXh3 || bjYh3 || bjXYh3 || bjYXh3)) ||
			(bjYh3 && (bXh3 || bXYh3 || bYXh3 || bjXh3 || bjXYh3 || bjYXh3)) ||
			(bjXYh3 && (bXh3 || bYh3 || bYXh3 || bjXh3 || bjYh3 || bjYXh3))  ||
			(bjYXh3 && (bXh3 || bYh3 || bXYh3 || bjXh3 || bjYh3 || bjXYh3) ))
	{
		nOrder=4;
	}
	//死 4 活 2
	else if((bXYs4 && (bYXh2 || bYh2 || bXh2)) ||
			(bYXs4 && (bXYh2 || bYh2 || bXh2)) ||
			(bXs4  && (bXYh2 || bYXh2 || bYh2)) ||
			(bYs4  && (bXYh2 || bYXh2 || bXh2)))
	{
		nOrder=5;
	}
	//死 4 死 3
	else if((bXYs4 && (bYXs3 || bYs3 || bXs3)) ||
			(bYXs4 && (bXYs3 || bYs3 || bXs3)) ||
			(bXs4 && (bXYs3 || bYXs3 || bYs3)) ||
			(bYs4 && (bXYs3 || bYXs3 || bXs3)))
	{
		nOrder=6;
	}
	////死 4 活 1
	else if((bXYs4 && (bYXh1 || bYh1 || bXh1)) ||
			(bYXs4 && (bXYh1 || bYh1 || bXh1)) ||
			(bXs4 && (bXYh1 || bYXh1 || bYh1)) ||
			(bYs4 && (bXYh1 || bYXh1 || bXh1)))
	{
		nOrder=7;
	}
	////死 4 活 2 
	else if((bXYs4 && (bYXs2 || bYs2 || bXs2)) ||
			(bYXs4 && (bXYs2 || bYs2 || bXs2)) ||
			(bXs4 && (bXYs2 || bYXs2 || bYs2)) ||
			(bYs4 && (bXYs2 || bYXs2 || bXs2)))
	{
		nOrder=8;
	}
	//死 4
	else if(bXYs4 || bYXs4 || bXs4 ||bYs4)
	{
		nOrder=9;
	}
	//活 3 活 2
	else if((bXYh3 && (bYXh2 || bYh2 || bXh2)) ||
			(bYXh3 && (bXYh2 || bYh2 || bXh2)) ||
			(bXh3 && (bXYh2 || bYXh2 || bYh2)) ||
			(bYh3 && (bXYh2 || bYXh2 || bXh2)))
	{
		nOrder=10;
	}
	///活 3 死 3
	else if((bXYh3 && (bYXs3 || bYs3 || bXs3)) ||
			(bYXh3 && (bXYs3 || bYs3 || bXs3)) ||
			(bXh3 && (bXYs3 || bYXs3 || bYs3)) ||
			(bYh3 && (bXYs3 || bYXs3 || bXs3)))
	{
		nOrder=11;
	}
	//活 3 活 1
	else if((bXYh3 && (bYXh1 || bYh1 || bXh1)) ||
			(bYXh3 && (bXYh1 || bYh1 || bXh1)) ||
			(bXh3 && (bXYh1 || bYXh1 || bYh1)) ||
			(bYh3 && (bXYh1 || bYXh1 || bXh1)))
	{
		nOrder=12;
	}
	//活 3 死 2
	else if((bXYh3 && (bYXs2 || bYs2 || bXs2)) ||
			(bYXh3 && (bXYs2 || bYs2 || bXs2)) ||
			(bXh3 && (bXYs2 || bYXs2 || bYs2)) ||
			(bYh3 && (bXYs2 || bYXs2 || bXs2)))
	{
		nOrder=13;
	}
	//活 3
	else if(bXYh3 || bYXh3 || bXh3 || bYh3)
	{
		nOrder=14;
	}
	//双活 2
	else if((bXYh2 && (bYXh2 || bYh2 || bXh2)) ||
			(bYXh2 && (bXYh2 || bYh2 || bXh2)) ||
			(bXh2 && (bXYh2 || bYXh2 || bYh2)) ||
			(bYh2 && (bXYh2 || bYXh2 || bXh2)))
	{
		nOrder=25;
	}
	//活 2 
	else if(bXYh2 || bYXh2 || bXh2 || bYh2)
	{
		nOrder=16;
	}
	//死 3 
	else if(bXYs3 || bYXs3 || bXs3 || bYs3)
	{
		nOrder=17;
	}
	//死 2 
	else if(bXYs2 ||bYXs2 || bXs2 |bYs2)
	{
		nOrder=18;
	}
	//活 1 
	else if(bXYh1 || bYXh1 || bXh1 || bYh1)
	{
		nOrder=19;
	}
	else
		nOrder=20;
	if(nOrder>15)
		if((m_board[x][y-1]==0 || m_board[x][y-1]==color) &&
			(m_board[x+1][y]==0 || m_board[x+1][y]==color) &&
			(m_board[x][y+1]==0 || m_board[x][y+1]==color) &&
			(m_board[x-1][y]==0 || m_board[x-1][y]==color) &&
			((x+2<15 && y-2>=0 && (m_board[x+2][y-2]==0 || m_board[x+2][y-2]==color) &&
			m_board[x][y-2]==color && m_board[x+1][y-1]==color && m_board[x+2][y]==color) ||
			(x+2<15 && y+2<15 && (m_board[x+2][y+2]==0 || m_board[x+2][y+2]==color) &&
			m_board[x][y+2]==color && m_board[x+1][y+1]==color && m_board[x+2][y]==color) ||
			(x-2>=0 && y+2<15 && (m_board[x-2][y+2]==0 || m_board[x-2][y+2]==color) &&
			m_board[x][y+2]==color && m_board[x-1][y+1]==color && m_board[x-2][y]==color) ||
			(x-2>=0 && y-2>=0 && (m_board[x-2][y-2]==0 || m_board[x-2][y-2]==color) &&
			m_board[x][y-2]==color && m_board[x-1][y-1]==color && m_board[x-2][y]==color)))

			nOrder=15;

		return nOrder;
}
	/////为各种棋型 分类
	//成 5     order=0;~  //活 4      order=1;~  //成双死 4  order=2;~  //死 4 活 3   order=3;~ 
	//成双活 3 order=4;~  //死 4 活 2 order=5;  //死 4 死 3 order=6;  ////死 4 活 1 order=7;
	//死 4 死2 order=8;  //死 4      order=9;  //活 3 活 2 order=10; ///活 3 死 3  order=11;
	//活 3 活1 order=12; //活 3 死 2 order=13; //活 3      order=14; //双活 2      order=25;
	//活 2     order=16; //死 3      order=17; //死 2      order=18; //活 1        order=19;

void CMenAndComputer::ScoreComputer(int m_board[][15],int color)
{
	int i,j,order;
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(m_board[i][j]==0)
			{
				order=Scan(i,j,m_board,color);
				if(order==0)
					Computer[i][j]=1000;                      //成 5
				else if(order==1 || order==2 || order==3)
					Computer[i][j]=900;                       //活 4 双死 4 死 4 活 3
				else if(order==4)
					Computer[i][j]=800;                       //双活 3
				else if(order==5)
					Computer[i][j]=700;                       //死 4 活 2
				else if(order==6)
					Computer[i][j]=600;                       //死 4 死 3
				else if(order==7)
					Computer[i][j]=500;                       //死 4 活 1
				else if(order==8)
					Computer[i][j]=400;                       //死 4 死 2
				else if(order==9)
					Computer[i][j]=300;                       //死 4 
				else if(order==10)
					Computer[i][j]=200;                       //活 3 活 2
				else if(order==11)
					Computer[i][j]=100;                       //活 3 死 3
				else if(order==12)
					Computer[i][j]=90;                        //活 3 活 1
				else if(order==13)
					Computer[i][j]=80;                        //活 3 死 2
				else if(order==14)
					Computer[i][j]=70;                        //活 3
				else if(order==25)
					Computer[i][j]=60;                        //双活 2
				else if(order==16)
					Computer[i][j]=50;                        //活 2
				else if(order==17)
					Computer[i][j]=40;                        //死 3
				else if(order==18)
					Computer[i][j]=30;                        //死 2
				else if(order==19)
					Computer[i][j]=20;                        //活 1
				//Computer[i][j]+=100;
			}
		}
	}
}

void CMenAndComputer::ScorePlayer(int m_board[][15], int color)
{
	int i,j,order;
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(m_board[i][j]==0)
			{
				order=Scan(i,j,m_board,color);
				if(order==0)
					Player[i][j]=1000;                      //成 5
				else if(order==1 || order==2 || order==3)
					Player[i][j]=900;                       //活 4 双死 4 死 4 活 3
				else if(order==4)
					Player[i][j]=800;                       //双活 3
				else if(order==5)
					Player[i][j]=700;                       //死 4 活 2
				else if(order==6)
					Player[i][j]=600;                       //死 4 死 3
				else if(order==7)
					Player[i][j]=500;                       //死 4 活 1
				else if(order==8)
					Player[i][j]=400;                       //死 4 死 2
				else if(order==9)
					Player[i][j]=300;                       //死 4 
				else if(order==10)
					Player[i][j]=200;                       //活 3 活 2
				else if(order==11)
					Player[i][j]=100;                       //活 3 死 3
				else if(order==12)
					Player[i][j]=90;                        //活 3 活 1
				else if(order==13)
					Player[i][j]=80;                        //活 3 死 2
				else if(order==14)
					Player[i][j]=70;                        //活 3
				else if(order==25)
					Player[i][j]=60;                        //双活 2
				else if(order==16)
					Player[i][j]=50;                        //活 2
				else if(order==17)
					Player[i][j]=40;                        //死 3
				else if(order==18)
					Player[i][j]=30;                        //死 2
				else if(order==19)
					Player[i][j]=20;                        //活 1

				//Player[i][j]+=5;
			}
		}
	}
}

CPoint CMenAndComputer::MaxPoint()
{
	CPoint maxpt1,maxpt2;
	int i,j,k,l,max1,max2;

	maxpt1.x=0;
	maxpt1.y=0;
	maxpt2.x=0;
	maxpt2.y=0;
	max1=Computer[0][0];
	max2=Player[0][0];

	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			if(Computer[i][j]>=max1)
			{
				max1=Computer[i][j];
				maxpt1.x=i;
				maxpt1.y=j;
			}
	for(k=0;k<15;k++)
		for(l=0;l<15;l++)
			if(Player[k][l]>=max2)
			{
				max2=Player[k][l];
				maxpt2.x=k;
				maxpt2.y=l;
			}
	if(max1>=max2)
		return maxpt1;
	else
		return maxpt2;
}
