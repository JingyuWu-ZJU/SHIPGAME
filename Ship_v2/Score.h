// Score.h: interface for the CScore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCORE_H__E9F82DB8_A178_4B78_9211_62F808DBF7AB__INCLUDED_)
#define AFX_SCORE_H__E9F82DB8_A178_4B78_9211_62F808DBF7AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyObject.h"

class CScore : public CMyObject  
{
public:
	bool Draw(CDC* pDC, bool bPause);
	CScore(CPoint ptPos,int nMuti, int nScore, DWORD nColor);
	CRect GetRect()	{ return NULL; }
	static int GetTotalScore()	{ return m_nTotalScore; }
	virtual ~CScore();

private:
	COLORREF m_nColor;
	int m_nProcess;
	int m_nScore;
	int m_nMuti;
	static int m_nTotalScore;
};

#endif // !defined(AFX_SCORE_H__E9F82DB8_A178_4B78_9211_62F808DBF7AB__INCLUDED_)
