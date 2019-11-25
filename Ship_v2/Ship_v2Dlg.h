// Ship_v2Dlg.h : header file
//

#if !defined(AFX_SHIP_V2DLG_H__AA188C17_5DE6_4BA3_8B7A_C51A0112AB3F__INCLUDED_)
#define AFX_SHIP_V2DLG_H__AA188C17_5DE6_4BA3_8B7A_C51A0112AB3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShip_v2Dlg dialog

class CShip_v2Dlg : public CDialog
{
// Construction
public:
	CShip_v2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShip_v2Dlg)
	enum { IDD = IDD_SHIP_V2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShip_v2Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShip_v2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//	0: MyShip
	//	1: Enemy Ship
	//	2: Bomb
	//	3: Enemy weapons
	//	4: explosion
	//	5: score
	CObList m_Objects[6];


	CBitmap m_VirtualBitmap;
	CDC		m_VirtualDC;

	bool m_bGamePause;

private:
	int random(int __num) { return(int)(((long)rand()*__num)/(RAND_MAX+1)); }
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHIP_V2DLG_H__AA188C17_5DE6_4BA3_8B7A_C51A0112AB3F__INCLUDED_)
