// MyObject.h: interface for the CMyObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYOBJECT_H__B694AB26_64B9_4EA8_ACFC_3DCEFA777D55__INCLUDED_)
#define AFX_MYOBJECT_H__B694AB26_64B9_4EA8_ACFC_3DCEFA777D55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyObject : public CObject  
{
public:
	CPoint GetPos()		{ return m_ptPos;	}
	virtual CRect GetRect()=0;
	virtual bool Draw(CDC* pDC, bool bPause)=0;
	bool IsSubmarine()	{ return m_bSubmarine; }
	CMyObject();
	virtual ~CMyObject();

protected:
	CPoint m_ptPos;
	bool m_bSubmarine;

};


#endif // !defined(AFX_MYOBJECT_H__B694AB26_64B9_4EA8_ACFC_3DCEFA777D55__INCLUDED_)
