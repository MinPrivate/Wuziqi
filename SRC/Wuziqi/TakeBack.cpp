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
//   �������м��� huiqi ���Ա		

//   ���� ����λͼ     CDC		m_dchuiqi;  CBitmap		 m_bmphuiqi;

//   ��bushu()��¼�������huiQiCiShu(Ҳ���ܵĴ���)  ���ݶ�Ϊ3��

//ʹ�û���huiQi()ǰ�������ж��Ƿ����isHuiQi()

//��display()���ؿ��Ի���Ĵ���

//	��������û���������̵�С���ָ�����  ��¼������ ��row ��col �滻	
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//���캯��  ��ʼ������
CTakeBack::CTakeBack()
{
	bushu = 0;                      //��δ������

	heiCiShu = 0;                 //����������Ϊ0
	baiCiShu = 0;                 //����������Ϊ0

	numZUOBIAO = 0;
	
	m_bmpHuiQi.DeleteObject();                    //��ʼ������
	m_dcHuiQi.DeleteDC();
}

/////////////////////////////////////////�����������
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

///////////////////////////////////////////�����������岽��
		ZUOBIAO *swap;
		swap = bushu;
		for(int i = 0;i < (2*MAXHUIQI - heiCiShu - baiCiShu)*2;i++)
		{
			swap = swap->next;
		}
		swap = 0;
	}
}
//ִ�л������
void CTakeBack::huiQi(int color)
{
	if(bushu==NULL)
		::AfxMessageBox("��ǰ���ӿɻ�!");
	else
	{
		for(int i = 0;i <= 2 && bushu!=NULL;i ++)
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//��ͼ  ����
			//��֪����bushu.row  bushu.col
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
	
	//////////////////////////////////��¼һ�ζ�Ӧ��ɫ���������
		if(color == BAI)
			baiCiShu += 1;
		else
			heiCiShu += 1;
	}
}

//�ж��Ƿ���Ի���
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
/////////////////////////////��ʾ�ɻ������
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
