// Submarine.h: interface for the CSubmarine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBMARINE_H__B2FC888F_3AA9_4979_AB70_676ABA4881C7__INCLUDED_)
#define AFX_SUBMARINE_H__B2FC888F_3AA9_4979_AB70_676ABA4881C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MyObject.h"

#define SUBMARINE_WIDTH		63
#define SUBMARINE_HEIGHT	19

class CSubmarine : public CMyObject
{
public:
	static void DeleteImage();
	static BOOL LoadImage();
	
	CRect GetRect() { return CRect(m_ptPos, CSize(SUBMARINE_WIDTH, SUBMARINE_HEIGHT)); }
	int GetType() { return m_nType; }
	bool Draw(CDC* pDC, bool bPause);
	void SetFireFlag() { m_bFired = false; }
	bool GetFireFlag() { return m_bFired; }
	CSubmarine(bool bDir, int nVert, int nType, int nSpeed);
	virtual ~CSubmarine();

private:
	int m_nType;
	bool m_bDirect;
	int m_nSpeed;
	int m_nFireWait;
	bool m_bFired;

	static CImageList m_Images;
};


#endif // !defined(AFX_SUBMARINE_H__B2FC888F_3AA9_4979_AB70_676ABA4881C7__INCLUDED_)
