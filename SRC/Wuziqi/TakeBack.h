// TakeBack.h: interface for the CTakeBack class.
//
//////////////////////////////////////////////////////////////////////
//   �������м��� huiqi ���Ա		

//   ���� ����λͼ     CDC		m_dchuiqi;  CBitmap		 m_bmphuiqi;

//   ��bushu(){}��¼�������huiQiCiShu(Ҳ���ܵĴ���)  ���ݶ�Ϊ3��

//ʹ�û���huiQi()ǰ�������ж��Ƿ����isHuiQi()

//��display()���ؿ��Ի���Ĵ���

//	��������û���������̵�С���ָ�����  ��¼������ ��row ��col �滻	
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAKEBACK_H__8839E90C_BEA0_4D50_8A0F_E7C370082697__INCLUDED_)
#define AFX_TAKEBACK_H__8839E90C_BEA0_4D50_8A0F_E7C370082697__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXHUIQI 3     /////////////����Ĵ���
#define BAI 1	                   //����     1
#define HEI 2	                   //����     2

////////////////////////////�����������ӵ��������꣨row,col������
struct ZUOBIAO{
	int row;
	int col;
	ZUOBIAO *next;
};

class CTakeBack  
{
public:
	CTakeBack();                       //���캯��
	virtual ~CTakeBack();


/////////////////////////////////////////���������Ϣ
	void jiaRu(ZUOBIAO *mes);

/////////////////////////////////////////����
	void huiQi(int);

//////////////////////////////////////////�Ƿ���Ի���  �����򷵻�1 
	bool isHuiQi(int color);

////////////////////////////////////////////��ʾ���Ի������
	int display(int color);


private:

	// ���ڴ��豸��λͼ 
	CDC		m_dcHuiQi;
	CBitmap m_bmpHuiQi;

//////////////////////////////////��������
	ZUOBIAO * bushu;

/////////////////////////////////��¼�������
	int baiCiShu;
	int heiCiShu;

////////////////////////////////��������ĳ���
	int numZUOBIAO;

	int m_X;                     //���������
	int m_Y;
};	

#endif // !defined(AFX_TAKEBACK_H__8839E90C_BEA0_4D50_8A0F_E7C370082697__INCLUDED_)
